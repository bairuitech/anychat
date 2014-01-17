// JavaScript Document

	// 常见出错代码定义
    var BRAC_ERRORCODE_SUCCESS			= 0;	 ///< 没有错误
    var BRAC_ERRORCODE_SESSION_QUIT		= 100101;///< 源用户主动放弃会话
    var BRAC_ERRORCODE_SESSION_OFFLINE	= 100102;///< 目标用户不在线
    var BRAC_ERRORCODE_SESSION_BUSY		= 100103;///< 目标用户忙
    var BRAC_ERRORCODE_SESSION_REFUSE	= 100104;///< 目标用户拒绝会话
    var BRAC_ERRORCODE_SESSION_TIMEOUT	= 100105;///< 会话请求超时
    var BRAC_ERRORCODE_SESSION_DISCONNECT=100106;///< 网络断线
//会话提示信息
function ForSession(message) {
    var mBrowserWidth = document.body.offsetWidth; // 网页可见区域宽
    var mBrowserHeight = document.documentElement.clientHeight; //  网页可见区域高
    CenterPosition(mBrowserWidth, mBrowserHeight, "SessionPrompt_Div", 300, 170); //主动呼叫层垂直水平居中
    Getdmo("Shade_Div").style.display = "none";
    Getdmo("Initiative_Call_Div").style.display = "none";// 隐藏正在呼叫层
	Getdmo("BeCalls_Div").style.display = "none";// 隐藏被呼叫层
	Getdmo("advanceset_div").style.display = "none"; // 隐藏设置层
    Getdmo("VideoShowDiv").style.display = "none"; // 隐藏设置层
	mTargetUserId=0;
    Getdmo("SessionPrompt_Div").style.color = "White";
    Getdmo("SessionPrompt_Div").innerHTML = message;
    $("#SessionPrompt_Div").fadeTo("slow", 1);
        setTimeout("$('#SessionPrompt_Div').fadeTo('slow', 0 , BusyDivOut)", 2000);
    //$("#SessionPrompt_Div").css("left", (document.body.offsetWidth - 600) / 2 + "px");
}

//取消主动呼叫
function CancelCall() {
    $("#Shade_Div").hide();
    $("#Initiative_Call_Div").hide();
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,BRAC_ERRORCODE_SESSION_QUIT,0,0,"");  
    ForSession("取消呼叫...");
}
//呼叫用户双击
function VideoCallRequest(ID) {
    if (mSelfUserId == ID)
	    ForSession("不能呼叫自己...");
    else {
        mTargetUserId = ID;
		BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REQUEST,mTargetUserId,0,0,0,"");  // 向指定的用户发送会话邀请
    }
}
//同意会话
function AcceptRequestBtnClick() {
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,0,0,0,"");  
    $("#BeCalls_Div").hide();
}
//拒绝会话
function RejectRequestBtnClick() {
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,BRAC_ERRORCODE_SESSION_REFUSE,0,0,"");  
    $("#Shade_Div").hide();
    $("#BeCalls_Div").hide();
    ForSession("拒绝对方请求...");
}
//收到视频呼叫请求
function onVideoCallControlRequest(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr)
{
	 var UserName = BRAC_GetUserInfo(dwUserId,USERINFO_NAME); // 用户姓名
	 $("#Shade_Div").show();
	 $("#BeCalls_Div").show();
	 $("#BeCalls_Div_Content").html("收到用户  " +UserName + "  会话邀请<br />      是否同意?");
	 mTargetUserId = dwUserId;
}

//视频呼叫请求回复
function onVideoCallControlReply(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr)
{
	
	switch(dwErrorCode)
	{
		case BRAC_ERRORCODE_SUCCESS:
		    onSendVideoCallRequestSucess(dwUserId);
			break;
		case BRAC_ERRORCODE_SESSION_QUIT:
			ForSession("源用户主动放弃会话");
			break;
		case BRAC_ERRORCODE_SESSION_OFFLINE:
		    ForSession("目标用户不在线");
			break;
		case BRAC_ERRORCODE_SESSION_BUSY:
			ForSession("目标用户忙");
			break; 
		case BRAC_ERRORCODE_SESSION_REFUSE:
		 	ForSession("目标用户拒绝会话");
			break; 
		case BRAC_ERRORCODE_SESSION_TIMEOUT:
		 	ForSession("会话请求超时");
			break; 
		case BRAC_ERRORCODE_SESSION_DISCONNECT:
			ForSession("网络断线");
			break; 
		
	}
}

//通话开始
function onVideoCallControlStart(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr)
{
	BRAC_EnterRoom(dwParam, "", 0);
	Getdmo("Initiative_Call_Div").style.display = "none";
	Getdmo("hall_div").style.display = "none";
	$("#VideoShowDiv").show();
}

//视频通话结束
function onVideoCallControlFinish(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr)
{
	BRAC_LeaveRoom(-1);
    ForSession("会话结束..."); // 提示层
	ShowHallDiv(true); // 显示大厅
    //clearInterval(mRefreshVolumeTimer); // 关闭语音音量显示
}

//视频呼叫请求发送成功
function onSendVideoCallRequestSucess(mTargetUserId)
{
	
	var UserName = BRAC_GetUserInfo(mTargetUserId,USERINFO_NAME); // 用户姓名
    UserName = UserName.fontcolor("Red");
    Getdmo("Initiative_Call_Div_Content").innerHTML = "正在呼叫" + UserName + "用户，等待对方响应<br /><img src='./images/Others/LoadImg.gif'    style='width: 145px;height:30px;' />";
    Getdmo("Shade_Div").style.display = "block";
    Getdmo("Initiative_Call_Div").style.display = "block";
}



function BusyDivOut() {
    $("#SessionPrompt_Div").css("top", "500%");
}



