// AnyChat for Web SDK

/*******************************************************************************
 * 事件回调部分 *
 ******************************************************************************/
var type,videoBitrate,audioBitrate;
// 异步消息通知，包括连接服务器、登录系统、进入房间等消息
function OnAnyChatNotifyMessage(dwNotifyMsg, wParam, lParam) {
	switch (dwNotifyMsg) {
	case WM_GV_CONNECT:
		OnAnyChatConnect(wParam, lParam);
		break;// 连接
	case WM_GV_LOGINSYSTEM:
		OnAnyChatLoginSystem(wParam, lParam);
		break;// 登录系统
	case WM_GV_ENTERROOM:
		OnAnyChatEnterRoom(wParam, lParam);
		break;// 进入房间
	case WM_GV_ONLINEUSER:
		OnAnyChatRoomOnlineUser(wParam, lParam);
		break;// 线上用户
	case WM_GV_USERATROOM:
		OnAnyChatUserAtRoom(wParam, lParam);
		break;// 在房间的用户
	case WM_GV_LINKCLOSE:
		OnAnyChatLinkClose(wParam, lParam);
		break;// 连接关闭
	case WM_GV_MICSTATECHANGE:
		OnAnyChatMicStateChange(wParam, lParam);
		break;// 改变话筒状态
	case WM_GV_CAMERASTATE:
		OnAnyChatCameraStateChange(wParam, lParam);
		break;// 摄像头状态
	case WM_GV_P2PCONNECTSTATE:
		OnAnyChatP2PConnectState(wParam, lParam);
		break;// p2p连接状态
	case WM_GV_PRIVATEREQUEST:
		OnAnyChatPrivateRequest(wParam, lParam);
		break;// 私有请求
	case WM_GV_PRIVATEECHO:
		OnAnyChatPrivateEcho(wParam, lParam);
		break;// 私有输出
	case WM_GV_PRIVATEEXIT:
		OnAnyChatPrivateExit(wParam, lParam);
		break;// 私有离开
	case WM_GV_USERINFOUPDATE:
		OnAnyChatUserInfoUpdate(wParam, lParam);
		break;// 用户信息更新
	case WM_GV_FRIENDSTATUS:
		OnAnyChatFriendStatus(wParam, lParam);
		break;// 友人状态
	default:
		break;
	}
}

// 收到文字消息
function OnAnyChatTextMessage(dwFromUserId, dwToUserId, bSecret, lpMsgBuf,dwLen) {
}

// 收到透明通道传输数据
function OnAnyChatTransBuffer(dwUserId, lpBuf, dwLen) {

}

// 收到透明通道（扩展）传输数据
function OnAnyChatTransBufferEx(dwUserId, lpBuf, dwLen, wParam, lParam,dwTaskId) {

}

// 文件传输完成通知
function OnAnyChatTransFile(dwUserId, lpFileName, lpTempFilePath, dwFileLength,wParam, lParam, dwTaskId) {

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
function OnAnyChatRecordSnapShotEx(dwUserId, lpFileName, dwElapse, dwFlags,dwParam, lpUserStr) {

}

/*******************************************************************************
 * AnyChat SDK核心业务流程 *
 ******************************************************************************/

// 客户端连接服务器，bSuccess表示是否连接成功，errorcode表示出错代码
function OnAnyChatConnect(bSuccess, errorcode) {
	if (errorcode == 0) {
//		alert("SERVER CONNECT SUCCESS!");
	} else {
//		alert("SERVER CONNECT False!");
	}
}

// 客户端登录系统，dwUserId表示自己的用户ID号，errorcode表示登录结果：0 成功，否则为出错代码，参考出错代码定义
function OnAnyChatLoginSystem(dwUserId, errorcode) {
	if (errorcode == 0) {
		AddLog("客户端登录系统成功,dwUserId="+dwUserId, LOG_TYPE_NORMAL);
	    if (userType == 2) {//客服
	        currentAgentID = dwUserId;
			dwAgentFlags=ANYCHAT_OBJECT_FLAGS_AGENT;//坐席标识
		}else if(userType==1){
			dwAgentFlags=0;//客户
		}
			mSelfUserId = dwUserId;	
			dwPriority = parseInt($("#dwPrioritySelect option:selected").val());
			//身份信息设置
			InitClientObjectInfo(mSelfUserId,dwAgentFlags,dwPriority);
	} else {
		ForSession("Client logon failure!", true);
		AddLog("客户端登录系统失败,dwUserId="+dwUserId, LOG_TYPE_ERROR);
	}
}

// 客户端进入房间，dwRoomId表示所进入房间的ID号，errorcode表示是否进入房间：0成功进入，否则为出错代码
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
	if (errorcode == 0) {
		AddLog("客户端进入房间成功,dwRoomId="+dwRoomId, LOG_TYPE_NORMAL);
		if (userType == 2) {
			
		} else if (userType ==1) {
			/**客服姓名*/
			var name1 = BRAC_GetUserInfo(mTargetUserId,USERINFO_NAME); 
			/**个人姓名*/
			var myName = BRAC_GetUserInfo(mSelfUserId,USERINFO_NAME);
			$("#videoCallContent").html('<div style="width: 530px;float:left;"><b style="color:orange;">客服名称：</b>'+name1+'</div><div id="remoteVideoPos" style="float: left;"></div><div style="padding-left:540px;"><b style="color:orange;">客户姓名：</b>'+myName+'</div><div id="localVideoPos" style="width: 380px;height: 285px;float: right;margin-left: 10px;"></div><button id="hangUp" class="buttonCls hangUp">中 止 视 频 通 话</button><div id="localAudioVolume" style="position: absolute;bottom: 130px;left: 555px;"></div><div id="remoteAudioVolume" style="bottom: 13px;"></div>');//填充视频会话层
			$("#videoCall").show();
			setMarTop($('#videoCall').outerHeight());
			$("#callLayer").hide();//隐藏等待信息弹出层
		}
		//打开本地视频
		startVideo(mSelfUserId, GetID("localVideoPos"), "ANYCHAT_VIDEO_LOCAL",1);
		setVolumeTimer();//设置音量感应
		
	}else{
		AddLog("客户端进入房间失败,dwRoomId="+dwRoomId, LOG_TYPE_ERROR);
	}
}

// 收到当前房间的在线用户信息，进入房间后触发一次，dwUserCount表示在线用户数（包含自己），dwRoomId表示房间ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {
	//请求对方视频
	startVideo(mTargetUserId, GetID("remoteVideoPos"), "ANYCHAT_VIDEO_REMOTE",1);
}

// 用户进入（离开）房间，dwUserId表示用户ID号，bEnterRoom表示该用户是进入（1）或离开（0）房间
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {
	//请求对方视频
		if (bEnterRoom == 1) {
			AddLog("用户进入房间,dwUserId="+dwUserId, LOG_TYPE_NORMAL);
			//请求对方视频
			startVideo(mTargetUserId, GetID("remoteVideoPos"), "ANYCHAT_VIDEO_REMOTE",1);
			if(userType == 1){
				
			}
		} else {
			AddLog("用户离开房间,dwUserId="+dwUserId, LOG_TYPE_NORMAL);
			if (userType == 2) {
				if (dwUserId == mTargetUserId) { // 当前被请求的用户离开房间
					
					/**客服结束服务*/
					BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AGENT, mSelfUserId, ANYCHAT_AGENT_CTRL_FINISHSERVICE, 0,0,0,0,"");	

					mTargetUserId=-1;
					$("#remoteVideoPos").text("");//设置远程视频区域为空
					$("#clientList iframe").hide();
					$("#remoteAudioVolume").css('width',0);//设置远程音量条为0
					/**关闭视频操作*/
					BRAC_UserCameraControl(dwUserId, 0); 
					/**关闭语音操作*/
					BRAC_UserSpeakControl(dwUserId, 0); 
				}
			}
			if(mTargetUserId==dwUserId)
				BRAC_LeaveRoom(roomNum);
		}
	
}

// 网络连接已关闭，该消息只有在客户端连接服务器成功之后，网络异常中断之时触发，reason表示连接断开的原因
function OnAnyChatLinkClose(reason, errorcode) {
	ForSession("网络异常中断!请检查网络，reason【 " + reason + " 】,errorcode【 " + errorcode + " 】,请联系相关工作人员!",true);
	AddLog("网络异常中断!请检查网络，reason【 " + reason + " 】,errorcode【 " + errorcode + " 】,请联系相关工作人员!", LOG_TYPE_ERROR);
	GetID('LOADING_GREY_DIV').style.display='none';
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
function OnAnyChatVideoCallEvent(dwEventType, dwUserId, dwErrorCode, dwFlags,dwParam, szUserStr) {
	switch(dwEventType)
	{
		case BRAC_VIDEOCALL_EVENT_REQUEST:
			//收到视频呼叫请求 
			onVideoCallControlRequest(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
			break;
		case BRAC_VIDEOCALL_EVENT_REPLY:
			////视频呼叫请求回复 
		    onVideoCallControlReply(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
			break;
		case BRAC_VIDEOCALL_EVENT_START:
			//通话开始 
			onVideoCallControlStart(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
			break;
		case BRAC_VIDEOCALL_EVENT_FINISH:
			//视频通话结束 
		     onVideoCallControlFinish(dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr);
			break; 
		
	}
}

// 用户信息更新通知，dwUserId表示用户ID号，dwType表示更新类别
function OnAnyChatUserInfoUpdate(dwUserId, dwType) {

}

// 好友在线状态变化，dwUserId表示好友用户ID号，dwStatus表示用户的当前活动状态：0 离线， 1 上线
function OnAnyChatFriendStatus(dwUserId, dwStatus) {

}

//业务对象事件通知
function OnAnyChatObjectEvent(dwObjectType, dwObjectId, dwEventType, dwParam1, dwParam2, dwParam3, dwParam4, strParam) {
	AddLog("OnAnyChatObjectEvent(dwObjectType=" + dwObjectType + ", dwObjectId=" + dwObjectId +  ", dwEventType=" + dwEventType + ")", LOG_TYPE_EVENT);
	switch(dwEventType) {
		case ANYCHAT_OBJECT_EVENT_UPDATE:		OnAnyChatObjectUpdate(dwObjectType, dwObjectId);			break;
		case ANYCHAT_AREA_EVENT_ENTERRESULT:	OnAnyChatEnterAreaResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_AREA_EVENT_LEAVERESULT:	OnAnyChatLeaveAreaResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_QUEUE_EVENT_STATUSCHANGE:	OnAnyChatQueueStatusChanged(dwObjectType, dwObjectId);			break;
		case ANYCHAT_QUEUE_EVENT_ENTERRESULT:	OnAnyChatEnterQueueResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_QUEUE_EVENT_LEAVERESULT:	OnAnyChatLeaveQueueResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_AGENT_EVENT_STATUSCHANGE:	OnAnyChatAgentStatusChanged(dwObjectType, dwObjectId, dwParam1);			break;
		case ANYCHAT_AGENT_EVENT_SERVICENOTIFY:	OnAnyChatServiceStart(dwParam1,dwParam2);			break;
		case ANYCHAT_AGENT_EVENT_WAITINGUSER:   OnAnyChatAgentWaitingUser(); break;
		default:
			break;
	}
}

//业务对象数据更新事件
function OnAnyChatObjectUpdate(dwObjectType, dwObjectId) {
	var str;
	if(dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) {
		
		str='业务对象数据更新事件。服务区域';
		var areaName = BRAC_ObjectGetStringValue(dwObjectType, dwObjectId, ANYCHAT_OBJECT_INFO_NAME);
		console.info("Area object udpate, name=" + areaName+",dwObjectId="+dwObjectId);
		$("#LOADING_GREY_DIV").hide();//隐藏登录蒙层
		if(queueListName==-1){
			$("#loginDiv").hide(); //隐藏登录界面
	        $("#enterRoom").show(); //显示大厅
	        $("#enterRoom h2").text("营业厅列表");
			$("#hallList li").each(function(index){ 
				if(dwObjectId==$(this).attr('dwObjectId')){$(this).remote();}
			});
				$("#hallList").prepend('<li class="poptip" style="background-color: #6295E1" dwObjectId="'+dwObjectId+'">'+areaName+'<br><p>编号:'+dwObjectId+'</p></li>');
		}
	} else if(dwObjectType == ANYCHAT_OBJECT_TYPE_QUEUE) {
		str='业务对象数据更新事件。队列对象';
	} else if(dwObjectType == ANYCHAT_OBJECT_TYPE_AGENT) {
		str='业务对象数据更新事件。客服对象';
	}
	AddLog(str+'，其中：dwObjectType为：' + dwObjectType + ',dwObjectId为：' + dwObjectId, LOG_TYPE_EVENT);
}

// 进入服务区域通知事件
function OnAnyChatEnterAreaResult(dwObjectType, dwObjectId, dwErrorCode) {
	AddLog('进入服务区域通知事件，其中：dwObjectType为：' + dwObjectType + ',dwObjectId为：' + dwObjectId +',dwErrorCode:'+dwErrorCode, LOG_TYPE_EVENT);
	if(dwErrorCode == 0) {
		// 进入服务区域成功
		if(userType==1){//客户
			/**获取队列*/
			var queueList =BRAC_ObjectGetIdList(ANYCHAT_OBJECT_TYPE_QUEUE);
			for ( var i in queueList) {
				var queueid=parseInt(queueList[i]);
				/**获取队列名称*/
				var queueName=BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_OBJECT_INFO_NAME);
				/**获取队列排队人数*/
				var queueLength=BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE,queueid,ANYCHAT_QUEUE_INFO_LENGTH);
				queueLength=queueLength<0?0:queueLength;
				/**获取队列信息*/
				var queueInfo=BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_OBJECT_INFO_DESCRIPTION);
				$("#LOADING_GREY_DIV img").hide();//隐藏登录等待gif
				$("#LOADING_GREY_DIV").hide();//隐藏蒙层
				$("#enterRoom h2").text(queueListName);
				$('#hallList').hide(); //隐藏营业厅
	            $('#roomOut').hide(); //隐藏营业厅退出按钮
	            $('#loginOut').show(); //显示队列返回按钮
	            $('#selectList').show(); //显示队列
				$('#selectList').append('<li><h3 class="title">'+queueName+'</h3><p class="content">'+queueInfo+'。</p><p class="content">(当前排队人数:<b>'+queueLength+'</b>)<a queueid="'+queueid+'" href="javascript:;">立即办理</a></p></li>');
			}
		}
	}
}

// 离开服务区域通知事件
function OnAnyChatLeaveAreaResult(dwObjectType, dwObjectId, dwErrorCode) {
}

// 队列状态变化
function OnAnyChatQueueStatusChanged(dwObjectType, dwObjectId) {
	AddLog('触发了队列状态变化回调函数：OnAnyChatQueueStatusChanged，其中：dwObjectType为：' + dwObjectType + ',dwObjectId为：' + dwObjectId, LOG_TYPE_API);
    refreshUserWaitingInfo(dwObjectId);
}

// 本地用户进入队列结果
function OnAnyChatEnterQueueResult(dwObjectType, dwObjectId, dwErrorCode) {
}

// 本地用户离开队列结果
function OnAnyChatLeaveQueueResult(dwObjectType, dwObjectId, dwErrorCode) {
}

// 坐席状态变化
function OnAnyChatAgentStatusChanged(dwObjectType, dwObjectId, dwParam1) {
	AddLog('触发了坐席状态变化回调函数：OnAnyChatAgentStatusChanged，其中：dwObjectType为：' + dwObjectType + ',dwObjectId为：' + dwObjectId+',dwParam1为：'+dwParam1, LOG_TYPE_API);
    if (dwObjectType == ANYCHAT_OBJECT_TYPE_AGENT && currentAgentID == dwObjectId) {
        if (dwParam1 == ANYCHAT_AGENT_STATUS_WAITTING) {
            refreshAgentServiceInfo();

            refreshServicedUserInfo(-1);
            startServiceTag = false;
        }
    }
}

// 坐席服务开始
function OnAnyChatServiceStart(dwAgentId, clientId){
	AddLog('坐席服务开始', LOG_TYPE_NORMAL);
	if (userType == 2 && mSelfUserId == dwAgentId) {
	    refreshServicedUserInfo(clientId);
		mTargetUserId=clientId;//客户id
		VideoCallRequest(clientId);//呼叫用户
	}
}

//队列里没有客户，坐席端处理方式
function OnAnyChatAgentWaitingUser(){
	AddLog('队列里没有客户', LOG_TYPE_EVENT);
	$('#LOADING_GREY_DIV').hide();
	startServiceTag=false;
	ForSession('当前队列中已没有客户！',true);
}