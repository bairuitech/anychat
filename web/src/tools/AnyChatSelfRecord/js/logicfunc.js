// AnyChat for Web SDK
/**
 *@demoVersion 1.0
 *@editor Z.Yanni
 *@timeByFin 2014.12.18
 *@partByEdit logicfunc.js,anychatevent.js,record.html
 */
/*******************************************************************************
 * 业务逻辑控制 *
 ******************************************************************************/
 
var mDefaultServerAddr = "demo.anychat.cn";		// 默认服务器地址
var mDefaultServerPort = 8906;					// 默认服务器端口号
var mSelfUserId = -1; 							// 本地用户ID
var mTargetUserId = -1;							// 目标用户ID（请求了对方的音视频）
var mUserName="AnyChat"
var mRefreshPluginTimer = -1;					// 检查插件是否安装完成定时器
var change=false,colorTSet=-1;


// 文件传输路径
var lpLocalPathName,picPath;
var control=false;
var recordstart=0;
var timecontrol=1;
var time;

function LogicInit() {
    setTimeout(function () {
		if (navigator.plugins && navigator.plugins.length) {
			window.navigator.plugins.refresh(false);
		}
        // 检查是否安装了插件
        var NEED_ANYCHAT_APILEVEL = "0"; 						// 定义业务层需要的AnyChat
																// API Level
        var errorcode = BRAC_InitSDK(NEED_ANYCHAT_APILEVEL); 	// 初始化插件
        if (errorcode == GV_ERR_SUCCESS) {
			/**
			modifyed by liaobin:2014-12-19
			**/
			BRAC_SetSDKOption(BRAC_SO_SNAPSHOT_TMPDIR,"d:\\ScreenShot");// 视频抓拍文件存储路径
			BRAC_SetSDKOption(BRAC_SO_RECORD_TMPDIR,"d:\\videoRecord");// 视频录制文件存储路径
    		BRAC_SetSDKOption(BRAC_SO_RECORD_FILETYPE,0);// 0 MP4[默认], 1 WMV, 2 FLV, 3 MP3
			BRAC_SetSDKOption(BRAC_SO_ENABLEWEBSERVICE, 1);                // 启动本地Web服务
			if(mRefreshPluginTimer != -1)
				clearInterval(mRefreshPluginTimer); 			// 清除插件安装检测定时器
			GetID("prompt_div").style.display = "none"; 		// 隐藏插件安装提示界面
			ShowLoginDiv(true);
			// 初始化界面元素
			InitInterfaceUI();
        } else { 						// 没有安装插件，或是插件版本太旧，显示插件下载界面
            GetID("prompt_div").style.display = "block";
           // SetDivTop("prompt_div", 300);
            if (errorcode == GV_ERR_PLUGINNOINSTALL)
                GetID("prompt_div_line1").innerHTML = "首次进入需要安装插件，请点击下载按钮进行安装！";
            else if (errorcode == GV_ERR_PLUGINOLDVERSION)
                GetID("prompt_div_line1").innerHTML = "检测到当前插件的版本过低，请下载安装最新版本！";
				
			if(mRefreshPluginTimer == -1) {
				mRefreshPluginTimer = setInterval(function(){ LogicInit(); }, 1000);
			}
		}
    }, 500);
	

}

// 初始化界面元素
function InitInterfaceUI() {

    // 下载插件按钮鼠标划入划出时间
    GetID("prompt_div_btn_load").onmouseover = function () {
        GetID("prompt_div_btn_load").style.backgroundColor = "#ffc200";
    }
    GetID("prompt_div_btn_load").onmouseout = function () {
        GetID("prompt_div_btn_load").style.backgroundColor = "#ff8100";
    }
    // 下载插件界面关闭按钮
    GetID("prompt_div_headline2").onclick = function () {
        document.URL = location.href;
    }

    
  // 登录AnyChat服务器，准备录像
    GetID("loginRoom").onclick = function () {
    	if (GetID("username").value != "") {
			DisplayLoadingDiv(true);
//			GetID("regist-process").style.display="block";
    		var errorcode = BRAC_Connect(GetID("ServerAddr").value, parseInt(GetID("ServerPort").value)); // 连接服务器
            errorcode = BRAC_Login(GetID("username").value, "", 0);
    		BRAC_EnterRoom(3, "", 0);
    	}else{
    		alert("用户名不能为空！");
    		GetID("username").focus();
    	}
    	
    }
	// 拍照
    GetID("ScreenShot").onclick = function () {
    		 
	/**
	modifyed by liaobin:2014-12-19
	**/
			BRAC_SnapShot(-1, 0, 0);
	}
	// 重拍
	GetID("reScreenShot").onclick = function () {
		displayList("AnyChatFileTransDiv,advanceset_iframe,uScreenShot,reScreenShot,enterRecord","none");
		GetID("AnyChatLocalVideoDiv").style.display="block";
    	
		/**
	modifyed by liaobin:2014-12-19
	**/
		BRAC_UserCameraControl(-1, 1); 	// 打开本地视频
        BRAC_UserSpeakControl(-1, 1); 		// 打开本地语音
        // 设置本地视频显示位置
        BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
		GetID("ScreenShot").style.display="block";
	}
	//进入录制
	GetID("enterRecord").onclick = function () {
		
		displayList("AnyChatFileTransDiv,advanceset_iframe,enterRecord,reScreenShot,uScreenShot","none");
		GetID("tip").getElementsByTagName("div")[0].innerHTML="<p>请将人脸正对摄像头，用普</p><p>通话朗读以下内容：</p><p>1.我是张三，自愿申请开户</p><p>2.我已阅读数字证书文件、</p><p>理解合同并接受相关条款</p>";

		GetID("regist-process").className="step2";
		
		
		GetID("AnyChatLocalVideoDiv").style.display="block";
			ApplyVideoConfig(150000,3,320,240,15,3);
		/**
		modifyed by liaobin:2014-12-19
	**/
		BRAC_UserCameraControl(-1, 1); 	// 打开本地视频
        BRAC_UserSpeakControl(-1, 1); 		// 打开本地语音
        // 设置本地视频显示位置
        BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
		
		GetID("recordtime").style.display="block";
		GetID("record_ready").style.display="block";
	}
  // 录制
    GetID("record_ready").onclick = function () {
		/**
		modifyed by liaobin:2014-12-19
	**/
    	// 录制本地音视频
    
    		var tag=BRAC_RECORD_FLAGS_VIDEO+BRAC_RECORD_FLAGS_AUDIO;
    		
    		BRAC_StreamRecordCtrl(-1,control?0:1,tag, 0);
			GetID("record_ready").title =control?"开始录制":"录制中";
		
		if(timecontrol==1){
		time=setInterval(function(){GetID("recordtime").innerHTML="录制时间："+formatSeconds(recordstart);recordstart++;
	},1000);
	timecontrol=0;
	}else if(timecontrol==0){
		clearInterval(time);
		timecontrol=1;
		}
			if(!control){
				colorTSet=setInterval(function() {
					GetID("record_ready").style.background=change?"url('./img/recordon.png') no-repeat":"url('./img/recordoff.png') no-repeat";
					change=!change;
				}, 650);
			}else{
				clearInterval(colorTSet);
				recordstart=0;
				GetID("recordtime").innerHTML="录制停止：0时0分0秒";
				colorTSet=-1;
				change=false;
			}
			control=!control;
    }
    // 文件传输
    var file1,t1,bTimeSet,t2,file2,y;// 文件，文件进度，计时器标识,子div
    GetID("upload").onclick = function () {
    	var taskInfo1;
    	var taskInfo2;
    	GetID("video_shadow").getElementsByTagName("b")[0].innerHTML="&nbsp;&nbsp;文件上传中,请稍后...&nbsp;&nbsp;";
    	GetID("video_shadow").style.display="block";
    	GetID("uploadCancel").style.display="block";
    	GetID("upload").style.display="none";
    	file1=BRAC_TransFile(0,lpLocalPathName,0,0,0);
    	file2=BRAC_TransFile(0,picPath,0,0,0);
    	
    	bTimeSet=setInterval(function() {
    		taskInfo1= BRAC_QueryTransTaskInfo(mSelfUserId, file1, BRAC_TRANSTASK_PROGRESS);
    		taskInfo2=BRAC_QueryTransTaskInfo(mSelfUserId, file2, BRAC_TRANSTASK_PROGRESS);
    		
		    GetID("rateOfProgress").style.width = 10+370 * taskInfo1 / 100 + "px";
				GetID("rateOfProgress2").style.width = 10+370 * taskInfo2 / 100 + "px";
					
				GetID("rate").innerHTML= taskInfo1+"%";
				GetID("rate2").innerHTML= taskInfo2+"%";
    		if(taskInfo1==100&&taskInfo2==100){
    			clearInterval(bTimeSet);
						GetID("video_shadow").getElementsByTagName("b")[0].innerHTML="文件成功上传至服务器!请等待审核";
						GetID("regist-process").className="step4";
						displayList("uploadCancel,video_shadow","none");
						displayList("recordTip1,return","block");
    			}
			}, 100);
		}
		   

    
    //上传取消
    GetID("uploadCancel").onclick = function () {
    	BRAC_CancelTransTask(mSelfUserId, file1);
    BRAC_CancelTransTask(mSelfUserId, file2);
    	clearInterval(bTimeSet);
    	displayList("video_shadow,uploadCancel,AnyChatFileTransDiv","none");
    GetID("regist-process").className="step2";
    GetID("rateOfProgress").style.width=10;
    GetID("rate").innerHTML="0%";
    GetID("rateOfProgress2").style.width=10;
    GetID("rate2").innerHTML="0%";
    displayList("AnyChatLocalVideoDiv,backRecord,Recordplay,next","block");
    }
    // 视频播放
    GetID("Recordplay").onclick = function () {
    	
    	displayList("advanceset_iframe,recordmsg,backRecord,Recordplay,next,AnyChatLocalVideoDiv,AnyChatFileTransDiv","none");
    	displayList("personVideo,videotag,return","block");
        //GetID("videotag").innerHTML="<video width=\"600\" height=\"450\" autoplay=\"autoplay\" controls preload><source src=\""+lpLocalPathUrl+"\" type=\"video/mp4\">浏览器不支持视频播放，请尝试更新</video>";
//    	GetID("videotag").getElementsByTagName("video")[0].setAttribute("src", lpLocalPathUrl);
    	
    	//GetID("videotag").innerHTML="<iframe style=\"width:600;height:450;border:0;\" src=\""+lpLocalPathUrl+"\"></iframe>";
    	Mp4Player(lpLocalPathUrl);
    	
    }
 // 返回
    GetID("return").onclick = function () {
    	GetID("videotag").innerHTML="";
//    	GetID("videotag").getElementsByTagName("video")[0].setAttribute("src", "");
    	GetID("regist-process").className="step2";
		
        GetID("rateOfProgress").style.width=10;
        GetID("rate").innerHTML="0%";
GetID("rateOfProgress2").style.width=10;
        GetID("rate2").innerHTML="0%";
        displayList("videotag,return,AnyChatFileTransDiv,recordTip1,upload","none");
        displayList("AnyChatLocalVideoDiv,backRecord,Recordplay,next","block");
    }
 // 下一步
    GetID("next").onclick = function () {
    	displayList("AnyChatLocalVideoDiv,recordmsg,backRecord,Recordplay,next,recordmsg","none");
		GetID("AnyChatFileTransDiv").style.display="block";
    	GetID("AnyChatFileTransDiv").style.background="#B5B2B2";
    	GetID("video_shadow").getElementsByTagName("b")[0].style.backgroundColor="";
    	
    	GetID("video_shadow").getElementsByTagName("b")[0].innerHTML="请点击上传按钮，上传文件";
    	
    	displayList("upload,video_shadow","block");
    	GetID("regist-process").className="step3";
    }
       
    
    // backRecord返回录制
    GetID("backRecord").onclick = function () {
    	GetID("recordtime").innerHTML="录制时间:0时0分0秒";
    	displayList("recordmsg,backRecord,Recordplay,next,recordmsg,advanceset_iframe","none");
    	displayList("tip,record_ready,recordtime","block");
		
    	BRAC_UserCameraControl(mSelfUserId, 1); 	// 打开本地视频
        BRAC_UserSpeakControl(mSelfUserId, 1); 		// 打开本地语音
        BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
       
    }

}

function showPopWindow(divid,showtime)
{
	GetID(divid).style.display="block";
    setTimeout(function(){GetID(divid).style.display="none";},showtime);
}

// 显示等待进度条，提示用户操作正在进行中
function DisplayLoadingDiv(bShow) {
    if (bShow) {
    	displayList("LOADING_GREY_DIV,LOADING_DIV","block");
        var TheWidth = document.body.offsetWidth;
        GetID("LOADING_DIV").style.marginTop = "250px";
        GetID("LOADING_DIV").style.marginLeft = (TheWidth - 130) / 2 + "px";
    }
    else {
    	displayList("LOADING_DIV,LOADING_GREY_DIV","none");
    }
}


// 显示登录界面
function ShowLoginDiv(bShow) {
	if(bShow) {
		displayList("loginTip,login_div","block"); 	// 显示登录界面
		GetID("username").focus();
		GetID("ServerAddr").value = mDefaultServerAddr;
		GetID("ServerPort").value = mDefaultServerPort;
		GetID("username").value= mUserName;
	} else {
		displayList("loginTip,login_div","none"); 	// 显示登录界面
	}
}
// 显示视频录像界面
function ShowVideoRecordDiv(bShow) {
	if(bShow){
		GetID("AnyChatFileTransDiv").style.display="none";
		displayList("regist-process,tip,personVideo,AnyChatLocalVideoDiv","block");
		GetID("record_ready").style.background="url('./img/recordon.png') no-repeat";
	}
	else{
		displayList("regist-process,personVideo,tip,AnyChatFileTransDiv","none");
		GetID("videotag").innerHTML="";
	}
}
		

function GetID(id) {
	if (document.getElementById) {
		return document.getElementById(id);
	} else if (window[id]) {
		return window[id];
	}
	return null;
}

//
function Mp4Player(mp4){
	var embed="<embed src=\"player.swf\" allowfullscreen=\"true\" flashvars=\"controlbar=over&file="+mp4+"&autostart=true\" width=\"600\" height=\"450\"/>";
	//var embed="<embed src=\"ckplayer/ckplayer.swf\" flashvars=\"f="+mp4+"\" quality=\"high\" width=\"600\" height=\"450\" align=\"middle\" allowScriptAccess=\"always\" allowFullscreen=\"true\" type=\"application/x-shockwave-flash\"></embed>"
	GetID("videotag").innerHTML="";
	GetID("videotag").innerHTML=embed;
}
//录制时间设置

function formatSeconds(value) {
   var s = parseInt(value);// 秒
   var min = 0;// 分
   var hour = 0;// 小时
   if(s > 60) {
      min = parseInt(s/60);
      s = parseInt(s%60);
      if(min > 60) {
         hour = parseInt(min/60);
         min = parseInt(min%60);
       }
   }
       var result = ""+parseInt(s)+"秒";
       if(min > 0) {
       result = ""+parseInt(min)+"分"+result;
       }
       if(hour > 0) {
       result = ""+parseInt(hour)+"小时"+result;
       }
       
       tt=""+parseInt(hour)+"小时"+parseInt(min)+"分"+parseInt(s)+"秒";
       
       return tt;
   }

function record_readyBtn(i){
	if(i==0){
		GetID("record_ready").style.background="url('./img/recordoff.png') no-repeat";
	}else{
		GetID("record_ready").style.background="url('./img/recordon.png') no-repeat";
	}
	
}

// 
function Btn(id,i) {
	if(i==0){
		GetID(id).style.color = "#fff";
		GetID(id).style.background="url('./img/video_btn.png') no-repeat right 0";
		}else{
			GetID(id).style.backgroundPosition="0 0";
			GetID(id).style.width="143px";
			GetID(id).style.textAlign="center";
			GetID(id).style.height="43px";
			GetID(id).style.lineHeight="43px";
			GetID(id).style.color="#adabab";
			GetID(id).style.position="relative";
			GetID(id).style.top="3px";
		}
}

function loginBtn(i){
	if(i==0){
		GetID("loginRoom").style.backgroundColor = "#ABCB64";
	}else{
		GetID("loginRoom").style.backgroundColor=  "#7CAF00";
	}
}
/**
modifyed by liaobin:2014-12-19
**/
// 视频参数设置
function ApplyVideoConfig(bitrate,quality,videoWidth,videoHeight,fps,preset) {
	// 设置本地视频编码的码率（如果码率为0，则表示使用质量优先模式）
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL,bitrate);
	// 设置本地视频编码的质量
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,quality);
	// 设置本地视频采集分辨率
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, videoWidth);
    BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, videoHeight);
	// 设置本地视频编码的帧率
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL,fps);
	// 设置本地视频编码的关键帧间隔
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_GOPCTRL, fps*4);
	// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL,preset);
	// 让视频参数生效
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, 1);
}
function displayList(list,type){
	var list=list.split(",");
	for (var i = 0; i < list.length; i++) {
		GetID(list[i]).style.display=type;
	}
}

