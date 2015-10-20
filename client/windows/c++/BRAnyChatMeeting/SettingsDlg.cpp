// SettingsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "BRAnyChatMeeting.h"
#include "SettingsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define VIDEO_QUALITY_BAD			1
#define VIDEO_QUALITY_NORMAL		2
#define VIDEO_QUALITY_MIDDLE		3
#define VIDEO_QUALITY_GOOD			4
#define VIDEO_QUALITY_BEST			5

#define AUDIO_VOLUME_SLIDECHG		WM_USER + 100

#define BITRATE_REFRESHTIMER		1				///< 码率刷新定时器
#define RESOLUTION_REFRESHTIMER		2				///< 分辩率刷新定时器


CSettingsDlg::CSettingsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSettingsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSettingsDlg)
	m_iProxyUserId = 0;
	m_iMultiCastPort = 0;
	//}}AFX_DATA_INIT
}


void CSettingsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDlg)
	DDX_Control(pDX, IDC_COMBO_MULTICASTNIC, m_MultiCastNicCombo);
	DDX_Control(pDX, IDC_COMBO_MULTICASTCTRL, m_MultiCastCtrlCombo);
	DDX_Control(pDX, IDC_COMBO_MULTICASTPOLITIC, m_MultiCastPoliticCombo);
	DDX_Control(pDX, IDC_COMBO_AUDIOPLAYBACK, m_AudioPlaybackCombo);
	DDX_Control(pDX, IDC_COMBO_VIDEOPRESET, m_VideoPresetCombo);
	DDX_Control(pDX, IDC_COMBO_VIDEOBITRATE, m_VideoBitrateCombo);
	DDX_Control(pDX, IDC_COMBO_VIDEOFPS, m_VideoFpsCombo);
	DDX_Control(pDX, IDC_COMBO_VIDEOSIZE, m_VideoSizeCombo);
	DDX_Control(pDX, IDC_COMBO_AUDIOWORKMODE, m_AudioWorkModeCombo);
	DDX_Control(pDX, IDC_SLIDER_WAVEINVOLUME, m_ctrlWaveInVolume);
	DDX_Control(pDX, IDC_SLIDER_WAVEOUTVOLUME, m_ctrlWaveOutVolume);
	DDX_Control(pDX, IDC_COMBO_VIDEOQUALITY, m_VideoQualityCombo);
	DDX_Control(pDX, IDC_COMBO_VIDEOCAPTURE, m_VideoCaptureCombo);
	DDX_Control(pDX, IDC_COMBO_AUDIOCAPTURE, m_AudioCaptureCombo);
	DDX_Text(pDX, IDC_EDIT_PROXYUSERID, m_iProxyUserId);
	DDX_Text(pDX, IDC_EDIT_MULTICASTPORT, m_iMultiCastPort);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSettingsDlg, CDialog)
	//{{AFX_MSG_MAP(CSettingsDlg)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOCAPTURE, OnSelchangeVideoCapture)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIOCAPTURE, OnSelchangeAudioCapture)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOPROPERTY, OnButtonVideoProperty)
	ON_MESSAGE(AUDIO_VOLUME_SLIDECHG,OnAudioVolumeSlideChange)
	ON_BN_CLICKED(IDC_CHECK_AUDIOVAD, OnCheckAudioVAD)
	ON_BN_CLICKED(IDC_CHECK_AUDIOAEC, OnCheckAudioAEC)
	ON_BN_CLICKED(IDC_CHECK_AUDIONS, OnCheckAudioNS)
	ON_BN_CLICKED(IDC_CHECK_AUDIOAGC, OnCheckAudioAGC)
	ON_WM_SHOWWINDOW()
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIOWORKMODE, OnSelchangeAudioWorkMode)
	ON_BN_CLICKED(IDC_CHECK_DEINTERLACE, OnCheckDeinterlace)
	ON_BN_CLICKED(IDC_CHECK_MICBOOST, OnCheckMicBoost)
	ON_BN_CLICKED(IDC_CHECK_STREAMPROXY, OnCheckStreamProxy)
	ON_BN_CLICKED(IDC_BUTTON_CHANGEPROXYUSER, OnButtonChangeProxyUser)
	ON_BN_CLICKED(IDC_BUTTON_VIDEOAPPLY, OnButtonVideoApply)
	ON_BN_CLICKED(IDC_CHECK_SERVERVIDEOSETTINGS, OnCheckServerVideoSettings)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEOBITRATE, OnSelchangeComboVideoBitrate)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIOPLAYBACK, OnSelchangeComboAudioPlayback)
	ON_CBN_SELCHANGE(IDC_COMBO_MULTICASTPOLITIC, OnSelchangeComboMulticastPolitic)
	ON_BN_CLICKED(IDC_BUTTON_MULTICASTAPPLY, OnButtonMulticastApply)
	ON_BN_CLICKED(IDC_CHECK_ENABLEP2P, OnCheckEnableP2P)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSettingsDlg message handlers

BOOL CSettingsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	DWORD dwIndex = 0;
	dwIndex = m_VideoQualityCombo.AddString("较差质量");
	m_VideoQualityCombo.SetItemData(dwIndex,VIDEO_QUALITY_BAD);
	dwIndex = m_VideoQualityCombo.AddString("一般质量");
	m_VideoQualityCombo.SetItemData(dwIndex,VIDEO_QUALITY_NORMAL);
	dwIndex = m_VideoQualityCombo.AddString("中等质量");
	m_VideoQualityCombo.SetItemData(dwIndex,VIDEO_QUALITY_MIDDLE);
	m_VideoQualityCombo.SetCurSel(dwIndex);
	dwIndex = m_VideoQualityCombo.AddString("较好质量");
	m_VideoQualityCombo.SetItemData(dwIndex,VIDEO_QUALITY_GOOD);
	dwIndex = m_VideoQualityCombo.AddString("最好质量");
	m_VideoQualityCombo.SetItemData(dwIndex,VIDEO_QUALITY_BEST);
	m_VideoQualityCombo.EnableWindow(FALSE);

	dwIndex = m_VideoSizeCombo.AddString("176x144");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(176,144));
	dwIndex = m_VideoSizeCombo.AddString("320x240");
	m_VideoSizeCombo.SetItemData(dwIndex, MAKELONG(320,240));
	m_VideoSizeCombo.SetCurSel(dwIndex);
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

	dwIndex = m_VideoFpsCombo.AddString("5  FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,5);
	dwIndex = m_VideoFpsCombo.AddString("8  FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,8);
	m_VideoFpsCombo.SetCurSel(dwIndex);
	dwIndex = m_VideoFpsCombo.AddString("12 FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,12);
	dwIndex = m_VideoFpsCombo.AddString("15 FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,15);
	dwIndex = m_VideoFpsCombo.AddString("20 FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,20);
	dwIndex = m_VideoFpsCombo.AddString("25 FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,25);
	dwIndex = m_VideoFpsCombo.AddString("30 FPS");
	m_VideoFpsCombo.SetItemData(dwIndex,30);

	dwIndex = m_VideoBitrateCombo.AddString("质量模式");
	m_VideoBitrateCombo.SetItemData(dwIndex,0);
	dwIndex = m_VideoBitrateCombo.AddString("40");
	m_VideoBitrateCombo.SetItemData(dwIndex,40*1000);
	dwIndex = m_VideoBitrateCombo.AddString("60");
	m_VideoBitrateCombo.SetItemData(dwIndex,60*1000);
	m_VideoBitrateCombo.SetCurSel(dwIndex);
	dwIndex = m_VideoBitrateCombo.AddString("100");
	m_VideoBitrateCombo.SetItemData(dwIndex,100*1000);
	dwIndex = m_VideoBitrateCombo.AddString("150");
	m_VideoBitrateCombo.SetItemData(dwIndex,150*1000);
	dwIndex = m_VideoBitrateCombo.AddString("200");
	m_VideoBitrateCombo.SetItemData(dwIndex,200*1000);
	dwIndex = m_VideoBitrateCombo.AddString("300");
	m_VideoBitrateCombo.SetItemData(dwIndex,300*1000);
	dwIndex = m_VideoBitrateCombo.AddString("400");
	m_VideoBitrateCombo.SetItemData(dwIndex,400*1000);
	dwIndex = m_VideoBitrateCombo.AddString("500");
	m_VideoBitrateCombo.SetItemData(dwIndex,500*1000);
	dwIndex = m_VideoBitrateCombo.AddString("600");
	m_VideoBitrateCombo.SetItemData(dwIndex,600*1000);
	dwIndex = m_VideoBitrateCombo.AddString("800");
	m_VideoBitrateCombo.SetItemData(dwIndex,800*1000);
	dwIndex = m_VideoBitrateCombo.AddString("1000");
	m_VideoBitrateCombo.SetItemData(dwIndex,1000*1000);
	dwIndex = m_VideoBitrateCombo.AddString("1200");
	m_VideoBitrateCombo.SetItemData(dwIndex,1200*1000);
	dwIndex = m_VideoBitrateCombo.AddString("1500");
	m_VideoBitrateCombo.SetItemData(dwIndex,1500*1000);

	dwIndex = m_VideoPresetCombo.AddString("1");
	m_VideoPresetCombo.SetItemData(dwIndex,1);
	dwIndex = m_VideoPresetCombo.AddString("2");
	m_VideoPresetCombo.SetItemData(dwIndex,2);
	dwIndex = m_VideoPresetCombo.AddString("3");
	m_VideoPresetCombo.SetItemData(dwIndex,3);
	m_VideoPresetCombo.SetCurSel(dwIndex);
	dwIndex = m_VideoPresetCombo.AddString("4");
	m_VideoPresetCombo.SetItemData(dwIndex,4);
	dwIndex = m_VideoPresetCombo.AddString("5");
	m_VideoPresetCombo.SetItemData(dwIndex,5);


	dwIndex = m_AudioWorkModeCombo.AddString("发言模式(默认)");
	m_AudioWorkModeCombo.SetCurSel(dwIndex);
	m_AudioWorkModeCombo.SetItemData(dwIndex,0);
	dwIndex = m_AudioWorkModeCombo.AddString("放歌模式");
	m_AudioWorkModeCombo.SetItemData(dwIndex,1);
	dwIndex = m_AudioWorkModeCombo.AddString("卡拉OK模式");
	m_AudioWorkModeCombo.SetItemData(dwIndex,2);
	dwIndex = m_AudioWorkModeCombo.AddString("线路输入模式");
	m_AudioWorkModeCombo.SetItemData(dwIndex,3);

	DWORD dwVolume = 0;
	BRAC_AudioGetVolume(BRAC_AD_WAVEOUT,dwVolume);
	m_ctrlWaveOutVolume.SetPos(dwVolume);
	m_ctrlWaveOutVolume.SetNotifyMsg(AUDIO_VOLUME_SLIDECHG);
	dwVolume = 0;
	BRAC_AudioGetVolume(BRAC_AD_WAVEIN,dwVolume);
	m_ctrlWaveInVolume.SetPos(dwVolume);
	m_ctrlWaveInVolume.SetNotifyMsg(AUDIO_VOLUME_SLIDECHG);

	// 仅仅测试流代理功能
	GetDlgItem(IDC_CHECK_STREAMPROXY)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_EDIT_PROXYUSERID)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON_CHANGEPROXYUSER)->ShowWindow(SW_HIDE);

	// 默认是采用服务器配置参数
	((CButton*)GetDlgItem(IDC_CHECK_SERVERVIDEOSETTINGS))->SetCheck(TRUE);
	RefreshVideoSettingsCtrlStatus(TRUE);

	dwIndex = m_MultiCastPoliticCombo.AddString("仅服务器策略(默认)");
	m_MultiCastPoliticCombo.SetItemData(dwIndex, 0);
	m_MultiCastPoliticCombo.SetCurSel(dwIndex);
	dwIndex = m_MultiCastPoliticCombo.AddString("仅组播策略");
	m_MultiCastPoliticCombo.SetItemData(dwIndex, 1);
	dwIndex = m_MultiCastPoliticCombo.AddString("服务器策略+组播");
	m_MultiCastPoliticCombo.SetItemData(dwIndex, 2);

	dwIndex = m_MultiCastCtrlCombo.AddString("加入多播组");
	m_MultiCastCtrlCombo.SetItemData(dwIndex, BRAC_MCFLAGS_JOINGROUP);
	m_MultiCastCtrlCombo.SetCurSel(dwIndex);
	dwIndex = m_MultiCastCtrlCombo.AddString("退出多播组");
	m_MultiCastCtrlCombo.SetItemData(dwIndex, BRAC_MCFLAGS_LEAVEGROUP);

	SetDlgItemText(IDC_MULTICAST_IPADDR,"224.2.3.4");
	SetDlgItemText(IDC_EDIT_MULTICASTPORT,"9810");

	dwIndex = m_MultiCastNicCombo.AddString("默认网络设备");
	m_MultiCastNicCombo.SetCurSel(dwIndex);
	// 枚举系统中的所有网络设备
	DWORD LocalIPArray[10] = {0};
	DWORD dwCount = GetLocalIPAddr(LocalIPArray, 10);
	for (int i=0; i<(int)dwCount; i++)
	{
		struct in_addr in = {0};
		in.s_addr = htonl(LocalIPArray[i]);
		m_MultiCastNicCombo.AddString(inet_ntoa(in));
	}

	((CButton*)GetDlgItem(IDC_CHECK_ENABLEP2P))->SetCheck(TRUE);		// 默认是P2P优先

	SetTimer(BITRATE_REFRESHTIMER, 500, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSettingsDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	
}
/**
 *	界面显示消息，刷新相关的状态
 */
void CSettingsDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
		RefreshAllStatus();
}

void CSettingsDlg::OnSelchangeVideoCapture() 
{
	CString strCaptureName;
	m_VideoCaptureCombo.GetLBText(m_VideoCaptureCombo.GetCurSel(),strCaptureName);
	BRAC_SelectVideoCapture(strCaptureName);	
}
// 用户选择指定的音频采集设备
void CSettingsDlg::OnSelchangeAudioCapture() 
{
	CString strCaptureName;
	m_AudioCaptureCombo.GetLBText(m_AudioCaptureCombo.GetCurSel(),strCaptureName);
	BRAC_SelectAudioCapture(strCaptureName);
}
// 用户选择指定的音频播放设备
void CSettingsDlg::OnSelchangeComboAudioPlayback() 
{
	CString strDeviceName;
	m_AudioPlaybackCombo.GetLBText(m_AudioPlaybackCombo.GetCurSel(),strDeviceName);
	BRAC_SelectAudioPlayback(strDeviceName);
}

// 刷新音、视频采集设备
void CSettingsDlg::RefreshCaptureDevice(void)
{
	// 刷新视频采集设备下拉列表
	PCHAR DeviceName[10] = {0};
	DWORD DeviceNum = 10;
	BRAC_EnumVideoCapture(DeviceName,DeviceNum);
	
	m_VideoCaptureCombo.ResetContent();
	for(INT i=0; i<(INT)DeviceNum; i++)
	{
		if(DeviceName[i])
		{
			m_VideoCaptureCombo.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}
	
	// 选择当前打开的视频采集设备
	CHAR szVideoDeviceName[100] = {0};
	BRAC_GetCurVideoCapture(szVideoDeviceName,sizeof(szVideoDeviceName));
	m_VideoCaptureCombo.SelectString(-1,szVideoDeviceName);
	
	// 刷新音频采集设备下拉列表
	DeviceNum = 10;
	BRAC_EnumAudioCapture(DeviceName,DeviceNum);
	
	m_AudioCaptureCombo.ResetContent();
	for(i=0; i<(INT)DeviceNum; i++)
	{
		if(DeviceName[i])
		{
			m_AudioCaptureCombo.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}
	// 选择当前打开的音频采集设备
	CHAR szAudioDeviceName[100] = {0};
	BRAC_GetCurAudioCapture(szAudioDeviceName,sizeof(szAudioDeviceName));
	m_AudioCaptureCombo.SelectString(-1,szAudioDeviceName);

	// 刷新音频播放设备下拉列表
	DeviceNum = 10;
	BRAC_EnumAudioPlayback(DeviceName,DeviceNum);
	
	m_AudioPlaybackCombo.ResetContent();
	for(i=0; i<(INT)DeviceNum; i++)
	{
		if(DeviceName[i])
		{
			m_AudioPlaybackCombo.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}
	// 选择当前打开的音频播放设备
	CHAR szAudioPlayDevice[100] = {0};
	BRAC_GetCurAudioPlayback(szAudioPlayDevice,sizeof(szAudioPlayDevice));
	m_AudioPlaybackCombo.SelectString(-1,szAudioPlayDevice);	
}

void CSettingsDlg::OnButtonVideoProperty() 
{
	BRAC_ShowLVProperty(m_hWnd,"AnyChat 本地视频画质调节");
}
/**
 *	用户拖动音量滑动条
 *	@param lParam 消息发送方的窗口句柄
 */
LRESULT CSettingsDlg::OnAudioVolumeSlideChange(WPARAM wParam, LPARAM lParam)
{
	if((HWND)lParam == m_ctrlWaveOutVolume.GetSafeHwnd())
	{
		DWORD dwVolume = m_ctrlWaveOutVolume.GetPos();
		BRAC_AudioSetVolume(BRAC_AD_WAVEOUT,dwVolume);
	}
	else if((HWND)lParam == m_ctrlWaveInVolume.GetSafeHwnd())
	{
		DWORD dwVolume = m_ctrlWaveInVolume.GetPos();
		BRAC_AudioSetVolume(BRAC_AD_WAVEIN,dwVolume);
	}
	return 0;
}

// 系统音量变化通知
void CSettingsDlg::OnSystemVolumeChangeNotify(BRAC_AudioDevice device, DWORD dwVolume)
{
	if(device == BRAC_AD_WAVEOUT)
		m_ctrlWaveOutVolume.SetPos(dwVolume);
	else if(device == BRAC_AD_WAVEIN)
		m_ctrlWaveInVolume.SetPos(dwVolume);
}
/**
 *	用户设置音频静音检测特性
 */
void CSettingsDlg::OnCheckAudioVAD() 
{
	BOOL bEnableVAD = ((CButton*)GetDlgItem(IDC_CHECK_AUDIOVAD))->GetCheck();
	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL,(PCHAR)&bEnableVAD,sizeof(bEnableVAD));	

/*	// 测试动态调节音频质量代码 only for test!
	BOOL bSelect = ((CButton*)GetDlgItem(IDC_CHECK_AUDIOVAD))->GetCheck();
	DWORD dwMonoBitrate = bSelect ? 5000 : 25000;
	BRAC_SetSDKOption(BRAC_SO_AUDIO_MONOBITRATE,(PCHAR)&dwMonoBitrate,sizeof(DWORD));
	DWORD dwStereoBitrate = bSelect? 15000 : 96000;
	BRAC_SetSDKOption(BRAC_SO_AUDIO_STEREOBITRATE,(PCHAR)&dwStereoBitrate,sizeof(DWORD));
*/
}
/**
 *	用户设置音频回音消除特性
 */
void CSettingsDlg::OnCheckAudioAEC() 
{
	BOOL bEnableAEC = ((CButton*)GetDlgItem(IDC_CHECK_AUDIOAEC))->GetCheck();
	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,(PCHAR)&bEnableAEC,sizeof(bEnableAEC));	
}
/**
 *	用户设置音频噪音抑制特性
 */
void CSettingsDlg::OnCheckAudioNS() 
{
	BOOL bEnableNS = ((CButton*)GetDlgItem(IDC_CHECK_AUDIONS))->GetCheck();
	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL,(PCHAR)&bEnableNS,sizeof(bEnableNS));	
}
/**
 *	用户设置音频自动增益特性
 */
void CSettingsDlg::OnCheckAudioAGC() 
{
	BOOL bEnableAGC = ((CButton*)GetDlgItem(IDC_CHECK_AUDIOAGC))->GetCheck();
	BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(PCHAR)&bEnableAGC,sizeof(bEnableAGC));
	
}
/**
 *	用户选择音频工作模式
 */
void CSettingsDlg::OnSelchangeAudioWorkMode() 
{
	DWORD dwSelectMode = m_AudioWorkModeCombo.GetItemData(m_AudioWorkModeCombo.GetCurSel());
	BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE,(PCHAR)&dwSelectMode,sizeof(dwSelectMode));
	// 修改模式后，底层会对特效进行修改，并根据对应的模式，自动选择合适的音频输入设备，所以需要再刷新一下相关的状态
	RefreshAllStatus();
}
/**
 *	用户对视频“反交织”进行设置
 *	当输入视频源是隔行扫描源（如电视信号）时通过反交织处理可以提高画面质量
 */
void CSettingsDlg::OnCheckDeinterlace() 
{
	BOOL bDeinterlace = ((CButton*)GetDlgItem(IDC_CHECK_DEINTERLACE))->GetCheck();
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_DEINTERLACE,(PCHAR)&bDeinterlace,sizeof(bDeinterlace));	
}

// 刷新所有状态
void CSettingsDlg::RefreshAllStatus(void)
{
	// 刷新音视频采集设备信息
	RefreshCaptureDevice();
	// 刷新音频特效工作状态
	BOOL bEnableAGC = FALSE;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(PCHAR)&bEnableAGC,sizeof(bEnableAGC));
	((CButton*)GetDlgItem(IDC_CHECK_AUDIOAGC))->SetCheck(bEnableAGC);
	BOOL bEnableAEC = FALSE;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,(PCHAR)&bEnableAEC,sizeof(bEnableAEC));
	((CButton*)GetDlgItem(IDC_CHECK_AUDIOAEC))->SetCheck(bEnableAEC);
	BOOL bEnableVAD = FALSE;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_VADCTRL,(PCHAR)&bEnableVAD,sizeof(bEnableVAD));
	((CButton*)GetDlgItem(IDC_CHECK_AUDIOVAD))->SetCheck(bEnableVAD);
	BOOL bEnableNS = FALSE;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_NSCTRL,(PCHAR)&bEnableNS,sizeof(bEnableNS));
	((CButton*)GetDlgItem(IDC_CHECK_AUDIONS))->SetCheck(bEnableNS);
	
	BOOL bDeinterlace = FALSE;
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_DEINTERLACE,(PCHAR)&bDeinterlace,sizeof(bDeinterlace));
	((CButton*)GetDlgItem(IDC_CHECK_DEINTERLACE))->SetCheck(bDeinterlace);

	// 刷新音频采集模式
	DWORD dwCurMode = 0;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE,(PCHAR)&dwCurMode,sizeof(dwCurMode));
	for (int i=0; i<m_AudioWorkModeCombo.GetCount(); i++)
	{
		if(m_AudioWorkModeCombo.GetItemData(i) == dwCurMode)
		{
			m_AudioWorkModeCombo.SetCurSel(i);
			break;
		}
	}
	// 刷新Mic增强状态
	DWORD dwMicBoostState = 0;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_MICBOOST,(PCHAR)&dwMicBoostState,sizeof(dwMicBoostState));
	if(dwMicBoostState == 2)
		GetDlgItem(IDC_CHECK_MICBOOST)->EnableWindow(FALSE);
	else
	{
		GetDlgItem(IDC_CHECK_MICBOOST)->EnableWindow(TRUE);
		((CButton*)GetDlgItem(IDC_CHECK_MICBOOST))->SetCheck(dwMicBoostState);
	}
	// 刷新视频采集当前分辨率
	DWORD dwVideoSize=0;
	BRAC_QueryUserState(-1, BRAC_USERSTATE_VIDEOSIZE, (PCHAR)&dwVideoSize, sizeof(DWORD));
	CString strVideoSize;
	strVideoSize.Format("(当前分辨率:%dx%d)", LOWORD(dwVideoSize), HIWORD(dwVideoSize));
	GetDlgItem(IDC_STATIC_CURVIDEOSIZE)->SetWindowText(strVideoSize);
}
/**
 *	用户操作Mic增强控制选项
 */
void CSettingsDlg::OnCheckMicBoost() 
{
	BOOL bSelect = ((CButton*)GetDlgItem(IDC_CHECK_MICBOOST))->GetCheck();
	BRAC_SetSDKOption(BRAC_SO_AUDIO_MICBOOST,(PCHAR)&bSelect,sizeof(bSelect));
}
/**
 *	用户启动，或关闭流代理功能
 */
void CSettingsDlg::OnCheckStreamProxy() 
{
	UpdateData();
	BOOL bStartProxy = ((CButton*)GetDlgItem(IDC_CHECK_STREAMPROXY))->GetCheck();
	if(bStartProxy)
	{
		// 如果启动代理，则先设置被代理的用户ID
		BRAC_SetSDKOption(BRAC_SO_PROXY_VIDEOCTRL,(PCHAR)&m_iProxyUserId,sizeof(DWORD));
		BRAC_SetSDKOption(BRAC_SO_PROXY_AUDIOCTRL,(PCHAR)&m_iProxyUserId,sizeof(DWORD));
	}
	BRAC_SetSDKOption(BRAC_SO_PROXY_FUNCTIONCTRL,(PCHAR)&bStartProxy,sizeof(DWORD));
}

void CSettingsDlg::OnButtonChangeProxyUser() 
{
	UpdateData();
	// 动态切换被代理用户的ID
	BRAC_SetSDKOption(BRAC_SO_PROXY_VIDEOCTRL,(PCHAR)&m_iProxyUserId,sizeof(DWORD));
	BRAC_SetSDKOption(BRAC_SO_PROXY_AUDIOCTRL,(PCHAR)&m_iProxyUserId,sizeof(DWORD));
}
/**
 *	用户应用视频参数的修改
 */
void CSettingsDlg::OnButtonVideoApply() 
{
	// 获取是否使用服务器默认视频配置参数
	BOOL bUserServerVideoSettings = ((CButton*)GetDlgItem(IDC_CHECK_SERVERVIDEOSETTINGS))->GetCheck();
	BOOL bUseAppParam = !bUserServerVideoSettings;
	if(bUseAppParam)
	{
		// 如果码率为0，则表示使用质量优先模式
		DWORD dwBitrate = m_VideoBitrateCombo.GetItemData(m_VideoBitrateCombo.GetCurSel());
		// 设置本地视频编码的码率
		BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL,(const char*)&dwBitrate,sizeof(DWORD));
		if(dwBitrate==0)
		{
			DWORD dwQuality = m_VideoQualityCombo.GetItemData(m_VideoQualityCombo.GetCurSel());
			// 设置本地视频编码的质量
			BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,(const char*)&dwQuality,sizeof(DWORD));
		}

		DWORD dwFps = m_VideoFpsCombo.GetItemData(m_VideoFpsCombo.GetCurSel());
		// 设置本地视频编码的帧率
		BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL,(PCHAR)&dwFps,sizeof(DWORD));
		// 设置本地视频编码的关键帧间隔
		DWORD dwGop = dwFps >= 20 ? dwFps : dwFps*4;
		BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_GOPCTRL,(const char*)&dwGop,sizeof(DWORD));

		// 设置本地视频采集分辨率
		DWORD dwVideoSize = m_VideoSizeCombo.GetItemData(m_VideoSizeCombo.GetCurSel());
		DWORD dwWidth = LOWORD(dwVideoSize);
		DWORD dwHeight = HIWORD(dwVideoSize);
		BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL,(PCHAR)&dwWidth,sizeof(DWORD));
		BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL,(PCHAR)&dwHeight,sizeof(DWORD));

		// 设置视频编码预设参数（值越大，编码质量越高，占用CPU资源也会越高）
		DWORD dwVideoPreset = m_VideoPresetCombo.GetItemData(m_VideoPresetCombo.GetCurSel());
		BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL,(const char*)&dwVideoPreset,sizeof(DWORD));
		
	}
	// 让设置生效
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM,(const char*)&bUseAppParam,sizeof(DWORD));
	// 设置一个定时器刷新分辩率
	SetTimer(RESOLUTION_REFRESHTIMER, 1500, NULL);
}
/**
 *	用户在服务器默认配置参数和应用程序自定义参数方面进行选择
 */
void CSettingsDlg::OnCheckServerVideoSettings() 
{
	BOOL bUserServerVideoSettings = ((CButton*)GetDlgItem(IDC_CHECK_SERVERVIDEOSETTINGS))->GetCheck();
	RefreshVideoSettingsCtrlStatus(bUserServerVideoSettings);
}

// 切换视频参数配置控件状态
void CSettingsDlg::RefreshVideoSettingsCtrlStatus(BOOL bUseServerParam)
{
	GetDlgItem(IDC_COMBO_VIDEOBITRATE)->EnableWindow(!bUseServerParam);
	GetDlgItem(IDC_COMBO_VIDEOFPS)->EnableWindow(!bUseServerParam);
	GetDlgItem(IDC_COMBO_VIDEOPRESET)->EnableWindow(!bUseServerParam);
	GetDlgItem(IDC_COMBO_VIDEOSIZE)->EnableWindow(!bUseServerParam);
}

void CSettingsDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case BITRATE_REFRESHTIMER:
		{
			DWORD dwVideoBitrate = 0;
			CString strNotify;
			BRAC_QueryUserState(-1,BRAC_USERSTATE_VIDEOBITRATE,(PCHAR)&dwVideoBitrate,sizeof(DWORD));
			strNotify.Format(_T("Video:%.02fkbps"),(dwVideoBitrate*8)/1000.0);
			GetDlgItem(IDC_STATIC_VIDEOBITRATE)->SetWindowText(strNotify);
		}
		break;
	case RESOLUTION_REFRESHTIMER:
		KillTimer(RESOLUTION_REFRESHTIMER);
		RefreshAllStatus();
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CSettingsDlg::OnSelchangeComboVideoBitrate() 
{
	// 如果码率为0，则表示使用质量优先模式
	DWORD dwBitrate = m_VideoBitrateCombo.GetItemData(m_VideoBitrateCombo.GetCurSel());
	m_VideoQualityCombo.EnableWindow(dwBitrate==0);
}
// 用户改变组播策略
void CSettingsDlg::OnSelchangeComboMulticastPolitic() 
{
	DWORD dwMultiCastPolitic = m_MultiCastPoliticCombo.GetItemData(m_MultiCastPoliticCombo.GetCurSel());
	BRAC_SetSDKOption(BRAC_SO_NETWORK_MULTICASTPOLITIC,(const char*)&dwMultiCastPolitic,sizeof(DWORD));
}
// 用户操作IP组播接口
void CSettingsDlg::OnButtonMulticastApply() 
{
	UpdateData();
	DWORD dwFlags = 0;
	dwFlags |= m_MultiCastCtrlCombo.GetItemData(m_MultiCastCtrlCombo.GetCurSel());
	if(dwFlags&BRAC_MCFLAGS_JOINGROUP)
	{
		if(((CButton*)GetDlgItem(IDC_CHECK_SENDDATA))->GetCheck())
			dwFlags |= BRAC_MCFLAGS_SENDDATA;
		if(((CButton*)GetDlgItem(IDC_CHECK_RECVDATA))->GetCheck())
			dwFlags |= BRAC_MCFLAGS_RECVDATA;
	}
	CString strMultiCastIP;
	GetDlgItemText(IDC_MULTICAST_IPADDR, strMultiCastIP);

	CString strNicIP;
	GetDlgItemText(IDC_COMBO_MULTICASTNIC, strNicIP);
	if(strNicIP.CompareNoCase("默认网络设备") == 0)
		strNicIP = "";

	BRAC_MultiCastControl(strMultiCastIP, m_iMultiCastPort, strNicIP.GetBuffer(0), 5, dwFlags);
}

// 获取本地IP地址列表
DWORD CSettingsDlg::GetLocalIPAddr(LPDWORD iparray, DWORD size)
{
	DWORD offset = 0;
	char hostname[256]={0};
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0)
		return 0;
	
	// 根据主机名获取主机信息.
	hostent* pHostent = gethostbyname(hostname);
	if (pHostent==NULL)
		return 0;
	
	// 解析返回的hostent信息.
	hostent& he = *pHostent;
	
	sockaddr_in sa;
	for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++)
	{
		memcpy(&sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
		iparray[offset++] = ntohl(sa.sin_addr.s_addr);
		if(offset > size)
			break;
	}
	return offset;
}

void CSettingsDlg::OnCheckEnableP2P() 
{
	BOOL bEnableP2P = ((CButton*)GetDlgItem(IDC_CHECK_ENABLEP2P))->GetCheck();
	DWORD dwP2PPolitic = bEnableP2P ? 1 : 0;
	BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC,(PCHAR)&dwP2PPolitic,sizeof(dwP2PPolitic));
}
