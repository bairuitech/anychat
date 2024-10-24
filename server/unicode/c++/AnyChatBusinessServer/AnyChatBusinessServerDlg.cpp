// AnyChatBusinessServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnyChatBusinessServer.h"
#include "AnyChatBusinessServerDlg.h"

#include "AnyChatServerSDK.h"
#ifdef _UNICODE
#	pragma comment(lib,"AnyChatServerSDKU.lib")
#else
#	pragma comment(lib,"AnyChatServerSDK.lib")
#endif //_UNICODE

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define SENDBUF_STYLE_SYSTEM	0		///< 系统广播
#define SENDBUF_STYLE_ROOM		1		///< 房间广播
#define SENDBUF_STYLE_USER		2		///< 指定用户



// 服务器应用程序消息回调函数定义
void CALLBACK OnServerAppMessageCallBack(DWORD dwMsg, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(dwMsg == BRAS_SERVERAPPMSG_CONNECTED)
		lpServerDlg->AppendLogString(_T("与AnyChat服务器连接成功！"));
	else if(dwMsg == BRAS_SERVERAPPMSG_DISCONNECT)
		lpServerDlg->AppendLogString(_T("与AnyChat服务器断开连接！"));
	else
	{
		CString strMsg;
		strMsg.Format(_T("收到服务器应用程序消息：%d"),dwMsg);
		lpServerDlg->AppendLogString(strMsg);
	}
}

/**
 *	SDK定时器回调函数定义，上层应用可以在该回调中处理定时任务，而不需要额外开启线程，或是定时器
 *	如果单独开启线程，或是注册Windows定时器，则必须考虑多线程同步的问题
 *	而使用SDK的TimerEvent回调，则不需要考虑，因为定时器回调和别的回调函数均是顺序触发的
 */
void CALLBACK OnTimerEventCallBack(LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
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

	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
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
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
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
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserLoginAction(dwUserId:%d - Name:%s)"),(int)dwUserId,szUserName);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 用户注销回调函数定义
void CALLBACK OnUserLogoutActionCallBack(DWORD dwUserId, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserLogoutAction(dwUserId:%d)"),(int)dwUserId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 用户进入房间回调函数定义
void CALLBACK OnUserEnterRoomActionCallBack(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserEnterRoomAction(dwUserId:%d - dwRoomId:%d)"),(int)dwUserId,(int)dwRoomId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 用户离开房间回调函数定义
void CALLBACK OnUserLeaveRoomActionCallBack(DWORD dwUserId, DWORD dwRoomId, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnUserLeaveRoomAction(dwUserId:%d - dwRoomId:%d)"),(int)dwUserId,(int)dwRoomId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 上层业务自定义数据回调函数定义
void CALLBACK OnRecvUserFilterDataCallBack(DWORD dwUserId, BYTE* lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnRecvUserFilterData(dwUserId:%d - Buf:%s)"),(int)dwUserId,lpBuf);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 收到用户文字聊天通信数据回调函数定义
void CALLBACK OnRecvUserTextMsgCallBack(DWORD dwRoomId, DWORD dwSrcUserId, DWORD dwTarUserId, BOOL bSecret, LPCTSTR lpTextMessage, DWORD dwLen, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnRecvUserTextMsg(dwRoomId:%d, dwSrcUserId:%d, dwTarUserId:%d - Buf:%s)"),(int)dwRoomId,(int)dwSrcUserId,(int)dwTarUserId,lpTextMessage);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 透明通道数据回调函数定义
void CALLBACK OnTransBufferCallBack(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnTransBufferCallBack(dwUserId:%d - BufLen:%d)"),(int)dwUserId,dwLen);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 透明通道数据扩展回调函数定义
void CALLBACK OnTransBufferExCallBack(DWORD dwUserId, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnTransBufferExCallBack(dwUserId:%d - BufLen:%d - wParam:%d - lParam:%d - dwTaskId:%d)"),(int)dwUserId,dwLen, wParam, lParam, dwTaskId);
		lpServerDlg->AppendLogString(strMsg);
	}
}
// 文件传输回调函数定义
void CALLBACK OnTransFileCallBack(DWORD dwUserId, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnTransFileCallBack(dwUserId:%d, PathName:%s - wParam:%d - lParam:%d - dwTaskId:%d)"),(int)dwUserId, lpFileName, wParam, lParam, dwTaskId);
		lpServerDlg->AppendLogString(strMsg);
	}
}

// 服务器录像回调函数定义
void CALLBACK OnServerRecord_CallBack(DWORD dwUserId, DWORD dwParam, DWORD dwRecordServerId, DWORD dwElapse, LPCTSTR lpRecordFileName, LPVOID lpUserValue)
{
	CAnyChatBusinessServerDlg* lpServerDlg = (CAnyChatBusinessServerDlg*)lpUserValue;
	if(lpServerDlg)
	{
		CString strMsg;
		strMsg.Format(_T("OnServerRecordCallBack(dwUserId:%d, FileName:%s)"),(int)dwUserId, lpRecordFileName);
		lpServerDlg->AppendLogString(strMsg);
	}
}


CAnyChatBusinessServerDlg::CAnyChatBusinessServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnyChatBusinessServerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnyChatBusinessServerDlg)
	m_iTargetId = 0;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnyChatBusinessServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnyChatBusinessServerDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_ctrlEditLog);
	DDX_Control(pDX, IDC_COMBO_STYLE, m_ComboStyle);
	DDX_Text(pDX, IDC_EDIT_TARGETID, m_iTargetId);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnyChatBusinessServerDlg, CDialog)
	//{{AFX_MSG_MAP(CAnyChatBusinessServerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SENDBUF, OnButtonSendbuf)
	ON_BN_CLICKED(IDC_BUTTONTRANSFILE, OnButtonTransFile)
	ON_BN_CLICKED(IDC_BUTTONTRANSBUFFEREX, OnButtonTransBufferEx)
	ON_BN_CLICKED(IDC_BUTTON_TRANSBUFFER, OnButtonTransBuffer)
	ON_BN_CLICKED(IDC_BUTTON_STARTRECORD, OnButtonStartRecord)
	ON_BN_CLICKED(IDC_BUTTON_STOPRECORD, OnButtonStopRecord)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatBusinessServerDlg message handlers

BOOL CAnyChatBusinessServerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	DWORD dwIndex = m_ComboStyle.AddString(_T("所有用户广播"));
	m_ComboStyle.SetItemData(dwIndex,SENDBUF_STYLE_SYSTEM);
	m_ComboStyle.SetCurSel(dwIndex);
	dwIndex = m_ComboStyle.AddString(_T("指定房间广播"));
	m_ComboStyle.SetItemData(dwIndex,SENDBUF_STYLE_ROOM);
	dwIndex = m_ComboStyle.AddString(_T("指定用户发送"));
	m_ComboStyle.SetItemData(dwIndex,SENDBUF_STYLE_USER);

	
	// 设置服务器应用程序消息回调函数
	BRAS_SetOnServerAppMessageCallBack(OnServerAppMessageCallBack,this);
	// 设置SDK定时器回调函数
	BRAS_SetTimerEventCallBack(1000,OnTimerEventCallBack,this);
	// 设置用户身份验证回调函数
	BRAS_SetVerifyUserCallBack(VerifyUserCallBack,this);
	// 设置用户申请进入房间回调函数
	BRAS_SetPrepareEnterRoomCallBack(PrepareEnterRoomCallBack, this);
	// 设置用户登录成功回调函数
	BRAS_SetOnUserLoginActionCallBack(OnUserLoginActionCallBack, this);
	// 设置用户注销回调函数
	BRAS_SetOnUserLogoutActionCallBack(OnUserLogoutActionCallBack, this);
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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnyChatBusinessServerDlg::OnPaint() 
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

HCURSOR CAnyChatBusinessServerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CAnyChatBusinessServerDlg::OnDestroy() 
{
	BRAS_Release();

	CDialog::OnDestroy();
}

void CAnyChatBusinessServerDlg::OnButtonSendbuf() 
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
void CAnyChatBusinessServerDlg::AppendLogString(CString logstr)
{
	m_strLogInfo += (logstr + "\r\n");
	m_ctrlEditLog.SetWindowText(m_strLogInfo);
	m_ctrlEditLog.LineScroll(m_ctrlEditLog.GetLineCount());
}

void CAnyChatBusinessServerDlg::OnButtonTransFile() 
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
void CAnyChatBusinessServerDlg::OnButtonTransBufferEx() 
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
void CAnyChatBusinessServerDlg::OnButtonTransBuffer() 
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

void CAnyChatBusinessServerDlg::OnButtonStartRecord() 
{
	UpdateData(TRUE);
	BRAS_StreamRecordCtrl(m_iTargetId, TRUE, 0, 0, -1);
}

void CAnyChatBusinessServerDlg::OnButtonStopRecord() 
{
	UpdateData(TRUE);
	BRAS_StreamRecordCtrl(m_iTargetId, FALSE, 0, 0, -1);
}
