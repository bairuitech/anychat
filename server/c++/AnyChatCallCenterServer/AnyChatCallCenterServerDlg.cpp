// AnyChatCallCenterServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnyChatCallCenterServer.h"
#include "AnyChatCallCenterServerDlg.h"

#include "AnyChatServerSDK.h"
#pragma comment(lib,"AnyChatServerSDK.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define SENDBUF_STYLE_SYSTEM	0		///< 系统广播
#define SENDBUF_STYLE_ROOM		1		///< 房间广播
#define SENDBUF_STYLE_USER		2		///< 指定用户

#define TIMER_REFRESH_ONLINES	1		///< 刷新在线用户数定时器



// 服务器应用程序消息回调函数定义
void CALLBACK OnServerAppMessageExCallBack(DWORD dwNotifyMessage, DWORD wParam, DWORD lParam, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(dwNotifyMessage == BRAS_MESSAGE_CORESERVERCONN)
	{
		lpServerDlg->m_dwOnlineUsers = 0;
		if(wParam == 0)
			lpServerDlg->AppendLogString("Success connected with AnyChatCoreServer...");
		else
			lpServerDlg->AppendLogString("Disconnected from the AnyChatCoreServer");
		// 清空在线用户列表
		lpServerDlg->m_onlineUserList.clear();
	}
	else if(dwNotifyMessage == BRAS_MESSAGE_RECORDSERVERCONN)
	{
		if(wParam == 0)
		{
			CString strNotify;
			strNotify.Format("Success connected with AnyChatRecordServer...(serverid:%d)", lParam);
			lpServerDlg->AppendLogString(strNotify);
		}
		else
		{
			CString strNotify;
			strNotify.Format("Disconnected from the AnyChatRecordServer...(errorcode:%d, serverid:%d)", wParam, lParam);
			lpServerDlg->AppendLogString(strNotify);
		}
	}
	else
	{
		CString strNotify;
		strNotify.Format("OnServerAppMessageExCallBack(dwNotifyMessage:%d, wParam:%d, lParam:%d)", dwNotifyMessage, wParam, lParam);
		lpServerDlg->AppendLogString(strNotify);
	}
}

/**
 *	SDK定时器回调函数定义，上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器
 *	如果单独开启线程，或是注册Windows定时器，则必须考虑多线程同步的问题
 *	而使用SDK的TimerEvent回调，则不需要考虑，因为定时器回调和别的回调函数均是顺序触发的
 */
void CALLBACK OnTimerEventCallBack(LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
//		lpServerDlg->AppendLogString("定时器事件");
	}
}

// 用户身份验证回调函数定义
DWORD CALLBACK VerifyUserCallBack(IN LPCTSTR lpUserName,IN LPCTSTR lpPassword, OUT LPDWORD lpUserID, OUT LPDWORD lpUserLevel, OUT LPTSTR lpNickName,IN DWORD dwNCLen, LPVOID lpUserValue)
{
	static DWORD dwUserIdSeed = 1;
	*lpUserID = dwUserIdSeed++;

	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("VerifyUser(%s - %s) --> userid(%d)"),lpUserName,lpPassword,(int)*lpUserID);
		lpServerDlg->AppendLogString(strMsg);
	}
	return 0;
}
// 用户申请进入房间回调函数定义
DWORD CALLBACK PrepareEnterRoomCallBack(DWORD dwUserId, DWORD dwRoomId, LPCTSTR lpRoomName,LPCTSTR lpPassword, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("PrepareEnterRoom(dwUserId:%d - dwRoomId:%d)"),(int)dwUserId,(int)dwRoomId);
		lpServerDlg->AppendLogString(strMsg);
	}
	return 0;
}
// 用户登录成功回调函数定义
void CALLBACK OnUserLoginActionCallBack(DWORD dwUserId, LPCTSTR szUserName, DWORD dwLevel, LPCTSTR szIpAddr, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(!lpServerDlg)
		return;
	
	// 添加用户分组
	int iGroupId = 1;
	BRAS_UserInfoControl(dwUserId, BRAS_USERINFO_CTRLCODE_ADDGROUP, iGroupId, 0, "我的好友");	// 用户名+密码方式登录的用户
	iGroupId = 2;
	BRAS_UserInfoControl(dwUserId, BRAS_USERINFO_CTRLCODE_ADDGROUP, iGroupId, 0, "在线游客");	// 密码为空的用户

	// 将当前所有在线用户添加为自己的好友
	std::list<DWORD>::iterator it = lpServerDlg->m_onlineUserList.begin();
	while(it != lpServerDlg->m_onlineUserList.end())
	{
		DWORD otheruserid = *it;
		BRAS_UserInfoControl(dwUserId, BRAS_USERINFO_CTRLCODE_ADDFRIEND, otheruserid, 0, "");
		it++;
	}

	// 设置好友与分组的关系（即好友属于哪一个分组）
	iGroupId = 1;
	it = lpServerDlg->m_onlineUserList.begin();
	while(it != lpServerDlg->m_onlineUserList.end())
	{
		DWORD otheruserid = *it;
		iGroupId = (otheruserid > 0) ? 1 : 2;		// 游客密码为空，userid由核心服务器分配，为负数
		BRAS_UserInfoControl(dwUserId, BRAS_USERINFO_CTRLCODE_SETGROUPRELATION, iGroupId, otheruserid, "");
		it++;
	}

	// 设置当前用户信息（用户资料，客户端可以通过API：BRAC_GetUserInfo来获取这些信息）
	int iInfoId = 1;	// InfoId由业务层自己定义
	BRAS_SetUserInfo(dwUserId, iInfoId, szUserName, 0);
	iInfoId = 2;
	BRAS_SetUserInfo(dwUserId, iInfoId, szIpAddr, 0);
	iInfoId = 3;
	BRAS_SetUserInfo(dwUserId, iInfoId, "我的签名", 0);
	iInfoId = 4;
	CHAR szImageId[10] = {0};
	_snprintf(szImageId, sizeof(szImageId), "%d", dwUserId%10 + 1);
	BRAS_SetUserInfo(dwUserId, iInfoId, szImageId, 0);		// 随机分配一个图像ID

	// 将本地用户添加为其它用户的好友列表中
	it = lpServerDlg->m_onlineUserList.begin();
	while(it != lpServerDlg->m_onlineUserList.end())
	{
		DWORD otheruserid = *it;
		// 添加好友
		BRAS_UserInfoControl(otheruserid, BRAS_USERINFO_CTRLCODE_ADDFRIEND, dwUserId, 0, "");
		// 关联好友分组
		iGroupId = (dwUserId > 0) ? 1 : 2;
		BRAS_UserInfoControl(otheruserid, BRAS_USERINFO_CTRLCODE_SETGROUPRELATION, iGroupId, dwUserId, "");
		// 下发同步指令，将新设置的好友同步给客户端
		BRAS_UserInfoControl(otheruserid, BRAS_USERINFO_CTRLCODE_SYNCDATA,  0, 0, "");
		it++;
	}

	// 下发同步指令，将前面设置的资料同步给当前客户端
	BRAS_UserInfoControl(dwUserId, BRAS_USERINFO_CTRLCODE_SYNCDATA,  0, 0, "");

	// 将本地用户加入在线用户列表
	lpServerDlg->m_onlineUserList.push_back(dwUserId);

	lpServerDlg->m_dwOnlineUsers++;
	if(lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserLoginAction(dwUserId:%d - Name:%s)"),(int)dwUserId,szUserName);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 用户注销回调函数定义
void CALLBACK OnUserLogoutActionExCallBack(DWORD dwUserId, DWORD dwErrorCode, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(!lpServerDlg)
		return;

	// 从在线用户列表中删除
	std::list<DWORD>::iterator it = lpServerDlg->m_onlineUserList.begin();
	while(it != lpServerDlg->m_onlineUserList.end())
	{
		if(*it == dwUserId)
		{
			lpServerDlg->m_onlineUserList.erase(it);
			break;
		}
	}
	// 核心服务器会通知其它用户（如果是好友），提示好友下线，不需要业务服务器干预

	lpServerDlg->m_dwOnlineUsers--;
	if(lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserLogoutAction(dwUserId:%d, dwErrorCode:%d)"),(int)dwUserId, dwErrorCode);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 用户进入房间回调函数定义
void CALLBACK OnUserEnterRoomActionCallBack(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserEnterRoomAction(dwUserId:%d - dwRoomId:%d)"),(int)dwUserId,(int)dwRoomId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 用户离开房间回调函数定义
void CALLBACK OnUserLeaveRoomActionCallBack(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserLeaveRoomAction(dwUserId:%d - dwRoomId:%d)"),(int)dwUserId,(int)dwRoomId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 上层业务自定义数据回调函数定义
void CALLBACK OnRecvUserFilterDataCallBack(DWORD dwUserId, BYTE* lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnRecvUserFilterData(dwUserId:%d - Buf:%s)"),(int)dwUserId,lpBuf);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 收到用户文字聊天通信数据回调函数定义
void CALLBACK OnRecvUserTextMsgCallBack(DWORD dwRoomId, DWORD dwSrcUserId, DWORD dwTarUserId, BOOL bSecret, LPCTSTR lpTextMessage, DWORD dwLen, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnRecvUserTextMsg(dwRoomId:%d, dwSrcUserId:%d, dwTarUserId:%d - Buf:%s)"),(int)dwRoomId,(int)dwSrcUserId,(int)dwTarUserId,lpTextMessage);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 透明通道数据回调函数定义
void CALLBACK OnTransBufferCallBack(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnTransBufferCallBack(dwUserId:%d - BufLen:%d)"),(int)dwUserId,dwLen);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 透明通道数据扩展回调函数定义
void CALLBACK OnTransBufferExCallBack(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnTransBufferExCallBack(dwUserId:%d - BufLen:%d - wParam:%d - lParam:%d - dwTaskId:%d)"),(int)dwUserId,dwLen, wParam, lParam, dwTaskId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 文件传输回调函数定义
void CALLBACK OnTransFileCallBack(DWORD dwUserId, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg && lpServerDlg->m_bShowUserLog)
	{
		CString strMsg;
		strMsg.Format(_T("OnTransFileCallBack(dwUserId:%d, PathName:%s - wParam:%d - lParam:%d - dwTaskId:%d)"),(int)dwUserId, lpFileName, wParam, lParam, dwTaskId);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 服务器录像回调函数定义
void CALLBACK OnServerRecord_CallBack(DWORD dwUserId, DWORD dwParam, DWORD dwRecordServerId, DWORD dwElapse, LPCTSTR lpRecordFileName, LPVOID lpUserValue)
{
	CAnyChatCallCenterServerDlg* lpServerDlg = (CAnyChatCallCenterServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnServerRecordCallBack(dwUserId:%d, FileName:%s)"),(int)dwUserId, lpRecordFileName);
		lpServerDlg->AppendLogString(strMsg);
	}
}


CAnyChatCallCenterServerDlg::CAnyChatCallCenterServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnyChatCallCenterServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnyChatCallCenterServerDlg)
	m_iTargetId = 0;
	m_bShowUserLog = FALSE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnyChatCallCenterServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnyChatCallCenterServerDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_ctrlEditLog);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_ComboStyle);
	DDX_Text(pDX, IDC_EDIT_TARGETID, m_iTargetId);
	DDX_Check(pDX, IDC_CHECK_SHOWLOG, m_bShowUserLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnyChatCallCenterServerDlg, CDialog)
	//{{AFX_MSG_MAP(CAnyChatCallCenterServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SENDBUF, OnButtonSendbuf)
	ON_BN_CLICKED(IDC_BUTTONTRANSFILE, OnButtonTransFile)
	ON_BN_CLICKED(IDC_BUTTONTRANSBUFFEREX, OnButtonTransBufferEx)
	ON_BN_CLICKED(IDC_BUTTON_TRANSBUFFER, OnButtonTransBuffer)
	ON_BN_CLICKED(IDC_BUTTON_STARTRECORD, OnButtonStartRecord)
	ON_BN_CLICKED(IDC_BUTTON_STOPRECORD, OnButtonStopRecord)
	ON_BN_CLICKED(IDC_CHECK_SHOWLOG, OnCheckShowLog)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_KICKOUT, OnButtonKickOut)
	ON_BN_CLICKED(IDC_BUTTON_HANGUP, OnButtonHangUp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatCallCenterServerDlg message handlers

BOOL CAnyChatCallCenterServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_bShowUserLog = TRUE;
	UpdateData(FALSE);
	
	DWORD dwIndex = m_ComboStyle.AddString(_T("所有用户广播"));
	m_ComboStyle.SetItemData(dwIndex,SENDBUF_STYLE_SYSTEM);
	m_ComboStyle.SetCurSel(dwIndex);
	dwIndex = m_ComboStyle.AddString(_T("指定房间广播"));
	m_ComboStyle.SetItemData(dwIndex,SENDBUF_STYLE_ROOM);
	dwIndex = m_ComboStyle.AddString(_T("指定用户发送"));
	m_ComboStyle.SetItemData(dwIndex,SENDBUF_STYLE_USER);

	
	// 设置服务器应用程序消息回调函数
	BRAS_SetOnServerAppMessageExCallBack(OnServerAppMessageExCallBack,this);
	// 设置SDK定时器回调函数
	BRAS_SetTimerEventCallBack(1000,OnTimerEventCallBack,this);
	// 设置用户身份验证回调函数
	BRAS_SetVerifyUserCallBack(VerifyUserCallBack,this);
	// 设置用户申请进入房间回调函数
	BRAS_SetPrepareEnterRoomCallBack(PrepareEnterRoomCallBack, this);
	// 设置用户登录成功回调函数
	BRAS_SetOnUserLoginActionCallBack(OnUserLoginActionCallBack, this);
	// 设置用户注销回调函数（扩展）
	BRAS_SetOnUserLogoutActionExCallBack(OnUserLogoutActionExCallBack, this);
	// 设置用户进入房间回调函数
	BRAS_SetOnUserEnterRoomActionCallBack(OnUserEnterRoomActionCallBack, this);
	// 设置用户离开房间回调函数
	BRAS_SetOnUserLeaveRoomActionCallBack(OnUserLeaveRoomActionCallBack, this);
	// 设置用户上层业务自定义数据回调函数
	BRAS_SetOnRecvUserFilterDataCallBack(OnRecvUserFilterDataCallBack, this);
	// 用户文字聊天通信数据回调函数
	BRAS_SetOnRecvUserTextMsgCallBack(OnRecvUserTextMsgCallBack,this);
	// 设置透明通道数据回调函数
	BRAS_SetOnTransBufferCallBack(OnTransBufferCallBack, this);
	// 设置透明通道数据扩展回调函数
	BRAS_SetOnTransBufferExCallBack(OnTransBufferExCallBack, this);
	// 设置文件传输回调函数
	BRAS_SetOnTransFileCallBack(OnTransFileCallBack, this);
	// 设置服务器录像回调函数
	BRAS_SetOnServerRecordCallBack(OnServerRecord_CallBack, this);
	
	BRAS_InitSDK(0);

	m_dwOnlineUsers = 0;
	SetTimer(TIMER_REFRESH_ONLINES, 1000, NULL);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnyChatCallCenterServerDlg::OnPaint() 
{
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

HCURSOR CAnyChatCallCenterServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAnyChatCallCenterServerDlg::OnDestroy() 
{
	BRAS_Release();

	CDialog::OnDestroy();
}

void CAnyChatCallCenterServerDlg::OnButtonSendbuf() 
{
	UpdateData(TRUE);
	CString strBuffer;
	GetDlgItemText(IDC_EDIT_SENDBUF,strBuffer);
	if(strBuffer.IsEmpty())
		return;

	DWORD dwStyle = m_ComboStyle.GetCurSel();
	if(dwStyle == SENDBUF_STYLE_SYSTEM)
		BRAS_SendBufToRoom(-1,strBuffer.GetBuffer(0),strBuffer.GetLength());
	else if(dwStyle == SENDBUF_STYLE_ROOM)
		BRAS_SendBufToRoom(m_iTargetId,strBuffer.GetBuffer(0),strBuffer.GetLength());
	else
		BRAS_SendBufToUser(m_iTargetId,strBuffer.GetBuffer(0),strBuffer.GetLength());	
}

/**
 *	显示日志信息
 */
void CAnyChatCallCenterServerDlg::AppendLogString(CString logstr)
{
	m_strLogInfo += (logstr + "\r\n");
	m_ctrlEditLog.SetWindowText(m_strLogInfo);
	m_ctrlEditLog.LineScroll(m_ctrlEditLog.GetLineCount());
}

void CAnyChatCallCenterServerDlg::OnButtonTransFile() 
{
	UpdateData(TRUE);
	if(m_iTargetId == -1)
	{
		AppendLogString("BRAS_TransFile 方法目标用户不能为-1");
		return;
	}
	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)|*.*||");
	CFileDialog dlg(TRUE,_T(""),NULL,  OFN_HIDEREADONLY ,szFilter);
	if(dlg.DoModal() == IDOK)
	{
		DWORD wParam = 1;				// wParam、lParam是附带参数，便于上层应用扩展
		DWORD lParam = 2;
		DWORD dwFlags = 0;
		DWORD dwTaskId = 0;
		DWORD ret = BRAS_TransFile(m_iTargetId, dlg.GetPathName(), wParam, lParam, dwFlags, dwTaskId);
		CString strLog;
		if(ret == 0)
			strLog.Format(_T("BRAS_TransFile 任务提交成功，TaskId:%d"), dwTaskId);
		else
			strLog.Format(_T("BRAS_TransFile 任务提交失败，ErrorCode:%d"), ret);
		AppendLogString(strLog);
	}
}

// 使用透明通道扩展函数向指定用户发送大数据块缓冲区
void CAnyChatCallCenterServerDlg::OnButtonTransBufferEx() 
{
	UpdateData(TRUE);
	if(m_iTargetId == -1)
	{
		AppendLogString("BRAS_TransBufferEx 方法目标用户不能为-1");
		return;
	}
	BYTE szBuf[1024*10] = {0};		// 实验，传一个空缓冲区给目标用户，判断是否能接收到
	DWORD wParam = 1;				// wParam、lParam是附带参数，便于上层应用扩展
	DWORD lParam = 2;
	DWORD dwFlags = 0;
	DWORD dwTaskId = 0;
	DWORD ret = BRAS_TransBufferEx(m_iTargetId, szBuf, sizeof(szBuf), wParam, lParam, dwFlags, dwTaskId);
	CString strLog;
	if(ret == 0)
		strLog.Format(_T("BRAS_TransBufferEx 任务提交成功，TaskId:%d"), dwTaskId);
	else
		strLog.Format(_T("BRAS_TransBufferEx 任务提交失败，ErrorCode:%d"), ret);
	AppendLogString(strLog);
}
// 使用透明通道函数向指定用户发送缓冲区
void CAnyChatCallCenterServerDlg::OnButtonTransBuffer() 
{
	UpdateData(TRUE);
	CString strBuffer;
	GetDlgItemText(IDC_EDIT_SENDBUF,strBuffer);
	if(strBuffer.IsEmpty())
		return;
	if(m_iTargetId == -1)
	{
		AppendLogString("BRAS_TransBuffer 方法目标用户不能为-1");
		return;
	}
	BRAS_TransBuffer(m_iTargetId,(LPBYTE)strBuffer.GetBuffer(0),strBuffer.GetLength());	
}

void CAnyChatCallCenterServerDlg::OnButtonStartRecord() 
{
	UpdateData(TRUE);
	if(m_iTargetId == 0)
	{
		MessageBox("请输入目标用户编号", "警告", MB_OK);
		GetDlgItem(IDC_EDIT_TARGETID)->SetFocus();
		return;
	}
	BRAS_StreamRecordCtrl(m_iTargetId, TRUE, 0, 0, -1);
}

void CAnyChatCallCenterServerDlg::OnButtonStopRecord() 
{
	UpdateData(TRUE);
	if(m_iTargetId == 0)
	{
		MessageBox("请输入目标用户编号", "警告", MB_OK);
		GetDlgItem(IDC_EDIT_TARGETID)->SetFocus();
		return;
	}
	BRAS_StreamRecordCtrl(m_iTargetId, FALSE, 0, 0, -1);
}
/**
 *	用户选择是否显示用户活动日志
 *	当并发用户量大时，显示用户活动日志会影响到服务器程序的性能
 */
void CAnyChatCallCenterServerDlg::OnCheckShowLog() 
{
	UpdateData(TRUE);
}

void CAnyChatCallCenterServerDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_REFRESH_ONLINES)
	{
		CString strNotify;
		strNotify.Format("在线用户数：%d", m_dwOnlineUsers);
		SetDlgItemText(IDC_STATIC_ACTIVEINFO, strNotify);
	}
	CDialog::OnTimer(nIDEvent);
}
/**
 *	将目标用户从系统中踢掉，目标用户将会强制下线
 */
void CAnyChatCallCenterServerDlg::OnButtonKickOut() 
{
	UpdateData(TRUE);
	if(m_iTargetId == 0)
	{
		MessageBox("请输入目标用户编号", "警告", MB_OK);
		GetDlgItem(IDC_EDIT_TARGETID)->SetFocus();
		return;
	}
	BRAS_UserInfoControl(m_iTargetId, BRAS_USERINFO_CTRLCODE_KICKOUT);
}
/**
 *	挂断目标用户的视频呼叫会话，视频呼叫会话为客户端采用API：BRAC_VideoCallControl建立的会话业务
 */
void CAnyChatCallCenterServerDlg::OnButtonHangUp() 
{
	UpdateData(TRUE);
	if(m_iTargetId == 0)
	{
		MessageBox("请输入目标用户编号", "警告", MB_OK);
		GetDlgItem(IDC_EDIT_TARGETID)->SetFocus();
		return;
	}
	BRAS_VideoCallControl(BRAS_VIDEOCALL_EVENT_FINISH, m_iTargetId, 0);
}
