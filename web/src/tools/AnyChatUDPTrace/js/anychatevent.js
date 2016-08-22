// AnyChat for Web SDK

/*******************************************************************************
 * 事件回调部分 *
 ******************************************************************************/

// 异步消息通知，包括连接服务器、登录系统、进入房间等消息
function OnAnyChatNotifyMessage(dwNotifyMsg, wParam, lParam) {
	switch (dwNotifyMsg) {
	case WM_GV_CONNECT:
		OnAnyChatConnect(wParam, lParam);
		break;
	case WM_GV_LOGINSYSTEM:
		OnAnyChatLoginSystem(wParam, lParam);
		break;
	case WM_GV_ENTERROOM:
		OnAnyChatEnterRoom(wParam, lParam);
		break;
	case WM_GV_ONLINEUSER:
		OnAnyChatRoomOnlineUser(wParam, lParam);
		break;
	case WM_GV_USERATROOM:
		OnAnyChatUserAtRoom(wParam, lParam);
		break;
	case WM_GV_LINKCLOSE:
		OnAnyChatLinkClose(wParam, lParam);
		break;
	case WM_GV_MICSTATECHANGE:
		OnAnyChatMicStateChange(wParam, lParam);
		break;
	case WM_GV_CAMERASTATE:
		OnAnyChatCameraStateChange(wParam, lParam);
		break;
	case WM_GV_P2PCONNECTSTATE:
		OnAnyChatP2PConnectState(wParam, lParam);
		break;
	case WM_GV_PRIVATEREQUEST:
		OnAnyChatPrivateRequest(wParam, lParam);
		break;
	case WM_GV_PRIVATEECHO:
		OnAnyChatPrivateEcho(wParam, lParam);
		break;
	case WM_GV_PRIVATEEXIT:
		OnAnyChatPrivateExit(wParam, lParam);
		break;
	case WM_GV_USERINFOUPDATE:
		OnAnyChatUserInfoUpdate(wParam, lParam);
		break;
	case WM_GV_FRIENDSTATUS:
		OnAnyChatFriendStatus(wParam, lParam);
		break;
	case WM_GV_VIDEOSIZECHG:
		onAnyChatVideoSizeChange(wParam, lParam);
		break;
	default:
		break;
	}
}
function onAnyChatVideoSizeChange(wParam, lParam) {

}

// 收到文字消息receiveCount
function OnAnyChatTextMessage(dwFromUserId, dwToUserId, bSecret, lpMsgBuf, dwLen) {

}

// 收到透明通道传输数据
function OnAnyChatTransBuffer(dwUserId, lpBuf, dwLen) {
	// alert("收到:"+dwUserId+"用户发送过来的透明通道数据数据："+lpBuf);
}

// 收到透明通道（扩展）传输数据
function OnAnyChatTransBufferEx(dwUserId, lpBuf, dwLen, wParam, lParam, dwTaskId) {
	// alert("收到:"+dwUserId+"用户发送过来的扩展透明通道数据数据："+lpBuf);
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

// 收到录像或拍照完成事件（扩展：增加errorcode）
function OnAnyChatRecordSnapShotEx2(dwUserId, dwErrorCode, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr) {

}

/*******************************************************************************
 * AnyChat SDK核心业务流程 *
 ******************************************************************************/

// 客户端连接服务器，bSuccess表示是否连接成功，errorcode表示出错代码
function OnAnyChatConnect(bSuccess, errorcode) {
}

// 客户端登录系统，dwUserId表示自己的用户ID号，errorcode表示登录结果：0 成功，否则为出错代码，参考出错代码定义
function OnAnyChatLoginSystem(dwUserId, errorcode) {
	
	if (errorcode == 0) {
		mSelfUserId = dwUserId;
	}

}

// 客户端进入房间，dwRoomId表示所进入房间的ID号，errorcode表示是否进入房间：0成功进入，否则为出错代码
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
	var ip=BRAC_QueryUserStateString(mSelfUserId,BRAC_USERSTATE_INTERNETIP);
	if (errorcode == 0) {
		ShowLoginDiv(false);
		ShowUDPBox(true);
		// 设置本地视频显示位置
//		BRAC_SetVideoPos(mSelfUserId, GetID("AnyChatLocalVideoDiv"),
//				"ANYCHAT_VIDEO_LOCAL");
		
		GetID("serverIP").innerHTML=mDefaultServerAddr;
		getIp(mDefaultServerAddr,"serverLocaltion");
		
		if(GetID("reciveRadio").checked){
			
			GetID("hidden").style.display="none";
			GetID("UDP_control").style.display="none";
			GetID("otherUser").style.display="block";
			controller(true);
			GetID("remoteName").innerHTML=BRAC_GetUserName(mSelfUserId);
			GetID("remoteIP").innerHTML=ip;
			getIp(ip,"remotelocaltion");
			setInterval(function() {
				var senduserid = BRAC_GetSDKOptionInt(167);
				var senduserip=BRAC_QueryUserStateString(senduserid,BRAC_USERSTATE_INTERNETIP);
				//console.log(senduserid);
				senduserid==""?"":GetID("sendName").innerHTML=BRAC_GetUserName(senduserid);
				GetID("sendIP").innerHTML=senduserip;
				getIp(senduserip,"sendLocaltion");
				},1000);
			
		}
		
		if(GetID("sendRadio").checked){
			GetID("hidden").style.display="block";
			GetID("otherUser").style.display="none";
  		GetID("UDP_control").style.display="block";
			GetID("sendName").innerHTML=BRAC_GetUserName(mSelfUserId);
			GetID("sendIP").innerHTML=ip;
			getIp(ip,"sendLocaltion");
			
		}
		} 
		DisplayLoadingDiv(false);
	
}

// 收到当前房间的在线用户信息，进入房间后触发一次，dwUserCount表示在线用户数（包含自己），dwRoomId表示房间ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {

}

// 用户进入（离开）房间，dwUserId表示用户ID号，bEnterRoom表示该用户是进入（1）或离开（0）房间
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {

}

// 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，reason表示连接断开的原因
function OnAnyChatLinkClose(reason, errorcode) {
	ShowLoginDiv(true);
	ShowUDPBox(false);
	alert("跟视频服务器连接断开，错误代码是" + errorcode + "正在尝试重连，请检测网络");

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

}

// 用户信息更新通知，dwUserId表示用户ID号，dwType表示更新类别
function OnAnyChatUserInfoUpdate(dwUserId, dwType) {

}

// 好友在线状态变化，dwUserId表示好友用户ID号，dwStatus表示用户的当前活动状态：0 离线， 1 上线
function OnAnyChatFriendStatus(dwUserId, dwStatus) {

}
