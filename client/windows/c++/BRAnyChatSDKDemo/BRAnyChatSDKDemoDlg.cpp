// BRAnyChatSDKDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include <WINSOCK2.H>
#include "BRAnyChatSDKDemo.h"
#include "BRAnyChatSDKDemoDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define REFRESH_TRANSTASK_STATUS_TIMER	1	///< 刷新传输任务状态定时器
#define REFRESH_SPEAKVOLUME_TIMER		2	///< 更新用户说话音量定时器
#define REFRESH_RECORDSTATE_TIMER		3	///< 更新录像状态定时器

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatSDKDemoDlg dialog

CBRAnyChatSDKDemoDlg::CBRAnyChatSDKDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBRAnyChatSDKDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBRAnyChatSDKDemoDlg)
	m_bEnableAGC = TRUE;
	m_bEnableEcho = TRUE;
	m_bEnableNS = TRUE;
	m_bEnableVAD = TRUE;
	m_iPort = 8906;
	m_iRoomId = 1;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBRAnyChatSDKDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBRAnyChatSDKDemoDlg)
	DDX_Control(pDX, IDC_PROGRESS_SPEAKVOLUME0, m_ctrlSpeakVolume0);
	DDX_Control(pDX, IDC_PROGRESS_SPEAKVOLUME1, m_ctrlSpeakVolume1);
	DDX_Control(pDX, IDC_PROGRESS_SPEAKVOLUME2, m_ctrlSpeakVolume2);
	DDX_Control(pDX, IDC_PROGRESS_SPEAKVOLUME3, m_ctrlSpeakVolume3);
	DDX_Control(pDX, IDC_SLIDER_OUTVOLUME, m_ctrlOutVolume);
	DDX_Control(pDX, IDC_SLIDER_INVOLUME, m_ctrlInVolume);
	DDX_Control(pDX, IDC_COMBO_VCAPTURE, m_cbVideoCapture);
	DDX_Control(pDX, IDC_COMBO_ACAPTURE, m_cbAudioCapture);
	DDX_Control(pDX, IDC_EDIT_LOG, m_ctrlEditLog);
	DDX_Check(pDX, IDC_CHECK_AGC, m_bEnableAGC);
	DDX_Check(pDX, IDC_CHECK_ECHO, m_bEnableEcho);
	DDX_Check(pDX, IDC_CHECK_NS, m_bEnableNS);
	DDX_Check(pDX, IDC_CHECK_VAD, m_bEnableVAD);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_ROOMID, m_iRoomId);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CBRAnyChatSDKDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CBRAnyChatSDKDemoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_INIT, OnButtonInit)
	ON_MESSAGE(WM_GV_CONNECT,OnGVClientConnect)
	ON_MESSAGE(WM_GV_LOGINSYSTEM,OnGVClientLogin)
	ON_MESSAGE(WM_GV_ENTERROOM,OnGVClientEnterRoom)
	ON_MESSAGE(WM_GV_ONLINEUSER,OnGVClientOnlineUser)
	ON_MESSAGE(WM_GV_USERATROOM,OnGVClientUserAtRoom)
	ON_MESSAGE(WM_GV_MICSTATECHANGE,OnGVClientMicStateChange)
	ON_MESSAGE(WM_GV_LINKCLOSE,OnGVClientLinkClose)
	ON_MESSAGE(WM_GV_CHATMODECHG,OnGVClientChatModeChange)
	ON_BN_CLICKED(IDC_BUTTON_ENTERROOM, OnButtonEnterRoom)
	ON_BN_CLICKED(IDC_BUTTON_LEAVEROOM, OnButtonLeaveRoom)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOPROPERTY, OnButtonVideoproperty)
	ON_BN_CLICKED(IDC_BUTTON_REFRESHCAPTURE, OnButtonRefreshCapture)
	ON_CBN_SELCHANGE(IDC_COMBO_VCAPTURE, OnSelchangeComboVideoCapture)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_OUTVOLUME, OnSliderOutVolumeChange)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_INVOLUME, OnOnSliderInVolumeChange)
	ON_CBN_SELCHANGE(IDC_COMBO_ACAPTURE, OnSelChangeComboAudioCapture)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SENDFILE, OnButtonSendFile)
	ON_BN_CLICKED(IDC_CHECK_VAD, OnCheckVad)
	ON_BN_CLICKED(IDC_CHECK_AGC, OnCheckAgc)
	ON_BN_CLICKED(IDC_CHECK_ECHO, OnCheckEcho)
	ON_BN_CLICKED(IDC_CHECK_NS, OnCheckNs)
	ON_BN_CLICKED(IDC_BUTTON_TRANSBUF, OnButtonTransbuf)
	ON_BN_CLICKED(IDC_BUTTON_RELEASE, OnButtonRelease)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCTRL0, OnButtonVideoctrl0)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCTRL1, OnButtonVideoctrl1)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCTRL2, OnButtonVideoctrl2)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOCTRL3, OnButtonVideoctrl3)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOCTRL0, OnButtonAudioctrl0)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOCTRL1, OnButtonAudioctrl1)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOCTRL2, OnButtonAudioctrl2)
	ON_BN_CLICKED(IDC_BUTTON_AUDIOCTRL3, OnButtonAudioctrl3)
	ON_BN_CLICKED(IDC_BUTTON_RECORDCTRL0, OnButtonRecordctrl0)
	ON_BN_CLICKED(IDC_BUTTON_RECORDCTRL1, OnButtonRecordctrl1)
	ON_BN_CLICKED(IDC_BUTTON_RECORDCTRL2, OnButtonRecordctrl2)
	ON_BN_CLICKED(IDC_BUTTON_RECORDCTRL3, OnButtonRecordctrl3)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOTCTRL0, OnButtonSnapshotctrl0)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOTCTRL1, OnButtonSnapshotctrl1)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOTCTRL2, OnButtonSnapshotctrl2)
	ON_BN_CLICKED(IDC_BUTTON_SNAPSHOTCTRL3, OnButtonSnapshotctrl3)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, OnButtonLogout)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**
 *	视频数据回调函数
 */
void CALLBACK VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
		pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
}
/**
 *	音频数据回调函数
 */
void CALLBACK AudioData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		// do something ...
	}
}

/**
 *	音量更改回调函数
 */
void CALLBACK VolumeChange_CallBack(BRAC_AudioDevice device, DWORD dwCurrentVolume, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		if(device == BRAC_AD_WAVEIN)
			pDemoDlg->OnWaveInVolumeChange(dwCurrentVolume);
		else
			pDemoDlg->OnWaveOutVolumeChange(dwCurrentVolume);
	}
}
// 透明通道数据回调函数定义
void CALLBACK TransBuffer_CallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		CString strNotify;
		strNotify.Format("TransBuffer_CallBack:dwUserid-%d, bufSize-%d",dwUserid,dwLen);
		pDemoDlg->AppendLogString(strNotify);
	}
}

// 透明通道数据扩展回调函数定义
void CALLBACK TransBufferEx_CallBack(DWORD dwUserid, LPBYTE lpBuf, DWORD dwLen, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		BOOL bSuccess = FALSE;
		if(dwLen > 1000)
		{
			bSuccess = lpBuf[1000] == 'Y' ? TRUE : FALSE;
		}
		CString strNotify;
		strNotify.Format("TransBufferEx_CallBack:dwUserid-%d, bufSize-%d,verify:%s",dwUserid,dwLen,bSuccess ? "Success" : "Fail");
		pDemoDlg->AppendLogString(strNotify);
	}	
}
// 文件传输回调函数定义
void CALLBACK TransFile_CallBack(DWORD dwUserid, LPCTSTR lpFileName, LPCTSTR lpTempFilePath, DWORD dwFileLength, DWORD wParam, DWORD lParam, DWORD dwTaskId, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		CString strNotify;
		strNotify.Format("TransFile_CallBack:dwUserid-%d, lpFileName-%s, lpTempFilePath-%s",dwUserid,lpFileName,lpTempFilePath);
		pDemoDlg->AppendLogString(strNotify);
	}
}

// 录像、快照任务完成扩展回调函数定义
void CALLBACK RecordSnapShotEx_CallBack(DWORD dwUserId, LPCTSTR lpFileName, DWORD dwElapse, DWORD dwFlags, DWORD dwParam, LPCTSTR lpUserStr, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		CString strNotify;
		BOOL bSnapShotType = !!(dwFlags & ANYCHAT_RECORD_FLAGS_SNAPSHOT);
		strNotify.Format(_T("%s CallBack:dwUserid:%d, FilePathName:%s, UserStr:%s"),bSnapShotType?_T("SnapShot"):_T("Record"),(int)dwUserId, lpFileName, lpUserStr);
		pDemoDlg->AppendLogString(strNotify);
	}
}

// SDK Filter 通信数据回调函数定义
void CALLBACK SDKFilterData_CallBack(LPBYTE lpBuf, DWORD dwLen, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
	{
		CString strNotify;
		strNotify.Format("SDK Filter CallBack:%s",lpBuf);
		pDemoDlg->AppendLogString(strNotify);
	}
}

/**
 *	绘制用户视频
 *	数据来源于回调函数
 *	@param dwUserid 用户ID号
 *	@param lpBuf 视频数据缓冲区
 *	@param dwLen 缓冲区大小
 *	@param bmiHeader 视频缓冲区的头信息，包含了视频的大小、颜色位数等信息
 */
void CBRAnyChatSDKDemoDlg::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	// 根据用户ID号找到合适的显示区域
	DWORD dwSite = -1;
	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		if(m_iUserID[i] == (INT)dwUserid)
		{
			dwSite = i;
			break;
		}
	}
	if(dwSite == -1)
		return;

	CRect dispRect = m_UserRect[dwSite];

	//构建Bitmap  
	BITMAPINFOHEADER  *lpbmi = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER)+dwLen);  
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
    memcpy((LPBYTE)lpbmi,&bmiHeader,sizeof(bmiHeader));
	memcpy(((LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER)),lpBuf,dwLen);  

	HDC hdc = ::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,lpbmi,CBM_INIT,(LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)lpbmi,DIB_RGB_COLORS);  
	//绘图  
	HBITMAP holdbm = (HBITMAP)SelectObject(dcMem,hBitmap);  
	::SetStretchBltMode(hdc,COLORONCOLOR);
	::StretchBlt(hdc,dispRect.left,dispRect.top,dispRect.Width(),dispRect.Height(),dcMem,0,0,bmiHeader.biWidth,bmiHeader.biHeight,SRCCOPY);

	SelectObject(dcMem,holdbm);  
	::DeleteDC(dcMem);
	::DeleteObject(hBitmap);
	::ReleaseDC(m_hWnd,hdc);
	free(lpbmi);
	lpbmi = NULL;
}

BOOL CBRAnyChatSDKDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// 初始化每个视频显示位置信息
	GetDlgItem(IDC_STATIC_USER0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USER0)->GetClientRect(m_UserRect[0]);	
	GetDlgItem(IDC_STATIC_USER0)->ClientToScreen(m_UserRect[0]);
	ScreenToClient(m_UserRect[0]);

	GetDlgItem(IDC_STATIC_USER1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USER1)->GetClientRect(m_UserRect[1]);	
	GetDlgItem(IDC_STATIC_USER1)->ClientToScreen(m_UserRect[1]);
	ScreenToClient(m_UserRect[1]);

	GetDlgItem(IDC_STATIC_USER2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USER2)->GetClientRect(m_UserRect[2]);	
	GetDlgItem(IDC_STATIC_USER2)->ClientToScreen(m_UserRect[2]);
	ScreenToClient(m_UserRect[2]);

	GetDlgItem(IDC_STATIC_USER3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_USER3)->GetClientRect(m_UserRect[3]);	
	GetDlgItem(IDC_STATIC_USER3)->ClientToScreen(m_UserRect[3]);
	ScreenToClient(m_UserRect[3]);

	// 隐藏录像状态标志
	GetDlgItem(IDC_STATIC_RECORDSTATE0)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECORDSTATE1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECORDSTATE2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC_RECORDSTATE3)->ShowWindow(SW_HIDE);
	
	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		m_iUserID[i] = -1;
	}
	
	m_dwTransTaskId = -1;

	m_iPort = 8906;
	m_iRoomId = 1;
	SetDlgItemText(IDC_IPADDRESS_SERVER,"demo.anychat.cn");
	SetDlgItemText(IDC_EDIT_USERNAME,"AnyChat5");
	UpdateData(FALSE);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CBRAnyChatSDKDemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CBRAnyChatSDKDemoDlg::OnPaint() 
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

HCURSOR CBRAnyChatSDKDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CBRAnyChatSDKDemoDlg::OnDestroy() 
{
	BRAC_Release();
	CDialog::OnDestroy();	
}

void CBRAnyChatSDKDemoDlg::OnButtonInit() 
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
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_AUTODISP | BRAC_FUNC_AUDIO_AUTOPLAY | BRAC_FUNC_CHKDEPENDMODULE | 
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME| BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_CONFIG_LOCALINI;
	BRAC_InitSDK(this->GetSafeHwnd(),dwFuncMode);
	BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_RGB24,VideoData_CallBack,this);
	BRAC_SetAudioDataCallBack(AudioData_CallBack,this);
	BRAC_SetVolumeChangeCallBack(VolumeChange_CallBack,this);
	BRAC_SetTransBufferExCallBack(TransBufferEx_CallBack,this);
	BRAC_SetTransBufferCallBack(TransBuffer_CallBack,this);
	BRAC_SetTransFileCallBack(TransFile_CallBack,this);
	BRAC_SetSDKFilterDataCallBack(SDKFilterData_CallBack,this);
	BRAC_SetCallBack(BRAC_CBTYPE_STREAMRECORDEX, (void*)RecordSnapShotEx_CallBack, this);
	
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(PCHAR)&m_bEnableAGC,sizeof(m_bEnableAGC));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL,(PCHAR)&m_bEnableVAD,sizeof(m_bEnableVAD));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL,(PCHAR)&m_bEnableNS,sizeof(m_bEnableNS));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,(PCHAR)&m_bEnableEcho,sizeof(m_bEnableEcho));

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
	
	// 设置服务器认证密码
	BRAC_SetServerAuthPass("BaiRuiTech");		// 需要与服务器配置项“SDKAuthPass”相同（大小写敏感），SDK才能正常连接到服务器

	DWORD dwVolume = 0;
	BRAC_AudioGetVolume(BRAC_AD_WAVEOUT,dwVolume);
	m_ctrlOutVolume.SetPos(dwVolume);
	
	dwVolume = 0;
	BRAC_AudioGetVolume(BRAC_AD_WAVEIN,dwVolume);
	m_ctrlInVolume.SetPos(dwVolume);

	SetTimer(REFRESH_SPEAKVOLUME_TIMER,100,NULL);
	SetTimer(REFRESH_RECORDSTATE_TIMER,1000,NULL);
}

void CBRAnyChatSDKDemoDlg::OnButtonLogin() 
{
	UpdateData(TRUE);
	CString strServerIp,strUserName,strPassword;
	GetDlgItemText(IDC_IPADDRESS_SERVER,strServerIp);
	GetDlgItemText(IDC_EDIT_USERNAME,strUserName);
	GetDlgItemText(IDC_EDIT_LOGINPASS,strPassword);
	if(strServerIp.IsEmpty() || m_iPort <= 0)
	{
		AfxMessageBox("Invalid  server ip address or port!");
		return;
	}
	if(strUserName.IsEmpty())
	{
		AfxMessageBox("Must input username for login system!");
		return;
	}

	BRAC_Connect(strServerIp.GetBuffer(0),m_iPort);
	BRAC_Login(strUserName.GetBuffer(0),strPassword.GetBuffer(0),0);	
}

void CBRAnyChatSDKDemoDlg::OnButtonEnterRoom() 
{
	UpdateData(TRUE);
	BRAC_EnterRoom(m_iRoomId,"",0);
}

void CBRAnyChatSDKDemoDlg::OnButtonLeaveRoom() 
{
	BRAC_LeaveRoom(1);
	
	// 保留自己的userid，因为这儿只是leaveroom，并非logout
	for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
	{
		m_iUserID[i] = -1;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonLogout() 
{
	BRAC_Logout();
	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		m_iUserID[i] = -1;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonRelease() 
{
	BRAC_Release();
	
	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		m_iUserID[i] = -1;
	}
	m_dwTransTaskId = -1;
}

/**
 *	收到消息：客户端连接服务器
 *	@param wParam （BOOL）表示是否连接成功
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)wParam;
	AppendLogString(bSuccess ? "连接服务器成功..." : "连接服务器失败...");
	return 0;
}
/**
 *	收到消息：客户端登录系统
 *	@param wParam （INT）表示自己的用户ID号
 *	@param lParam （INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	DWORD dwUserID = wParam;
	if(lParam == 0)
	{
		CHAR username[30]={0};
		BRAC_GetUserName(dwUserID,username,sizeof(username));
		logstr.Format("登录服务器成功，自己的用户编号为：%d(%s)",wParam,username);

		// 将用户的ID保存在第一个位置，否则在回调函数里面可能找不到绘制的位置
		m_iUserID[0] = dwUserID;
	}
	else
		logstr.Format("登录服务器失败，出错代码为： %d ",lParam);

	AppendLogString(logstr);

	return 0;
}
/**
 *	收到消息：客户端进入房间
 *	@param wParam （INT）表示所进入房间的ID号
 *	@param lParam （INT）表示是否进入房间：0成功进入，否则为出错代码
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT roomid = (INT)wParam;
	if(lParam == 0)
	{
		logstr.Format("成功进入编号为：%d 的房间",roomid);

		BRAC_SetVideoPos(-1,m_hWnd,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].right,m_UserRect[0].bottom);
		BRAC_UserCameraControl(-1,TRUE);
		BRAC_UserSpeakControl(-1,TRUE);
	}
	else
		logstr.Format("申请进入房间失败，出错代码为： %d ",lParam);

	AppendLogString(logstr);
	return 0;
}
/**
 *	显示日志信息
 */
void CBRAnyChatSDKDemoDlg::AppendLogString(CString logstr)
{
	m_strLogInfo += (logstr + "\r\n");
	m_ctrlEditLog.SetWindowText(m_strLogInfo);
	m_ctrlEditLog.LineScroll(m_ctrlEditLog.GetLineCount());
}

/**
 *	收到当前房间的在线用户信息
 *	进入房间后触发一次
 *	@param wParam （INT）表示在线用户数（不包含自己）
 *	@param lParam （INT）表示房间ID
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT onlinenum = (INT)wParam;

	logstr.Format("在编号为：%d 的房间共有 %d 位在线用户",lParam, onlinenum);
	AppendLogString(logstr);

	

	DWORD dwUserNum = 0;
	BRAC_GetOnlineUser(NULL,dwUserNum);		///< 首先获取房间内在线人数
	if(!dwUserNum)
		return 0;

	LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwUserNum);
	BRAC_GetOnlineUser(lpdwUserList,dwUserNum);	///< 真正获取在线用户列表

	for(INT i=0; i< (INT)dwUserNum; i++)
	{
		DWORD userid = lpdwUserList[i];
		// 给用户找一个空的位置显示面板（第0号位置留给自己）
		INT site = -1;
		for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
		{
			if(m_iUserID[i] == -1)
			{
				site = i;
				break;
			}
		}
		if(site != -1)
		{
			BRAC_SetVideoPos(userid,m_hWnd,m_UserRect[site].left,m_UserRect[site].top,m_UserRect[site].right,m_UserRect[site].bottom);
			BRAC_UserCameraControl(userid,TRUE);
			BRAC_UserSpeakControl(userid,TRUE);

			DWORD dwState = 0;
			BRAC_GetCameraState(userid,dwState);
			logstr.Format("用户%d 的视频状态是： %d",userid,dwState);
			AppendLogString(logstr);
			

			m_iUserID[site] = userid;
		}
		else				///< 已经没有位置了，Demo演示限制
			break;
	}

	free(lpdwUserList);

	return 0;
}
/**
 *	收到消息：用户进入（离开）房间
 *	@param wParam （INT）表示用户ID号
 *	@param lParam （BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT		userid = (INT)wParam;
	BOOL	bEnter = (BOOL)lParam;

	CHAR username[30]={0};
	BRAC_GetUserName(userid,username,sizeof(username));
	logstr.Format("编号为：%d 的用户(%s) %s 房间",userid,username, bEnter ? "进入" : "离开");
	AppendLogString(logstr);

	if(bEnter)
	{
		// 给用户找一个空的位置显示面板（第0号位置留给自己）
		INT site = -1;
		for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
		{
			if(m_iUserID[i] == -1)
			{
				site = i;
				break;
			}
		}
		if(site != -1)
		{
			BRAC_SetVideoPos(userid,m_hWnd,m_UserRect[site].left,m_UserRect[site].top,m_UserRect[site].right,m_UserRect[site].bottom);
			BRAC_UserCameraControl(userid,TRUE);
			BRAC_UserSpeakControl(userid,TRUE);
			m_iUserID[site] = userid;
		}

	}
	else
	{
		//清除该用户占用位置的信息
		for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
		{
			if(m_iUserID[i] == userid)
			{
				m_iUserID[i] = -1;
				break;
			}
		}
	}

	return 0;
}

/**
 *	收到消息：用户的音频设备状态变化消息
 *	@param wParam （INT）表示用户ID号
 *	@param lParam （BOOL）表示该用户是否已打开音频采集设备
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam)
{
	CString logstr;

	logstr.Format("编号为：%d 的用户 %s 本地Mic设备",wParam, lParam ? "打开" : "关闭");
	AppendLogString(logstr);

	return 0;
}

/**
 *	收到消息：网络连接已关闭
 *	该消息只有在客户端连接服务器成功之后，网络异常中断之时触发
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
	AppendLogString("网络连接已关闭（断开）");

	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		m_iUserID[i] = -1;
	}
	return 0;
}

/**
 *	用户聊天模式发生变化
 *	@param wParam （INT）表示用户ID号
 *	@param lParam （INT）表示用户的当前聊天模式
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientChatModeChange(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT userid = (INT)wParam;
	INT chatmode = (INT)lParam;

	if(m_iUserID[0] == userid)
	{
		logstr.Format("自己（%d ）的聊天模式改变，当前聊天模式为：%s",userid, chatmode == 0 ? "公聊模式" : "私聊模式");
	}
	else
		logstr.Format("编号为：%d 的用户聊天模式改变，当前聊天模式为：%s",userid, chatmode == 0 ? "公聊模式" : "私聊模式");

	AppendLogString(logstr);
	return 0;
}
void CBRAnyChatSDKDemoDlg::OnButtonVideoproperty() 
{
	BRAC_ShowLVProperty(m_hWnd,"AnyChat 本地视频画质调节");
	
}
/**
 *	刷新设备列表
 */
void CBRAnyChatSDKDemoDlg::OnButtonRefreshCapture() 
{
	// 刷新视频采集设备下拉列表
	PCHAR DeviceName[10] = {0};
	DWORD DeviceNum = 10;
	BRAC_EnumVideoCapture(DeviceName,DeviceNum);
	

	m_cbVideoCapture.ResetContent();
	INT i=0;
	for(i=0; i<(INT)DeviceNum; i++)
	{
		if(DeviceName[i])
		{
			m_cbVideoCapture.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}

	// 选择当前打开的视频采集设备
	CHAR szVideoDeviceName[100] = {0};
	BRAC_GetCurVideoCapture(szVideoDeviceName,sizeof(szVideoDeviceName));
	m_cbVideoCapture.SelectString(-1,szVideoDeviceName);

	// 刷新音频采集设备下拉列表
	DeviceNum = 10;
	BRAC_EnumAudioCapture(DeviceName,DeviceNum);
	
	m_cbAudioCapture.ResetContent();
	for(i=0; i<(INT)DeviceNum; i++)
	{
		if(DeviceName[i])
		{
			m_cbAudioCapture.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}
	// 选择当前打开的视频采集设备
	CHAR szAudioDeviceName[100] = {0};
	BRAC_GetCurAudioCapture(szAudioDeviceName,sizeof(szAudioDeviceName));
	m_cbAudioCapture.SelectString(-1,szAudioDeviceName);
}

void CBRAnyChatSDKDemoDlg::OnSelchangeComboVideoCapture() 
{
	CString strCaptureName;
	m_cbVideoCapture.GetLBText(m_cbVideoCapture.GetCurSel(),strCaptureName);
	BRAC_SelectVideoCapture(strCaptureName);
}

void CBRAnyChatSDKDemoDlg::OnSelChangeComboAudioCapture() 
{
	CString strCaptureName;
	m_cbAudioCapture.GetLBText(m_cbAudioCapture.GetCurSel(),strCaptureName);
	BRAC_SelectAudioCapture(strCaptureName);
}

void CBRAnyChatSDKDemoDlg::OnSliderOutVolumeChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwVolume = m_ctrlOutVolume.GetPos();
	BRAC_AudioSetVolume(BRAC_AD_WAVEOUT,dwVolume);
	*pResult = 0;
}

void CBRAnyChatSDKDemoDlg::OnOnSliderInVolumeChange(NMHDR* pNMHDR, LRESULT* pResult) 
{
	DWORD dwVolume = m_ctrlInVolume.GetPos();
	BRAC_AudioSetVolume(BRAC_AD_WAVEIN,dwVolume);	
	*pResult = 0;
}

// 录音的音量发生改变
void CBRAnyChatSDKDemoDlg::OnWaveInVolumeChange(DWORD dwVolume)
{
	m_ctrlInVolume.SetPos(dwVolume);
}
// 放音的音量发生改变
void CBRAnyChatSDKDemoDlg::OnWaveOutVolumeChange(DWORD dwVolume)
{
	m_ctrlOutVolume.SetPos(dwVolume);
}



void CBRAnyChatSDKDemoDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case REFRESH_TRANSTASK_STATUS_TIMER:	// 刷新缓冲区传输任务状态
		{
			if(m_dwTransTaskId == -1)
			{
				KillTimer(REFRESH_TRANSTASK_STATUS_TIMER);
				break;
			}
			DWORD ret;
			DWORD dwStatus = 0;
			ret = BRAC_QueryTransTaskInfo(-1,m_dwTransTaskId,BRAC_TRANSTASK_STATUS,(PCHAR)&dwStatus,sizeof(DWORD));
			if(ret != GV_ERR_SUCCESS)
			{
				KillTimer(REFRESH_TRANSTASK_STATUS_TIMER);
				m_dwTransTaskId = -1;
				SetDlgItemText(IDC_STATIC_FILESTATUS,"");
				if(ret == GV_ERR_TRANSBUF_NOTASK)
					AppendLogString("传输任务不存在，可能对方已离开房间！");
				else
					AppendLogString("查询任务信息失败！");
				break;
			}
			DOUBLE dbProgress = 0.0;
			BRAC_QueryTransTaskInfo(-1,m_dwTransTaskId,BRAC_TRANSTASK_PROGRESS,(PCHAR)&dbProgress,sizeof(DOUBLE));
			DWORD dwBitrate = 0;
			BRAC_QueryTransTaskInfo(-1,m_dwTransTaskId,BRAC_TRANSTASK_BITRATE,(PCHAR)&dwBitrate,sizeof(DWORD));

			CString strStatus;
			switch(dwStatus)
			{
			case 1:		strStatus = "Ready";	break;
			case 2:		strStatus = "Process";	break;
			case 3:		strStatus = "Finish";	break;
			case 4:		strStatus = "Cancel";	break;
			case 5:		strStatus = "Reject";	break;
			default:	strStatus = "Unkonw";	break;
			}
			if(dwStatus == 3)		// finish
			{
				KillTimer(REFRESH_TRANSTASK_STATUS_TIMER);
				m_dwTransTaskId = -1;
				AppendLogString("传输任务已完成！");
			}
			CString strBitrate;
			if(dwBitrate >= 1000 * 1000)
				strBitrate.Format("%.02f Mbps",(float)dwBitrate/1000/1000);
			else if(dwBitrate >= 1000)
				strBitrate.Format("%.02f Kbps",(float)dwBitrate/1000);
			else
				strBitrate.Format("%.02f bps",(float)dwBitrate);

			CString strNotify;
			strNotify.Format("%s-%.02f%%-%s",strStatus,dbProgress,strBitrate);
			SetDlgItemText(IDC_STATIC_FILESTATUS,strNotify);
		}
	case REFRESH_SPEAKVOLUME_TIMER:		// 刷新用户说话音量
		{
			DOUBLE fSpeakVolume = 0.0;
			if(m_iUserID[0] != -1 && BRAC_QueryUserState(m_iUserID[0],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
				m_ctrlSpeakVolume0.SetPos((INT)fSpeakVolume);
			else
				m_ctrlSpeakVolume0.SetPos(0);

			fSpeakVolume = 0.0;
			if(m_iUserID[1] != -1 && BRAC_QueryUserState(m_iUserID[1],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
				m_ctrlSpeakVolume1.SetPos((INT)fSpeakVolume);
			else
				m_ctrlSpeakVolume1.SetPos(0);
			fSpeakVolume = 0.0;
			if(m_iUserID[2] != -1 && BRAC_QueryUserState(m_iUserID[2],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
				m_ctrlSpeakVolume2.SetPos((INT)fSpeakVolume);
			else
				m_ctrlSpeakVolume2.SetPos(0);
			fSpeakVolume = 0.0;
			if(m_iUserID[3] != -1 && BRAC_QueryUserState(m_iUserID[3],BRAC_USERSTATE_SPEAKVOLUME,(PCHAR)&fSpeakVolume,sizeof(DOUBLE)) == GV_ERR_SUCCESS)
				m_ctrlSpeakVolume3.SetPos((INT)fSpeakVolume);
			else
				m_ctrlSpeakVolume3.SetPos(0);
		}
		break;
	case REFRESH_RECORDSTATE_TIMER:		// 刷新录像状态
		{
			DWORD dwRecordState = 0;
			if(m_iUserID[0] != -1 && BRAC_QueryUserState(m_iUserID[0],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
			{
				static BOOL bShow = FALSE;
				bShow = dwRecordState ? !bShow : FALSE;
				GetDlgItem(IDC_STATIC_RECORDSTATE0)->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
			}
			dwRecordState = 0;
			if(m_iUserID[1] != -1 && BRAC_QueryUserState(m_iUserID[1],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
			{
				static BOOL bShow = FALSE;
				bShow = dwRecordState ? !bShow : FALSE;
				GetDlgItem(IDC_STATIC_RECORDSTATE1)->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
			}
			dwRecordState = 0;
			if(m_iUserID[2] != -1 && BRAC_QueryUserState(m_iUserID[2],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
			{
				static BOOL bShow = FALSE;
				bShow = dwRecordState ? !bShow : FALSE;
				GetDlgItem(IDC_STATIC_RECORDSTATE2)->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
			}
			dwRecordState = 0;
			if(m_iUserID[3] != -1 && BRAC_QueryUserState(m_iUserID[3],BRAC_USERSTATE_RECORDING,(PCHAR)&dwRecordState,sizeof(DWORD)) == GV_ERR_SUCCESS)
			{
				static BOOL bShow = FALSE;
				bShow = dwRecordState ? !bShow : FALSE;
				GetDlgItem(IDC_STATIC_RECORDSTATE3)->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
			}
		}
		break;
	default:
	    break;
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CBRAnyChatSDKDemoDlg::OnButtonSendFile() 
{
	if(m_dwTransTaskId != -1)	// 演示程序为了简洁，同时只允许传一个任务，实际上SDK是可以多任务并发的
		return;

	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)||*.*\0");
	CFileDialog	dlg(TRUE, NULL, NULL, /*OFN_HIDEREADONLY | */OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		DWORD dwTaskId = 0;
		DWORD wParam = 1;			// 上层应用程序可自定义wParam、lParam的值，这两个参数的值将被回调给对方
		DWORD lParam = 2;
		DWORD dwFlags = 0;			// 该标志设置为0，则SDK将自动根据网络状态选择合适的传输途径（TCP、UDP or P2P）
		DWORD ret = BRAC_TransFile(m_iUserID[1],strFileName.GetBuffer(0),wParam,lParam,dwFlags,dwTaskId);
		if(ret == GV_ERR_SUCCESS)
		{
			m_dwTransTaskId = dwTaskId;
			SetTimer(REFRESH_TRANSTASK_STATUS_TIMER,100,NULL);
		}
		else
		{
			CString strError;
			strError.Format("创建文件传输任务失败，出错代码:%d",ret);
			AppendLogString(strError);
			SetDlgItemText(IDC_STATIC_FILESTATUS,"");
		}
	}
}
// 传输超大缓冲区任务演示
void CBRAnyChatSDKDemoDlg::OnButtonTransbuf() 
{
	if(m_dwTransTaskId != -1)	// 演示程序为了简洁，同时只允许传一个任务，实际上SDK是可以多任务并发的
		return;
	
	PCHAR lpBuf = (PCHAR)malloc(10*1024);		// 为了演示，创建一个10KByte大小的缓冲区
	DWORD dwLen = 10*1024;
	if(!lpBuf)
		return;
	lpBuf[1000] = 'Y';			// 演示的需要，为了验证收到的数据是否正确，在缓冲区中间某个位置设置一个标志，对方接收后，可判断该标志是否为设定值

	DWORD dwTaskId = 0;
	DWORD wParam = 3;			// 上层应用程序可自定义wParam、lParam的值，这两个参数的值将被回调给对方
	DWORD lParam = 4;
	DWORD dwFlags = 0;			// 该标志设置为0，则SDK将自动根据网络状态选择合适的传输途径（TCP、UDP or P2P）
	DWORD ret = BRAC_TransBufferEx(m_iUserID[1],(PBYTE)lpBuf,dwLen,wParam,lParam,dwFlags,dwTaskId);
	if(ret == GV_ERR_SUCCESS)
	{
		m_dwTransTaskId = dwTaskId;
		SetTimer(REFRESH_TRANSTASK_STATUS_TIMER,100,NULL);
	}
	else
	{
		CString strError;
		strError.Format("创建缓冲区传输任务失败，出错代码:%d",ret);
		AppendLogString(strError);
		SetDlgItemText(IDC_STATIC_FILESTATUS,"");
	}
	// 缓冲区调用完成后， 可以立即释放掉
	free(lpBuf);

//	BRAC_TransBuffer(m_iUserID[1],(LPBYTE)"bairuitech",10);
}


void CBRAnyChatSDKDemoDlg::OnCheckVad() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL,(PCHAR)&m_bEnableVAD,sizeof(m_bEnableVAD));
}

void CBRAnyChatSDKDemoDlg::OnCheckAgc() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(PCHAR)&m_bEnableAGC,sizeof(m_bEnableAGC));	
}

void CBRAnyChatSDKDemoDlg::OnCheckEcho() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,(PCHAR)&m_bEnableEcho,sizeof(m_bEnableEcho));
}

void CBRAnyChatSDKDemoDlg::OnCheckNs() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL,(PCHAR)&m_bEnableNS,sizeof(m_bEnableNS));
}

void CBRAnyChatSDKDemoDlg::OnButtonVideoctrl0() 
{
	// 为了演示程序简单，这儿采用静态变量保存上一次的状态，可能不准确，因为可能在别的地方有打开，或是关闭的操作，下同
	// 特别是当前用户离开房间，别的用户再进来时，初始状态将不准确
	static BOOL bLastState = TRUE;		
	if(m_iUserID[0] != -1)
	{
		BRAC_UserCameraControl(m_iUserID[0],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonVideoctrl1() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[1] != -1)
	{
		BRAC_UserCameraControl(m_iUserID[1],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonVideoctrl2() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[2] != -1)
	{
		BRAC_UserCameraControl(m_iUserID[2],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonVideoctrl3() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[3] != -1)
	{
		BRAC_UserCameraControl(m_iUserID[3],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonAudioctrl0() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[0] != -1)
	{
		BRAC_UserSpeakControl(m_iUserID[0],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonAudioctrl1() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[1] != -1)
	{
		BRAC_UserSpeakControl(m_iUserID[1],!bLastState);
		bLastState = !bLastState;
	}	
}

void CBRAnyChatSDKDemoDlg::OnButtonAudioctrl2() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[2] != -1)
	{
		BRAC_UserSpeakControl(m_iUserID[2],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonAudioctrl3() 
{
	static BOOL bLastState = TRUE;
	if(m_iUserID[3] != -1)
	{
		BRAC_UserSpeakControl(m_iUserID[3],!bLastState);
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl0() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[0] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[0], !bLastState, dwFlags, 0, _T("用户自定义字符串：hellow world!"));
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl1() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[1] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[1], !bLastState, dwFlags, 0, _T("用户自定义字符串：hellow world!"));
		bLastState = !bLastState;
	}	
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl2() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[2] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[2], !bLastState, dwFlags, 0, _T("用户自定义字符串：hellow world!"));
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl3() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[3] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[3], !bLastState, dwFlags, 0, _T("用户自定义字符串：hellow world!"));
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonSnapshotctrl0() 
{
	if(m_iUserID[0] != -1)
	{
		BRAC_SnapShot(m_iUserID[0],0,0);
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonSnapshotctrl1() 
{
	if(m_iUserID[1] != -1)
	{
		BRAC_SnapShot(m_iUserID[1],0,0);
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonSnapshotctrl2() 
{
	if(m_iUserID[2] != -1)
	{
		BRAC_SnapShot(m_iUserID[2],0,0);
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonSnapshotctrl3() 
{
	if(m_iUserID[3] != -1)
	{
		BRAC_SnapShot(m_iUserID[3],0,0);
	}
}

