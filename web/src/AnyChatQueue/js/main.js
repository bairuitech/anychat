var mDefaultServerAddr = "www.anychat.cn"; // 默认服务器地址
var mDefaultServerPort = 8906; // 默认服务器端口号
var mRefreshPluginTimer = -1; // 检查插件是否安装完成定时器
var mSelfUserId = -1; // 本地用户ID
var mTargetUserId = -1; // 目标用户ID（请求了对方的音视频）
var mRefreshVolumeTimer = -1; // 实时音量大小定时器
var hallbuinessNum = -1; // 营业厅号
var userType; // 用户类型 1为客户,2为坐席
var servantName=-1;//坐席名称
var TimeSet;//个人数据更新计时器
var dwAgentFlags=-1;//身份标识(用户，坐席)
var queueid;//进入的队列id
var startServiceTag=false;//开始服务点击按钮事件
var waitTimeSet; //等待时间计时器
var currentAgentID = -1;  //当前座席ID
var queueListName=-1; //队列名称

// onload默认运行
function LogicInit() {
	setTimeout(
			function() {
				// 判断是否支持插件和插件长度（插件检测）
				if (navigator.plugins && navigator.plugins.length) {
					window.navigator.plugins.refresh(false);
				}
				// 检查是否安装了插件
				var NEED_ANYCHAT_APILEVEL = "0"; // 定义业务层需要的AnyChat
				// API Level
				var errorcode = BRAC_InitSDK(NEED_ANYCHAT_APILEVEL); // 初始化插件（返回成功(0)或插件版本号太低的编号）
				if (errorcode == GV_ERR_SUCCESS) {// 安装成功的情况下
					// BRAC_SetSDKOption(BRAC_SO_CORESDK_SCREENCAMERACTRL,1);//显示桌面
					if (mRefreshPluginTimer != -1)// 检查插件是否安装完成定时器
						clearInterval(mRefreshPluginTimer); // 清除插件安装检测定时器(下面else有定义)

					GetID("prompt_div").style.display = "none"; // 隐藏插件安装提示界面

				} else { // 没有安装插件，或是插件版本太旧，显示插件下载界面
					// ShowLoginDiv(false);

					$("#loginDiv").hide();
					GetID("prompt_div").style.display = "block";// 显示插件安装提示界面
					if (errorcode == GV_ERR_PLUGINNOINSTALL)// 第2个参数指 插件没有安装(编码)
						GetID("prompt_div_line1").innerHTML = "首次进入需要安装插件，请点击下载按钮进行安装！";
					else if (errorcode == GV_ERR_PLUGINOLDVERSION)// 第2个参数指
						// 插件版本太低(编码)
						GetID("prompt_div_line1").innerHTML = "检测到当前插件的版本过低，请下载安装最新版本！";

					if (mRefreshPluginTimer == -1) {// 检查插件是否安装完成定时器
						mRefreshPluginTimer = setInterval(function() {
							LogicInit();
						}, 1000);
					}
				}
			}, 500);
}

//初始化本地对象信息
function InitClientObjectInfo(mSelfUserId,dwAgentFlags) {
	/**业务对象身份初始化*/
	BRAC_SetSDKOption(BRAC_SO_OBJECT_INITFLAGS, dwAgentFlags);
	var dwPriority = 10;
	/**客户端用户对象优先级*/
	BRAC_ObjectSetValue(ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
	var dwAttribute = -1;
	BRAC_ObjectSetValue(ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwAttribute);
	/**向服务器发送数据同步请求指令*/
	BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, ANYCHAT_INVALID_OBJECT_ID, ANYCHAT_OBJECT_CTRL_SYNCDATA, mSelfUserId, 0, 0, 0, "");
}

$(function () {

    LogicInit(); // 初始化sdk
    setMarTop($("#loginDiv").outerHeight()); // 设置登录界面距离顶部的高
    setClientBrowerView(); //设置自适应浏览器高宽
    setObjMiddle($("#Initiative_Call_Div")); //设置主动呼叫等待框居中
    setObjMiddle($("#BeCalls_Div")); //设置被呼叫询问框居中
    setObjMiddle($("#SessionPrompt_Div")); //设置被呼叫询问框居中
    var tipByUserName="请输入用户名!";
    //用户名输入提示
    $("#username").blur(function(){
    	if(!$(this).val().length){
    		$(this).val(tipByUserName);
    	}
    });
    $("#username").focus(function(){
    	if($(this).val()==tipByUserName)
    		$(this).val("");
    });
    // 所有按钮点击后不显示虚线
    $("body").delegate('button,a', 'focus', function () {
        $(this).blur();
    });
    //业务下拉绑定
    $("#selectList").delegate('li', 'click', function () {
        $(this).siblings().find(".content").slideUp();
        $(".content", this).slideDown();
    });
    //进入队列
    $("#selectList").delegate('a', 'click', function () {
        queueid = parseInt($(this).attr('queueid')); //获取队列id
        $("#LOADING_GREY_DIV img").hide();//隐藏登录等待gif
        console.log('进入队列');
        /**进入队列*/
        BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERENTER, 0, 0, 0, 0, "");
        $("#enterRoom").hide(); //隐藏队列
        $("#queueMsg1").show(); //重置显示排队信息
        $("#queueMsg2").hide(); //隐藏呼叫信息
        $("#callLayer").show(); //显示弹出窗口
        $("#queueMsg1 strong:eq(2)").text(0); //清零排队时间
        clearInterval(waitTimeSet);
        waitTimeSet = setInterval(function () {
            var time = formatSeconds(BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_INFO_WAITTIMESECOND));
            $("#queueMsg1 strong:eq(2)").text(time);
        }, 1000);
    });
    $('#mDefaultServerAddr').val(mDefaultServerAddr);
    $('#mDefaultServerPort').val(mDefaultServerPort);
    // 登录按钮(进入大厅)
    $("#loginRoom").click(function () {
		$("#LOADING_GREY_DIV span").text("正在进入营业厅，请稍候......");
    	$("#password").val(333);
        mDefaultServerAddr = $('#mDefaultServerAddr').val();
        mDefaultServerPort = $('#mDefaultServerPort').val();

        if ($("#username").val() == tipByUserName||$("#username").val()==0) {
            $("#username").focus();
            return;
        }
        userType = parseInt($("#askSelect option:selected").val()); // 获取目标用户类型
        $("#enterRoom .poptip").remove(); //清除营业厅
        $("#LOADING_GREY_DIV img").show();//显示登录等待gif
        $("#LOADING_GREY_DIV").show();//显示登录蒙层
        setMarTop($("#enterRoom").height()); //动态设置大厅居中
        switch (userType) {
            case 1: //用户登入的情况
                /**连接服务器*/
                BRAC_Connect(mDefaultServerAddr, mDefaultServerPort);
                /**登入anychat*/
                var loginTag = BRAC_Login($("#username").val(), "", 0);
                $("#videoCall").css("width", "980px"); //设置视频会话层宽度
                break;
            default:
                
                    servantName = $("#username").val(); //客服登入账户名

                    if (userType == 2) {
                        /**连接服务器*/
                        BRAC_Connect(mDefaultServerAddr, mDefaultServerPort);
                        $("#videoCall").css("width", "880px"); //设置视频会话层宽度
                        //坐席呼叫视频界面
                        var videoHtml = '<div style="background:#E9E5E6;">' +
                                            '<div style="height:505px;">' +
                                                '<div style="width:240px;float: left">'+
                                                    '<div id="clientList" style="text-align: center;position: relative;background:#5d739c;height:300px;width:240px;padding-top: 15px;overflow-y:auto;">'+
                                                        '<iframe frameborder="0" style="background-color:transparent; z-index: 9999;width: 100%;height: 100%;top:0;left: 0;position: absolute;display: none" scrolling="no"></iframe>'+
                                                        '<h3 style="color:pink;">服务信息</h3><br>'+
                                                        '<!-- <b style="font-size: 15px;color: white">服务区域内访客的用户数<br>（没有排入队列的用户）</b><strong style="color:orange;margin-top:10px;display: block;"></strong> -->'+
                                                        '<b style="margin-top:10px;font-size: 15px;color: white">当前服务的队列数量为：</b><strong style="color:orange;margin-top:5px;display: block;"></strong><br/>' +
                                                        '<b style="margin-top:10px;font-size: 15px;color: white">当前排队的用户总数为：</b><strong style="color:orange;margin-top:5px;display: block;"></strong><br/>' +
                                                        '<b style="margin-top:10px;font-size: 15px;color: white">已服务人数为：</b><strong style="color:orange;margin-top:5px;display: block;"></strong>' +
                                                        '<!-- <b style="margin-top:10px;font-size: 15px;color: white">累计服务时长为：</b><strong style="color:orange;margin-top:5px;display: block;"></strong> -->'+
                                                    '</div>'+
                                                    '<div id="localVideoDiv" style="width:240px;padding-top:10px;">'+
                                                        '<div style="width:240px;height:180px;" id="localVideoPos"></div>'+
                                                        '<div style="width:240px;height:5px;" id="localAudioVolume"></div>'+
                                                    '</div>'+
                                                '</div>'+
                                                '<div style="float:right;text-align: center" id="removeVideoDiv">' +
                                                    '<div id="currentServicedUserInfo" style="height:20px;background:#5d739c;">' +
                                                        '<b style="color: white">当前服务用户：</b><strong></strong>' +
                                                        '<!-- <b style="color: white"> 当前开始服务时间：</b><strong></strong> -->' +
                                                    '</div>' +
                                                    '<div style="width:568px;height:426px;" id="removeVideoPos"></div>'+
                                                    '<div style="background:green;width:568px;height:5px;" id="remoteAudioVolume"></div>'+
                                                    '<button id="startService" class="buttonCls">开始服务</button><button id="stopVideo" class="buttonCls">停止视频</button><!-- <button id="testBtn" class="buttonCls">测试</button> -->'+
                                                '</div>'+
                                            '</div>'+
                                        '</div>';

                        $("#videoCallContent").html(videoHtml); //填充视频会话层
                        //停止视频事件
                        $("#stopVideo").click(function () {

                            if ($("#removeVideoPos").html() != "") {
                                if (confirm("你确定中止当前视频吗？")) {
                                    BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断
                                    $("#Initiative_Call_Div").hide(); //隐藏主动呼叫层
                                    $("#clientList iframe").hide();

                                }
                            }
                        });
                        $('#startService').click(function () {
                            if (!startServiceTag) {
                                startServiceTag = true;
                                /**客服开始服务*/
                                BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AGENT, mSelfUserId, ANYCHAT_AGENT_CTRL_SERVICEREQUEST, 0, 0, 0, 0, "");
                            }
                        });
                        
                        /**登入anychat*/
                        var loginTag = BRAC_Login($("#username").val(), "", 0);

                    }
                    if (userType == 3) {
                        $("#ServiceInfoReSet").click();
                    }
                break;
        }
    });

    // 退出大厅按钮
    $("#roomOut").click(sysOut);
    $("#Out").click(sysOut);
    function sysOut() {
        setMarTop($("#loginDiv").outerHeight());
        $("#enterRoom").hide();
        $("#loginDiv").show();
        BRAC_Logout(); //退出系统
        dwAgentFlags = -1;
        mSelfUserId = -1;
        $("#ServiceInfoDiv").hide();
    }
    $("#loginOut").click(function () {
    	$("#enterRoom h2").text("营业厅列表");
        /**离开营业厅*/
        BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");
        $(this).hide();
        $('#selectList').hide();
        $('#roomOut').show();
        $('#hallList').show();
    });

    //绑定营业厅点击事件
    $("#hallList").delegate('li[class="poptip"]', 'click', function () {
    	queueListName=$(this).text()+" - 队列列表";
    	$("#LOADING_GREY_DIV img").show();//显示登录等待gif
    	$("#LOADING_GREY_DIV").show();//显示蒙层
    	$("#LOADING_GREY_DIV span").hide();
    	if(userType==1){
    		$("#LOADING_GREY_DIV span").text("正在进入队列，请稍候......");
    		$("#LOADING_GREY_DIV span").show();
    	}
        hallbuinessNum = parseInt($(this).attr('dwobjectid')); //营业厅号为id
        console.log('进入营业厅号：' + hallbuinessNum);
        /**进入营业厅*/
        BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERENTER, 0, 0, 0, 0, "");

        if (userType == 1) {//客户
            $('#selectList').empty(); //清空队列
        } else if (userType == 2) {//客服
            $('#enterRoom').hide(); //直接隐藏进入队列步骤
            $('#videoCall').show(); //显示客户视频窗口

            setMarTop(9999);
        }
    });

    // 绑定挂断按钮事件
    $("#videoCallContent").delegate('#hangUp', 'click', function () {

        BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断

        if (userType == 1) {
            /**离开队列*/
            BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
        }
        clearInterval(mRefreshVolumeTimer); // 清除实时音量显示计时器
        $("#clientList iframe").hide();
        $("#videoCall").hide(); //隐藏视频窗口
        $("#enterRoom").show();
        setMarTop($("#enterRoom").height());

        if ($("#clientList div").length > 0) {
            $("#clientList div").remove();
        }

    });
    // 排队信息确认框
    $(".confirmMsg").click(function () {
        clearInterval(waitTimeSet); //清除排队时间计时器
        $('#callLayer').hide(); //隐藏排队信息窗口
        $("#queueMsg2").hide(); //隐藏客服呼叫信息
        $("#queueMsg1").show(); //重置排队信息
        //判断信息执行对应操作
        switch ($(this).text()) {
            case "取消排队":
                $("#enterRoom").show(); //显示队列列表
                /**离开队列*/
                BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
                break;
            case "接受":
                AcceptRequestBtnClick();
                break;
            case "拒绝":
                $("#enterRoom").show();
                RejectRequestBtnClick();
                break;
            default:
                break;
        }
    });
    
});
//设置组件居中
function setObjMiddle(obj){
	var Left= parseInt(($(document).width()-obj.width())/2);//获取呼叫请求弹窗距离右侧的宽度
	var Top= parseInt(($(document).height()-obj.height())/2);//获取呼叫请求弹窗距离顶部的宽度
	obj.css({"left":Left,"top":Top});
}
// 根据视窗大小调整顶部高度
function setMarTop(t) {
	$("#bodyHeader").height($(document).height() > t ? ($(document).height() - t) / 2 + "px" : "0px");
}

function getAreaInfo(){
	if(userType==2){		
		var queueCount=BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_INFO_QUEUECOUNT);
		var queueUserCount = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_INFO_QUEUEUSERCOUNT);
	
		$('#clientList strong:eq(0)').text(queueCount + "个");	
		$('#clientList strong:eq(1)').text(queueUserCount + "人");
	}
}
// 控制视频打开关闭
function startVideo(uid, videoID, videoType, state) {
	/**视频操作*/
	BRAC_UserCameraControl(uid, state); 
	/**语音操作*/
	BRAC_UserSpeakControl(uid, state); 
	/**设置视频显示位置*/
	BRAC_SetVideoPos(uid, videoID, videoType);
}

// 打开指定用户的音视频
function RequestOtherUserVideo(userid) {

	// 判断是否需要关闭之前已请求的用户音视频数据
	if (mTargetUserId != -1) {
		/**操作本地用户视频（或请求远程用户视频）*/
		BRAC_UserCameraControl(mTargetUserId, 0);
		/**操作本地用户语音（或请求远程用户语音）*/
		BRAC_UserSpeakControl(mTargetUserId, 0);
		GetID(mTargetUserId + "_UserDiv").style.backgroundColor = "";
	}
	// 设置远程视频显示位置
/*	startVideo(userid, GetID("removeVideoPos"), "ANYCHAT_VIDEO_REMOTE", 1);
*/	
	
	GetID(userid + "_UserDiv").style.backgroundColor = "rgba(255, 255, 255, .5)"; // 设置被点击<a>元素的背景颜色
	mTargetUserId = userid; // 设置被点用户ID为全局变量
}

//录制时间设置
function formatSeconds(value) {
	var s = parseInt(value);// 秒
	var min = 0;// 分
	if(s > 60) {
      min = parseInt(s/60);
      s = parseInt(s%60);
		if(min > 60) {
			min = parseInt(min%60);
		}
	}

	var result = ""+parseInt(s)+"秒";
	if(min > 0) {
		result = ""+parseInt(min)+"分"+result;
	}
	tt=parseInt(min)+"分"+parseInt(s)+"秒";
    return tt;
}


//设置音量感应计时器
function setVolumeTimer(){
	mRefreshVolumeTimer = setInterval(
			function() {
				var LocalAudioVolume= GetID("localVideoPos").offsetHeight * BRAC_QueryUserStateInt(mSelfUserId,BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";//本地音量大小百分比
				GetID("localAudioVolume").style.width = LocalAudioVolume==0?"0px":LocalAudioVolume;
				if (mTargetUserId != -1) {
				var RemoteAudioVolume=GetID("removeVideoPos").offsetHeight * BRAC_QueryUserStateInt(mTargetUserId,BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";//远程音量大小百分比
				GetID("remoteAudioVolume").style.width = RemoteAudioVolume==0?"0px":RemoteAudioVolume;
			    }
	}, 100);
}

//设置自适应浏览器高宽
function setClientBrowerView(){
	var BrowserViewHg=$(document).height(),//浏览器可视高度
	BrowserViewWd=$(document).width(),//浏览器可视宽度
	TargetHg=$("#loginDiv").height(),//目标div高度
	TargetWd=$("#loginDiv").width(),//目标div宽度
	extraHg=BrowserViewHg>TargetHg?parseInt((BrowserViewHg-TargetHg)/2):"",//额外高度
	extraWd=BrowserViewWd>TargetWd?parseInt((BrowserViewWd-TargetWd)/2):"";//额外宽度
		
	if(extraHg!=""){
		$("#page_01").height(17+extraHg+"px");
		$("#page_02").height(17+extraHg+"px");
		$("#page_03").height(17+extraHg+"px");
		$("#page_04").css("top",17+extraHg+"px");
		$("#page_05").css("top",17+extraHg+"px");
		$("#page_06").css("top",17+extraHg+"px");
		$("#page_07").css("top",574+extraHg+"px");
		$("#page_08").css({"height":17+extraHg+"px","top":651+extraHg+"px"});
		$("#page_09").css({"height":17+extraHg+"px","top":651+extraHg+"px"});
		$("#page_10").css({"height":17+extraHg+"px","top":651+extraHg+"px"});
	}
	if(extraWd!=""){
		$("#page_01").width(58+extraWd+"px");
		$("#page_04").width(58+extraWd+"px");
		$("#page_08").width(58+extraWd+"px");
		$("#page_02").css("left",58+extraWd+"px");
		$("#page_05").css("left",58+extraWd+"px");
		$("#page_07").css("left",58+extraWd+"px");
		$("#page_09").css("left",58+extraWd+"px");
		$("#page_03").css({"width":58+extraWd+"px","left":1310+extraWd+"px"});
		$("#page_06").css({"width":58+extraWd+"px","left":1310+extraWd+"px"});
		$("#page_10").css({"width":58+extraWd+"px","left":1310+extraWd+"px"});
	}
}

//刷新用户进入队列后，排队等待时的显示信息
function refreshUserWaitingInfo(queueID) {
    var queueUserNum; //当前队列人数
    var beforeUserNum; //排在自己前面的队列人数

    /**获取当前队列人数*/
    queueUserNum = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueID, ANYCHAT_QUEUE_INFO_LENGTH);
    $('#queueMsg1 strong:eq(0)').text(queueUserNum);

    /**获取排在自己前面的用户数*/
    beforeUserNum = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueID, ANYCHAT_QUEUE_INFO_BEFOREUSERNUM);
    beforeUserNum = beforeUserNum < 0 ? 0 : beforeUserNum;
    beforeUserNum++;

    $('#queueMsg1 strong:eq(0)').text(queueUserNum);
    $('#queueMsg1 strong:eq(1)').text(beforeUserNum);

    $('#selectList li a[queueid=' + queueID + ']').prev().text(queueUserNum); //队列中当前排队人数填充


}

//刷新坐席进入服务区域后的显示信息
function refreshAgentServiceInfo() {
    if (userType == 2) {
        var queueCount = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_INFO_QUEUECOUNT);
        var queuesUserCount = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_INFO_QUEUEUSERCOUNT);

        //累计服务时长
        var serviceTotalTime = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AGENT, currentAgentID, ANYCHAT_AGENT_INFO_SERVICETOTALTIME);

        //累计服务的用户数
        var serviceUserCount = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AGENT, currentAgentID, ANYCHAT_AGENT_INFO_SERVICETOTALNUM);

        $('#clientList strong:eq(0)').text(queueCount + "个");
        $('#clientList strong:eq(1)').text(queuesUserCount + "人");
        $('#clientList strong:eq(2)').text(serviceUserCount + "人");
        $('#clientList strong:eq(3)').text(serviceTotalTime + "秒");
    }
}

//刷新当前接通服务的用户信息
//如果userID = -1，则表示清空用户信息
function refreshServicedUserInfo(userID) {

    //当前服务的用户ID
    var serviceUserID = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_AGENT, currentAgentID, ANYCHAT_AGENT_INFO_SERVICEUSERID);

    //用户登录名
    var userName = BRAC_GetUserInfo(userID, USERINFO_NAME); 

    if (userID == -1) {
        $('#currentServicedUserInfo strong:eq(0)').text("");
    } else {
        $('#currentServicedUserInfo strong:eq(0)').text(userName);
    }
}

