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
    MessageFlicker(); // ��ť��˸��ʾ
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
	if(errorcode == 0)
		prompt("���ӷ������ɹ�");
}

// �ͻ��˵�¼ϵͳ��dwUserId��ʾ�Լ����û�ID�ţ�errorcode��ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
function OnAnyChatLoginSystem(dwUserId, errorcode) {
    mSelfUserId = dwUserId;
    GoToHall(); // ��ʾ����
    initialize();
    document.body.style.backgroundColor = "#58a8c9";
}

// �ͻ��˽��뷿�䣬dwRoomId��ʾ�����뷿���ID�ţ�errorcode��ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
function OnAnyChatEnterRoom(dwRoomId, errorcode) {
	// �򿪱�����Ƶ����Ƶ
	BRAC_UserCameraControl(-1, 1);
	BRAC_UserSpeakControl(-1, 1);
	// ����Է���Ƶ����Ƶ
	BRAC_UserCameraControl(mTargetUserId, 1);
	BRAC_UserSpeakControl(mTargetUserId, 1);
	
    CreateWideScreen(); // ������Ƶ��ʾλ��
    $("#GetExpression").load("./sub/emote.html"); //��ɫ������ҳ��
}

// �յ���ǰ����������û���Ϣ�����뷿��󴥷�һ�Σ�dwUserCount��ʾ�����û����������Լ�����dwRoomId��ʾ����ID
function OnAnyChatRoomOnlineUser(dwUserCount, dwRoomId) {

}

// �û����루�뿪�����䣬dwUserId��ʾ�û�ID�ţ�bEnterRoom��ʾ���û��ǽ��루1�����뿪��0������
function OnAnyChatUserAtRoom(dwUserId, bEnterRoom) {
	if(dwUserId == mTargetUserId && bEnterRoom != 0) {
		
		// ����Է���Ƶ����Ƶ
		BRAC_UserCameraControl(mTargetUserId, 1);
		BRAC_UserSpeakControl(mTargetUserId, 1);
	}
}

// ���������ѹرգ�����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ������reason��ʾ���ӶϿ���ԭ��
function OnAnyChatLinkClose(reason, errorcode) {
	BRAC_Logout();	// �ر��Զ�����
	GoToLogin();	// ��ʾ��¼����
}

// �û�����Ƶ�豸״̬�仯��Ϣ��dwUserId��ʾ�û�ID�ţ�State��ʾ���û��Ƿ��Ѵ���Ƶ�ɼ��豸��0���رգ�1���򿪣�
function OnAnyChatMicStateChange(dwUserId, State) {

}

// �û�����ͷ״̬�����仯��dwUserId��ʾ�û�ID�ţ�State��ʾ����ͷ�ĵ�ǰ״̬��0��û������ͷ��1��������ͷ��û�д򿪣�2���򿪣�
function OnAnyChatCameraStateChange(dwUserId, State) {

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
//	AddLog("OnAnyChatVideoCallEvent(dwEventType=" + dwEventType + ", dwUserId=" + dwUserId + ", dwErrorCode=" + dwErrorCode + ", dwFlags=" + dwFlags + ", dwParam=" + dwParam + ", szUserStr=" + szUserStr + ")", LOG_TYPE_EVENT);
	switch(dwEventType) {
		case BRAC_VIDEOCALL_EVENT_REQUEST:	// ��������
			 $("#Shade_Div").show();
			$("#BeCalls_Div").show();
			 $("#BeCalls_Div_Content").html("�յ��û�  " + BRAC_GetUserName(dwUserId) + "  �Ự����<br />      �Ƿ�ͬ��?");
			 mTargetUserId = dwUserId;
		break;
		case BRAC_VIDEOCALL_EVENT_REPLY:	// ��������ظ�
				  if (dwErrorCode == ICS_RETCODE_SESSION_REJECT) {
					 ForSession("�Է��ܾ��Ự����...");
				 }
				 else if (dwErrorCode == ICS_RETCODE_SESSION_BUSY) {
					ForSession("�û����ڻỰ��...");
				 }
				  else if (dwErrorCode == ICS_RETCODE_SESSION_CANCEL) {
					  ForSession("�û�ȡ���Ự����...");
					 Getdmo("BeCalls_Div").style.display = "none";
				}
		break;
		case BRAC_VIDEOCALL_EVENT_START:	// ��Ƶ���лỰ��ʼ�¼�
			BRAC_EnterRoom(dwParam, "", 0);
			mMissionQuantity = 0;
			Getdmo("ReceiveMsg").innerHTML = "";
			Getdmo("Initiative_Call_Div").style.display = "none";
			Getdmo("HallDiv").style.display = "none";
			chatuserid = dwUserId;
			$("#VideoShowDiv").show();
			$("#mTargetPhoto").html("<img src='" + GetUserImageAddrById(dwUserId, 50) + "' alt='�û�ͷ��' style='height:65px;width:65px;' />");
			$("#mTargetInfo").html("Ŀ���ID��" + dwUserId + "<br />Ŀ�����ƣ�" + BRAC_GetUserName(dwUserId) + "<br />�������飺" + BRAC_GetGroupName(GetUserGroupIdByUserId(dwUserId)) + "<br />");
			//    ComboboxInint();
			InitAdvanced();
			ReceiveMsgBoxScroll();
		break;
		case BRAC_VIDEOCALL_EVENT_FINISH:	// �Ҷϣ����������лỰ
			BackToHall();
		break;
		default:
			break;
	}
	
	
	
}

var bFirstUserInfoUpdate = true;
// �û���Ϣ����֪ͨ��dwUserId��ʾ�û�ID�ţ�dwType��ʾ�������
function OnAnyChatUserInfoUpdate(dwUserId, dwType) {
	if(bFirstUserInfoUpdate) {
		bFirstUserInfoUpdate = false;
		// ����ͷ����Ϣ��ʾ
		var MinePic = document.createElement("img");
		MinePic.src = GetUserImageAddrById(mSelfUserId, 50);
		MinePic.alt = "�û�ͼ��";
		MinePic.id = "MyPhoto";
		Getdmo("mSelfPhoto").appendChild(MinePic);
		Getdmo("mSelfInfo").innerHTML = "<br />�û�ID: " + mSelfUserId +
								 "<br />�û���: " + BRAC_GetUserName(mSelfUserId) +
								 "<br />������: " + BRAC_GetGroupName(GetUserGroupIdByUserId(mSelfUserId));
		CreateUserImage("whole");
	}
	// ˢ���û�����
	Getdmo("GroupContent").innerHTML = "";
	UserGroupDiv(0, "�����û�");
	mGroupList = BRAC_GetUserGroups();
	for (var i = 0; i < mGroupList.length; i++) {
		var GroupName = BRAC_GetGroupName(mGroupList[i]);
		UserGroupDiv(mGroupList[i], GroupName);
	}
	OpenGroup(0);
	StartScroll("GroupListScroll", "GroupSlider", "GroupContent", "GroupBaseLine");
}

// ��������״̬�仯��dwUserId��ʾ�����û�ID�ţ�dwStatus��ʾ�û��ĵ�ǰ�״̬��0 ���ߣ� 1 ����
function OnAnyChatFriendStatus(dwUserId, dwStatus) {

//	AddLog("OnAnyChatFriendStatus(dwUserId=" + dwUserId + ", dwStatus=" + dwStatus + ")", LOG_TYPE_EVENT);
	if (dwStatus == 1) {	// ����
		DisplayOnLineUser(dwUserId);
	} else { 				// ����
		if (Getdmo("UserID_"+dwUserId) != null)
			Getdmo("UserListContent").removeChild(Getdmo("UserID_"+dwUserId));
	}
}