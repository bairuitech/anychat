// VideoSetDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Hello AnyChat.h"
#include "VideoSetDlg.h"
#include <BRAnyChatCoreSDK.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// VideoSetDlg dialog


VideoSetDlg::VideoSetDlg(CWnd* pParent /*=NULL*/)
	: CDialog(VideoSetDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(VideoSetDlg)
	m_enableAGC = TRUE;
	m_enableEcho = TRUE;
	m_enableNS = TRUE;
	m_enableVAD = TRUE;
	m_serverPriority = TRUE;
	//}}AFX_DATA_INIT
}


void VideoSetDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(VideoSetDlg)
	DDX_Control(pDX, IDC_COMBO_PLAYDEVICE, m_playDevice);
	DDX_Control(pDX, IDC_COMBO_VIDEODEVICE, m_videoDevice);
	DDX_Control(pDX, IDC_COMBO_RESOLUTION, m_resolution);
	DDX_Control(pDX, IDC_COMBO_QUALITY, m_quality);
	DDX_Control(pDX, IDC_COMBO_PREPARAM, m_preparam);
	DDX_Control(pDX, IDC_COMBO_FRAMERATE, m_frameRate);
	DDX_Control(pDX, IDC_COMBO_BITRATE, m_bitRate);
	DDX_Control(pDX, IDC_COMBO_AUDIOMODE, m_audioMode);
	DDX_Control(pDX, IDC_COMBO_AUDIODEVICE, m_audioDevice);
	DDX_Check(pDX, IDC_CHECK_ENABLEAGC, m_enableAGC);
	DDX_Check(pDX, IDC_CHECK_ENABLEECHO, m_enableEcho);
	DDX_Check(pDX, IDC_CHECK_ENABLENS, m_enableNS);
	DDX_Check(pDX, IDC_CHECK_ENABLEVAD, m_enableVAD);
	DDX_Check(pDX, IDC_CHK_SERVERPRIORITY, m_serverPriority);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(VideoSetDlg, CDialog)
	//{{AFX_MSG_MAP(VideoSetDlg)
	ON_BN_CLICKED(IDC_CHECK_ENABLEAGC, OnCheckAGC)
	ON_BN_CLICKED(IDC_CHECK_ENABLEECHO, OnCheckEcho)
	ON_BN_CLICKED(IDC_CHECK_ENABLENS, OnCheckNS)
	ON_BN_CLICKED(IDC_CHECK_ENABLEVAD, OnCheckVAD)
	ON_BN_CLICKED(IDC_CHK_SERVERPRIORITY, OnCheckServerPriority)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIODEVICE, OnSelAudioDevice)
	ON_CBN_SELCHANGE(IDC_COMBO_AUDIOMODE, OnSelAudioMode)
	ON_CBN_SELCHANGE(IDC_COMBO_BITRATE, OnSelBitRate)
	ON_CBN_SELCHANGE(IDC_COMBO_FRAMERATE, OnSelFrameRate)
	ON_CBN_SELCHANGE(IDC_COMBO_PREPARAM, OnSelPreParam)
	ON_CBN_SELCHANGE(IDC_COMBO_QUALITY, OnSelVideoQuality)
	ON_CBN_SELCHANGE(IDC_COMBO_RESOLUTION, OnSelResolution)
	ON_CBN_SELCHANGE(IDC_COMBO_VIDEODEVICE, OnSelVideodevice)
	ON_CBN_SELCHANGE(IDC_COMBO_PLAYDEVICE, OnSelPlayDevice)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// VideoSetDlg message handlers

BOOL VideoSetDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	initDlg();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void VideoSetDlg::initDlg()
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL, (PCHAR)&m_enableAGC, sizeof(m_enableAGC));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL, (PCHAR)&m_enableVAD, sizeof(m_enableVAD));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL, (PCHAR)&m_enableNS, sizeof(m_enableNS));
	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL, (PCHAR)&m_enableEcho, sizeof(m_enableEcho));

	
	refreshDevice();

	int configMode = 0;
	if (m_serverPriority == TRUE)
	{
		m_resolution.EnableWindow(FALSE);
		m_quality.EnableWindow(FALSE);
		m_preparam.EnableWindow(FALSE);
		m_frameRate.EnableWindow(FALSE);
		m_bitRate.EnableWindow(FALSE);

		configMode = 0;
	}
	else
	{
		m_resolution.EnableWindow(TRUE);
		m_quality.EnableWindow(TRUE);
		m_preparam.EnableWindow(TRUE);
		m_frameRate.EnableWindow(TRUE);
		m_bitRate.EnableWindow(TRUE);

		configMode = 1;
	}

	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, (PCHAR)&configMode, sizeof(configMode));
}
void VideoSetDlg::OnCheckAGC() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_AGCCTRL,(PCHAR)&m_enableAGC,sizeof(m_enableAGC));	
}

void VideoSetDlg::OnCheckEcho() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_ECHOCTRL,(PCHAR)&m_enableEcho,sizeof(m_enableEcho));
}

void VideoSetDlg::OnCheckNS() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_NSCTRL,(PCHAR)&m_enableNS,sizeof(m_enableNS));	
}

void VideoSetDlg::OnCheckVAD() 
{
	UpdateData(TRUE);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_VADCTRL,(PCHAR)&m_enableVAD,sizeof(m_enableVAD));
}

void VideoSetDlg::OnCheckServerPriority() 
{
	UpdateData(TRUE);
	int configMode = 0;
	if (m_serverPriority == TRUE)
	{
		m_resolution.EnableWindow(FALSE);
		m_quality.EnableWindow(FALSE);
		m_preparam.EnableWindow(FALSE);
		m_frameRate.EnableWindow(FALSE);
		m_bitRate.EnableWindow(FALSE);

		configMode = 0;
	}
	else
	{
		m_resolution.EnableWindow(TRUE);
		m_quality.EnableWindow(TRUE);
		m_preparam.EnableWindow(TRUE);
		m_frameRate.EnableWindow(TRUE);
		m_bitRate.EnableWindow(TRUE);
		
		configMode = 1;
	}
	
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM, (PCHAR)&configMode, sizeof(configMode));
}

void VideoSetDlg::OnSelAudioDevice() 
{
	CString strCaptureName;
	m_audioDevice.GetLBText(m_audioDevice.GetCurSel(), strCaptureName);
	BRAC_SelectAudioCapture(strCaptureName);
}

void VideoSetDlg::OnSelAudioMode() 
{
	UpdateData(TRUE);
	CString strPlayMode;
	int playModeIndex = m_audioMode.GetCurSel();
	m_audioMode.GetLBText(m_audioMode.GetCurSel(), strPlayMode);
	BRAC_SetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, (PCHAR)&playModeIndex, sizeof(playModeIndex));
}

// 刷新设备列表
void VideoSetDlg::refreshDevice() 
{
	// 刷新视频采集设备下拉列表
	PCHAR DeviceName[10] = {0};
	DWORD DeviceNum = 10;
	BRAC_EnumVideoCapture(DeviceName, DeviceNum);

	m_videoDevice.ResetContent();
	int i = 0;
	for (i = 0; i < (int) DeviceNum; ++i)
	{
		if (DeviceName[i])
		{
			m_videoDevice.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}

	// 选择当前打开的视频采集设备
	CHAR szVideoDeviceName[100] = {0};
	BRAC_GetCurVideoCapture(szVideoDeviceName, sizeof(szVideoDeviceName));
	m_videoDevice.SelectString(-1, szVideoDeviceName);

	// 刷新音频采集设备下拉列表
	DeviceNum = 10;
	BRAC_EnumAudioCapture(DeviceName, DeviceNum);

	m_audioDevice.ResetContent();
	for (i = 0; i < (int)DeviceNum; ++i)
	{
		if (DeviceName[i])
		{
			m_audioDevice.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}

	// 选择当前打开的视频采集设备
	CHAR szAudioDeviceName[100] = {0};
	BRAC_GetCurAudioCapture(szAudioDeviceName, sizeof(szAudioDeviceName));
	m_audioDevice.SelectString(-1, szAudioDeviceName);

	// 刷新音频播放设备下拉列表
	DeviceNum = 10;
	BRAC_EnumAudioPlayback(DeviceName, DeviceNum);

	m_playDevice.ResetContent();
	for (i = 0; i < (int)DeviceNum; ++i)
	{
		if (DeviceName[i])
		{
			m_playDevice.AddString(DeviceName[i]);
			::GlobalFree((HGLOBAL)DeviceName[i]);
			DeviceName[i] = NULL;
		}
	}

	// 选择当前打开的音频播放设备
	CHAR szAudioPlayDeviceName[100] = {0};
	BRAC_GetCurAudioPlayback(szAudioPlayDeviceName, sizeof(szAudioPlayDeviceName));
	m_playDevice.SelectString(-1, szAudioPlayDeviceName);

	// 刷新音频播放模式下拉列表
	PCHAR modeName[4] = {"发言模式(默认)", "放歌模式", "卡拉OK模式", "线路输入模式"};
	m_audioMode.ResetContent();
	for (i = 0; i < 4; ++i)
	{
		m_audioMode.AddString(modeName[i]);
	}

	int playMode = 0;
	BRAC_GetSDKOption(BRAC_SO_AUDIO_CAPTUREMODE, (PCHAR)&playMode, sizeof(playMode));
	m_audioMode.SelectString(-1, modeName[playMode]);

	// 码率列表
	PCHAR bitRate[15] = {"质量模式", "40Kbps", "60Kbps", "90Kbps", "100Kbps", "150Kbps",
			"200Kbps", "300Kbps", "400Kbps", "500Kbps", "600Kbps", "800Kbps",
			"1000Kbps", "1200Kbps", "1500Kbps"};
	int iUnit = 1000;
	int bitRateValue[15] = {0, 40*iUnit, 60*iUnit, 90*iUnit, 100*iUnit, 150*iUnit,
							200*iUnit, 300*iUnit, 400*iUnit, 500*iUnit, 600*iUnit,
							800*iUnit, 1000*iUnit, 1200*iUnit, 1500*iUnit};
	m_bitRate.ResetContent();
	for (i = 0; i < 15; ++i)
	{
		m_bitRate.AddString(bitRate[i]);
	}
	
	int bitRateIndex = 0;
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL, (PCHAR)&bitRateIndex, sizeof(bitRateIndex));
	for (i =0; i < 15; ++i)
	{
		if(bitRateIndex == bitRateValue[i])
		{
			m_bitRate.SelectString(-1, bitRate[i]);
			break;
		}
	}
	
	// 帧率
	PCHAR frameRate[7] = {"5 FPS", "8 FPS", "12 FPS", "15 FPS", "20 FPS",
						"25 FPS", "30 FPS"};
	int frameRateValue[7] = {5, 8, 12, 15, 20, 25, 30};
	m_frameRate.ResetContent();
	for (i = 0; i < 7; ++i)
	{
		m_frameRate.AddString(frameRate[i]);
	}
	int frameRateIndex = 0;
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL, (PCHAR)&frameRateIndex, sizeof(frameRateIndex));
	for (i = 0; i < 15; ++i)
	{
		if (frameRateIndex == frameRateValue[i])
		{
			m_frameRate.SelectString(-1, frameRate[i]);
			break;
		}
	}
	
	// 质量
	PCHAR videoQuality[3] = {"普通视频质量", "中等视频质量", "较好视频质量"};
	int videoQualityValue[3] = {2, 3, 4};
	m_quality.ResetContent();
	for (i = 0; i < 3; ++i)
	{
		m_quality.AddString(videoQuality[i]);
	}
	int videoQualityIndex = 0;
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL, (PCHAR)&videoQualityIndex, sizeof(videoQualityIndex));
	for (i = 0; i < 3; ++i)
	{
		if (videoQualityIndex == videoQualityValue[i])
		{
			m_quality.SelectString(-1, videoQuality[i]);
			break;
		}
	}
	
	// 分辨率
	PCHAR resolutionText[12] = {"176x144", "320x240", "352x288", "640x480", "720x480",
		"720x576", "800x600", "960x720", "1024x576", "1280x720", "1280x1024", "1920x1080" };
	for (i = 0; i < 12; ++i)
	{
		m_resolution.AddString(resolutionText[i]);
	}

	int resolutionWidth = 320;
	int resolutionHeigth = 240;
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, (PCHAR)&resolutionWidth, sizeof(resolutionWidth));
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, (PCHAR)&resolutionHeigth, sizeof(resolutionHeigth));
	CString strResolution;
	strResolution.Format("%dx%d", resolutionWidth, resolutionHeigth);
	m_resolution.SelectString(-1, strResolution);

	// 预设
	PCHAR preParam[5] = {"1", "2", "3", "4", "5"};
	int iPreParamValue[5] = {1, 2, 3, 4, 5};
	for (i = 0; i < 5; ++i)
	{
		m_preparam.AddString(preParam[i]);
	}
	int iPreParam = 1;
	BRAC_GetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL, (PCHAR)&iPreParam, sizeof(iPreParam));
	for (i = 0; i < 5; ++i)
	{
		if (iPreParam == iPreParamValue[i])
		{
			m_preparam.SelectString(-1, preParam[i]);
			break;
		}
	}
}

void VideoSetDlg::OnSelBitRate() 
{
	UpdateData(TRUE);
	CString strBitRate;
	int selBitRateIndex = m_bitRate.GetCurSel();
	int iUnit = 1000;
	int bitRateValue[15] = {0, 40*iUnit, 60*iUnit, 90*iUnit, 100*iUnit, 150*iUnit,
		200*iUnit, 300*iUnit, 400*iUnit, 500*iUnit, 600*iUnit,
							800*iUnit, 1000*iUnit, 1200*iUnit, 1500*iUnit};
	m_bitRate.GetLBText(m_bitRate.GetCurSel(), strBitRate);
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL, (PCHAR)&bitRateValue[selBitRateIndex], sizeof(bitRateValue[selBitRateIndex]));
}

void VideoSetDlg::OnSelFrameRate() 
{
	UpdateData(TRUE);
	CString strFrameRate;
	int selFrameRateIndex = m_frameRate.GetCurSel();
	int frameRateValue[7] = {5, 8, 12, 15, 20, 25, 30};
	m_frameRate.GetLBText(m_frameRate.GetCurSel(), strFrameRate);
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL, (PCHAR)&frameRateValue[selFrameRateIndex], sizeof(frameRateValue[selFrameRateIndex]));
}

void VideoSetDlg::OnSelPreParam() 
{
	UpdateData(TRUE);
	CString strPreParam;
	int selPreParamIndex = m_preparam.GetCurSel();
	int arrPreParam[5] = {1, 2, 3, 4, 5};
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL, (PCHAR)&arrPreParam[selPreParamIndex], sizeof(arrPreParam[selPreParamIndex]));
}

void VideoSetDlg::OnSelVideoQuality() 
{
	UpdateData(TRUE);
	CString strQuality;
	int selQualityIndex = m_quality.GetCurSel();
	int videoQualityValue[3] = {2, 3, 4};
	m_quality.GetLBText(selQualityIndex, strQuality);
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL, (PCHAR)&videoQualityValue[selQualityIndex], sizeof(videoQualityValue[selQualityIndex]));
}

void VideoSetDlg::OnSelResolution() 
{
	UpdateData(TRUE);
	CString strResolution;
	int resolutionWidth[12] = {176, 320, 352, 640, 720, 720, 800, 960, 1024, 1280, 1280, 1920};
	int resolutionHeigth[12] = {144, 240, 288, 480, 480, 576, 600, 720, 576, 720, 1024, 1080};
	int selResolutionIndex = m_resolution.GetCurSel();
	m_resolution.GetLBText(selResolutionIndex, strResolution);
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL, (PCHAR)&resolutionWidth[selResolutionIndex], sizeof(resolutionWidth[selResolutionIndex]));
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL, (PCHAR)&resolutionHeigth[selResolutionIndex], sizeof(resolutionHeigth[selResolutionIndex]));
}

void VideoSetDlg::OnSelVideodevice() 
{
	CString strCaptureName;
	m_videoDevice.GetLBText(m_videoDevice.GetCurSel(), strCaptureName);
	BRAC_SelectAudioCapture(strCaptureName);
}

void VideoSetDlg::OnSelPlayDevice() 
{
	CString strPlayDevice;
	m_playDevice.GetLBText(m_playDevice.GetCurSel(), strPlayDevice);
	BRAC_SelectAudioPlayback(strPlayDevice);
}
