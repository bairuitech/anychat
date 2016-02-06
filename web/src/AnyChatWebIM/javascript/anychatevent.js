// AnyChat for Web SDK

/********************************************
 *				事件回调部分				*
 *******************************************/
 
 // 异步消息通知，包括连接服务器、登录系统、进入房间等消息
function OnAnyChatNotifyMessage(dwNotifyMsg, wParam, lParam) {
	switch(dwNotifyMsg) {
		case WM_GV_CONNECT:			OnAnyChatConnect(wParam, lParam);			break;
		case WM_GV_LOGINSYSTEM:		OnAnyChatLoginSystem(wParam, lParam);		break;
		case WM_GV_ENTERROOM:		OnAnyChatEnterRoom(wParam, lParam);			break;
		case WM_GV_ONLINEUSER:		OnAnyChatRoomOnlineUser(wParam, lParam);	break;
		case WM_GV_USERATROOM:		OnAnyChatUserAtRoom(wParam, lParam);		break;
		case WM_GV_LINKCLOSE:		OnAnyChatLinkClose(wParam, lParam);			break;
		case WM_GV_MICSTATECHANGE:	OnAnyChatMicStateChange(wParam, lParam);	break;
		case WM_GV_CAMERASTATE:		OnAnyChatCameraStateChange(wParam, lParam);	break;
		case WM_GV_P2PCONNECTSTATE:	OnAnyChatP2PConnectState(wParam, lParam);	break;
		case WM_GV_PRIVATEREQUEST:	OnAnyChatPrivateRequest(wParam, lParam);	break;
		case WM_GV_PRIVATEECHO:		OnAnyChatPrivateEcho(wParam, lParam);		break;
		case WM_GV_PRIVATEEXIT:		OnAnyChatPrivateExit(wParam, lParam);		break;
		case WM_GV_USERINFOUPDATE:	OnAnyChatUserInfoUpdate(wParam, lParam);	break;
		case WM_GV_FRIENDSTATUS:	OnAnyChatFriendStatus(wParam, lParam);		break;
		default:
			break;
	}
}

// 收到文字消息
function OnAnyChatTextMessage(dwFromUserId, dwToUserId, bSecret, lpMsgBuf, dwLen) {
    MessageFlicker(); // 按钮闪烁提示
    var TimeFormat = new Date();
    var ShowTime = TimeFormat.toLocaleTimeString();

    var time_div = document.createElement("div");
    time_div.className = "ReceiveMsgStyle";
    time_div.innerHTML = BRAC_GetUserName(dwFromUserId) + "  " + ShowTime;
    Getdmo("ReceiveMsg").appendChild(time_div);
    var content_div = document.createElement("div");
    content_div.style.width = "360px";
    content_div.style.margin = "0px 0px 0px 10px";
    content_div.innerHTML = Expression(lpMsgBuf, 1);
    Getdmo("ReceiveMsg").appendChild(content_div);

    ReceiveMsgBoxScroll();
}

// 收到透明通道传输数据
function OnAnyChatTransBuffer(dwUserId, lpBuf, dwLen) {

}

// 收到透明通道（扩展）传输数据
function OnAnyChatTransBufferEx(dwUserId, lpBuf, dwLen, wParam, lParam, dwTaskId) {

}

// 文件传输完成通知
function OnAnyChatTransFile(dwUserId, lpFileName, lpTempFilePath, dwFileLength, wParam, lParam, dwTaskId) {

}

// 系统音量改变通知
function OnAnyChatVolumeChange(device, dwCurrentVolume) {

}

// 收到服务器发送的SDK Filter数据
function OnAnyChatSDKFilterData(lpBuf, dwLen) {

}

// 收到录像或拍照完成事件
function OnAnyChatRecordSnapShot(dwUserId, lpFileName, dwParam, bRecordType) {

}

// 收到录像或拍照完成事件（扩展）
function OnAnyChatRecordSnapShotEx(dwUserId, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr) {

}


/********************************************
 *		AnyChat SDK核心业务流程				*
 *******************************************/
 
// 客户端连接服务器，bSuccess表示是否连接成功，errorcode表示出错代码
function OnAnyChatConnect(bSuccess, errorcode) {
	if(errorcode == 0)
		prompt("连接服务器成功");
}

// 客户端登录系统，dwUserId表示自己的用户ID号，errorcode表示登录结果：0 成功，否则为出错代码，参考出错代码定义
function OnAnyChatLoginSystem(dwUserId, errorcode) {
    mSelfUserId = dwUserId;
    GoToHall(); // 显示大厅
    initialize();
    document.body.style.backgroundColor = "#58a8c9";
}

// 客户端进入房间，dwRoomId表示所进入房间的ID号，errorcode表示是否进入房间：0成功进入，否则为出错代码
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
	// 打开本地音频、视频
	BRAC_UserCameraControl(-1, 1);
	BRAC_UserSpeakControl(-1, 1);
	// 请求对方音频、视频
	BRAC_UserCameraControl(mTargetUserId, 1);
	BRAC_UserSpeakControl(mTargetUserId, 1);
	
    CreateWideScreen(); // 设置视频显示位置
    $("#GetExpression").load("./sub/emote.html"); //颜色面板加载页面
}

// 收到当前房间的在线用户信息，进入房间后触发一次，dwUserCount表示在线用户数（包含自己），dwRoomId表示房间ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {

}

// 用户进入（离开）房间，dwUserId表示用户ID号，bEnterRoom表示该用户是进入（1）或离开（0）房间
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {
	if(dwUserId == mTargetUserId && bEnterRoom != 0) {
		
		// 请求对方音频、视频
		BRAC_UserCameraControl(mTargetUserId, 1);
		BRAC_UserSpeakControl(mTargetUserId, 1);
	}
}

// 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，reason表示连接断开的原因
function OnAnyChatLinkClose(reason, errorcode) {
	BRAC_Logout();	// 关闭自动重连
	GoToLogin();	// 显示登录界面
}

// 用户的音频设备状态变化消息，dwUserId表示用户ID号，State表示该用户是否已打开音频采集设备（0：关闭，1：打开）
function OnAnyChatMicStateChange(dwUserId, State) {

}

// 用户摄像头状态发生变化，dwUserId表示用户ID号，State表示摄像头的当前状态（0：没有摄像头，1：有摄像头但没有打开，2：打开）
function OnAnyChatCameraStateChange(dwUserId, State) {

}

// 本地用户与其它用户的P2P网络连接状态发生变化，dwUserId表示其它用户ID号，State表示本地用户与其它用户的当前P2P网络连接状态（0：没有连接，1：仅TCP连接，2：仅UDP连接，3：TCP与UDP连接）
function OnAnyChatP2PConnectState(dwUserId, State) {

}

// 用户发起私聊请求，dwUserId表示发起者的用户ID号，dwRequestId表示私聊请求编号，标识该请求
function OnAnyChatPrivateRequest(dwUserId, dwRequestId) {

}

// 用户回复私聊请求，dwUserId表示回复者的用户ID号，errorcode为出错代码
function OnAnyChatPrivateEcho(dwUserId, errorcode) {

}

// 用户退出私聊，dwUserId表示退出者的用户ID号，errorcode为出错代码
function OnAnyChatPrivateExit(dwUserId, errorcode) {

}

// 视频通话消息通知回调函数
function OnAnyChatVideoCallEvent(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr) {
//	AddLog("OnAnyChatVideoCallEvent(dwEventType=" + dwEventType + ", dwUserId=" + dwUserId + ", dwErrorCode=" + dwErrorCode + ", dwFlags=" + dwFlags + ", dwParam=" + dwParam + ", szUserStr=" + szUserStr + ")", LOG_TYPE_EVENT);
	switch(dwEventType) {
		case BRAC_VIDEOCALL_EVENT_REQUEST:	// 呼叫请求
			 $("#Shade_Div").show();
			$("#BeCalls_Div").show();
			 $("#BeCalls_Div_Content").html("收到用户  " + BRAC_GetUserName(dwUserId) + "  会话邀请<br />      是否同意?");
			 mTargetUserId = dwUserId;
		break;
		case BRAC_VIDEOCALL_EVENT_REPLY:	// 呼叫请求回复
				  if (dwErrorCode == ICS_RETCODE_SESSION_REJECT) {
					 ForSession("对方拒绝会话邀请...");
				 }
				 else if (dwErrorCode == ICS_RETCODE_SESSION_BUSY) {
					ForSession("用户正在会话中...");
				 }
				  else if (dwErrorCode == ICS_RETCODE_SESSION_CANCEL) {
					  ForSession("用户取消会话邀请...");
					 Getdmo("BeCalls_Div").style.display = "none";
				}
		break;
		case BRAC_VIDEOCALL_EVENT_START:	// 视频呼叫会话开始事件
			BRAC_EnterRoom(dwParam, "", 0);
			mMissionQuantity = 0;
			Getdmo("ReceiveMsg").innerHTML = "";
			Getdmo("Initiative_Call_Div").style.display = "none";
			Getdmo("HallDiv").style.display = "none";
			chatuserid = dwUserId;
			$("#VideoShowDiv").show();
			$("#mTargetPhoto").html("<img src='" + GetUserImageAddrById(dwUserId, 50) + "' alt='用户头像' style='height:65px;width:65px;' />");
			$("#mTargetInfo").html("目标的ID：" + dwUserId + "<br />目标名称：" + BRAC_GetUserName(dwUserId) + "<br />所属分组：" + BRAC_GetGroupName(GetUserGroupIdByUserId(dwUserId)) + "<br />");
			//    ComboboxInint();
			InitAdvanced();
			ReceiveMsgBoxScroll();
		break;
		case BRAC_VIDEOCALL_EVENT_FINISH:	// 挂断（结束）呼叫会话
			BackToHall();
		break;
		default:
			break;
	}
	
	
	
}

var bFirstUserInfoUpdate = true;
// 用户信息更新通知，dwUserId表示用户ID号，dwType表示更新类别
function OnAnyChatUserInfoUpdate(dwUserId, dwType) {
	if(bFirstUserInfoUpdate) {
		bFirstUserInfoUpdate = false;
		// 本人头像信息显示
		var MinePic = document.createElement("img");
		MinePic.src = GetUserImageAddrById(mSelfUserId, 50);
		MinePic.alt = "用户图像";
		MinePic.id = "MyPhoto";
		Getdmo("mSelfPhoto").appendChild(MinePic);
		Getdmo("mSelfInfo").innerHTML = "<br />用户ID: " + mSelfUserId +
								 "<br />用户名: " + BRAC_GetUserName(mSelfUserId) +
								 "<br />所属组: " + BRAC_GetGroupName(GetUserGroupIdByUserId(mSelfUserId));
		CreateUserImage("whole");
	}
	// 刷新用户分组
	Getdmo("GroupContent").innerHTML = "";
	UserGroupDiv(0, "在线用户");
	mGroupList = BRAC_GetUserGroups();
	for (var i = 0; i < mGroupList.length; i++) {
		var GroupName = BRAC_GetGroupName(mGroupList[i]);
		UserGroupDiv(mGroupList[i], GroupName);
	}
	OpenGroup(0);
	StartScroll("GroupListScroll", "GroupSlider", "GroupContent", "GroupBaseLine");
}

// 好友在线状态变化，dwUserId表示好友用户ID号，dwStatus表示用户的当前活动状态：0 离线， 1 上线
function OnAnyChatFriendStatus(dwUserId, dwStatus) {

//	AddLog("OnAnyChatFriendStatus(dwUserId=" + dwUserId + ", dwStatus=" + dwStatus + ")", LOG_TYPE_EVENT);
	if (dwStatus == 1) {	// 上线
		DisplayOnLineUser(dwUserId);
	} else { 				// 下线
		if (Getdmo("UserID_"+dwUserId) != null)
			Getdmo("UserListContent").removeChild(Getdmo("UserID_"+dwUserId));
	}
}