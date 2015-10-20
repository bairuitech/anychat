// BRAnyChatMeetingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "BRAnyChatMeetingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// 图标在ImageList中的索引
#define IMAGE_INDEX_NULL			-1
#define IMAGE_INDEX_MIC				0
#define IMAGE_INDEX_CAMERA_NORMAL	1
#define IMAGE_INDEX_CAMERA_OPEN		2


CBRAnyChatMeetingDlg::CBRAnyChatMeetingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBRAnyChatMeetingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBRAnyChatMeetingDlg)
	m_pLoginDlg = NULL;
	m_pHallDlg = NULL;
	m_dwSelfUserId = -1;
	m_pSelfVideoDlg = NULL;
	m_pSettingsDlg = NULL;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBRAnyChatMeetingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBRAnyChatMeetingDlg)
	DDX_Control(pDX, IDC_EDIT_TEXTOUTPUT, m_ctrlTextOutput);
	DDX_Control(pDX, IDC_COMBO_DISPNUM, m_ctrlDispNumCombo);
	DDX_Control(pDX, IDC_LIST_USER, m_ctrlUserList);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBRAnyChatMeetingDlg, CDialog)
	//{{AFX_MSG_MAP(CBRAnyChatMeetingDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_CBN_SELCHANGE(IDC_COMBO_DISPNUM, OnSelchangeComboDispNum)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USER, OnDblclkListUser)
	ON_BN_CLICKED(IDC_BUTTON_SENDTEXT, OnButtonSendText)
	ON_BN_CLICKED(IDC_BUTTON_ADVSET, OnButtonAdvSet)
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatMeetingDlg message handlers

BOOL CBRAnyChatMeetingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
/*
#ifdef _HRC_USE_SKIN_
	skinppRemoveSkinHwnd(GetDlgItem(IDC_EDIT_TEXTOUTPUT)->GetSafeHwnd());
	skinppSetSkinOwnerMenu(FALSE);
#endif
*/
	TCHAR szLogoPath[MAX_PATH] = {0};
	TCHAR szLogoFile[MAX_PATH] = {0};
	GetModuleFileName(NULL,szLogoPath,sizeof(szLogoPath)); 
	(strrchr(szLogoPath,'\\'))[1] = 0; 
	strcat(szLogoPath,SUB_PATH_SKINFILE);
	_snprintf(szLogoFile,sizeof(szLogoFile),"%s\\%s",szLogoPath,_T("logo.jpg"));
	if(IsFileExist(szLogoFile))
		m_LogoPic.Load(szLogoFile);
	else
		m_LogoPic.Load(IDR_IMAGE_CHATLOGO);

	ShowWindow(SW_HIDE);
	// 界面首先显示登录对话框
	m_pLoginDlg = new CLoginDlg(this);
	if(m_pLoginDlg->Create(IDD_DIALOG_LOGIN,this))
	{
		m_pLoginDlg->ModifyStyleEx(0,WS_EX_APPWINDOW);
		m_pLoginDlg->CenterWindow();
		m_pLoginDlg->ShowWindow(SW_SHOW);
	}
	// 创建房间大厅界面，并隐藏
	m_pHallDlg = new CHallDlg(this);
	if(m_pHallDlg->Create(IDD_DIALOG_HALL,this))
	{
		m_pHallDlg->ModifyStyleEx(0,WS_EX_APPWINDOW);
		m_pHallDlg->CenterWindow();
		m_pHallDlg->ShowWindow(SW_HIDE);
	}
	// 初始化SDK
	InitAnyChatSDK();

	InitUserListCtrl();

	DWORD dwDispNumIdx = m_ctrlDispNumCombo.AddString("一分屏显示");
	m_ctrlDispNumCombo.SetCurSel(dwDispNumIdx);
	m_ctrlDispNumCombo.SetItemData(dwDispNumIdx,1);
	dwDispNumIdx = m_ctrlDispNumCombo.AddString("二分屏显示");
	m_ctrlDispNumCombo.SetItemData(dwDispNumIdx,2);
	dwDispNumIdx = m_ctrlDispNumCombo.AddString("四分屏显示");
	m_ctrlDispNumCombo.SetItemData(dwDispNumIdx,4);

	// 初始化本地视频显示面板
	m_pSelfVideoDlg = new CVideoPanelDlg(this);
	if(m_pSelfVideoDlg->Create(IDD_DIALOG_VIDEOPANEL))
	{
		CRect rcLocalVideo;
		GetDlgItem(IDC_STATIC_LOCALVIDEO)->GetWindowRect(rcLocalVideo);
		ScreenToClient(rcLocalVideo);
		m_pSelfVideoDlg->ShowWindow(SW_SHOW);
		m_pSelfVideoDlg->MoveWindow(rcLocalVideo);
	}
	for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		m_pPanelObjectArray[i] = new CVideoPanelDlg(this);
		if(m_pPanelObjectArray[i]->Create(IDD_DIALOG_VIDEOPANEL))
		{
			CleanVideoPanelBind(m_pPanelObjectArray[i]);
			m_pPanelObjectArray[i]->ShowWindow(SW_HIDE);
		}
	}
	// 默认设置为单屏模式
	RelocateVideoPanel(1);

	CHAR szConfigFile[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szConfigFile,_MAX_PATH);
	(strrchr(szConfigFile,'\\'))[1] = 0; 
	strcat(szConfigFile,DEFAULT_CONFIG_FILENAME);
	
	TCHAR szTempStr[200] = {0};
	// 读产品名称
	if(::GetPrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ProductName"),NULL,szTempStr,sizeof(szTempStr),szConfigFile))
	{
		strcat(szTempStr, " — 会议厅");
		SetWindowText(szTempStr);
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBRAnyChatMeetingDlg::InitAnyChatSDK(void)
{
	// 打开（关闭）SDK的日志记录功能
	BRAC_ActiveCallLog(TRUE);
	
	// 设置SDK核心组件所在目录
	CHAR szCoreSDKPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szCoreSDKPath,sizeof(szCoreSDKPath));
	(strrchr(szCoreSDKPath,'\\'))[1] = 0; 
	BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,szCoreSDKPath,strlen(szCoreSDKPath));
	
	// 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE | 
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_CONFIG_LOCALINI;
	BRAC_InitSDK(this->GetSafeHwnd()/*NULL*/,dwFuncMode);
	
	
	// 设置录像临时文件保存路径
	CHAR szRecordDirectory[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szRecordDirectory,MAX_PATH);
	(strrchr(szRecordDirectory,'\\'))[1] = 0; 
	strcat(szRecordDirectory,"Record");
	BRAC_SetSDKOption(BRAC_SO_RECORD_TMPDIR,szRecordDirectory,strlen(szRecordDirectory));
	// 设置录像文件质量参数
	DWORD dwVideoBitrate = 200 * 1000;	// 200kbps
	BRAC_SetSDKOption(BRAC_SO_RECORD_VIDEOBR,(PCHAR)&dwVideoBitrate,sizeof(DWORD));
	DWORD dwAudioBitrate = 96 * 1000;	// 96kbps
	BRAC_SetSDKOption(BRAC_SO_RECORD_AUDIOBR,(PCHAR)&dwAudioBitrate,sizeof(DWORD));
	
	// 设置快照临时文件保存路径
	CHAR szSnapShotDirectory[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szSnapShotDirectory,MAX_PATH);
	(strrchr(szSnapShotDirectory,'\\'))[1] = 0; 
	strcat(szSnapShotDirectory,"SnapShot");
	BRAC_SetSDKOption(BRAC_SO_SNAPSHOT_TMPDIR,szSnapShotDirectory,strlen(szSnapShotDirectory));
	
	// 设置SDK临时文件路径
	CHAR szTempPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szTempPath,MAX_PATH);
	(strrchr(szTempPath,'\\'))[1] = 0; 
	strcat(szTempPath,"Temp");
	BRAC_SetSDKOption(BRAC_SO_CORESDK_TMPDIR,szTempPath,strlen(szTempPath));

	// 启用音频自动参数功能（默认关闭）
	DWORD bAudioAutoParam = TRUE;
	BRAC_SetSDKOption(BRAC_SO_AUDIO_AUTOPARAM,(PCHAR)&bAudioAutoParam,sizeof(DWORD));

	// 设置视频显示驱动为DirectShow模式
	DWORD dwVideoDriver = BRAC_VSD_DIRECTSHOW;
	BRAC_SetSDKOption(BRAC_SO_VIDEOSHOW_DRIVERCTRL,(const char*)&dwVideoDriver, sizeof(DWORD));

	// 设置服务器认证密码
	BRAC_SetServerAuthPass("BaiRuiTech");		// 需要与服务器配置项“SDKAuthPass”相同（大小写敏感），SDK才能正常连接到服务器
/*	
	DWORD dwVolume = 0;
	BRAC_AudioGetVolume(BRAC_AD_WAVEOUT,dwVolume);
	m_ctrlOutVolume.SetPos(dwVolume);
	
	dwVolume = 0;
	BRAC_AudioGetVolume(BRAC_AD_WAVEIN,dwVolume);
	m_ctrlInVolume.SetPos(dwVolume);
*/
/*	用于测试SDK指定客户端服务端口功能
	DWORD dwTCPService = 8006;
	BRAC_SetSDKOption(BRAC_SO_NETWORK_TCPSERVICEPORT,(PCHAR)&dwTCPService,sizeof(DWORD));
	DWORD dwUDPService = 8008;
	BRAC_SetSDKOption(BRAC_SO_NETWORK_UDPSERVICEPORT,(PCHAR)&dwUDPService,sizeof(DWORD));
*/
}

void CBRAnyChatMeetingDlg::OnPaint() 
{
	CPaintDC paintdc(this);
	// 绘制顶部的Logo图片
	m_LogoPic.Render(&paintdc,CRect(20,0,m_LogoPic.GetImageSize().cx+20,m_LogoPic.GetImageSize().cy));

	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CBRAnyChatMeetingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBRAnyChatMeetingDlg::OnDestroy() 
{
	if(m_pLoginDlg)
	{
		m_pLoginDlg->DestroyWindow();
		delete m_pLoginDlg;
		m_pLoginDlg = NULL;
	}
	if(m_pHallDlg)
	{
		m_pHallDlg->DestroyWindow();
		delete m_pHallDlg;
		m_pHallDlg = NULL;
	}
	if(m_pSettingsDlg)
	{
		m_pSettingsDlg->DestroyWindow();
		delete m_pSettingsDlg;
		m_pSettingsDlg = NULL;
	}

	for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(m_pPanelObjectArray[i])
		{
			CleanVideoPanelBind(m_pPanelObjectArray[i],FALSE);
			m_pPanelObjectArray[i]->DestroyWindow();
			delete m_pPanelObjectArray[i];
			m_pPanelObjectArray[i] = NULL;
		}
	}
	if(m_pSelfVideoDlg)
	{
		CleanVideoPanelBind(m_pSelfVideoDlg,FALSE);
		m_pSelfVideoDlg->DestroyWindow();
		delete m_pSelfVideoDlg;
		m_pSelfVideoDlg = NULL;
	}
	m_UserStateImageList.DeleteImageList();
	// 释放SDK 资源
	BRAC_Release();
	CDialog::OnDestroy();
}

int CBRAnyChatMeetingDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	

	
	return 0;
}

// 用户关闭系统
void CBRAnyChatMeetingDlg::OnUserExitSystem(void)
{
	PostQuitMessage(0);
//	CDialog::DestroyWindow();
}

// 连接服务器消息
void CBRAnyChatMeetingDlg::OnAnyChatConnectMessage(BOOL bSuccess, DWORD dwErrorCode)
{
	if(m_pLoginDlg)
		m_pLoginDlg->OnConnectNotify(bSuccess ? GV_ERR_SUCCESS : dwErrorCode);
}
// 用户登陆消息
void CBRAnyChatMeetingDlg::OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode)
{
	if(m_pLoginDlg)
		m_pLoginDlg->OnLoginNotify(dwErrorCode);
	// 如果登录成功，则隐藏登录界面，显示房间大厅界面
	if(dwErrorCode == GV_ERR_SUCCESS)
	{
		m_dwSelfUserId = dwUserId;
		if(m_pLoginDlg)
			m_pLoginDlg->ShowWindow(SW_HIDE);
		if(m_pHallDlg)
		{
			m_pHallDlg->UpdateUserInfo(dwUserId);
			m_pHallDlg->ShowWindow(SW_SHOW);	
		}
	}
}
// 用户进入房间消息
void CBRAnyChatMeetingDlg::OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode)
{
	if(m_pHallDlg)
		m_pHallDlg->OnEnterRoomNotify(dwRoomId,dwErrorCode);
	// 如果进入房间成功，则显示主界面，隐藏房间大厅界面
	if(dwErrorCode == GV_ERR_SUCCESS)
	{
		if(m_pHallDlg)
			m_pHallDlg->ShowWindow(SW_HIDE);
		ShowWindow(SW_SHOW);
		// 将输入焦点定位在输入栏
		GetDlgItem(IDC_EDIT_TEXTINPUT)->SetFocus();
		if(m_pSelfVideoDlg)
		{
			BindUserAndVideoPanel(m_dwSelfUserId,m_pSelfVideoDlg);
		}
		// 调整为单屏模式
		m_ctrlDispNumCombo.SetCurSel(0);
		RelocateVideoPanel(1);

		// 清空文字消息输入框中的内容
		m_strTextOutput.Empty();
		m_ctrlTextOutput.SetWindowText("");
		// 插入欢迎信息
		CString strWelcomeMsg;

		CHAR szConfigFile[MAX_PATH] = {0};
		::GetModuleFileName(NULL,szConfigFile,_MAX_PATH);
		(strrchr(szConfigFile,'\\'))[1] = 0; 
		strcat(szConfigFile,DEFAULT_CONFIG_FILENAME);
		
		TCHAR szTempStr[200] = {0};
		// 读产品名称
		if(::GetPrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ProductName"),NULL,szTempStr,sizeof(szTempStr),szConfigFile))
			strWelcomeMsg.Format("欢迎使用%s，您已成功进入%d号会议室！",szTempStr, dwRoomId);
		else
			strWelcomeMsg.Format("欢迎使用AnyChat音视频互动平台，您已成功进入%d号会议室！",dwRoomId);
		InsertStringToTextOutput(strWelcomeMsg);
	}
}
// 房间在线用户消息
void CBRAnyChatMeetingDlg::OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId)
{
	DWORD dwOtherUsersNum = 0;
	// 清空之前的所有数据
	m_ctrlUserList.DeleteAllItems();
	// 将自己加入列表第一行（因为自己的信息不在在线用户列表中）
	AddNewUserToList(m_dwSelfUserId);
	
	BRAC_GetOnlineUser(NULL,dwOtherUsersNum);		///< 首先获取房间内在线人数
	if(dwOtherUsersNum)
	{
		LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwOtherUsersNum);
		if(lpdwUserList)
		{
			BRAC_GetOnlineUser(lpdwUserList,dwOtherUsersNum);	///< 真正获取在线用户列表
			// 添加新的用户列表
			for(int i=0; i<(INT)dwOtherUsersNum; i++)
				AddNewUserToList(lpdwUserList[i]);
			free(lpdwUserList);		// 释放资源
		}
	}

	// 刷新在线用户数显示
	RefreshOnlineUserNum();
	// 刷新面板显示
	RefreshVideoPanel();
}

// 用户进入/退出房间消息
void CBRAnyChatMeetingDlg::OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter)
{
	if(bEnter)
	{
		AddNewUserToList(dwUserId);
		// 刷新面板显示，当有空余位置时，自动分配显示面板，并打开视频
		if(GetEmptyVideoPanelIndex() != -1)
			RefreshVideoPanel();
	}
	else
	{
		// 用户离开房间，需要从列表中清除该用户的记录
		INT iItemCount = m_ctrlUserList.GetItemCount();
		for(int i=0; i<iItemCount; i++)
		{
			if(m_ctrlUserList.GetItemData(i) == dwUserId)
			{
				m_ctrlUserList.DeleteItem(i);
				break;
			}
		}
		// 清除与该用户相关的面板
		BOOL bReleaseEmptyPanel = FALSE;
		for(int k=0; k<MAX_VIDEOPANEL_NUM; k++)
		{
			if(m_pPanelObjectArray[k] && m_pPanelObjectArray[k]->GetUserId() == dwUserId)
			{
				bReleaseEmptyPanel = TRUE;
				CleanVideoPanelBind(m_pPanelObjectArray[k]);
				break;
			}
		}
		// 重新刷新一次视频面板，将空余出来的面板分配给其它的用户
		if(bReleaseEmptyPanel)
			RefreshVideoPanel();
	}
	// 刷新在线用户数显示
	RefreshOnlineUserNum();

	// 插入Log信息
	CHAR szUserName[50] = {0};
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_NICKNAME,szUserName,sizeof(szUserName));
	CTime tm = CTime::GetCurrentTime();
	CString strMessage;
	strMessage.Format("用户%s(%d)%s房间----(%s)",szUserName,(int)dwUserId,bEnter ? "进入" : "离开",tm.Format("%H:%M:%S"));
	InsertStringToTextOutput(strMessage);
}
//网络断开消息
void CBRAnyChatMeetingDlg::OnAnyChatLinkCloseMessage(DWORD dwReason, DWORD dwErrorCode)
{
	if(m_pSelfVideoDlg)
	{
		CleanVideoPanelBind(m_pSelfVideoDlg,FALSE);
	}
	for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(m_pPanelObjectArray[i])
		{
			CleanVideoPanelBind(m_pPanelObjectArray[i],FALSE);
		}
	}
	BRAC_LeaveRoom(-1);
	BRAC_Logout();		// 避免SDK内部重新连接
	m_dwSelfUserId = INVALID_USERID;
	

	CHAR szNotify[100] = {0};
	_snprintf(szNotify,sizeof(szNotify),"网络连接已断开(出错代码:%d)\r\n\r\n按确定返回登录界面，按取消退出系统！",dwErrorCode);
	if(::MessageBox(m_hWnd,szNotify,"提示",MB_OKCANCEL|MB_ICONQUESTION) == IDOK)
	{
		// 隐藏设置面板
		if(m_pSettingsDlg)
			m_pSettingsDlg->ShowWindow(SW_HIDE);
		// 隐藏大厅界面
		if(m_pHallDlg)
			m_pHallDlg->ShowWindow(SW_HIDE);
		// 隐藏当前界面
		ShowWindow(SW_HIDE);
		// 显示登录界面
		if(m_pLoginDlg)
			m_pLoginDlg->OnNeedShowLoginDlg();
	}
	else
	{
		OnUserExitSystem();
	}
}
// 用户得到/释放mic消息
void CBRAnyChatMeetingDlg::OnAnyChatMicStateChgMessage(DWORD dwUserId, BOOL bGetMic)
{
	INT iItemCount = m_ctrlUserList.GetItemCount();
	for(int i=0; i<iItemCount; i++)
	{
		if(m_ctrlUserList.GetItemData(i) == dwUserId)
		{
			RefreshListItemState(i,dwUserId);
			break;
		}
	}
}

// 用户摄像头状态改变消息
void CBRAnyChatMeetingDlg::OnAnyChatCameraStateChgMessage(DWORD dwUserId, DWORD dwState)
{
	INT iItemCount = m_ctrlUserList.GetItemCount();
	for(int i=0; i<iItemCount; i++)
	{
		if(m_ctrlUserList.GetItemData(i) == dwUserId)
		{
			RefreshListItemState(i,dwUserId);
			break;
		}
	}
}
// 用户聊天模式改变消息
void CBRAnyChatMeetingDlg::OnAnyChatChatModeChgMessage(DWORD dwUserId, BOOL bPublicChat)
{

}
// 用户活动状态发生变化消息
void CBRAnyChatMeetingDlg::OnAnyChatActiveStateChgMessage(DWORD dwUserId, DWORD dwState)
{

}
// P2P连接状态变化消息
void CBRAnyChatMeetingDlg::OnAnyChatP2PConnectStateMessage(DWORD dwUserId, DWORD dwState)
{

}
/**
 *	用户视频分辨率改变消息
 *	应用程序可根据用户的原始分辨率调节显示视频画面的大小，保持画面的比例不失真
 */
void CBRAnyChatMeetingDlg::OnAnyChatVideoSizeChgMessage(DWORD dwUserId, DWORD dwWidth, DWORD dwHeight)
{
	for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(m_pPanelObjectArray[i])
		{
			if(m_pPanelObjectArray[i]->GetUserId() == dwUserId)
			{
				m_pPanelObjectArray[i]->OnVideoSizeChange(dwWidth, dwHeight);
				break;
			}
		}
	}
}

// 用户私聊请求消息
void CBRAnyChatMeetingDlg::OnAnyChatPrivateRequestMessage(DWORD dwUserId, DWORD dwRequestId)
{

}
// 用户私聊请求回复消息
void CBRAnyChatMeetingDlg::OnAnyChatPrivateEchoMessage(DWORD dwUserId, DWORD dwErrorCode)
{

}
// 用户退出私聊消息
void CBRAnyChatMeetingDlg::OnAnyChatPrivateExitMessage(DWORD dwUserId, DWORD dwErrorCode)
{

}

// SDK警告消息
void CBRAnyChatMeetingDlg::OnAnyChatSDKWarningMessage(DWORD dwErrorCode, DWORD dwReserved)
{

}

// 视频数据回调
void CBRAnyChatMeetingDlg::OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader)
{
	if(dwUserid == m_dwSelfUserId && m_pSelfVideoDlg)
		m_pSelfVideoDlg->OnRecvCallBackVideoData(lpBuf,dwLen,*lpbmiHeader);
	else
	{
		for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
		{
			if(m_pPanelObjectArray[i])
			{
				if(m_pPanelObjectArray[i]->GetUserId() == dwUserid)
				{
					m_pPanelObjectArray[i]->OnRecvCallBackVideoData(lpBuf,dwLen,*lpbmiHeader);
					break;
				}
			}
		}
	}
}
// 音频数据回调
void CBRAnyChatMeetingDlg::OnAnyChatAudioDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPWAVEFORMATEX lpWaveFormatEx)
{

}
// 发送文字的回调函数
void CBRAnyChatMeetingDlg::OnAnyChatTextMsgCallBack(DWORD dwFromUserid, DWORD dwToUserid, BOOL bSecret, LPCTSTR lpMsgBuf, DWORD dwLen)
{
	CString strMessage;

	CHAR szUserName[50] = {0};
	BRAC_QueryUserState(dwFromUserid,BRAC_USERSTATE_NICKNAME,szUserName,sizeof(szUserName));
	CTime tm = CTime::GetCurrentTime();
	strMessage.Format("%s说：%s (%s)",szUserName,lpMsgBuf,tm.Format("%H:%M:%S"));
	InsertStringToTextOutput(strMessage);
}
// 透明通道回调函数
void CBRAnyChatMeetingDlg::OnAnyChatTransBufferCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen)
{

}
// 透明通道数据扩展回调函数
void CBRAnyChatMeetingDlg::OnAnyChatTransBufferExCallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId)
{

}
// 文件传输回调函数
void CBRAnyChatMeetingDlg::OnAnyChatTransFileCallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId)
{

}
// 音量变化回调函数
void CBRAnyChatMeetingDlg::OnAnyChatVolumeChangeCallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume)
{
	if(m_pSettingsDlg)
		m_pSettingsDlg->OnSystemVolumeChangeNotify(device,dwCurrentVolume);
}
// SDK Filter 通信数据回调函数
void CBRAnyChatMeetingDlg::OnAnyChatSDKFilterDataCallBack(LPBYTE lpBuf, DWORD dwLen)
{

}
// 录像、快照任务完成回调函数
void CBRAnyChatMeetingDlg::OnAnyChatRecordSnapShotCallBack(DWORD dwUserid, LPCTSTR lpFileName, DWORD dwParam, BOOL bRecordType)
{

}
// 异步消息通知回调函数
void CBRAnyChatMeetingDlg::OnAnyChatNotifyMessageCallBack(DWORD dwNotifyMsg, DWORD wParam, DWORD lParam)
{

}
/**
 *	用户关闭会议室，退出房间，返回大厅
 */
void CBRAnyChatMeetingDlg::OnClose() 
{
	if(m_pSelfVideoDlg)
	{
		CleanVideoPanelBind(m_pSelfVideoDlg,FALSE);
	}
	for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(m_pPanelObjectArray[i])
		{
			CleanVideoPanelBind(m_pPanelObjectArray[i],FALSE);
		}
	}

	BRAC_LeaveRoom(-1);
	// 隐藏主界面
	ShowWindow(SW_HIDE);
	if(m_pHallDlg)
	{
		m_pHallDlg->ShowWindow(SW_SHOW);
	}

//	CDialog::OnClose();
}

/**
 *	初始化在线用户列表控件
 */
void CBRAnyChatMeetingDlg::InitUserListCtrl(void)
{
	DWORD dwStyle = 0;
	dwStyle = LVS_EX_FULLROWSELECT | LVS_SHAREIMAGELISTS | LVS_REPORT | LVS_EX_FLATSB | LVS_EX_SUBITEMIMAGES;
	dwStyle &= ~LVS_EX_GRIDLINES;
	
	m_ctrlUserList.SetExtendedStyle(dwStyle);
	m_ctrlUserList.ModifyStyle(0, LVS_REPORT);
	m_ctrlUserList.ModifyStyle(0, WS_EX_CLIENTEDGE);
	
	m_ctrlUserList.InsertColumn(0,_T("视频状态"),LVCFMT_CENTER,20);
	m_ctrlUserList.InsertColumn(1,_T("音频状态"),LVCFMT_CENTER,20);
	m_ctrlUserList.InsertColumn(2,_T("用户名"),LVCFMT_LEFT,120);

	m_UserStateImageList.Create(16,16,ILC_COLOR32|ILC_MASK,8,8);
	m_UserStateImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_MIC));
	m_UserStateImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CAMERA_CLOSE));
	m_UserStateImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CAMERA_OPEN));

	m_ctrlUserList.SetImageList(&m_UserStateImageList,LVSIL_SMALL/*LVSIL_NORMAL*/);
}

// 刷新在线用户数显示
void CBRAnyChatMeetingDlg::RefreshOnlineUserNum(void)
{
	DWORD dwUserNum;
	BRAC_GetOnlineUser(NULL,dwUserNum);

	CHAR szUserListTitle[50] = {0};
	_snprintf(szUserListTitle,sizeof(szUserListTitle),"用户列表(%d人在线)",dwUserNum+1);		// 需要加上自己
	GetDlgItem(IDC_STATIC_USERLIST)->SetWindowText(szUserListTitle);
}
// 增加新的用户到列表中
void CBRAnyChatMeetingDlg::AddNewUserToList(DWORD dwUserId)
{
	CHAR szUserName[50] = {0};
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_NICKNAME,szUserName,sizeof(szUserName));
	if(dwUserId == m_dwSelfUserId)
		strcat(szUserName,"(自己)");
	
	LVITEM lvi = {0};
	lvi.mask =  LVIF_IMAGE | LVIF_TEXT;
	lvi.iItem = m_ctrlUserList.GetItemCount();		// 新的用户总是插入最尾端
	lvi.iSubItem = 0;
	lvi.iImage = 0;	
	lvi.pszText = "";
	
	INT itemno = m_ctrlUserList.InsertItem(&lvi);
	m_ctrlUserList.SetItemData(itemno,dwUserId);
	m_ctrlUserList.SetItemText(itemno,2,szUserName);
	RefreshListItemState(itemno,dwUserId);
}
/**
 *	刷新指定列表项状态
 *	根据用户设备状态的不同，在用户名前面显示不同的图标
 *	@param dwItemNo 在线用户列表行序号
 *	@param dwUserId 所对应的用户编号
 */
void CBRAnyChatMeetingDlg::RefreshListItemState(DWORD dwItemNo, DWORD dwUserId)
{
	DWORD dwMicImage,dwCameraImage;
	// 查询用户是否拿到Mic
	DWORD dwMicState;
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_HOLDMIC,(char*)&dwMicState,sizeof(dwMicState));
	dwMicImage = dwMicState ? IMAGE_INDEX_MIC : IMAGE_INDEX_NULL;
	// 查询用户的摄像头状态
	DWORD dwCameraState;
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_CAMERA,(char*)&dwCameraState,sizeof(dwCameraState));
	if(dwCameraState == GV_CAMERA_STATE_NULL)
		dwCameraImage = IMAGE_INDEX_NULL;
	else if(dwCameraState == GV_CAMERA_STATE_NORMAL)
		dwCameraImage = IMAGE_INDEX_CAMERA_NORMAL;
	else
		dwCameraImage = IMAGE_INDEX_CAMERA_OPEN;

	m_ctrlUserList.SetItem(dwItemNo,0,LVIF_IMAGE|LVIF_TEXT|LVIF_STATE,NULL,dwCameraImage,NULL,NULL,0);
	m_ctrlUserList.SetItem(dwItemNo,1,LVIF_IMAGE|LVIF_TEXT|LVIF_STATE,NULL,dwMicImage,NULL,NULL,0);
}

/**
 *	获取一个空闲的显示面板序号
 */
DWORD CBRAnyChatMeetingDlg::GetEmptyVideoPanelIndex(void)
{
	DWORD dwIndex = -1;
	DWORD dwCurrentDispNum = m_ctrlDispNumCombo.GetItemData(m_ctrlDispNumCombo.GetCurSel());
	for(int i=0; i<(int)dwCurrentDispNum && i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(m_pPanelObjectArray[i] && m_pPanelObjectArray[i]->GetUserId() == INVALID_USERID)
		{
			dwIndex = i;
			break;
		}
	}
	return dwIndex;
}

// 判断指定用户的视频面板是否已显示出来
BOOL CBRAnyChatMeetingDlg::IsUserVideoPanelShow(DWORD dwUserId)
{
	BOOL bAlreadyShow = FALSE;
	for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(m_pPanelObjectArray[i] && m_pPanelObjectArray[i]->GetUserId() == dwUserId)
		{
			bAlreadyShow = TRUE;
			break;
		}
	}
	return bAlreadyShow;
}

// 刷新视频显示面板
void CBRAnyChatMeetingDlg::RefreshVideoPanel(void)
{
	DWORD dwOtherUsersNum = 0;
	BRAC_GetOnlineUser(NULL,dwOtherUsersNum);		///< 首先获取房间内在线人数
	if(dwOtherUsersNum)
	{
		LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwOtherUsersNum);
		if(lpdwUserList)
		{
			BRAC_GetOnlineUser(lpdwUserList,dwOtherUsersNum);	///< 真正获取在线用户列表
			BOOL bNoneEmptySite = FALSE;
			// 第一次循环，为空闲位置找到视频打开的用户，并显示出来
			for(int i=0; i<(INT)dwOtherUsersNum; i++)
			{
				DWORD dwEmptyIndex = GetEmptyVideoPanelIndex();
				if(dwEmptyIndex == -1)
				{
					bNoneEmptySite = TRUE;
					break;
				}
				DWORD dwUserId = lpdwUserList[i];
				if(IsUserVideoPanelShow(dwUserId))
					continue;
				// 查询用户的摄像头状态
				DWORD dwCameraState;
				BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_CAMERA,(char*)&dwCameraState,sizeof(dwCameraState));
				if(dwCameraState == IMAGE_INDEX_CAMERA_OPEN)
				{
					BindUserAndVideoPanel(dwUserId,m_pPanelObjectArray[dwEmptyIndex]);
				}
			}
			// 第二次循环，为空闲位置按顺序分配用户
			for(int k=0; k<(INT)dwOtherUsersNum && !bNoneEmptySite; k++)
			{
				DWORD dwEmptyIndex = GetEmptyVideoPanelIndex();
				if(dwEmptyIndex == -1)
					break;
				DWORD dwUserId = lpdwUserList[k];
				if(!IsUserVideoPanelShow(dwUserId))
				{
					BindUserAndVideoPanel(dwUserId,m_pPanelObjectArray[dwEmptyIndex]);
				}
			}
			free(lpdwUserList);		// 释放资源
		}
	}
	else
	{
		// 没有其它的用户，隐藏所有视频面板
		for(int i=0; i<MAX_VIDEOPANEL_NUM; i++)
		{
			if(m_pPanelObjectArray[i])
			{
				CleanVideoPanelBind(m_pPanelObjectArray[i]);
			}
		}
	}
}

// 根据分屏数定位视频面板显示位置
void CBRAnyChatMeetingDlg::RelocateVideoPanel(DWORD dwSplitNum)
{
	CRect rcPanel[MAX_VIDEOPANEL_NUM] = {0};
	CRect rcClient;
	GetDlgItem(IDC_STATIC_REMOTEVIDEO)->GetWindowRect(rcClient);
	ScreenToClient(rcClient);
	switch(dwSplitNum)
	{
	case 1:
		rcPanel[0] = rcClient;
		break;
	case 2:
		rcPanel[0] = rcClient;	rcPanel[0].right = rcPanel[0].left + rcClient.Width()/2;
		rcPanel[1] = rcClient;	rcPanel[1].left = rcPanel[0].left + rcClient.Width()/2;
		break;
	case 4:
		rcPanel[0] = rcClient;	rcPanel[0].right = rcPanel[0].left + rcClient.Width()/2;	rcPanel[0].bottom = rcPanel[0].top + rcClient.Height()/2;
		rcPanel[1] = rcClient;	rcPanel[1].left = rcPanel[0].left + rcClient.Width()/2;		rcPanel[1].bottom = rcPanel[1].top + rcClient.Height()/2;
		rcPanel[2] = rcClient;	rcPanel[2].right = rcPanel[2].left + rcClient.Width()/2;	rcPanel[2].top = rcPanel[2].top + rcClient.Height()/2;
		rcPanel[3] = rcClient;	rcPanel[3].left = rcPanel[3].left + rcClient.Width()/2;		rcPanel[3].top = rcPanel[3].top + rcClient.Height()/2;
		break;
	default:
		break;
	}
	for (int i=0; i<MAX_VIDEOPANEL_NUM; i++)
	{
		if(i<(int)dwSplitNum)
		{
			m_pPanelObjectArray[i]->MoveWindow(rcPanel[i]);
			m_pPanelObjectArray[i]->ShowWindow(SW_SHOW);
			m_pPanelObjectArray[i]->Invalidate();
		}
		else
		{
			CleanVideoPanelBind(m_pPanelObjectArray[i]);
			m_pPanelObjectArray[i]->ShowWindow(SW_HIDE);
		}
	}
	RefreshVideoPanel();
}

// 绑定用户与视频面板
void CBRAnyChatMeetingDlg::BindUserAndVideoPanel(DWORD dwUserId, CVideoPanelDlg* lpVideoPanelDlg)
{
	ASSERT(lpVideoPanelDlg);
	CHAR szUserName[50] = {0};
	BRAC_QueryUserState(dwUserId,BRAC_USERSTATE_NICKNAME,szUserName,sizeof(szUserName));
	lpVideoPanelDlg->SetRelateUserId(dwUserId);
	lpVideoPanelDlg->SetPanelTitle(dwUserId == m_dwSelfUserId ? "本地视频" : szUserName);
}
// 取消视频面板与用户的绑定
void CBRAnyChatMeetingDlg::CleanVideoPanelBind(CVideoPanelDlg* lpVideoPanelDlg, BOOL bErase)
{
	ASSERT(lpVideoPanelDlg);
	lpVideoPanelDlg->SetRelateUserId(INVALID_USERID);
	lpVideoPanelDlg->SetPanelTitle("");
	if(bErase && IsWindowVisible())
		lpVideoPanelDlg->Invalidate();
}

/**
 *	用户选择分屏显示下拉列表
 */
void CBRAnyChatMeetingDlg::OnSelchangeComboDispNum() 
{
	DWORD dwSelectSplitNum = m_ctrlDispNumCombo.GetItemData(m_ctrlDispNumCombo.GetCurSel());
	RelocateVideoPanel(dwSelectSplitNum);
}
/**
 *	用户双击用户列表项，需要将对应的用户视频显示出来
 */
void CBRAnyChatMeetingDlg::OnDblclkListUser(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	INT itemno = pNMListView->iItem;
	do 
	{
		if(itemno < 0)
			break;
		DWORD dwUserId = m_ctrlUserList.GetItemData(itemno);
		if(dwUserId == INVALID_USERID || dwUserId == m_dwSelfUserId)
			break;
		if(IsUserVideoPanelShow(dwUserId))
			break;
		DWORD dwEmptySite = GetEmptyVideoPanelIndex();
		if(dwEmptySite == -1)	// 没有空的位置了，默认将0号位置分配给新的用户
		{
			dwEmptySite = 0;
			CleanVideoPanelBind(m_pPanelObjectArray[0]);
		}
		BindUserAndVideoPanel(dwUserId,m_pPanelObjectArray[dwEmptySite]);
	} while (FALSE);
	*pResult = 0;
}

BOOL CBRAnyChatMeetingDlg::PreTranslateMessage(MSG* pMsg) 
{
	HWND hTextInputWnd = GetDlgItem(IDC_EDIT_TEXTINPUT)->GetSafeHwnd();
	HWND hTextOutputWnd =GetDlgItem(IDC_EDIT_TEXTOUTPUT)->GetSafeHwnd();

	BOOL bNeedTranslate = TRUE;
	if(pMsg->message == WM_KEYDOWN)
    {
		switch(pMsg->wParam)
        {
        case VK_RETURN:
			if(pMsg->hwnd == hTextInputWnd)
				OnButtonSendText();
			bNeedTranslate = FALSE;
			break;
        case VK_SPACE:
			if(pMsg->hwnd != hTextInputWnd)
				bNeedTranslate = FALSE;
			break;
		case VK_ESCAPE:
			bNeedTranslate = FALSE;
			break;
		default:
			break;
        }
	}
	else if(pMsg->message == WM_RBUTTONDOWN)
	{
		bNeedTranslate = FALSE;		// 暂时不响应右键消息，因为皮肤库的原因，会导致弹出来的菜单有问题
	}
	
	return bNeedTranslate ? CDialog::PreTranslateMessage(pMsg) : TRUE;
}
/**
 *	用户按下发送文字消息按钮
 */
void CBRAnyChatMeetingDlg::OnButtonSendText() 
{
	CString strInput,strMessage;
	GetDlgItem(IDC_EDIT_TEXTINPUT)->GetWindowText(strInput);
	if(!strInput.IsEmpty())
	{
		BRAC_SendTextMessage(-1,FALSE,strInput.GetBuffer(0),strInput.GetLength());
		
		CTime tm = CTime::GetCurrentTime();
		strMessage.Format("我说：%s (%s)",strInput,tm.Format("%H:%M:%S"));
		InsertStringToTextOutput(strMessage);
	}
	GetDlgItem(IDC_EDIT_TEXTINPUT)->SetWindowText("");
	GetDlgItem(IDC_EDIT_TEXTINPUT)->SetFocus();
}

// 向文字消息输出框插入信息
void CBRAnyChatMeetingDlg::InsertStringToTextOutput(CString strMsg)
{
	m_strTextOutput += (strMsg + "\r\n");
	m_ctrlTextOutput.SetWindowText(m_strTextOutput);
	m_ctrlTextOutput.LineScroll(m_ctrlTextOutput.GetLineCount());
}
/**
 *	用户按下高级设置按钮，显示设置界面
 */
void CBRAnyChatMeetingDlg::OnButtonAdvSet() 
{
	if(!m_pSettingsDlg)
	{
		m_pSettingsDlg = new CSettingsDlg(this);
		m_pSettingsDlg->Create(IDD_DIALOG_SETTINGS,this);
	}
	m_pSettingsDlg->ShowWindow(SW_SHOW);
	m_pSettingsDlg->CenterWindow();
}

void CBRAnyChatMeetingDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	OnButtonAdvSet();
	PostMessage (WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialog::OnLButtonDown(nFlags, point);
}
