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


#define REFRESH_TRANSTASK_STATUS_TIMER	1	///< ˢ�´�������״̬��ʱ��
#define REFRESH_SPEAKVOLUME_TIMER		2	///< �����û�˵��������ʱ��
#define REFRESH_RECORDSTATE_TIMER		3	///< ����¼��״̬��ʱ��

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
 *	��Ƶ���ݻص�����
 */
void CALLBACK VideoData_CallBack(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
	CBRAnyChatSDKDemoDlg*	pDemoDlg = (CBRAnyChatSDKDemoDlg*)lpUserValue;
	if(pDemoDlg)
		pDemoDlg->DrawUserVideo(dwUserid,lpBuf,dwLen,bmiHeader);
}
/**
 *	��Ƶ���ݻص�����
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
 *	�������Ļص�����
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
// ͸��ͨ�����ݻص���������
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

// ͸��ͨ��������չ�ص���������
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
// �ļ�����ص���������
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

// ¼�񡢿������������չ�ص���������
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

// SDK Filter ͨ�����ݻص���������
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
 *	�����û���Ƶ
 *	������Դ�ڻص�����
 *	@param dwUserid �û�ID��
 *	@param lpBuf ��Ƶ���ݻ�����
 *	@param dwLen ��������С
 *	@param bmiHeader ��Ƶ��������ͷ��Ϣ����������Ƶ�Ĵ�С����ɫλ������Ϣ
 */
void CBRAnyChatSDKDemoDlg::DrawUserVideo(DWORD dwUserid, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader)
{
	// �����û�ID���ҵ����ʵ���ʾ����
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

	//����Bitmap  
	BITMAPINFOHEADER  *lpbmi = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER)+dwLen);  
	ZeroMemory(lpbmi,sizeof(BITMAPINFOHEADER)+dwLen);
    memcpy((LPBYTE)lpbmi,&bmiHeader,sizeof(bmiHeader));
	memcpy(((LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER)),lpBuf,dwLen);  

	HDC hdc = ::GetDC(m_hWnd);
	HDC dcMem = ::CreateCompatibleDC(hdc);  
	HBITMAP hBitmap = CreateDIBitmap(hdc,lpbmi,CBM_INIT,(LPBYTE)lpbmi+sizeof(BITMAPINFOHEADER),(LPBITMAPINFO)lpbmi,DIB_RGB_COLORS);  
	//��ͼ  
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
	
	// ��ʼ��ÿ����Ƶ��ʾλ����Ϣ
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

	// ����¼��״̬��־
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
	// ��ȡSDK�İ汾��Ϣ
	DWORD dwMainVer,dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRAC_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));

	CString logstr;
	logstr.Format("AnyChat Core SDK Version:%d.%d(%s)",dwMainVer,dwSubVer,szCompileTime);
	AppendLogString(logstr);

	// �򿪣��رգ�SDK����־��¼����
	BRAC_ActiveCallLog(TRUE);

	// ����SDK�����������Ŀ¼��ע��demo����ֻ������Ϊ��ǰĿ¼����Ŀ����Ҫ����Ϊʵ��·����
	CHAR szCoreSDKPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szCoreSDKPath,sizeof(szCoreSDKPath));
	(strrchr(szCoreSDKPath,'\\'))[1] = 0; 
	BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,szCoreSDKPath, (int)strlen(szCoreSDKPath));

	// ����BRAC_InitSDK�ĵڶ���������dwFuncMode��������SDK����δ�����ص�����������ο������ĵ���
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

	// ����¼����ʱ�ļ�����·��
	CHAR szRecordDirectory[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szRecordDirectory,MAX_PATH);
	(strrchr(szRecordDirectory,'\\'))[1] = 0; 
	strcat(szRecordDirectory,"Record");
	BRAC_SetSDKOption(BRAC_SO_RECORD_TMPDIR,szRecordDirectory, (int)strlen(szRecordDirectory));
	// ����¼���ļ���������
	DWORD dwVideoBitrate = 200 * 1000;	// 200kbps
	BRAC_SetSDKOption(BRAC_SO_RECORD_VIDEOBR,(PCHAR)&dwVideoBitrate,sizeof(DWORD));
	DWORD dwAudioBitrate = 96 * 1000;	// 96kbps
	BRAC_SetSDKOption(BRAC_SO_RECORD_AUDIOBR,(PCHAR)&dwAudioBitrate,sizeof(DWORD));

	// ���ÿ�����ʱ�ļ�����·��
	CHAR szSnapShotDirectory[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szSnapShotDirectory,MAX_PATH);
	(strrchr(szSnapShotDirectory,'\\'))[1] = 0; 
	strcat(szSnapShotDirectory,"SnapShot");
	BRAC_SetSDKOption(BRAC_SO_SNAPSHOT_TMPDIR,szSnapShotDirectory, (int)strlen(szSnapShotDirectory));

	// ����SDK��ʱ�ļ�·��
	CHAR szTempPath[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szTempPath,MAX_PATH);
	(strrchr(szTempPath,'\\'))[1] = 0; 
	strcat(szTempPath,"Temp");
	BRAC_SetSDKOption(BRAC_SO_CORESDK_TMPDIR,szTempPath, (int)strlen(szTempPath));
	
	// ���÷�������֤����
	BRAC_SetServerAuthPass("BaiRuiTech");		// ��Ҫ������������SDKAuthPass����ͬ����Сд���У���SDK�����������ӵ�������

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
	BRAC_LeaveRoom(m_iRoomId);

	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		if(m_iUserID[i] != -1)
		{
			//ˢ����ʾ�������������������
			InvalidateRect(m_UserRect[i]);
		}
	}
	
	// �����Լ���userid����Ϊ���ֻ��leaveroom������logout
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
 *	�յ���Ϣ���ͻ������ӷ�����
 *	@param wParam ��BOOL����ʾ�Ƿ����ӳɹ�
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
	BOOL bSuccess = (BOOL)wParam;
	AppendLogString(bSuccess ? "���ӷ������ɹ�..." : "���ӷ�����ʧ��...");
	return 0;
}
/**
 *	�յ���Ϣ���ͻ��˵�¼ϵͳ
 *	@param wParam ��INT����ʾ�Լ����û�ID��
 *	@param lParam ��INT����ʾ��¼�����0 �ɹ�������Ϊ������룬�ο�������붨��
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	DWORD dwUserID = (DWORD)wParam;
	if(lParam == 0)
	{
		CHAR username[30]={0};
		BRAC_GetUserName(dwUserID,username,sizeof(username));
		logstr.Format("��¼�������ɹ����Լ����û����Ϊ��%d(%s)",wParam,username);

		// ���û���ID�����ڵ�һ��λ�ã������ڻص�������������Ҳ������Ƶ�λ��
		m_iUserID[0] = dwUserID;
	}
	else
		logstr.Format("��¼������ʧ�ܣ��������Ϊ�� %d ",lParam);

	AppendLogString(logstr);

	return 0;
}
/**
 *	�յ���Ϣ���ͻ��˽��뷿��
 *	@param wParam ��INT����ʾ�����뷿���ID��
 *	@param lParam ��INT����ʾ�Ƿ���뷿�䣺0�ɹ����룬����Ϊ�������
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT roomid = (INT)wParam;
	if(lParam == 0)
	{
		logstr.Format("�ɹ�������Ϊ��%d �ķ���",roomid);

		BRAC_SetVideoPos(-1,m_hWnd,m_UserRect[0].left,m_UserRect[0].top,m_UserRect[0].right,m_UserRect[0].bottom);
		BRAC_UserCameraControl(-1,TRUE);
		BRAC_UserSpeakControl(-1,TRUE);
	}
	else
		logstr.Format("������뷿��ʧ�ܣ��������Ϊ�� %d ",lParam);

	AppendLogString(logstr);
	return 0;
}
/**
 *	��ʾ��־��Ϣ
 */
void CBRAnyChatSDKDemoDlg::AppendLogString(CString logstr)
{
	m_strLogInfo += (logstr + "\r\n");
	m_ctrlEditLog.SetWindowText(m_strLogInfo);
	m_ctrlEditLog.LineScroll(m_ctrlEditLog.GetLineCount());
}

/**
 *	�յ���ǰ����������û���Ϣ
 *	���뷿��󴥷�һ��
 *	@param wParam ��INT����ʾ�����û������������Լ���
 *	@param lParam ��INT����ʾ����ID
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT onlinenum = (INT)wParam;

	logstr.Format("�ڱ��Ϊ��%d �ķ��乲�� %d λ�����û�",lParam, onlinenum);
	AppendLogString(logstr);

	

	DWORD dwUserNum = 0;
	BRAC_GetOnlineUser(NULL,dwUserNum);		///< ���Ȼ�ȡ��������������
	if(!dwUserNum)
		return 0;

	LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwUserNum);
	BRAC_GetOnlineUser(lpdwUserList,dwUserNum);	///< ������ȡ�����û��б�

	for(INT i=0; i< (INT)dwUserNum; i++)
	{
		DWORD userid = lpdwUserList[i];
		// ���û���һ���յ�λ����ʾ��壨��0��λ�������Լ���
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
			logstr.Format("�û�%d ����Ƶ״̬�ǣ� %d",userid,dwState);
			AppendLogString(logstr);
			

			m_iUserID[site] = userid;
		}
		else				///< �Ѿ�û��λ���ˣ�Demo��ʾ����
			break;
	}

	free(lpdwUserList);

	return 0;
}
/**
 *	�յ���Ϣ���û����루�뿪������
 *	@param wParam ��INT����ʾ�û�ID��
 *	@param lParam ��BOOL����ʾ���û��ǽ��루TRUE�����뿪��FALSE������
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT		userid = (INT)wParam;
	BOOL	bEnter = (BOOL)lParam;

	CHAR username[30]={0};
	BRAC_GetUserName(userid,username,sizeof(username));
	logstr.Format("���Ϊ��%d ���û�(%s) %s ����",userid,username, bEnter ? "����" : "�뿪");
	AppendLogString(logstr);

	if(bEnter)
	{
		// ���û���һ���յ�λ����ʾ��壨��0��λ�������Լ���
		INT site = -1;
		for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
		{
			if(-1 == m_iUserID[i])
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
		//������û�ռ��λ�õ���Ϣ
		for(INT i=1; i<DEMO_SHOW_USER_NUM; i++)
		{
			if(m_iUserID[i] == userid)
			{
				m_iUserID[i] = -1;

				//ˢ����ʾ�������������������
				InvalidateRect(m_UserRect[i]);
				break;
			}
		}
	}

	return 0;
}

/**
 *	�յ���Ϣ���û�����Ƶ�豸״̬�仯��Ϣ
 *	@param wParam ��INT����ʾ�û�ID��
 *	@param lParam ��BOOL����ʾ���û��Ƿ��Ѵ���Ƶ�ɼ��豸
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientMicStateChange(WPARAM wParam, LPARAM lParam)
{
	CString logstr;

	logstr.Format("���Ϊ��%d ���û� %s ����Mic�豸",wParam, lParam ? "��" : "�ر�");
	AppendLogString(logstr);

	return 0;
}

/**
 *	�յ���Ϣ�����������ѹر�
 *	����Ϣֻ���ڿͻ������ӷ������ɹ�֮�������쳣�ж�֮ʱ����
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
	AppendLogString("���������ѹرգ��Ͽ���");

	for(INT i=0; i<DEMO_SHOW_USER_NUM; i++)
	{
		m_iUserID[i] = -1;
	}
	return 0;
}

/**
 *	�û�����ģʽ�����仯
 *	@param wParam ��INT����ʾ�û�ID��
 *	@param lParam ��INT����ʾ�û��ĵ�ǰ����ģʽ
 */
LRESULT CBRAnyChatSDKDemoDlg::OnGVClientChatModeChange(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT userid = (INT)wParam;
	INT chatmode = (INT)lParam;

	if(m_iUserID[0] == userid)
	{
		logstr.Format("�Լ���%d ��������ģʽ�ı䣬��ǰ����ģʽΪ��%s",userid, chatmode == 0 ? "����ģʽ" : "˽��ģʽ");
	}
	else
		logstr.Format("���Ϊ��%d ���û�����ģʽ�ı䣬��ǰ����ģʽΪ��%s",userid, chatmode == 0 ? "����ģʽ" : "˽��ģʽ");

	AppendLogString(logstr);
	return 0;
}
void CBRAnyChatSDKDemoDlg::OnButtonVideoproperty() 
{
	BRAC_ShowLVProperty(m_hWnd,"AnyChat ������Ƶ���ʵ���");
	
}
/**
 *	ˢ���豸�б�
 */
void CBRAnyChatSDKDemoDlg::OnButtonRefreshCapture() 
{
	// ˢ����Ƶ�ɼ��豸�����б�
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

	// ѡ��ǰ�򿪵���Ƶ�ɼ��豸
	CHAR szVideoDeviceName[100] = {0};
	BRAC_GetCurVideoCapture(szVideoDeviceName,sizeof(szVideoDeviceName));
	m_cbVideoCapture.SelectString(-1,szVideoDeviceName);

	// ˢ����Ƶ�ɼ��豸�����б�
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
	// ѡ��ǰ�򿪵���Ƶ�ɼ��豸
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

// ¼�������������ı�
void CBRAnyChatSDKDemoDlg::OnWaveInVolumeChange(DWORD dwVolume)
{
	m_ctrlInVolume.SetPos(dwVolume);
}
// ���������������ı�
void CBRAnyChatSDKDemoDlg::OnWaveOutVolumeChange(DWORD dwVolume)
{
	m_ctrlOutVolume.SetPos(dwVolume);
}



void CBRAnyChatSDKDemoDlg::OnTimer(UINT_PTR nIDEvent) 
{
	switch(nIDEvent)
	{
	case REFRESH_TRANSTASK_STATUS_TIMER:	// ˢ�»�������������״̬
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
					AppendLogString("�������񲻴��ڣ����ܶԷ����뿪���䣡");
				else
					AppendLogString("��ѯ������Ϣʧ�ܣ�");
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
				AppendLogString("������������ɣ�");
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
	case REFRESH_SPEAKVOLUME_TIMER:		// ˢ���û�˵������
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
	case REFRESH_RECORDSTATE_TIMER:		// ˢ��¼��״̬
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
	if(m_dwTransTaskId != -1)	// ��ʾ����Ϊ�˼�࣬ͬʱֻ����һ������ʵ����SDK�ǿ��Զ����񲢷���
		return;

	static TCHAR BASED_CODE szFilter[] = _T("All Files (*.*)||*.*\0");
	CFileDialog	dlg(TRUE, NULL, NULL, /*OFN_HIDEREADONLY | */OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilter, this);
	if (dlg.DoModal() == IDOK)
	{
		CString strFileName = dlg.GetPathName();
		DWORD dwTaskId = 0;
		DWORD wParam = 1;			// �ϲ�Ӧ�ó�����Զ���wParam��lParam��ֵ��������������ֵ�����ص����Է�
		DWORD lParam = 2;
		DWORD dwFlags = 0;			// �ñ�־����Ϊ0����SDK���Զ���������״̬ѡ����ʵĴ���;����TCP��UDP or P2P��
		DWORD ret = BRAC_TransFile(m_iUserID[1],strFileName.GetBuffer(0),wParam,lParam,dwFlags,dwTaskId);
		if(ret == GV_ERR_SUCCESS)
		{
			m_dwTransTaskId = dwTaskId;
			SetTimer(REFRESH_TRANSTASK_STATUS_TIMER,100,NULL);
		}
		else
		{
			CString strError;
			strError.Format("�����ļ���������ʧ�ܣ��������:%d",ret);
			AppendLogString(strError);
			SetDlgItemText(IDC_STATIC_FILESTATUS,"");
		}
	}
}
// ���䳬�󻺳���������ʾ
void CBRAnyChatSDKDemoDlg::OnButtonTransbuf() 
{
	if(m_dwTransTaskId != -1)	// ��ʾ����Ϊ�˼�࣬ͬʱֻ����һ������ʵ����SDK�ǿ��Զ����񲢷���
		return;
	
	PCHAR lpBuf = (PCHAR)malloc(10*1024);		// Ϊ����ʾ������һ��10KByte��С�Ļ�����
	DWORD dwLen = 10*1024;
	if(!lpBuf)
		return;
	lpBuf[1000] = 'Y';			// ��ʾ����Ҫ��Ϊ����֤�յ��������Ƿ���ȷ���ڻ������м�ĳ��λ������һ����־���Է����պ󣬿��жϸñ�־�Ƿ�Ϊ�趨ֵ

	DWORD dwTaskId = 0;
	DWORD wParam = 3;			// �ϲ�Ӧ�ó�����Զ���wParam��lParam��ֵ��������������ֵ�����ص����Է�
	DWORD lParam = 4;
	DWORD dwFlags = 0;			// �ñ�־����Ϊ0����SDK���Զ���������״̬ѡ����ʵĴ���;����TCP��UDP or P2P��
	DWORD ret = BRAC_TransBufferEx(m_iUserID[1],(PBYTE)lpBuf,dwLen,wParam,lParam,dwFlags,dwTaskId);
	if(ret == GV_ERR_SUCCESS)
	{
		m_dwTransTaskId = dwTaskId;
		SetTimer(REFRESH_TRANSTASK_STATUS_TIMER,100,NULL);
	}
	else
	{
		CString strError;
		strError.Format("������������������ʧ�ܣ��������:%d",ret);
		AppendLogString(strError);
		SetDlgItemText(IDC_STATIC_FILESTATUS,"");
	}
	// ������������ɺ� ���������ͷŵ�
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
	// Ϊ����ʾ����򵥣�������þ�̬����������һ�ε�״̬�����ܲ�׼ȷ����Ϊ�����ڱ�ĵط��д򿪣����ǹرյĲ�������ͬ
	// �ر��ǵ�ǰ�û��뿪���䣬����û��ٽ���ʱ����ʼ״̬����׼ȷ
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
		BRAC_StreamRecordCtrlEx(m_iUserID[0], !bLastState, dwFlags, 0, _T("�û��Զ����ַ�����hellow world!"));
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl1() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[1] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[1], !bLastState, dwFlags, 0, _T("�û��Զ����ַ�����hellow world!"));
		bLastState = !bLastState;
	}	
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl2() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[2] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[2], !bLastState, dwFlags, 0, _T("�û��Զ����ַ�����hellow world!"));
		bLastState = !bLastState;
	}
}

void CBRAnyChatSDKDemoDlg::OnButtonRecordctrl3() 
{
	static BOOL bLastState = FALSE;
	if(m_iUserID[3] != -1)
	{
		DWORD dwFlags = ANYCHAT_RECORD_FLAGS_AUDIO | ANYCHAT_RECORD_FLAGS_VIDEO;
		BRAC_StreamRecordCtrlEx(m_iUserID[3], !bLastState, dwFlags, 0, _T("�û��Զ����ַ�����hellow world!"));
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

