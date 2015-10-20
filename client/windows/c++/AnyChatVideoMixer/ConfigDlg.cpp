// ConfigDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnyChatVideoMixer.h"
#include "ConfigDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg dialog


CConfigDlg::CConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigDlg::IDD, pParent)
	, m_szServer(_T(""))
	, m_iPort(0)
	, m_szUserName(_T(""))
	, m_szPassword(_T(""))
	, m_iBitrate(0)
	, m_iFrameRate(0)
	, m_iRoomId(0)
	, m_bAudioMix(FALSE)
{
	//{{AFX_DATA_INIT(CConfigDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_EDIT_SERVER, m_szServer);
	DDX_Text(pDX, IDC_EDIT_PORT, m_iPort);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_szUserName);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_szPassword);
	DDX_Text(pDX, IDC_EDIT_BITRATE, m_iBitrate);
	DDX_Text(pDX, IDC_EDIT_VIDEO_FPS, m_iFrameRate);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_VideoSizeCombo);
	DDX_Text(pDX, IDC_EDIT_ROOMID, m_iRoomId);
	DDX_Check(pDX, IDC_CHECK_MIXAUDIO, m_bAudioMix);
}


BEGIN_MESSAGE_MAP(CConfigDlg, CDialog)
	//{{AFX_MSG_MAP(CConfigDlg)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigDlg message handlers

BOOL CConfigDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_szServer = g_localSettings.szServer;
	m_iPort = g_localSettings.dwPort;
	m_iRoomId = g_localSettings.dwRoomId;
	m_szUserName = g_localSettings.szUserName;
	m_szPassword = g_localSettings.szPassWord;
	m_iBitrate = g_localSettings.dwBitrate/1000;
	m_iFrameRate = g_localSettings.dwFrameRate;
	m_bAudioMix = g_localSettings.dwAudioMix;
	UpdateData(FALSE);

	DWORD dwIndex = m_VideoSizeCombo.AddString("320x240");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(320,240));
	dwIndex = m_VideoSizeCombo.AddString("352x288");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(352,288));
	dwIndex = m_VideoSizeCombo.AddString("640x480");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(640,480));
	dwIndex = m_VideoSizeCombo.AddString("720x480");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(720,480));
	dwIndex = m_VideoSizeCombo.AddString("720x576");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(720,576));
	dwIndex = m_VideoSizeCombo.AddString("800x600");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(800,600));
	dwIndex = m_VideoSizeCombo.AddString("960x720");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(960,720));
	dwIndex = m_VideoSizeCombo.AddString("1024x576");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(1024,576));
	dwIndex = m_VideoSizeCombo.AddString("1280x720");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(1280,720));
	dwIndex = m_VideoSizeCombo.AddString("1280x1024");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(1280,1024));
	dwIndex = m_VideoSizeCombo.AddString("1920x1080");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(1920,1080));

	for (int i=0; i<m_VideoSizeCombo.GetCount(); i++)
	{
		if(m_VideoSizeCombo.GetItemData(i) == (DWORD)MAKELONG(g_localSettings.dwWidth, g_localSettings.dwHeight))
		{
			m_VideoSizeCombo.SetCurSel(i);
			break;
		}
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

void CConfigDlg::OnOK() 
{
	UpdateData(TRUE);
	_snprintf(g_localSettings.szServer, sizeof(g_localSettings.szServer), "%s", m_szServer);
	_snprintf(g_localSettings.szUserName, sizeof(g_localSettings.szUserName), "%s", m_szUserName);
	_snprintf(g_localSettings.szPassWord, sizeof(g_localSettings.szPassWord), "%s", m_szPassword);

	g_localSettings.dwPort = m_iPort;
	g_localSettings.dwRoomId = m_iRoomId;
	g_localSettings.dwBitrate = m_iBitrate*1000;
	g_localSettings.dwFrameRate = m_iFrameRate;
	g_localSettings.dwAudioMix = m_bAudioMix;

	DWORD dwVideoSize = m_VideoSizeCombo.GetItemData(m_VideoSizeCombo.GetCurSel());
	g_localSettings.dwWidth = LOWORD(dwVideoSize);
	g_localSettings.dwHeight = HIWORD(dwVideoSize);

	UpdateLocalSettings2IniFile();
	CDialog::OnOK();
}
