var mDefaultServerAddr = "demo.anychat.cn"; // 默认服务器地址
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
var dwPriority;//用户优先级
var tipByUserName="请输入用户名!";//用户名文本提示信息

// 日志记录类型，在日志信息栏内显示不同的颜色
var LOG_TYPE_NORMAL = 0;
var LOG_TYPE_API = 1;
var LOG_TYPE_EVENT = 2;
var LOG_TYPE_ERROR = 3;

var USER_TYPE_CLIENT = 1;
var USER_TYPE_AGNET = 2;

var CLIENT_STATUS_AREA = 1;
var CLIENT_STATUS_QUEUE = 2;
var CLIENT_STATUS_QUEUEING = 3;
var CLIENT_STATUS_CHATTING = 4;

var AGENT_STATUS_AREA = 1;
var AGENT_STATUS_SERVICE = 2;

//座席与用户当前所处的状态
var mCurrentStatus = 0;
var colorIdx = 0;
//服务区域(营业厅)显示块颜色数组
var colorArray = ["#63C058", "#F49537", "#A2C926", "#FEC900"];

//队列显示块颜色数组
var colorQueueArray = ["#48cfae", "#a0d468", "#ffcf56"];

//当前被选择的队列名称
var currentSelectedQueueName = "";

//服务区域(营业厅)ID数组
var areaIdArray = null;
var areaArrayIdx = 0;

//房间号
var mRoomId = -1;

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
                AddLog("BRAC_InitSDK(" + NEED_ANYCHAT_APILEVEL + ")=" + errorcode, LOG_TYPE_API);
                if (errorcode == GV_ERR_SUCCESS) {// 安装成功的情况下
                    // BRAC_SetSDKOption(BRAC_SO_CORESDK_SCREENCAMERACTRL,1);//显示桌面
                    if (mRefreshPluginTimer != -1)// 检查插件是否安装完成定时器
                        clearInterval(mRefreshPluginTimer); // 清除插件安装检测定时器(下面else有定义)
                    GetID("loginDiv").style.display = "block";
                    GetID("prompt_div").style.display = "none"; // 隐藏插件安装提示界面
					BRAC_SetSDKOption(BRAC_SO_VIDEOBKIMAGE, "./img/videobk.jpg");
                    AddLog("AnyChat Plugin Version:" + BRAC_GetVersion(0), LOG_TYPE_NORMAL);
                    AddLog("AnyChat SDK Version:" + BRAC_GetVersion(1), LOG_TYPE_NORMAL);
                    AddLog("Build Time:" + BRAC_GetSDKOptionString(BRAC_SO_CORESDK_BUILDTIME), LOG_TYPE_NORMAL);
                } else { // 没有安装插件，或是插件版本太旧，显示插件下载界面

                    GetID("loginDiv").style.display = "none";
                    GetID("prompt_div").style.display = "block";// 显示插件安装提示界面
                    if (errorcode == GV_ERR_PLUGINNOINSTALL)// 第2个参数指 插件没有安装(编码)
                        GetID("prompt_div_line1").innerHTML = "首次进入需要安装插件，请点击下载按钮进行安装！";
                    else if (errorcode == GV_ERR_PLUGINOLDVERSION)// 第2个参数指
                        // 插件版本太低(编码)
                        GetID("prompt_div_line1").innerHTML = "检测到当前插件的版本过低，请下载安装最新版本！";

                    if (mRefreshPluginTimer == -1) {// 检查插件是否安装完成定时器
                        mRefreshPluginTimer = setInterval(function() {
                            LogicInit();
                        }, 500);
                    }
                }
				
			}, 500);
}

//初始化本地对象信息
function InitClientObjectInfo(mSelfUserId, dwAgentFlags, dwPriority) {
    AddLog("Initialize Client Object Information", LOG_TYPE_NORMAL);

    //初始化服务区域Id数组
    areaArrayIdx = 0;
    areaIdArray = new Array();

	//业务对象身份初始化
	BRAC_SetSDKOption(BRAC_SO_OBJECT_INITFLAGS, dwAgentFlags);
	//客户端用户对象优先级
	BRAC_ObjectSetValue(ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, ANYCHAT_OBJECT_INFO_PRIORITY, dwPriority);
	var dwAttribute = -1;
	BRAC_ObjectSetValue(ANYCHAT_OBJECT_TYPE_CLIENTUSER, mSelfUserId, ANYCHAT_OBJECT_INFO_ATTRIBUTE, dwAttribute);
	//向服务器发送数据同步请求指令
	BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, ANYCHAT_INVALID_OBJECT_ID, ANYCHAT_OBJECT_CTRL_SYNCDATA, mSelfUserId, 0, 0, 0, "");
}

$(function () {
    var ua = window.navigator.userAgent.toLowerCase();
    var info = {
        edge: /edge/.test(ua)
    };
    if (info.edge) {
        $("#loginDiv").hide();
        $("#prompt_div").hide();
        $('.showBox').hide();
        $('body').append('<iframe src="./html/needie.html?reason=3" style="width: 100%; height: 800px;" scrolling = "no"  frameborder="0"></iframe>');
    } else {
        LogicInit(); // 初始化sdk
    }

    setObjMiddle($("#Initiative_Call_Div")); //设置主动呼叫等待框居中
    setObjMiddle($("#SessionPrompt_Div")); //设置被呼叫询问框居中
    //用户名输入提示
    $("#username").blur(function () {
        if (!$(this).val().length) {
            $(this).val(tipByUserName);
        }
    });
    $("#username").focus(function () {
        if ($(this).val() == tipByUserName)
            $(this).val("");
    });

    getLoginInfo();

    // 所有按钮点击后不显示虚线
    $("body").delegate('button,a', 'focus', function () {
        $(this).blur();
    });
    //业务下拉绑定(暂定)
    $("#selectList").delegate('li', 'click', function () {
        $(this).siblings().find(".content").slideUp();
        $(".content", this).slideDown();
    });

    $('#mDefaultServerAddr').val(mDefaultServerAddr);
    $('#mDefaultServerPort').val(mDefaultServerPort);

    // 登录按钮(进入大厅)
    $("#loginRoom").click(function () {
        $("#LOADING_GREY_DIV span").show();
        $("#LOADING_GREY_DIV span").text("登录中，请稍候......");

        mDefaultServerAddr = $('#mDefaultServerAddr').val();
        mDefaultServerPort = $('#mDefaultServerPort').val();

        if ($("#username").val() == tipByUserName) {
            $("#username").focus();
            AddLog("The user name can not be empty!", LOG_TYPE_ERROR);
            return;
        }
        if (mDefaultServerAddr == "") {
            AddLog("The server IP can not be empty!", LOG_TYPE_ERROR);
            return;
        }
        if (mDefaultServerPort == "") {
            AddLog("The server port can not be empty!", LOG_TYPE_ERROR);
            return;
        }

        setLoginInfo();
        if ($("#AppGuid") && $("#AppGuid").val().length)				// 设置应用ID
            BRAC_SetSDKOption(BRAC_SO_CLOUD_APPGUID, $("#AppGuid").val().toString());

        userType = parseInt($("#askSelect option:selected").val()); // 获取目标用户类型
        $("#poptip li").remove(); //清除营业厅
        $("#LOADING_GREY_DIV img").show(); //显示登录等待蒙层
        $("#LOADING_GREY_DIV").show(); //显示登录蒙层
        /**连接服务器*/
        BRAC_Connect(mDefaultServerAddr, mDefaultServerPort);
        // 退出大厅按钮
        $("#roomOut").off().click(systemOut);

    });
    //日志显示按钮
    $(".showBox").click(function () {
        $("#LOG_DIV_BODY").show();
        $(".showBox").hide();
        $("#LOG_DIV_BODY").animate({
            bottom: 0
        }, "slow");

    });
    //日志隐藏按钮
    $("#LOG_DIV_TITLE").click(function () {
        $("#LOG_DIV_BODY").animate({
            bottom: -210, display: "none"
        }, "slow");
        $(".showBox").show();
    });

    $("#leaveQueue").click(function () {
        $("#enterRoom h2").text("营业厅列表");
        /**离开营业厅*/
        BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");
        $(this).hide();
        $('#selectList').hide();
        $('#roomOut').show();
        $('#hallList').show();
    });

    //绑定营业厅点击事件
    $("#poptip").delegate('.btn', 'click', function () {
        var areaId = $(this).parents("li").attr('areaId');
        var queueId = $(this).parents("li").attr('queueid');
        if (!isEmpty(areaId)) {
            $("#LOADING_GREY_DIV span").text("正在进入营业厅，请稍候......");

            queueListName = $(this).parents("li").find("p:first-child").text() + " - 队列列表";

            $("#LOADING_GREY_DIV img").show(); //显示登录等待蒙层
            $("#LOADING_GREY_DIV").show(); //显示蒙层
            if (userType == USER_TYPE_CLIENT) {//客户
                //$("#LOADING_GREY_DIV").hide(); //隐藏蒙层
                $('#poptip li[queueid]').remove(); //移除队列
            } else if (userType == USER_TYPE_AGNET) {//客服
                $('#enterRoom .contentArea').hide(); //直接隐藏进入队列步骤
                $("#enterRoom h2").text("坐席端服务窗口");
                $("#videoCall").show(); //显示客户视频窗口
                $("#roomOut").off().click(function () {
                    $('#returnHall').click();
                });

                mCurrentStatus = AGENT_STATUS_SERVICE;
            }
            hallbuinessNum = parseInt(areaId); //营业厅号为id
            /**进入营业厅*/
            var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERENTER, 0, 0, 0, 0, "");
            AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_AREA + "," + hallbuinessNum + "," + ANYCHAT_AREA_CTRL_USERENTER + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);

        } else if (!isEmpty(queueId)) {
            $("#LOADING_GREY_DIV span").text("正在进入队列，请稍候......");
            $("#enterRoom h2").text("排队信息");
            $("#LOADING_GREY_DIV").show(); //显示等待蒙层
            queueid = parseInt(queueId); //获取队列id
            /**进入队列*/
            var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERENTER, 0, 0, 0, 0, "");
            AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_QUEUE + "," + queueid + "," + ANYCHAT_QUEUE_CTRL_USERENTER + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);

            $("#roomOut").off().click(function () {
                if ($('#queueMsg1').css("display") == "block") {
                    $('#queueMsg1 .confirmMsg').click();
                } else if ($('#queueMsg2').css("display") == "block") {
                    $('#reject').click();
                } else if ($("#videoCall").css("display") == "block") {
                    $('#hangUp').click();
                }
            });
        }

    });

    // 绑定挂断按钮事件
    $("#videoCallContent").delegate('#hangUp', 'click', function () {

        var errorcode = BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断
        AddLog("BRAC_VideoCallControl(" + BRAC_VIDEOCALL_EVENT_FINISH + "," + mTargetUserId + ",0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);


        if (userType == USER_TYPE_CLIENT) {
            $("#enterRoom h2").text(queueListName);
            /**离开队列*/
            //BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");

            mCurrentStatus = CLIENT_STATUS_QUEUE;
        }
        clearInterval(mRefreshVolumeTimer); // 清除实时音量显示计时器
        $("#videoCall").hide(); //隐藏视频窗口
        $("#poptip").show();
        isShowReturnBtn(true);
        $("#roomOut").off().click(function () {
            $("#enterRoom h2").text("营业厅列表");
            $('#poptip li[queueid]').hide(); //隐藏队列
            $("#poptip li[areaId]").show();
            $(this).off().click(systemOut);
        });
    });
    // 排队信息确认框
    $("#callLayer a.confirmMsg").click(function () {
        $("#callLayer h4").text("排队等待中");
        clearInterval(waitTimeSet); //清除排队时间计时器
        $('#callLayer').hide(); //隐藏排队信息窗口
        $("#queueMsg2").hide(); //隐藏客服呼叫信息
        //判断信息执行对应操作
        switch ($(this).text()) {
            case "取消排队":
                $("#enterRoom h2").text(queueListName);
                $("#LOADING_GREY_DIV span").text("取消排队处理中，请稍候......"); //等待蒙层文本填充
                $("#LOADING_GREY_DIV").show(); //显示等待蒙层
                /**离开队列*/
                var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
                AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_QUEUE + "," + queueid + "," + ANYCHAT_QUEUE_CTRL_USERLEAVE + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);

                isShowReturnBtn(true);

                $("#roomOut").off().click(function () {
                    //离开营业厅
                    var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");
                    AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_AREA + "," + hallbuinessNum + "," + ANYCHAT_AREA_CTRL_USERLEAVE + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);

                    $("#enterRoom h2").text("营业厅列表");
                    $('#poptip li[queueid]').hide(); //隐藏队列
                    $("#poptip li[areaId]").show();
                    $(this).off().click(systemOut);
                });
                break;
            case "接受":
                $("#enterRoom h2").text(currentSelectedQueueName + "服务窗口");
                AcceptRequestBtnClick();
                break;
            case "拒绝":
                $("#enterRoom h2").text(queueListName);
                $("#poptip").show();
                isShowReturnBtn(true);
                $("#poptip li[queueid]").show(); //显示队列列表
                RejectRequestBtnClick();
                break;
            default:
                break;
        }
        $("#roomOut").off().click(function () {
            $("#enterRoom h2").text("营业厅列表");
            $('#poptip li[queueid]').hide(); //隐藏队列
            $("#poptip li[areaId]").show();
            $(this).off().click(systemOut);
        });

    });

});
//设置组件居中
function setObjMiddle(obj){
	var Left= parseInt(($(document).width()-obj.outerWidth())/2);//获取呼叫请求弹窗距离左侧的宽度
	var Top= parseInt(($(document).height()-obj.outerHeight())/2);//获取呼叫请求弹窗距离顶部的宽度
	obj.css({"left":Left,"top":Top});
}

// 控制视频打开关闭
function startVideo(uid, videoID, videoType, state) {
	/**视频操作*/
    var errorcode = BRAC_UserCameraControl(uid, state);
    AddLog("BRAC_UserCameraControl(" + uid + "," + state + ")=" + errorcode, LOG_TYPE_API);

	/**语音操作*/
    errorcode = BRAC_UserSpeakControl(uid, state);
    AddLog("BRAC_UserSpeakControl(" + uid + "," + state + ")=" + errorcode, LOG_TYPE_API);

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
/*	startVideo(userid, GetID("remoteVideoPos"), "ANYCHAT_VIDEO_REMOTE", 1);
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
				var RemoteAudioVolume=GetID("remoteVideoPos").offsetHeight * BRAC_QueryUserStateInt(mTargetUserId,BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";//远程音量大小百分比
				GetID("remoteAudioVolume").style.width = RemoteAudioVolume==0?"0px":RemoteAudioVolume;
			    }
	}, 100);
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

    //$('#selectList li a[queueid=' + queueID + ']').prev().text(queueUserNum); //队列中当前排队人数填充


}

//刷新坐席进入服务区域后的显示信息
function refreshAgentServiceInfo() {
    if (userType == USER_TYPE_AGNET) {
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


// 添加日志并显示，根据不同的类型显示不同的颜色
function AddLog(message, type) {
    if (type == LOG_TYPE_API) {			// API调用日志，绿色
        message = message.fontcolor("Green");
	} else if(type == LOG_TYPE_EVENT) {	// 回调事件日志，黄色
        message = message.fontcolor("#CC6600");
	} else if(type == LOG_TYPE_ERROR) {	// 出错日志，红色
        message = message.fontcolor("#FF0000");
	} else {							// 普通日志，灰色
        message = message.fontcolor("#333333");
	}
    GetID("LOG_DIV_CONTENT").innerHTML += message + "&nbsp" + GetTheTime().fontcolor("#333333") + "<br />";
	GetID("LOG_DIV_CONTENT").scrollTop = GetID("LOG_DIV_CONTENT").scrollHeight;
}
function GetID(id) {
	if (document.getElementById) {
		return document.getElementById(id);
	} else if (window[id]) {
		return window[id];
	}
	return null;
}
//获取当前时间  (00:00:00)
function GetTheTime() {
	var TheTime = new Date();
	return TheTime.toLocaleTimeString();
}

function isEmpty(fData){
    return ((fData==null) || (fData.length==0));
}

function systemOut() {
    $("#LOADING_GREY_DIV").hide();
    $("#enterRoom").hide();
    $("#callLayer").hide();
    $("#videoCall").hide(); //隐藏视频窗口
    $("#loginDiv").show();
    var errorcode=BRAC_Logout(); //退出系统
    //if (!errorcode) AddLog('退出系统', LOG_TYPE_NORMAL);
    AddLog("BRAC_Logout()=" + errorcode, LOG_TYPE_API);
    dwAgentFlags = -1;
    mSelfUserId = -1;
    queueListName = -1;
    colorIdx = 0;
    mCurrentStatus = 0;
}

//返回营业厅的逻辑处理
function leaveAreaClickEvent() {
    if (confirm("您确定要结束服务返回营业厅吗？")) {
        $("#enterRoom h2").text("营业厅列表");
        startServiceTag = false;
        var finishCallFlag = false;
        if ($("#remoteVideoPos").html() != "") {
            finishCallFlag = BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断
            AddLog("BRAC_VideoCallControl(" + BRAC_VIDEOCALL_EVENT_FINISH + "," + mTargetUserId +  ",0,0,0,''" + ")=" + finishCallFlag, LOG_TYPE_API);

            $("#Initiative_Call_Div").hide(); //隐藏主动呼叫层
        }
        if (!finishCallFlag) {
            $('#localVideoPos').empty();
            $('#remoteVideoPos').empty();
            /**离开营业厅*/
            var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");
            AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_AREA + "," + hallbuinessNum + "," + ANYCHAT_AREA_CTRL_USERLEAVE + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);

            $('#videoCall').hide();
            $('#enterRoom .contentArea').show();
        }
        $("#roomOut").off().click(systemOut);
    }

}


function refreshQueueInfoDisplay(queueID)
{
    //获取当前队列人数
    var queueUserNum = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueID, ANYCHAT_QUEUE_INFO_LENGTH);

    $('#poptip li[queueid=' + queueID + '] strong:eq(0)').text(queueUserNum + " 人"); //队列中当前排队人数填充
}

//是否显示返回按钮
function isShowReturnBtn(isShow) {
    if (isShow)
        $("#roomOut").show();
    else {
        $("#roomOut").hide();
    }
}

//显示服务区域(营业厅)
function showSerivceArea() {
    var areaName = "";
    var description = "";

    $("#loginDiv").hide(); //隐藏登录界面
    $("#enterRoom").show(); //显示大厅
    $("#poptip").show();    //显示营业厅列表
    $("#enterRoom h2:eq(1)").text("营业厅列表");

    for (var idx in areaIdArray)
    {
        areaName = BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_AREA, areaIdArray[idx], ANYCHAT_OBJECT_INFO_NAME);
        description = BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_AREA, areaIdArray[idx], ANYCHAT_OBJECT_INFO_DESCRIPTION);

        if (queueListName == -1) {
            $("#poptip li").each(function (index) {
                if (areaIdArray[idx] == $(this).attr('areaId')) { $(this).remove(); }
            });
            var createObj = $('<li areaId="' + areaIdArray[idx] + '">' + '<p>' + areaName + '</p>' + '<p class="description">' + description + '</p>' + '<p>' + '<img src="./img/area.png">' + '</p>' + '<p>编号：' + areaIdArray[idx] + '</p>' + '<p class="last">' + '<a class="btn">进入</a>' + '</p>' + '</li>');
            createObj.css("background-color", colorArray[colorIdx]);
            $("#poptip").append(createObj);
            colorIdx++;
            if (colorIdx == 4) {
                colorIdx = 0;
            }
        }
    }
    $("#LOADING_GREY_DIV").hide(); //隐藏登录蒙层
}

//连接关闭后的处理
function linkClose() {
    if (userType == USER_TYPE_CLIENT) {
        switch (mCurrentStatus) {
            case CLIENT_STATUS_AREA:
                break;
            case CLIENT_STATUS_QUEUE:
                $("#enterRoom h2").text("营业厅列表");
                startServiceTag = false;
                var finishCallFlag = false;
                if ($("#remoteVideoPos").html() != "") {
                    finishCallFlag = BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断
                    $("#Initiative_Call_Div").hide(); //隐藏主动呼叫层
                }
                if (!finishCallFlag) {
                    $('#localVideoPos').empty();
                    $('#remoteVideoPos').empty();
                    /**离开营业厅*/
                    var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");

                    //$('#videoCall').hide();
                    $('#enterRoom .contentArea').show();
                }

                break;
            case CLIENT_STATUS_QUEUEING:
                /**离开队列*/
                var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_CTRL_USERLEAVE, 0, 0, 0, 0, "");
                AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_QUEUE + "," + queueid + "," + ANYCHAT_QUEUE_CTRL_USERLEAVE + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);


                //离开营业厅
                var errorcode = BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");
                AddLog("BRAC_ObjectControl(" + ANYCHAT_OBJECT_TYPE_AREA + "," + hallbuinessNum + "," + ANYCHAT_AREA_CTRL_USERLEAVE + ",0,0,0,0,''" + ")=" + errorcode, LOG_TYPE_API);

                //$("#callLayer").hide();
                $("#enterRoom h2").text("营业厅列表");

                $("#poptip").show();
                $("#poptip li[areaId]").show();
                $('#poptip li[queueid]').hide(); //隐藏队列

                isShowReturnBtn(true);
                break;
            case CLIENT_STATUS_CHATTING:
                clearInterval(mRefreshVolumeTimer); // 清除实时音量显示计时器
                //$("#videoCall").hide(); //隐藏视频窗口
                isShowReturnBtn(true);
                $("#enterRoom h2").text("营业厅列表");
                $("#poptip").show();

                $('#poptip li[queueid]').hide(); //隐藏队列
                $("#poptip li[areaId]").show();

                break;
        }
    }

    if (userType == USER_TYPE_AGNET) {
        switch (mCurrentStatus) {
            case AGENT_STATUS_AREA:
                break;
            case AGENT_STATUS_SERVICE:
                var errorcode = BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_FINISH, mTargetUserId, 0, 0, 0, ""); 	// 挂断
                $("#Initiative_Call_Div").hide(); //隐藏主动呼叫层
                $('#enterRoom .contentArea').show();
                isShowReturnBtn(true);
                startServiceTag = false;
                break;
        }

    }

    systemOut();

}

//设置登录信息，包括用户名、服务器IP、服务器端口、应用ID
function setLoginInfo() {
    setCookie('username', $("#username").val(), 30);
    setCookie('ServerAddr', $("#ServerAddr").val(), 30);
    setCookie('ServerPort', $("#ServerPort").val(), 30);
    setCookie('AppGuid', $("#AppGuid").val(), 30);
    setCookie('askSelect', $("#askSelect").get(0).selectedIndex, 30);
    setCookie('PrioritySelect', $("#dwPrioritySelect").get(0).selectedIndex, 30);
}

//获取登录信息
function getLoginInfo() {
    $("#username").val(getCookie("username"))
    var serverIP = getCookie("ServerAddr");
    if (serverIP != "")
        $("#ServerAddr").val(serverIP);
    var serverPort = getCookie("ServerPort");
    if (serverPort != "")
        $("#ServerPort").val(serverPort);
    $("#AppGuid").val(getCookie("AppGuid"));
    $("#askSelect").get(0).selectedIndex = getCookie("askSelect");
    $("#dwPrioritySelect").get(0).selectedIndex = getCookie("PrioritySelect");
}

//获取cookie项的cookie值
function getCookie(c_name) {
    if (document.cookie.length > 0) {
        c_start = document.cookie.indexOf(c_name + "=");
        if (c_start != -1) {
            c_start = c_start + c_name.length + 1;
            c_end = document.cookie.indexOf(";", c_start);
            if (c_end == -1) c_end = document.cookie.length;
            return document.cookie.substring(c_start, c_end);
        }
    }
    return "";
}

//设置cookie
function setCookie(c_name, value, expiredays) {
    var exdate = new Date();
    exdate.setDate(exdate.getDate() + expiredays);
    document.cookie = c_name + "=" + value + ((expiredays == null) ? "" : ";expires=" + exdate.toGMTString());
}
