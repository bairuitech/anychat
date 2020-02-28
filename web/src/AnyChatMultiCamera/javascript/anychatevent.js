// AnyChat for Web SDK

/********************************************
 *				�¼��ص�����				*
 *******************************************/
 
 // �첽��Ϣ֪ͨ���������ӷ���������¼ϵͳ�����뷿�����Ϣ
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

// �յ�������Ϣ
function OnAnyChatTextMessage(dwFromUserId, dwToUserId, bSecret, lpMsgBuf, dwLen) {
	DisplayTextMessage(dwFromUserId, lpMsgBuf);
}

// �յ�͸��ͨ����������
function OnAnyChatTransBuffer(dwUserId, lpBuf, dwLen) {

}

// �յ�͸��ͨ������չ����������
function OnAnyChatTransBufferEx(dwUserId, lpBuf, dwLen, wParam, lParam, dwTaskId) {

}

// �ļ��������֪ͨ
function OnAnyChatTransFile(dwUserId, lpFileName, lpTempFilePath, dwFileLength, wParam, lParam, dwTaskId) {

}

// ϵͳ�����ı�֪ͨ
function OnAnyChatVolumeChange(device, dwCurrentVolume) {

}

// �յ����������͵�SDK Filter����
function OnAnyChatSDKFilterData(lpBuf, dwLen) {

}

// �յ�¼�����������¼�
function OnAnyChatRecordSnapShot(dwUserId, lpFileName, dwParam, dwFlags) {
	
}

// �յ�¼�����������¼�����չ��
function OnAnyChatRecordSnapShotEx(dwUserId, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr) {

}

// �յ�¼�����������¼�����չ2������errorcode��
function OnAnyChatRecordSnapShotEx2(dwUserId, dwErrorCode, lpFileName, dwElapse, dwFlags, dwParam, lpUserStr) {
	
}

// AnyChatCoreSDK�첽�¼�
function OnAnyChatCoreSDKEvent(dwEventType, lpEventJsonStr) {
	
}


/********************************************
 *		AnyChat SDK����ҵ������				*
 *******************************************/
 
// �ͻ������ӷ�������bSuccess��ʾ�Ƿ����ӳɹ���errorcode��ʾ�������
function OnAnyChatConnect(bSuccess, errorcode) {
	AddLog("OnAnyChatConnect(errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
    if (errorcode == 0) {
		
    }
    else {
		DisplayLoadingDiv(false);
    }
}

// �ͻ��˵�¼ϵͳ��dwUserId��ʾ�Լ����û�ID�ţ�errorcode��ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
function OnAnyChatLoginSystem(dwUserId, errorcode) {
	DisplayLoadingDiv(false);
	AddLog("OnAnyChatLoginSystem(userid=" + dwUserId + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
    if (errorcode == 0) {
		ConfigAnyChatParameter();
		mSelfUserId = dwUserId;	
		ShowHallDiv(true);
    } else {
		ShowHallDiv(false);
    }
	
}

// �ͻ��˽��뷿�䣬dwRoomId��ʾ�����뷿���ID�ţ�errorcode��ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
    DisplayLoadingDiv(false);
	AddLog("OnAnyChatEnterRoom(roomid=" + dwRoomId + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
    if (errorcode == 0) {
        ShowRoomDiv(true);
		RoomUserListControl(mSelfUserId, true);		// ���Լ������û��б�
	
		localVideoStream();
		createRemoteVideoDiv();
		
		
        mRefreshVolumeTimer = setInterval(function () {

            GetID("LocalAudioVolume").style.width = GetID("AnyChatLocalVideoDiv").offsetHeight * BRAC_QueryUserStateInt(mSelfUserId, BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";
			if(mTargetUserId != -1)
				GetID("RemoteAudioVolume").style.width = GetID("AnyChatRemoteVideoDiv").offsetHeight * BRAC_QueryUserStateInt(mTargetUserId, BRAC_USERSTATE_SPEAKVOLUME) / 100 + "px";
			else
				GetID("RemoteAudioVolume").style.width = "0px";
		
	}, 100);
    } else {
	
    }
   //var v = BRAC_QueryUserStateInt(mSelfUserId,BRAC_USERSTATE_VIDEOBITRATE);Console.log(v);
}
 
// �յ���ǰ����������û���Ϣ�����뷿��󴥷�һ�Σ�dwUserCount��ʾ�����û����������Լ�����dwRoomId��ʾ����ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {
	AddLog("OnAnyChatRoomOnlineUser(count=" + dwUserCount + ", roomid=" + dwRoomId + ")", LOG_TYPE_EVENT);
	var useridlist = BRAC_GetOnlineUser();
	for (var i = 0; i < useridlist.length; i++) {
		RoomUserListControl(useridlist[i], true);
    }
	//comeToRequestedScrenn(2);
}

// �û����루�뿪�����䣬dwUserId��ʾ�û�ID�ţ�bEnterRoom��ʾ���û��ǽ��루1�����뿪��0������
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {
	AddLog("OnAnyChatUserAtRoom(userid=" + dwUserId + ", benter=" + bEnterRoom + ")", LOG_TYPE_EVENT);
	RoomUserListControl(dwUserId, bEnterRoom ? true : false);
    if (bEnterRoom == 1) {
		//RequestVideoByUserId(dwUserId);
		//ShowNotifyMessage(BRAC_GetUserName(dwUserId) +"&nbspenter room!", NOTIFY_TYPE_NORMAL);
    }
    else {
		//ShowNotifyMessage(BRAC_GetUserName(dwUserId) +"&nbspleave room!", NOTIFY_TYPE_NORMAL);
		for(var i=0;i<list_videouser.length;i++)
		{
			if(list_videouser[i]==dwUserId)
			{
				BRAC_UserCameraControl(dwUserId, 0); // �򿪶Է���Ƶ
				BRAC_UserSpeakControl(dwUserId, 0); // �򿪶Է���Ƶ
				list_videouser[i]=0;
				list_videosite[i]=0;
				GetID("div_username"+i).innerHTML="��ǰû����";
				break;
			}
		}
    }
    DisplayScroll("room_div_userlist");
}

// ���������ѹرգ�����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ������reason��ʾ���ӶϿ���ԭ��
function OnAnyChatLinkClose(reason, errorcode) {
	AddLog("OnAnyChatLinkClose(reason=" + reason + ", errorcode=" + errorcode + ")", LOG_TYPE_EVENT);
	DisplayLoadingDiv(false);
	ShowRoomDiv(false);
	ShowHallDiv(false);
	ShowLoginDiv(true);
}

// �û�����Ƶ�豸״̬�仯��Ϣ��dwUserId��ʾ�û�ID�ţ�State��ʾ���û��Ƿ��Ѵ���Ƶ�ɼ��豸��0���رգ�1���򿪣�
function OnAnyChatMicStateChange(dwUserId, State) {
	//if (State == 0) GetID(dwUserId + "_MicrophoneTag").src = "./images/advanceset/microphone_false.png";
    //if (State == 1) GetID(dwUserId + "_MicrophoneTag").src = "./images/advanceset/microphone_true.png";
	
}

// �û�����ͷ״̬�����仯��dwUserId��ʾ�û�ID�ţ�State��ʾ����ͷ�ĵ�ǰ״̬��0��û������ͷ��1��������ͷ��û�д򿪣�2���򿪣�
function OnAnyChatCameraStateChange(dwUserId, State) {
	if (GetID(dwUserId + "_CameraTag") != null){
	    if (State == 0) GetID(dwUserId + "_CameraTag").src = "";
	    if (State == 1) GetID(dwUserId + "_CameraTag").src = "./images/advanceset/camera_false.png";
	    if (State == 2) GetID(dwUserId + "_CameraTag").src = "./images/advanceset/camera_true.png";
    }
}

// �����û��������û���P2P��������״̬�����仯��dwUserId��ʾ�����û�ID�ţ�State��ʾ�����û��������û��ĵ�ǰP2P��������״̬��0��û�����ӣ�1����TCP���ӣ�2����UDP���ӣ�3��TCP��UDP���ӣ�
function OnAnyChatP2PConnectState(dwUserId, State) {

}

// �û�����˽������dwUserId��ʾ�����ߵ��û�ID�ţ�dwRequestId��ʾ˽�������ţ���ʶ������
function OnAnyChatPrivateRequest(dwUserId, dwRequestId) {

}

// �û��ظ�˽������dwUserId��ʾ�ظ��ߵ��û�ID�ţ�errorcodeΪ�������
function OnAnyChatPrivateEcho(dwUserId, errorcode) {

}

// �û��˳�˽�ģ�dwUserId��ʾ�˳��ߵ��û�ID�ţ�errorcodeΪ�������
function OnAnyChatPrivateExit(dwUserId, errorcode) {

}

// ��Ƶͨ����Ϣ֪ͨ�ص�����
function OnAnyChatVideoCallEvent(dwEventType, dwUserId, dwErrorCode, dwFlags, dwParam, szUserStr) {
	AddLog("OnAnyChatVideoCallEvent(dwEventType=" + dwEventType + ", dwUserId=" + dwUserId + ", dwErrorCode=" + dwErrorCode + ", dwFlags=" + dwFlags + ", dwParam=" + dwParam + ", szUserStr=" + szUserStr + ")", LOG_TYPE_EVENT);
	
}

// �û���Ϣ����֪ͨ��dwUserId��ʾ�û�ID�ţ�dwType��ʾ�������
function OnAnyChatUserInfoUpdate(dwUserId, dwType) {
	AddLog("OnAnyChatUserInfoUpdate(dwUserId=" + dwUserId + ", dwType=" + dwType + ")", LOG_TYPE_EVENT);
}

// ��������״̬�仯��dwUserId��ʾ�����û�ID�ţ�dwStatus��ʾ�û��ĵ�ǰ�״̬��0 ���ߣ� 1 ����
function OnAnyChatFriendStatus(dwUserId, dwStatus) {
	AddLog("OnAnyChatFriendStatus(dwUserId=" + dwUserId + ", dwStatus=" + dwStatus + ")", LOG_TYPE_EVENT);
	
}

