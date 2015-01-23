// AnyChat for Web SDK
/**
 *@demoVersion 1.0
 *@editor Z.Yanni
 *@timeByFin 2014.12.18
 *@editTimeByFin 2015.1.20
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
var reocordVideoOverlayTimer;//发起录制后，在视频上面叠加“正在录制”文字
var XPOS=605;
var videoOverlayEffectTimer=0;//视频叠加动态效果定时器
var effectTransparentBgSwitch=false;//透明背景效果功能控制开关
var effectDymcMessageSwitch=false,dynamicFontSize=30,fontColorCtrl=false;//动态文字效果功能控制开关，动态字体大小，蝴蝶关闭标识，字体颜色控制
var effectDymcImageSwitch=false,btfIndex=1,btfCloseTag=0;//动态文字效果功能控制开关，蝴蝶图片显示位置，蝴蝶关闭标识
var constTransparentImg="recordTip.png";
var localHref;//动态图片源路径

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
  	      	// 视频抓拍文件存储路径
			BRAC_SetSDKOption(BRAC_SO_SNAPSHOT_TMPDIR,"d:\\ScreenShot");
			// 视频录制文件存储路径
			BRAC_SetSDKOption(BRAC_SO_RECORD_TMPDIR,"d:\\videoRecord");
			// 设置录制文件格式，0 MP4[默认], 1 WMV, 2 FLV, 3 MP3
			 BRAC_SetSDKOption(BRAC_SO_RECORD_FILETYPE,0);
			// 启动本地Web服务
			BRAC_SetSDKOption(BRAC_SO_ENABLEWEBSERVICE, 1);                
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
	localHref=document.location.href.split("index.html")[0]+"img/";
	localHref=(localHref.indexOf("file:///")!=-1)?localHref.split("file:///")[1]:localHref;

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
    GetID("startEnjoy").onclick = function () {
    	if (GetID("username").value != "") {
			DisplayLoadingDiv(true);
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
		BRAC_SnapShot(-1, 0, 0);
	}
	// 重拍
	GetID("reScreenShot").onclick = function () {
		GetID("effectBtn").style.display = "block";
		//蝴蝶等动画
		videoOverlayEffectTimer=setInterval(videoOverlayEffect,500);
		displayList("AnyChatFileTransDiv,advanceset_iframe,uScreenShot,reScreenShot,enterRecord","none");
		GetID("AnyChatLocalVideoDiv").style.display="block";
    	BRAC_UserCameraControl(-1, 1); 	 // 打开本地视频
        BRAC_UserSpeakControl(-1, 1); 	// 打开本地语音
        // 设置本地视频显示位置
       	BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
		GetID("ScreenShot").style.display="block";
	}
	// 进入录制
	GetID("enterRecord").onclick = function () {
		clearInterval(videoOverlayEffectTimer);
		displayList("AnyChatFileTransDiv,advanceset_iframe,enterRecord,reScreenShot,uScreenShot","none");
		GetID("tip").getElementsByTagName("div")[0].innerHTML="<p>请将人脸正对摄像头，用普</p><p>通话朗读以下内容：</p><p>1.我是张三，自愿申请开户</p><p>2.我已阅读数字证书文件、</p><p>理解合同并接受相关条款</p>";
		GetID("regist-process").className="step2";
		GetID("AnyChatLocalVideoDiv").style.display="block";
		ApplyVideoConfig(150000,3,320,240,15,3);
		BRAC_UserCameraControl(-1, 1); 	// 打开本地视频
        BRAC_UserSpeakControl(-1, 1); 		// 打开本地语音
        // 设置本地视频显示位置
        BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
		setTimeout(function(){
		//视频顶部叠加图片
		setVideoImg(localHref+"constTransparentImg",0,350);
    },300);
		
		GetID("recordtime").style.display="block";
		GetID("record_ready").style.display="block";
	}
  // 录制
    GetID("record_ready").onclick = function () {
    	setVideoImg(localHref+"topTip.png",0,0);
    	// 录制本地音视频
    	var tag=BRAC_RECORD_FLAGS_VIDEO+BRAC_RECORD_FLAGS_AUDIO;
    	BRAC_StreamRecordCtrl(-1,control?0:1,tag, 0);
		GetID("record_ready").title =control?"开始录制":"录制中";
		if(timecontrol==1){
			reocordVideoOverlayTimer=setInterval(function(){GetID("recordtime").innerHTML="录制时间："+formatSeconds(recordstart);recordstart++;
				// 在本地视频上迭加文字
				var messageFont = "<MESSAGE1><VALUE>视频录制中...</VALUE><XPOS>"+XPOS+"</XPOS><YPOS>5</YPOS><FONTCOLOR>#FAFAF9</FONTCOLOR></MESSAGE1>";
				GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, messageFont);
				XPOS-=30;
				if(XPOS<(-135)){
					XPOS=605;
				}
			},1000);
			timecontrol=0;
	
		}else if(timecontrol==0){
			clearInterval(reocordVideoOverlayTimer);
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

    // 上传取消
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
    	Mp4Player(lpLocalPathUrl);
    	
    }
 	// 返回
    GetID("return").onclick = function () {
    	GetID("videotag").innerHTML="";
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
    	XPOS=605;
    	GetID("recordtime").innerHTML="录制时间:0时0分0秒";
    	displayList("recordmsg,backRecord,Recordplay,next,recordmsg,advanceset_iframe","none");
    	displayList("tip,record_ready,recordtime","block");
    	BRAC_UserCameraControl(mSelfUserId, 1); 	// 打开本地视频
        BRAC_UserSpeakControl(mSelfUserId, 1); 		// 打开本地语音
        BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
				GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE1></MESSAGE1>");
		setTimeout(function(){
			setVideoImg(localHref+"constTransparentImg",0,350);
		},300);
    }
    /**
    *动态效果已在anychatevent.js底下用计时器打开
    *通过标识控制字体颜色大小改变(动态文字)，蝴蝶动态效果(动态图片)
    *由videoOverlay()这个函数控制effectDymcImageSwitch,effect3
    */
 // 透明背景效果控制开关
    GetID("effectTransparentBg").onclick = function () {
    	if(effectTransparentBgSwitch){
    		setVideoImg("",0,0);
			GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE2></MESSAGE2>");

    	}else{
    		setTimeout(function(){setVideoImg(localHref+"screenShotTip.png",0,0);
    		// 在本地视频上迭加文字
    		var szOverlayMessage2 = "<MESSAGE2><VALUE>请离我近点，再近点，使劲戳下面拍照按钮，让我一睹您的尊容~</VALUE><XPOS>13</XPOS><YPOS>385</YPOS><FONTCOLOR>#FAFAF9</FONTCOLOR></MESSAGE2>";
    		GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayMessage2);
    		},250);
    	}
    	effectTransparentBgSwitch=!effectTransparentBgSwitch;
    }
    
 // 动态图片效果控制开关
    GetID("effectDymcImage").onclick = function () {
    	if(effectDymcImageSwitch){
			//清空动态图片
			GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<IMAGE2></IMAGE2>");
    	}
    	effectDymcImageSwitch=!effectDymcImageSwitch;
    }
 // 动态文字效果控制开关
    GetID("effectDymcMessage").onclick = function () {
    	
    	if(effectDymcMessageSwitch){
			//清空动态文字
    		GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE1></MESSAGE1>");
    		GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE3></MESSAGE3>");
    		GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE4></MESSAGE4>");
    		GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE5></MESSAGE5>");	
    	}
    	effectDymcMessageSwitch=!effectDymcMessageSwitch;
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

//视频播放
function Mp4Player(mp4){
	var embed="<embed src=\"player.swf\" allowfullscreen=\"true\" flashvars=\"controlbar=over&file="+mp4+"&autostart=true\" width=\"600\" height=\"450\"/>";
	GetID("videotag").innerHTML="";
	GetID("videotag").innerHTML=embed;
}

// 录制时间设置
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
//录制按钮
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

function startEnjoy(i){
	if(i==0){
		GetID("startEnjoy").style.backgroundColor = "#ABCB64";
	}else{
		GetID("startEnjoy").style.backgroundColor=  "#7CAF00";
	}
}
/**
 * modifyed by liaobin:2014-12-19
 */
// 视频参数设置ApplyVideoConfig(150000,3,320,240,15,3);
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
//用于控制界面层的显示和隐藏
function displayList(list,type){
	var list=list.split(",");
	for (var i = 0; i < list.length; i++) {
		GetID(list[i]).style.display=type;
	}
}

function setVideoImg(pic,xpos,ypos){
	// 在本地视频上迭加图片
	var szOverlayImage = "<IMAGE1><VALUE>"+pic+"</VALUE><XPOS>"+xpos+"</XPOS><YPOS>"+ypos+"</YPOS></IMAGE1>";
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayImage);
}
//定时器执行定时执行这个函数，实现动态效果
function videoOverlayEffect(){
	
	if(effectDymcMessageSwitch){
		effectDymcMessage();
	}
	if(effectDymcImageSwitch){
		effectDymcImage();
	}
}
/**
**动态文字效果
*/
var tempCount=1,temp=0;
function effectDymcMessage(){
	var fontColor=fontColorCtrl?"#FF0000":"#FFFF80";
	// 在本地视频上迭加文字
	var szOverlayMessage1 = "<MESSAGE1><VALUE>开放  互联</VALUE><XPOS>5</XPOS><YPOS>5</YPOS><FONTCOLOR>#FFFFFF</FONTCOLOR><FONTSIZE>"+dynamicFontSize+"</FONTSIZE><FONTNAME>微软雅黑</FONTNAME></MESSAGE1>";
	var szOverlayMessage3 = "<MESSAGE3><VALUE> 跨平台</VALUE><XPOS>130</XPOS><YPOS>5</YPOS><FONTCOLOR>"+fontColor+"</FONTCOLOR><FONTSIZE>"+dynamicFontSize+"</FONTSIZE><FONTNAME>微软雅黑</FONTNAME></MESSAGE3>";
	var szOverlayMessage4 = "<MESSAGE4><VALUE>支 持 Windows 、Web 、Android、iOS、Linux 等 平 台</VALUE><XPOS>5</XPOS><YPOS>45</YPOS><FONTCOLOR>#00FF00</FONTCOLOR><FONTSIZE>20</FONTSIZE><FONTNAME>微软雅黑</FONTNAME></MESSAGE4>";
	var szOverlayMessage5 = "<MESSAGE5><VALUE>提 供 音 视 频 交 互 、 数 据 通 信 能 力</VALUE><XPOS>5</XPOS><YPOS>70</YPOS><FONTCOLOR>#00FF00</FONTCOLOR><FONTSIZE>20</FONTSIZE><FONTNAME>微软雅黑</FONTNAME></MESSAGE5>";
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayMessage1);
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayMessage3);
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayMessage4);
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayMessage5);
	fontColorCtrl=!fontColorCtrl;
	//字体大小动态变化
	if(temp==1){
		tempCount-=1;
		dynamicFontSize-=2;
		if(tempCount==1){
			temp=0;
		}
	}else{
		if(tempCount==4){temp=1;}
		if(tempCount<4){tempCount+=1;dynamicFontSize+=2;}
	}
}
/**
**动态图片效果
*/
function effectDymcImage(){
	//在本地视频上迭加图片
	var szOverlayImage = "<IMAGE2><VALUE>"+localHref+"btf"+btfIndex+".png</VALUE><XPOS>510</XPOS><YPOS>10</YPOS></IMAGE2>";
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, szOverlayImage);
	//图片显示动态变化
	if(btfCloseTag==1){
		btfIndex-=1;
		dynamicFontSize-=2;
		if(btfIndex==1){
			btfCloseTag=0;
		}
	}else{
		if(btfIndex==4){btfCloseTag=1;}
		if(btfIndex<4){btfIndex+=1;dynamicFontSize+=2;}
	}
}
/**
**清空之前视频界面叠加的文字、图片
*/
function clearVideoOverlayEffect(){
	//在本地视频上迭加图片
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE1></MESSAGE1>");
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE2></MESSAGE2>");
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE3></MESSAGE3>");
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE4></MESSAGE4>");
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<MESSAGE5></MESSAGE5>");
	GetID("ANYCHAT_VIDEO_LOCAL").SetSDKOptionString(ANYCHATWEB_VIDEO_SO_OVERLAY, "<IMAGE2></IMAGE2>");
	effectDymcImageSwitch=false;
	effectDymcMessageSwitch=false;

}
	