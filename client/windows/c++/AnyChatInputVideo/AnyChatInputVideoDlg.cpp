// AnyChatInputVideoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnyChatInputVideo.h"
#include "AnyChatInputVideoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define ANYCHAT_INPUTVIDEO_TIMER		1

#define INPUTVIDEO_WIDTH				320
#define INPUTVIDEO_HEIGHT				240
#define INPUTVIDEO_FPS					20

CAnyChatInputVideoDlg::CAnyChatInputVideoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnyChatInputVideoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnyChatInputVideoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnyChatInputVideoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnyChatInputVideoDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_ctrlEditLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnyChatInputVideoDlg, CDialog)
	//{{AFX_MSG_MAP(CAnyChatInputVideoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, OnButtonConnect)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnyChatInputVideoDlg message handlers

BOOL CAnyChatInputVideoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_bSuccessEnterRoom = FALSE;
	m_lpVideoBuf = NULL;
	m_dwRemoteUserId = -1;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnyChatInputVideoDlg::OnPaint() 
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

HCURSOR CAnyChatInputVideoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}



void CAnyChatInputVideoDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	// 释放资源
	BRAC_Release();	
	if(m_lpVideoBuf)
	{
		free(m_lpVideoBuf);
	}
}

/**
 *	视频数据扩展回调（增加时间戳）
 *	@param dwUserid 用户ID号
 *	@param lpBuf 视频数据缓冲区
 *	@param dwLen 缓冲区大小
 *	@param bmiHeader 视频缓冲区的头信息，包含了视频的大小、颜色位数等信息
 *	@param dwTimeStamp 时间戳
 */
void CALLBACK OnAnyChatVideoDataExCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, DWORD dwTimeStamp, LPVOID lpUserValue)
{
	TRACE("VideoDataExCallBack: userid:%d, timestamp:%d\r\n", (int)dwUserid, dwTimeStamp);
	CAnyChatInputVideoDlg* lpDlg = (CAnyChatInputVideoDlg*)lpUserValue;
	CRect dispRect;
	HWND hWnd;
	if(lpDlg->m_dwRemoteUserId == dwUserid && dwUserid != -1)					// 远程用户
	{
		hWnd = lpDlg->GetDlgItem(IDC_STATIC_REMOTEVIDEO)->GetSafeHwnd();
		lpDlg->GetDlgItem(IDC_STATIC_REMOTEVIDEO)->GetClientRect(dispRect);
	}
	else																// 本地用户
	{
		hWnd = lpDlg->GetDlgItem(IDC_STATIC_LOCALVIDEO)->GetSafeHwnd();
		lpDlg->GetDlgItem(IDC_STATIC_LOCALVIDEO)->GetClientRect(dispRect);
	}
	
	//构建Bitmap  
	BITMAPINFOHEADER  *lpbmi = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER)+dwLen);  
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
    memcpy((LPBYTE)lpbmi,&bmiHeader,sizeof(BITMAPINFOHEADER));
	memcpy(((LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER)),lpBuf,dwLen);  
	
	HDC hdc = ::GetDC(hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,lpbmi,CBM_INIT,(LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)lpbmi,DIB_RGB_COLORS);  
	//绘图  
	HBITMAP holdbm = (HBITMAP)SelectObject(dcMem,hBitmap);  
	::SetStretchBltMode(hdc,COLORONCOLOR);
	::StretchBlt(hdc,dispRect.left,dispRect.top,dispRect.Width(),dispRect.Height(),dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);
	
	SelectObject(dcMem,holdbm);  
	::DeleteDC(dcMem);
	::DeleteObject(hBitmap);
	::ReleaseDC(hWnd,hdc);
	free(lpbmi);
	lpbmi = NULL;
}

// 音频数据扩展回调函数定义（增加时间戳）
void CALLBACK OnAnyChatAudioDataExCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, DWORD dwTimeStamp, LPVOID lpUserValue)
{

}

void CAnyChatInputVideoDlg::OnButtonInit() 
{
	// 获取SDK的版本信息
	DWORD dwMainVer,dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRAC_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));
	
	CString logstr;
	logstr.Format("AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
	AppendLogString(logstr);
	
	// 打开（关闭）SDK的日志记录功能
	BRAC_ActiveCallLog(TRUE);
	
	// 设置SDK核心组件所在目录（注：demo程序只是设置为当前目录，项目中需要设置为实际路径）
	CHAR szCoreSDKPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szCoreSDKPath,sizeof(szCoreSDKPath));
	(strrchr(szCoreSDKPath,'\\'))[1] = 0; 
	BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,szCoreSDKPath,strlen(szCoreSDKPath));
	
	// 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_CBDATA/*BRAC_FUNC_VIDEO_AUTODISP*/ | BRAC_FUNC_AUDIO_AUTOPLAY /*BRAC_FUNC_AUDIO_CBDATA*/ | BRAC_FUNC_CHKDEPENDMODULE | 
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_CONFIG_LOCALINI;
	BRAC_InitSDK(this->GetSafeHwnd(),dwFuncMode);
	
	
	// 设置外部音频、视频输入模式
	BOOL bExtVideoInput = 1;
	BRAC_SetSDKOption(BRAC_SO_CORESDK_EXTVIDEOINPUT, (CHAR*)&bExtVideoInput, sizeof(DWORD));
//	BOOL bExtAudioInput = 1;
//	BRAC_SetSDKOption(BRAC_SO_CORESDK_EXTAUDIOINPUT, (CHAR*)&bExtAudioInput, sizeof(DWORD));

	// 设置扩展回调函数（带时间戳）
	BRAC_SetVideoDataExCallBack(BRAC_PIX_FMT_RGB24, OnAnyChatVideoDataExCallBack, this);
	BRAC_SetAudioDataExCallBack(OnAnyChatAudioDataExCallBack, this);
}

void CAnyChatInputVideoDlg::OnButtonConnect() 
{
	BRAC_Connect("demo.anychat.cn", 8906);
	BRAC_Login("demo-user", "", 0);
	BRAC_EnterRoom(1, "", 0);
}

void CAnyChatInputVideoDlg::OnButtonStart() 
{
	if(!m_bSuccessEnterRoom)
		return;
	// 设置输入视频格式
	BRAC_SetInputVideoFormat(BRAC_PIX_FMT_RGB24, INPUTVIDEO_WIDTH, INPUTVIDEO_HEIGHT, INPUTVIDEO_FPS, 0);
	// 分配缓冲区资源
	if(!m_lpVideoBuf)
	{
		m_lpVideoBuf = (BYTE*)malloc(INPUTVIDEO_WIDTH * INPUTVIDEO_HEIGHT * 3);
		if(!m_lpVideoBuf)
		{
			AppendLogString("分配缓冲区失败！");
			return;
		}
	}
	// 启动视频输入定时器
	SetTimer(ANYCHAT_INPUTVIDEO_TIMER, 1000/INPUTVIDEO_FPS, NULL);
}

// 记录日志到列表
void CAnyChatInputVideoDlg::AppendLogString(CString str)
{
	m_strLog += (str + "\r\n");
	m_ctrlEditLog.SetWindowText(m_strLog);
	m_ctrlEditLog.LineScroll(m_ctrlEditLog.GetLineCount());
}


// 连接服务器消息
void CAnyChatInputVideoDlg::OnAnyChatConnectMessage(BOOL bSuccess)
{
	if(bSuccess)
		AppendLogString("连接AnyChat服务器成功！");
	else
		AppendLogString("连接AnyChat服务器失败！");
}
// 用户登陆消息
void CAnyChatInputVideoDlg::OnAnyChatLoginMessage(DWORD dwUserId, DWORD dwErrorCode)
{
	CString str;
	if(dwErrorCode == 0)
		str.Format("登录AnyChat服务器成功，用户ID：%d", (int)dwUserId);
	else
		str.Format("登录AnyChat服务器失败，出错代码：%d", dwErrorCode);
	AppendLogString(str);
}
// 用户进入房间消息
void CAnyChatInputVideoDlg::OnAnyChatEnterRoomMessage(DWORD dwRoomId, DWORD dwErrorCode)
{
	CString str;
	if(dwErrorCode == 0)
	{
		CWnd* pWnd = GetDlgItem(IDC_STATIC_LOCALVIDEO);
		CRect rc;
		pWnd->GetClientRect(rc);
		BRAC_SetVideoPos(-1, pWnd->GetSafeHwnd(), rc.left, rc.top, rc.right, rc.bottom);
		
		str.Format("进入AnyChat房间成功，房间ID：%d", (int)dwRoomId);
		m_bSuccessEnterRoom = TRUE;

		//打开音频设备
		BRAC_UserSpeakControl(-1, TRUE);
		//打开视频设备（由于启动外部视频输入模式，这儿不需要打开本地视频设备）
		//BRAC_UserCameraControl(-1, TRUE);
	}
	else
	{
		str.Format("进入AnyChat房间失败，出错代码：%d", dwErrorCode);
		m_bSuccessEnterRoom = FALSE;
	}
	AppendLogString(str);
}
//网络断开消息
void CAnyChatInputVideoDlg::OnAnyChatLinkCloseMessage(DWORD dwErrorCode)
{
	CString str;
	str.Format("与AnyChat服务器连接断开，出错代码：%d", dwErrorCode);
	AppendLogString(str);
	m_bSuccessEnterRoom = FALSE;
	m_dwRemoteUserId = -1;
}


void CAnyChatInputVideoDlg::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
	case ANYCHAT_INPUTVIDEO_TIMER:
		if(m_lpVideoBuf)
		{
			static int f = 0;
			DWORD dwImageSize = INPUTVIDEO_WIDTH*INPUTVIDEO_HEIGHT*3;
			memset(m_lpVideoBuf, f, dwImageSize);
			f += 5;
			// 将产生的视频帧输入AnyChat
			DWORD dwTimeStamp = GetTickCount();			// 如果传入的timestamp为0，则采用AnyChat内核的时间戳
			BRAC_InputVideoData(m_lpVideoBuf, dwImageSize, dwTimeStamp);
		}
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

/**
 *	收到当前房间的在线用户信息
 *	进入房间后触发一次
 *	@param dwUserNum （INT）表示在线用户数（不包含自己）
 *	@param dwRoomId （INT）表示房间ID
 */
void CAnyChatInputVideoDlg::OnAnyChatOnlineUserMessage(DWORD dwUserNum, DWORD dwRoomId)
{
	CString logstr;
	logstr.Format(_T("在编号为：%d 的房间共有 %d 位在线用户"),dwRoomId, dwUserNum);
	AppendLogString(logstr);
		
	LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwUserNum);
	BRAC_GetOnlineUser(lpdwUserList,dwUserNum);	///< 真正获取在线用户列表
	
	ASSERT(m_dwRemoteUserId == -1);
	for(INT i=0; i< (INT)dwUserNum; i++)
	{
		m_dwRemoteUserId = lpdwUserList[i];
//		BRAC_SetVideoPos(m_dwRemoteUserId,m_hWnd,m_UserRect[site].left,m_UserRect[site].top,m_UserRect[site].right,m_UserRect[site].bottom);
		BRAC_UserCameraControl(m_dwRemoteUserId,TRUE);
		BRAC_UserSpeakControl(m_dwRemoteUserId,TRUE);
		break;
	}
	free(lpdwUserList);
}

// 用户进入/退出房间消息
void CAnyChatInputVideoDlg::OnAnyChatUserAtRoomMessage(DWORD dwUserId, BOOL bEnter)
{
	if(!bEnter || m_dwRemoteUserId != -1)		// 用户离开房间，或是已经请求了某个用户的视频，则忽略该消息
		return;
	m_dwRemoteUserId = dwUserId;
	BRAC_UserCameraControl(m_dwRemoteUserId,TRUE);
	BRAC_UserSpeakControl(m_dwRemoteUserId,TRUE);
}

/**
 *	视频数据回调
 *	@param dwUserid 用户ID号
 *	@param lpBuf 视频数据缓冲区
 *	@param dwLen 缓冲区大小
 *	@param bmiHeader 视频缓冲区的头信息，包含了视频的大小、颜色位数等信息
 */
void CAnyChatInputVideoDlg::OnAnyChatVideoDataCallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, LPBITMAPINFOHEADER lpbmiHeader)
{
	// 废弃，在OnAnyChatVideoDataExCallBack里面处理
}

