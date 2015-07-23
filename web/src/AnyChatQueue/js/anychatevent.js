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
    AddLog("OnAnyChatConnect(errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
	if (errorcode == 0) {

	} else {

	}
}

// 客户端登录系统，dwUserId表示自己的用户ID号，errorcode表示登录结果：0 成功，否则为出错代码，参考出错代码定义
function OnAnyChatLoginSystem(dwUserId, errorcode) {
    AddLog("OnAnyChatLoginSystem(userid=" + dwUserId + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
	if (errorcode == 0) {
	    if (userType == 2) {//客服
	        currentAgentID = dwUserId;
			dwAgentFlags=ANYCHAT_OBJECT_FLAGS_AGENT;//坐席标识
		}else if(userType==1){
			dwAgentFlags=0;//客户

        }

		mSelfUserId = dwUserId;
		dwPriority = parseInt($("#dwPrioritySelect option:selected").val());

		$("#LOADING_GREY_DIV span").text("正在加载营业厅，请稍候......");

		//身份信息设置
		InitClientObjectInfo(mSelfUserId,dwAgentFlags,dwPriority);
	} else {
		ForSession("Client logon failure!", true);
	}
}

// 客户端进入房间，dwRoomId表示所进入房间的ID号，errorcode表示是否进入房间：0成功进入，否则为出错代码
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
    AddLog("OnAnyChatEnterRoom(dwRoomId=" + dwRoomId + ',errorcode=' + errorcode + ')', LOG_TYPE_NORMAL);

	if (errorcode == 0) {
		if (userType == 2) {
			
		} else if (userType ==1) {
			/**客服姓名*/
			var name1 = BRAC_GetUserInfo(mTargetUserId,USERINFO_NAME); 
			/**个人姓名*/
			var myName = BRAC_GetUserInfo(mSelfUserId,USERINFO_NAME);
			
			var videoHtml='<div id="VideoShowDiv" style="display:block;margin-left:-80px;">'+
				'<div id="remoteVideoPos" class="videoshow0"></div>'+
				'<div id="remoteAudioVolume" style="width:480px;height:5px;top:370px;left: 21px;"></div>'+
				'<div id="localVideoPos" class="videoshow1"></div>'+
				'<div id="localAudioVolume" style="width:480px;height:5px;top:370px;left: 517px;"></div>'+
				'<div id="div_username0" uid="" class="ShowName" style="left: 21px;">'+name1+'(坐席)</div>'+
				'<div id="div_username1" uid="" class="ShowName" style="left:517px">'+myName+'(自己)</div>'+
				'<b style="position: absolute;bottom: -40;right: 30;font-size: 18px;"><a id="hangUp" class="Buttons"></a></b>'+
			'</div>';
			
			$("#videoCallContent").html(videoHtml);//填充视频会话层
			$("#LOADING_GREY_DIV").hide();
			$("#videoCall").show();
			$("#callLayer").hide();
		}
		//打开本地视频
		startVideo(mSelfUserId, GetID("localVideoPos"), "ANYCHAT_VIDEO_LOCAL",1);
		setVolumeTimer();//设置音量感应
		
	}else{
		AddLog("OnAnyChatEnterRoom(dwRoomId: "+dwRoomId+',errorcode: '+errorcode + ')', LOG_TYPE_ERROR);
	}
}

// 收到当前房间的在线用户信息，进入房间后触发一次，dwUserCount表示在线用户数（包含自己），dwRoomId表示房间ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {
	//请求对方视频
	startVideo(mTargetUserId, GetID("remoteVideoPos"), "ANYCHAT_VIDEO_REMOTE",1);
}

// 用户进入（离开）房间，dwUserId表示用户ID号，bEnterRoom表示该用户是进入（1）或离开（0）房间
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {
	AddLog("function OnAnyChatUserAtRoom(dwUserId="+dwUserId+')', LOG_TYPE_NORMAL);

	//请求对方视频
		if (bEnterRoom == 1) {
			//请求对方视频
			startVideo(mTargetUserId, GetID("remoteVideoPos"), "ANYCHAT_VIDEO_REMOTE",1);
			if(userType == 1){
				
			}
		} else {
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
	AddLog("function OnAnyChatLinkClose(reason: " + reason + ",errorcode: " + errorcode , LOG_TYPE_ERROR);
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
	//AddLog("OnAnyChatObjectEvent(dwObjectType=" + dwObjectType + ", dwObjectId=" + dwObjectId +  ", dwEventType=" + dwEventType + ")", LOG_TYPE_EVENT);
	//refreshAgentServiceInfo();
	switch(dwEventType) {
	    case ANYCHAT_OBJECT_EVENT_UPDATE: OnAnyChatObjectUpdate(dwObjectType, dwObjectId); break;
	    case ANYCHAT_OBJECT_EVENT_SYNCDATAFINISH: OnAnyChatObjectSyncDataFinish(dwObjectType, dwObjectId); break;
		case ANYCHAT_AREA_EVENT_ENTERRESULT:	OnAnyChatEnterAreaResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_AREA_EVENT_LEAVERESULT:    OnAnyChatLeaveAreaResult(dwObjectType, dwObjectId, dwParam1); break;
		case ANYCHAT_AREA_EVENT_STATUSCHANGE:   OnAnyChatAreaStatusChange(dwObjectType, dwObjectId, dwParam1); break;
		case ANYCHAT_QUEUE_EVENT_STATUSCHANGE:	OnAnyChatQueueStatusChanged(dwObjectType, dwObjectId);			break;
		case ANYCHAT_QUEUE_EVENT_ENTERRESULT:	OnAnyChatEnterQueueResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_QUEUE_EVENT_LEAVERESULT:	OnAnyChatLeaveQueueResult(dwObjectType, dwObjectId, dwParam1);	break;
		case ANYCHAT_AGENT_EVENT_STATUSCHANGE: OnAnyChatAgentStatusChanged(dwObjectType, dwObjectId, dwParam1); break;
		case ANYCHAT_AGENT_EVENT_SERVICENOTIFY: OnAnyChatServiceStart(dwParam1, dwParam2, dwParam3); break;
		case ANYCHAT_AGENT_EVENT_WAITINGUSER:   OnAnyChatAgentWaitingUser(); break;
		default:
			break;
	}
}

//业务对象数据更新事件
function OnAnyChatObjectUpdate(dwObjectType, dwObjectId) {
    var str = null;
    AddLog('OnAnyChatObjectUpdate(' + dwObjectType + ',' + dwObjectId + ')', LOG_TYPE_EVENT);

	if(dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) {
	    areaIdArray[areaArrayIdx] = dwObjectId;
	    areaArrayIdx++;
	} else if(dwObjectType == ANYCHAT_OBJECT_TYPE_QUEUE) {
		
	} else if(dwObjectType == ANYCHAT_OBJECT_TYPE_AGENT) {
		
	}
}

//业务对象同步完成事件
function OnAnyChatObjectSyncDataFinish(dwObjectType, dwObjectId) {
    AddLog('OnAnyChatObjectSyncDataFinish(' + dwObjectType + ',' + dwObjectId + ')', LOG_TYPE_EVENT);

    if (dwObjectType == ANYCHAT_OBJECT_TYPE_AREA) {
        showSerivceArea();
    }
}

// 进入服务区域通知事件
function OnAnyChatEnterAreaResult(dwObjectType, dwObjectId, dwErrorCode) {
	AddLog('OnAnyChatEnterAreaResult(' + dwObjectType + ',' + dwObjectId +','+dwErrorCode + ')', LOG_TYPE_EVENT);
	if (dwErrorCode == 0) {
	    colorIdx = 0;
		// 进入服务区域成功
		if(userType==1){//客户
			/**获取队列*/
			var queueList =BRAC_ObjectGetIdList(ANYCHAT_OBJECT_TYPE_QUEUE);
			for (var i in queueList) {
			    var queueListId = parseInt(queueList[i]);
			    /**获取队列名称*/
			    var queueName = BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueListId, ANYCHAT_OBJECT_INFO_NAME);
			    /**获取队列排队人数*/
			    var queueLength = BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueListId, ANYCHAT_QUEUE_INFO_LENGTH);
			    queueLength = queueLength < 0 ? 0 : queueLength;
			    /**获取队列信息*/
			    var queueInfo = BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueListId, ANYCHAT_OBJECT_INFO_DESCRIPTION);
			    $("#LOADING_GREY_DIV").hide(); //隐藏蒙层
			    $('#poptip li[dwobjectid]').hide(); //隐藏服务厅
			    $("#enterRoom h2:eq(1)").text(queueListName);
			    var liObject = $('<li class="queue-item" queueid="' + queueListId + '">' +
                    '<a class="queue-item-link"><img class="queue-item-pic" src="./img/queue.png" /></a>' +
                    '<span class="queue-item-layout">' +
                        '<span class="queue-item-layout-title">' + queueName + '</span>' +
                        '<span class="queue-item-layout-desc">' + queueInfo + '</span>' +
                        '<span class="queue-item-layout-desc">' + '当前排队人数：<strong>' + queueLength + " 人" + '</strong></span>' +
                        '<span class="queue-item-layout-btn">' + '<a class="btn">立即办理</a>' + '</span>' +
                    '</span>' +
                    '</li>');
			    liObject.css("background-color", colorQueueArray[colorIdx]);
			    $("#poptip").append(liObject);
			    colorIdx++;
			    if (colorIdx == 3) {
			        colorIdx = 0;
			    }
			}
			$("#roomOut").off().click(function() {
				$("#LOADING_GREY_DIV").show();//显示等待蒙层
				var leaveFlag;
            	if($("#callLayer").css("display")!="block"){
	                /**离开营业厅*/
            		leaveFlag=BRAC_ObjectControl(ANYCHAT_OBJECT_TYPE_AREA, hallbuinessNum, ANYCHAT_AREA_CTRL_USERLEAVE, 0, 0, 0, 0, "");
	                $("#LOADING_GREY_DIV span").text("正在离开营业厅，请稍候......");//显示等待蒙层
	                if(!leaveFlag){
	                	$('#poptip li[queueid]').hide(); //隐藏队列
	                	$('#poptip li[dwobjectid]').show(); //显示营业厅
	                	$("#LOADING_GREY_DIV").hide();//隐藏等待蒙层
	                }

	            	$("#enterRoom h2:eq(1)").text("营业厅列表");
	                $(this).off().click(systemOut);
            	}else{
            		if($("#queueMsg1").css("display")=="block"){
            			$("#queueMsg1 .confirmMsg").click();
            		}else if($("#queueMsg2").css("display")=="block"){
            			$("#queueMsg2 #reject").click();
            		}
            	}
            });
        }

        //坐席
        if (userType == 2) {

            $("#LOADING_GREY_DIV").hide(); //隐藏等待蒙层

            refreshAgentServiceInfo();

            $("#roomOut").off().click(function () {
                leaveAreaClickEvent();
            });

        }
	}
}

// 离开服务区域通知事件
function OnAnyChatLeaveAreaResult(dwObjectType, dwObjectId, dwErrorCode) {
	AddLog('OnAnyChatLeaveAreaResult(' + dwObjectType + ',' + dwObjectId+','+dwErrorCode + ')', LOG_TYPE_EVENT);
}

//营业厅状态变化
function OnAnyChatAreaStatusChange(dwObjectType, dwObjectId, dwErrorCode) {
    AddLog('OnAnyChatAreaStatusChange(' + dwObjectType + ',' + dwObjectId + ',' + dwErrorCode + ')', LOG_TYPE_EVENT);
}

// 队列状态变化
function OnAnyChatQueueStatusChanged(dwObjectType, dwObjectId) {
    AddLog('OnAnyChatQueueStatusChanged(' + dwObjectType + ',' + dwObjectId + ')', LOG_TYPE_EVENT);
    if (userType == 2) {
        refreshAgentServiceInfo();
    }

	refreshUserWaitingInfo(dwObjectId);
	refreshQueueInfoDisplay(dwObjectId);
}

// 本地用户进入队列结果
function OnAnyChatEnterQueueResult(dwObjectType, dwObjectId, dwErrorCode) {
    AddLog('OnAnyChatEnterQueueResult(' + dwObjectType + ',' + dwObjectId + ',' + dwErrorCode + ')', LOG_TYPE_EVENT);
    currentSelectedQueueName = BRAC_ObjectGetStringValue(ANYCHAT_OBJECT_TYPE_QUEUE, dwObjectId, ANYCHAT_OBJECT_INFO_NAME);
    $("#enterRoom h2").text(currentSelectedQueueName + " - 服务窗口");
    isShowReturnBtn(false);

	$("#LOADING_GREY_DIV").hide();//隐藏等待蒙层
	 $("#poptip").hide(); //隐藏队列
     $("#queueMsg1").show(); //重置显示排队信息
     $("#queueMsg2").hide(); //隐藏呼叫信息
     $("#callLayer").show(); //显示弹出窗口
     $("#queueMsg1 strong:eq(2)").text(0); //清零排队时间
     clearInterval(waitTimeSet);
     waitTimeSet = setInterval(function () {
         var time = formatSeconds(BRAC_ObjectGetIntValue(ANYCHAT_OBJECT_TYPE_QUEUE, queueid, ANYCHAT_QUEUE_INFO_WAITTIMESECOND));
         $("#queueMsg1 strong:eq(2)").text(time);
     }, 1000);
}

// 本地用户离开队列结果
function OnAnyChatLeaveQueueResult(dwObjectType, dwObjectId, dwErrorCode) {
    AddLog('OnAnyChatLeaveQueueResult(' + dwObjectType + ',' + dwObjectId + ',' + dwErrorCode + ')', LOG_TYPE_EVENT);
    if (dwErrorCode == 0) isShowReturnBtn(true);
    currentSelectedQueueName = "";

	if($("#callLayer").css("display")!="block"){
		$("#LOADING_GREY_DIV").hide();//隐藏等待蒙层
		$("#poptip").show(); 
	    $("#poptip li[queueid]").show(); //显示队列列表
	}
	
}

// 坐席状态变化
function OnAnyChatAgentStatusChanged(dwObjectType, dwObjectId, dwParam1) {
    AddLog('OnAnyChatAgentStatusChanged(' + dwObjectType + ',' + dwObjectId + ',' + dwParam1 + ')', LOG_TYPE_EVENT);
    if (dwObjectType == ANYCHAT_OBJECT_TYPE_AGENT && currentAgentID == dwObjectId) {
        if (dwParam1 == ANYCHAT_AGENT_STATUS_WAITTING) {
            refreshAgentServiceInfo();

            refreshServicedUserInfo(-1);
            startServiceTag = false;
            $("#LOADING_GREY_DIV span").show();

            isShowReturnBtn(true);
        }else if (dwParam1 == ANYCHAT_AGENT_STATUS_WORKING){
            startServiceTag = true;
        }
        
    }
}

// 坐席服务开始
function OnAnyChatServiceStart(dwAgentId, clientId, dwQueueId) {
    AddLog('OnAnyChatServiceStart(' + dwAgentId + ',' + clientId + ',' + dwQueueId +')', LOG_TYPE_EVENT);
	if (userType == 2 && mSelfUserId == dwAgentId) {
		$("#LOADING_GREY_DIV span").hide();
	    refreshServicedUserInfo(clientId);
		mTargetUserId=clientId;//客户id
		VideoCallRequest(clientId);//呼叫用户
	}
}

//队列里没有客户，坐席端处理方式
function OnAnyChatAgentWaitingUser(){
    AddLog('OnAnyChatAgentWaitingUser()', LOG_TYPE_EVENT);
	if($("#remoteVideoPos").html()==""){
		$('#LOADING_GREY_DIV').hide();
		startServiceTag=false;
		$("#LOADING_GREY_DIV span").show();
		ForSession('当前队列中已没有客户！',true);
	}
}