// JavaScript Document
var USER_ONLINE_STATUS=1;						// 用户上线
var USER_OFFLINE_STATUS=0;						// 用户下线

var USERINFO_NAME=1;							// 用户昵称信息
var USERINFO_IP=2;								// 用户IP地址信息


//创建在线好友图标
function CreateUserImage(type) {
    Getdmo("UserListContent").innerHTML = "";
    var OnLineUserList = BRAC_GetUserFriends(); // 获取所有好友
    if (type == "whole") { // 所有在线用户
        DisplayOnLineUser(mSelfUserId); // 在第一个位置创建自己的图标
        for (var i = 0; i < OnLineUserList.length; i++) {
            if (OnLineUserList[i] != mSelfUserId && BRAC_GetFriendStatus(OnLineUserList[i]) != 0)	// 只显示在线用户
                DisplayOnLineUser(OnLineUserList[i]);
        }
    }
    else { // 指定用户组在线用户
        for (var i = 0; i < OnLineUserList.length; i++) {
            var UserGroupID = GetUserGroupIdByUserId(OnLineUserList[i]);
            if (UserGroupID == mCurrentGroupNum && BRAC_GetFriendStatus(OnLineUserList[i]) != 0)	// 只显示在线用户
                DisplayOnLineUser(OnLineUserList[i]);
        }
    }
    //StartScroll("UserListScroll", "UserListSlider", "UserListContent", "UserListBaseLine");
}
//显示上线用户
function DisplayOnLineUser(userid) {
    var UserName = BRAC_GetUserInfo(userid,USERINFO_NAME); // 用户姓名
	var UserIp=BRAC_GetUserInfo(userid,USERINFO_IP); // 用户IP地址;
    var main_div = document.createElement("div");
    main_div.id = "UserID_" + userid;
    main_div.className = "OnLineUser_Div";

    var left_div = document.createElement("div");
    left_div.className = "UserImg_Holder";
    main_div.appendChild(left_div);

    var left_img = document.createElement("img");
    left_img.id = userid;
	var img_value=Math.abs(userid)%10;
    left_img.src = "./images/head/"+img_value+".gif";
    left_img.className = "UserImg";
    left_div.appendChild(left_img);

    var right_div = document.createElement("div");
    right_div.className = "UserInfo_Holder";
    main_div.appendChild(right_div);

    var right_name= document.createElement("div");
    right_name.className = "UserInfo";
    right_name.innerHTML = UserName;
    right_div.appendChild(right_name);
	
	var right_ip = document.createElement("div");
    right_ip.className = "UserInfo";
    right_ip.innerHTML = UserIp;
    right_div.appendChild(right_ip);
	
	var right_userId= document.createElement("div");
    right_userId.className = "UserInfo";
    right_userId.innerHTML = userid;
    right_div.appendChild(right_userId);
    
	//下载插件按钮鼠标划入划出时间
    main_div.onmouseover =	function () {	main_div.style.backgroundColor = "#8FBC8B";	}
    main_div.onmouseout =	function () {	main_div.style.backgroundColor = "#FAFADD";	}
	main_div.onclick=function () { VideoCallRequest(userid); }
    Getdmo("UserListContent").appendChild(main_div);
}

//清除离线用户
function removeOfflineUser(dwUserId)
{
	Getdmo("UserListContent").removeChild(Getdmo("UserID_" + dwUserId));
}

//会话提示信息
function ForSession(message) {
    var mBrowserWidth = document.body.offsetWidth; 				// 网页可见区域宽
    var mBrowserHeight = document.documentElement.clientHeight; //  网页可见区域高
    CenterPosition(mBrowserWidth, mBrowserHeight, "SessionPrompt_Div", 300, 170); //主动呼叫层垂直水平居中
    Getdmo("Shade_Div").style.display = "none";
    Getdmo("Initiative_Call_Div").style.display = "none";		// 隐藏正在呼叫层
	Getdmo("BeCalls_Div").style.display = "none";				// 隐藏被呼叫层
	Getdmo("advanceset_div").style.display = "none"; 			// 隐藏设置层
    Getdmo("VideoShowDiv").style.display = "none"; 				// 隐藏设置层
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
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,GV_ERR_SESSION_QUIT,0,0,"");  
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
	BRAC_VideoCallControl(BRAC_VIDEOCALL_EVENT_REPLY,mTargetUserId,GV_ERR_SESSION_REFUSE,0,0,"");  
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
		case GV_ERR_SUCCESS:
		    onSendVideoCallRequestSucess(dwUserId);
			break;
		case GV_ERR_SESSION_QUIT:
			ForSession("源用户主动放弃会话");
			break;
		case GV_ERR_SESSION_OFFLINE:
		    ForSession("目标用户不在线");
			break;
		case GV_ERR_SESSION_BUSY:
			ForSession("目标用户忙");
			break; 
		case GV_ERR_SESSION_REFUSE:
		 	ForSession("目标用户拒绝会话");
			break; 
		case GV_ERR_SESSION_TIMEOUT:
		 	ForSession("会话请求超时");
			break; 
		case GV_ERR_SESSION_DISCONNECT:
			ForSession("网络断线");
			break; 
		default:
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
	if(mRefreshVolumeTimer != -1)
		clearInterval(mRefreshVolumeTimer); // 清除实时音量显示计时器
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



