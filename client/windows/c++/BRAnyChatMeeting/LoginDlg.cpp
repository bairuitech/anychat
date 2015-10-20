// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "LoginDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define SETTINGS_AREA_HEIGHT	40		// 设置区域高度


CLoginDlg::CLoginDlg(CWnd* pParent)
	: CDialog(CLoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLoginDlg)
	m_pMainDlg = (CBRAnyChatMeetingDlg*)pParent;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLoginDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialog)
	//{{AFX_MSG_MAP(CLoginDlg)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_SETTINGS, OnButtonSettings)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, OnButtonLogin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLoginDlg message handlers

BOOL CLoginDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	TCHAR szBannerPath[MAX_PATH] = {0};
	TCHAR szBannerFile[MAX_PATH] = {0};
	GetModuleFileName(NULL,szBannerPath,sizeof(szBannerPath)); 
	(strrchr(szBannerPath,'\\'))[1] = 0; 
	strcat(szBannerPath,SUB_PATH_SKINFILE);
	_snprintf(szBannerFile,sizeof(szBannerFile),"%s\\%s",szBannerPath,_T("banner.jpg"));
	if(IsFileExist(szBannerFile))
		m_BannerPic.Load(szBannerFile);
	else
		m_BannerPic.Load(IDR_IMAGE_LOGINTOP);
	
	m_bkBrush.CreateSolidBrush(RGB(228,244,255));
	m_bottomBrush.CreateSolidBrush(RGB(194,227,250));
	m_settingsBrush.CreateSolidBrush(RGB(228,244,255));

	m_bSettingMode = FALSE;
	// 缩小窗口界面，隐藏设置项
	CRect rcClient;
	GetClientRect(rcClient);
	rcClient.bottom -= 20;
	MoveWindow(rcClient);
/*
#ifdef _HRC_USE_SKIN_
	// 如果使用皮肤，则需要将按钮位置下移一点
	CRect rcSettings;
	GetDlgItem(IDC_BUTTON_SETTINGS)->GetWindowRect(rcSettings);
	ScreenToClient(rcSettings);
	rcSettings.bottom += 8;	rcSettings.top += 8;
	GetDlgItem(IDC_BUTTON_SETTINGS)->MoveWindow(rcSettings);

	CRect rcLogin;
	GetDlgItem(IDC_BUTTON_LOGIN)->GetWindowRect(rcLogin);
	ScreenToClient(rcLogin);
	rcLogin.bottom += 8;	rcLogin.top += 8;
	GetDlgItem(IDC_BUTTON_LOGIN)->MoveWindow(rcLogin);
#endif //_HRC_USE_SKIN_
*/
	LoadSettingsParam();

	GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLoginDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_bkBrush.DeleteObject();
	m_bottomBrush.DeleteObject();
	m_settingsBrush.DeleteObject();
	m_BannerPic.Free();

	m_pMainDlg = NULL;
}

// 加载设置参数
void CLoginDlg::LoadSettingsParam(void)
{
	CHAR szConfigFile[MAX_PATH] = {0};
	::GetModuleFileName(NULL,szConfigFile,_MAX_PATH);
	(strrchr(szConfigFile,'\\'))[1] = 0; 
	strcat(szConfigFile,DEFAULT_CONFIG_FILENAME);
	
	TCHAR szTempStr[100] = {0};
	// 读服务器IP地址配置
	if(::GetPrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ServerIPAddr"),NULL,szTempStr,sizeof(szTempStr),szConfigFile))
		GetDlgItem(IDC_SERVER_IPADDR)->SetWindowText(szTempStr);
	else
		GetDlgItem(IDC_SERVER_IPADDR)->SetWindowText(DEFAULT_SERVER_IPADDR);
	// 读服务器端口配置
	DWORD dwPort = ::GetPrivateProfileInt(DEFAULT_CONFIG_SECTION,_T("ServerPort"),DEFAULT_SERVER_PORT,szConfigFile);
	_snprintf(szTempStr,sizeof(szTempStr),"%d",dwPort);
	GetDlgItem(IDC_EDIT_PORT)->SetWindowText(szTempStr);
	
	// 读登录用户名配置
	if(::GetPrivateProfileString(DEFAULT_CONFIG_SECTION,_T("LoginName"),NULL,szTempStr,sizeof(szTempStr),szConfigFile))
		GetDlgItem(IDC_EDIT_USERNAME)->SetWindowText(szTempStr);

	// 读产品名称
	if(::GetPrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ProductName"),NULL,szTempStr,sizeof(szTempStr),szConfigFile))
	{
		strcat(szTempStr, " — 用户登录");
		SetWindowText(szTempStr);
	}
}

void CLoginDlg::OnClose() 
{
	ASSERT(m_pMainDlg);
	m_pMainDlg->OnUserExitSystem();
//	CDialog::OnClose();
}

BOOL CLoginDlg::OnEraseBkgnd(CDC* pDC) 
{
	BOOL rc = CDialog::OnEraseBkgnd(pDC);
	
	return rc;
}

HBRUSH CLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	
	pDC->SetBkMode (TRANSPARENT);

	return m_bkBrush;
}

void CLoginDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	CRect rcClient;
	GetClientRect(rcClient);
	
//	dc.FillRect(rcClient,&m_bkBrush);
	
	// 绘制登录界面顶部图片
	CRect rcBanner;
	rcBanner.left = rcClient.left;		rcBanner.top = rcClient.top;
	rcBanner.right = rcClient.right;	rcBanner.bottom = rcBanner.top + m_BannerPic.GetImageSize().cy;
	m_BannerPic.Render(&dc,rcBanner);

	// 填充登录按钮周边背景颜色
	CRect rcBottom = rcClient;
	if(m_bSettingMode)
		rcBottom.bottom -= SETTINGS_AREA_HEIGHT;
	rcBottom.top = rcBottom.bottom - 35;
	dc.FillRect(rcBottom,&m_bottomBrush);

	// 填充设置区域背景颜色
	if(m_bSettingMode)
	{
		CRect rcSettingArea = rcClient;
		rcSettingArea.top = rcSettingArea.bottom - SETTINGS_AREA_HEIGHT;
		dc.FillRect(rcSettingArea,&m_settingsBrush);
	}

	// Do not call CDialog::OnPaint() for painting messages
}

void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	PostMessage (WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));	
	CDialog::OnLButtonDown(nFlags, point);
}
/**
 *	用户按下设置按钮，显示或隐藏设置区域
 */
void CLoginDlg::OnButtonSettings() 
{
	m_bSettingMode = !m_bSettingMode;

	CRect rcClient;
	GetWindowRect(rcClient);

	DWORD dwHeight = m_bSettingMode ? rcClient.Height() + SETTINGS_AREA_HEIGHT : rcClient.Height() - SETTINGS_AREA_HEIGHT;
	::SetWindowPos(m_hWnd,NULL, 0,0,rcClient.Width(), dwHeight,SWP_NOMOVE | SWP_NOZORDER);

	GetDlgItem(IDC_BUTTON_SETTINGS)->SetWindowText(m_bSettingMode ? "隐藏" : "设置");
}

void CLoginDlg::OnButtonLogin() 
{
	CString strIPAddr,strPort,strUserName,strPassword;
	DWORD dwPort;
	GetDlgItem(IDC_SERVER_IPADDR)->GetWindowText(strIPAddr);
	GetDlgItem(IDC_EDIT_PORT)->GetWindowText(strPort);
	GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(strUserName);
	GetDlgItem(IDC_EDIT_PASSWORD)->GetWindowText(strPassword);
	if(strUserName.IsEmpty())
	{
		AfxMessageBox("请输入用户名（游客方式登录可不用密码）！");
		GetDlgItem(IDC_EDIT_USERNAME)->SetFocus();
		return;
	}
	dwPort = atoi(strPort.GetBuffer(0));
	// 连接服务器
	BRAC_Connect(strIPAddr.GetBuffer(0),dwPort);
	// 登录系统
	BRAC_Login(strUserName.GetBuffer(0),strPassword.GetBuffer(0),0);
}

// 网络连接消息通知
void CLoginDlg::OnConnectNotify(DWORD dwErrorCode)
{
	if(dwErrorCode != GV_ERR_SUCCESS)
	{
		CHAR szNotify[100] = {0};
		_snprintf(szNotify,sizeof(szNotify),"连接服务器失败(%d)!",dwErrorCode);
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(szNotify);
	}
}
// 用户登录消息通知
void CLoginDlg::OnLoginNotify(DWORD dwErrorCode)
{
	if(dwErrorCode != GV_ERR_SUCCESS)
	{
		CHAR szNotify[100] = {0};
		_snprintf(szNotify,sizeof(szNotify),"登录失败(%d)!",dwErrorCode);
		GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText(szNotify);
	}
	else		// 如果登录成功，则保存IP地址、端口号以及登录用户名等信息到配制文件中
	{
		CString strIPAddr,strPort,strUserName;
		GetDlgItem(IDC_SERVER_IPADDR)->GetWindowText(strIPAddr);
		GetDlgItem(IDC_EDIT_PORT)->GetWindowText(strPort);
		GetDlgItem(IDC_EDIT_USERNAME)->GetWindowText(strUserName);


		CHAR szConfigFile[MAX_PATH] = {0};
		::GetModuleFileName(NULL,szConfigFile,_MAX_PATH);
		(strrchr(szConfigFile,'\\'))[1] = 0; 
		strcat(szConfigFile,DEFAULT_CONFIG_FILENAME);

		::WritePrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ServerIPAddr"),strIPAddr,szConfigFile);
		::WritePrivateProfileString(DEFAULT_CONFIG_SECTION,_T("ServerPort"),strPort,szConfigFile);
		::WritePrivateProfileString(DEFAULT_CONFIG_SECTION,_T("LoginName"),strUserName,szConfigFile);
	}
}

// 连接断开，返回登录界面
void CLoginDlg::OnNeedShowLoginDlg(void)
{
	// 清空提示信息
	GetDlgItem(IDC_STATIC_NOTIFY)->SetWindowText("");
	// 默认恢复隐藏设置面板模式
	if(m_bSettingMode)
		OnButtonSettings();
	ShowWindow(SW_SHOW);
}