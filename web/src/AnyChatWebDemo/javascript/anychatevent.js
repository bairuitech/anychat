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
	DisplayTextMessage(dwFromUserId, lpMsgBuf);
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
	AddLog("OnAnyChatConnect(errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
    if (errorcode == 0) {
		
    }
    else {
		DisplayLoadingDiv(false);
    }
}

// 客户端登录系统，dwUserId表示自己的用户ID号，errorcode表示登录结果：0 成功，否则为出错代码，参考出错代码定义
function OnAnyChatLoginSystem(dwUserId, errorcode) {
	DisplayLoadingDiv(false);
	AddLog("OnAnyChatLoginSystem(userid=" + dwUserId + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
    if (errorcode == 0) {
		mSelfUserId = dwUserId;	
		ShowHallDiv(true);
    } else {
		ShowHallDiv(false);
    }
}

// 客户端进入房间，dwRoomId表示所进入房间的ID号，errorcode表示是否进入房间：0成功进入，否则为出错代码
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
    DisplayLoadingDiv(false);
	AddLog("OnAnyChatEnterRoom(roomid=" + dwRoomId + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
    if (errorcode == 0) {
        ShowRoomDiv(true);
		RoomUserListControl(mSelfUserId, true);		// 将自己插入用户列表
        BRAC_UserCameraControl(mSelfUserId, 1); 	// 打开本地视频
        BRAC_UserSpeakControl(mSelfUserId, 1); 		// 打开本地语音

		ShowNotifyMessage("Welcome use AnyChat, successfully enter the room:" + dwRoomId, NOTIFY_TYPE_SYSTEM);
        // 设置本地视频显示位置
        BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"), "ANYCHAT_VIDEO_LOCAL");
        // 设置远程视频显示位置（没有关联到用户，只是占位置）
        BRAC_SetVideoPos(0, GetID("AnyChatRemoteVideoDiv"), "ANYCHAT_VIDEO_REMOTE");

        mRefreshVolumeTimer = setInterval(function () {
            GetID("LocalAudioVolume").style.width = GetID("AnyChatLocalVideoDiv").offsetHeight * BRAC_QueryUserStateInt(mSelfUserId, BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";
			if(mTargetUserId != -1)
				GetID("RemoteAudioVolume").style.width = GetID("AnyChatRemoteVideoDiv").offsetHeight * BRAC_QueryUserStateInt(mTargetUserId, BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";
			else
				GetID("RemoteAudioVolume").style.width = "0px";
        }, 100);
    } else {

    }
}

// 收到当前房间的在线用户信息，进入房间后触发一次，dwUserCount表示在线用户数（包含自己），dwRoomId表示房间ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {
	AddLog("OnAnyChatRoomOnlineUser(count=" + dwUserCount + ", roomid=" + dwRoomId + ")", LOG_TYPE_EVENT);
	var useridlist = BRAC_GetOnlineUser();
	for (var i = 0; i < useridlist.length; i++) {
		RoomUserListControl(useridlist[i], true);
    }
	// 请求其中一个用户的音视频
	for (var k=0; k<useridlist.length; k++) {
		if(useridlist[k] == mSelfUserId)
			continue;
		RequestOtherUserVideo(useridlist[k]);
		break;
	}
}

// 用户进入（离开）房间，dwUserId表示用户ID号，bEnterRoom表示该用户是进入（1）或离开（0）房间
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {
	AddLog("OnAnyChatUserAtRoom(userid=" + dwUserId + ", benter=" + bEnterRoom + ")", LOG_TYPE_EVENT);
	RoomUserListControl(dwUserId, bEnterRoom ? true : false);
    if (bEnterRoom == 1) {
		ShowNotifyMessage(BRAC_GetUserName(dwUserId) +"&nbspenter room!", NOTIFY_TYPE_NORMAL);
		if(mTargetUserId == -1)						// 默认打开一个用户的音视频
			RequestOtherUserVideo(dwUserId);
    }
    else {
		ShowNotifyMessage(BRAC_GetUserName(dwUserId) +"&nbspleave room!", NOTIFY_TYPE_NORMAL);
        if (dwUserId == mTargetUserId) {			// 当前被请求的用户离开房间，默认请求房间中其它用户的音视频
			var bRequestOtherUser = false;
			var useridlist = BRAC_GetOnlineUser();
			for (var k=0; k<useridlist.length; k++) {
				if(useridlist[k] == mSelfUserId)
				continue;
				RequestOtherUserVideo(useridlist[k]);
				bRequestOtherUser = true;
				break;
			}
			if(!bRequestOtherUser) {				// 如果没有其它用户在线，则清除状态
				mTargetUserId = -1;
				BRAC_SetVideoPos(0, GetID("AnyChatRemoteVideoDiv"), "ANYCHAT_VIDEO_REMOTE");
			}
		}
    }
    DisplayScroll("room_div_userlist");
}

// 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，reason表示连接断开的原因
function OnAnyChatLinkClose(reason, errorcode) {
	AddLog("OnAnyChatLinkClose(reason=" + reason + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
	DisplayLoadingDiv(false);
	ShowRoomDiv(false);
	ShowHallDiv(false);
	ShowLoginDiv(true);
}

// 用户的音频设备状态变化消息，dwUserId表示用户ID号，State表示该用户是否已打开音频采集设备（0：关闭，1：打开）
function OnAnyChatMicStateChange(dwUserId, State) {

}

// 用户摄像头状态发生变化，dwUserId表示用户ID号，State表示摄像头的当前状态（0：没有摄像头，1：有摄像头但没有打开，2：打开）
function OnAnyChatCameraStateChange(dwUserId, State) {
    if (State == 0) GetID(dwUserId + "_CameraTag").src = "";
    if (State == 1) GetID(dwUserId + "_CameraTag").src = "./images/advanceset/camera_false.png";
    if (State == 2) GetID(dwUserId + "_CameraTag").src = "./images/advanceset/camera_true.png";
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
	AddLog("OnAnyChatVideoCallEvent(dwEventType=" + dwEventType + ", dwUserId=" + dwUserId + ", dwErrorCode=" + dwErrorCode + ", dwFlags=" + dwFlags + ", dwParam=" + dwParam + ", szUserStr=" + szUserStr + ")", LOG_TYPE_EVENT);
	
}

// 用户信息更新通知，dwUserId表示用户ID号，dwType表示更新类别
function OnAnyChatUserInfoUpdate(dwUserId, dwType) {
	AddLog("OnAnyChatUserInfoUpdate(dwUserId=" + dwUserId + ", dwType=" + dwType + ")", LOG_TYPE_EVENT);
}

// 好友在线状态变化，dwUserId表示好友用户ID号，dwStatus表示用户的当前活动状态：0 离线， 1 上线
function OnAnyChatFriendStatus(dwUserId, dwStatus) {
	AddLog("OnAnyChatFriendStatus(dwUserId=" + dwUserId + ", dwStatus=" + dwStatus + ")", LOG_TYPE_EVENT);
	
}

