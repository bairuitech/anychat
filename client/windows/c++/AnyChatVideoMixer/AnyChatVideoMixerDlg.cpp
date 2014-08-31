// AnyChatVideoMixerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AnyChatVideoMixer.h"
#include "AnyChatVideoMixerDlg.h"
#include "ConfigDlg.h"
#include "AnyChatSDK/BRAnyChatCoreSDK.h"


#pragma comment(lib, "AnyChatSDK/BRAnyChatCore.lib")


#define MIX_SUPPORT_CHANNELS		1
#define MIX_SUPPORT_SAMPLESPERSEC	16000
#define MIX_SUPPORT_BITSPERSAMPLE	16

#define MIX_AUDIO_INTERVAL			20			///< 合成的时间间隔，单位：ms



#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

typedef enum ANYCHAT_PIXFMT_ENUM
{
	AC_PIX_FMT_UNKNOW = -1,
	AC_PIX_FMT_YUV420P = 100,
}AC_PIX_FMT;

// 图像迭加
typedef BOOL (__cdecl *ImageOverlayFunc)(DWORD dwSrcWidth, DWORD dwSrcHeight, AC_PIX_FMT srcFmt, LPBYTE lpSrcFrame, DWORD dwOvrWidth, DWORD dwOvrHeight, AC_PIX_FMT ovrFmt, LPBYTE lpOvrFrame, DWORD dwXPos, DWORD dwYPos, DWORD dwDesWidth, DWORD dwDesHeight, DWORD dwTransColor, DWORD dwFlags);

ImageOverlayFunc g_lpImageOverlayFunc = NULL;


CAnyChatVideoMixerDlg::CAnyChatVideoMixerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAnyChatVideoMixerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAnyChatVideoMixerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CAnyChatVideoMixerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAnyChatVideoMixerDlg)
	DDX_Control(pDX, IDC_EDIT_LOG, m_ctrlEditLog);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAnyChatVideoMixerDlg, CDialog)
	//{{AFX_MSG_MAP(CAnyChatVideoMixerDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CONFIG, OnButtonConfig)
	ON_MESSAGE(WM_GV_CONNECT,OnGVClientConnect)
	ON_MESSAGE(WM_GV_LOGINSYSTEM,OnGVClientLogin)
	ON_MESSAGE(WM_GV_ENTERROOM,OnGVClientEnterRoom)
	ON_MESSAGE(WM_GV_ONLINEUSER,OnGVClientOnlineUser)
	ON_MESSAGE(WM_GV_USERATROOM,OnGVClientUserAtRoom)
	ON_MESSAGE(WM_GV_LINKCLOSE,OnGVClientLinkClose)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/**
 *	合成视频工作线程
 */
unsigned int CALLBACK VideoAndAudioMixThread( void * args )
{
	DWORD dwAudioSamplesOnceInput = (MIX_SUPPORT_SAMPLESPERSEC/1000) * MIX_SUPPORT_CHANNELS * MIX_AUDIO_INTERVAL;
	LONG* lpAudioMixBuf = (LONG*)malloc(dwAudioSamplesOnceInput*sizeof(LONG));
	if(!lpAudioMixBuf)
		return -1;

	CAnyChatVideoMixerDlg*	lpDlg = (CAnyChatVideoMixerDlg*)args;
	while(lpDlg && !lpDlg->m_bStopThread)
	{
		if(!lpDlg->m_bInRoom)
		{
			Sleep(10);
			continue;
		}
		// 合成视频
		DWORD dwVideoInterval = GetTickCount() - lpDlg->m_dwLastVideoInputTime;
		DWORD dwFrameInterval = (g_localSettings.dwFrameRate==0 || g_localSettings.dwFrameRate >=30) ? 1000/25 : 1000/g_localSettings.dwFrameRate;
		if(lpDlg->m_dwLastVideoInputTime == 0 || dwVideoInterval > dwFrameInterval)
		{
			// 填充黑色背景
			DWORD dwPixels = g_localSettings.dwWidth * g_localSettings.dwHeight;
			memset(lpDlg->m_lpMixVideoBuf, 0, dwPixels);
			memset(lpDlg->m_lpMixVideoBuf+dwPixels, 128, dwPixels/2);

			DWORD dwSiteIndex = 0;
			DWORD dwSchemeIndex = lpDlg->m_dwSelectScheme;
			::EnterCriticalSection(&lpDlg->m_hMapSection);
			// 首先判断有几个视频源需要合成
			if(lpDlg->m_dwSelectScheme == -1)
			{
				DWORD dwVideoCount = 0;
				std::map<DWORD, LPUSER_ITEM>::iterator it = lpDlg->m_UserItemMap.begin();
				while(it != lpDlg->m_UserItemMap.end())
				{
					if(it->second->lpImageBuf)
						dwVideoCount++;
					it++;
				}
				if(dwVideoCount > 9)
					dwSchemeIndex = 15;			// 16分屏
				else if(dwVideoCount > 8)
					dwSchemeIndex = 8;			// 9分屏
				else if(dwVideoCount > 4)
					dwSchemeIndex = 7;			// 8分屏
				else if(dwVideoCount > 1)
					dwSchemeIndex = 3;			// 4分屏
				else
					dwSchemeIndex = 0;			// 1分屏
			}
			std::map<DWORD, LPUSER_ITEM>::iterator it = lpDlg->m_UserItemMap.begin();
			while(it != lpDlg->m_UserItemMap.end())
			{
				// 判断视频是否处于活动状态
				if(it->second->dwVideoActiveTime != 0 && (GetTickCount() - it->second->dwVideoActiveTime) >= 5000 && it->second->lpImageBuf)
				{
					free(it->second->lpImageBuf);
					it->second->lpImageBuf = NULL;
					it->second->dwImageSize = 0;
					it->second->dwVideoActiveTime = 0;
				}
				if(it->second->lpImageBuf)
					lpDlg->MixUserVideoByScheme(it->second, dwSchemeIndex, dwSiteIndex++);
				it++;
			}
			::LeaveCriticalSection(&lpDlg->m_hMapSection);
			
			if(dwSiteIndex)
			{
				BRAC_InputVideoData((BYTE*)lpDlg->m_lpMixVideoBuf, lpDlg->m_dwMixImageSize, 0);
			}
			lpDlg->m_dwLastVideoInputTime = GetTickCount();
		}
		// 合成音频
		if(lpDlg->m_dwAudioStartTime == 0)
		{
			lpDlg->m_dwAlreadInputAudioSamples = 0;
			lpDlg->m_dwAudioStartTime = GetTickCount();
		}
		DWORD dwAudioInterval = GetTickCount() - lpDlg->m_dwAudioStartTime;
		DWORD dwNeedGenerateSamples = (MIX_SUPPORT_SAMPLESPERSEC/1000) * MIX_SUPPORT_CHANNELS * dwAudioInterval;
		
		if((dwNeedGenerateSamples-lpDlg->m_dwAlreadInputAudioSamples) >= dwAudioSamplesOnceInput && g_localSettings.dwAudioMix)
		{
			memset(lpAudioMixBuf, 0, dwAudioSamplesOnceInput * sizeof(LONG));
			::EnterCriticalSection(&lpDlg->m_hMapSection);
			std::map<DWORD, LPUSER_ITEM>::iterator it = lpDlg->m_UserItemMap.begin();
			while(it != lpDlg->m_UserItemMap.end())
			{
				if(it->second->lpAudioBuf && it->second->dwAudioOffset)
				{
					DWORD dwMixBufSize = (it->second->dwAudioOffset>=dwAudioSamplesOnceInput*sizeof(USHORT)) ? dwAudioSamplesOnceInput*sizeof(USHORT) : it->second->dwAudioOffset;
				
					for(int k=0; k<(int)dwMixBufSize/2; k++)
						lpAudioMixBuf[k] += *((SHORT*)it->second->lpAudioBuf + k);

					// 将剩余部分前移
					DWORD dwLeaveSize = it->second->dwAudioOffset - dwMixBufSize;
					if(dwLeaveSize)
					{
						CHAR* lpTempBuf = (CHAR*)malloc(dwLeaveSize);
						if(lpTempBuf)
						{
							memcpy(lpTempBuf, it->second->lpAudioBuf + dwMixBufSize, dwLeaveSize);
							memcpy(it->second->lpAudioBuf, lpTempBuf, dwLeaveSize);
							free(lpTempBuf);
						}
					}
					it->second->dwAudioOffset -= dwMixBufSize;
				}
				it++;
			}
			::LeaveCriticalSection(&lpDlg->m_hMapSection);

			lpDlg->m_dwAlreadInputAudioSamples += dwAudioSamplesOnceInput;

			SHORT* lpAudioInputBuf = (SHORT*)malloc(dwAudioSamplesOnceInput * sizeof(SHORT));
			if(lpAudioInputBuf)
			{
 				memset(lpAudioInputBuf, 0, dwAudioSamplesOnceInput * sizeof(SHORT));
 				lpDlg->AudioBufferMixUpdate(lpAudioMixBuf, dwAudioSamplesOnceInput, lpAudioInputBuf);
				BRAC_InputAudioData((LPBYTE)lpAudioInputBuf, dwAudioSamplesOnceInput*sizeof(SHORT), 0);
				free(lpAudioInputBuf);
			}
		}
		Sleep(1);
	}
	free(lpAudioMixBuf);
	return 0;
}


/**
 *	视频数据回调函数
 */
void CALLBACK VideoData_CallBack(DWORD dwUserId, LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader, LPVOID lpUserValue)
{
	CAnyChatVideoMixerDlg*	lpDlg = (CAnyChatVideoMixerDlg*)lpUserValue;
	if(!lpDlg)
		return;

	::EnterCriticalSection(&lpDlg->m_hMapSection);
	std::map<DWORD, LPUSER_ITEM>::iterator it = lpDlg->m_UserItemMap.find(dwUserId);
	if(it != lpDlg->m_UserItemMap.end())
	{
		if(it->second->dwImageSize < dwLen)
		{
			it->second->lpImageBuf = (CHAR*)realloc(it->second->lpImageBuf, dwLen);
			if(!it->second->lpImageBuf)
			{
				::LeaveCriticalSection(&lpDlg->m_hMapSection);
				return;
			}
		}
		memcpy(it->second->lpImageBuf, lpBuf, dwLen);
		it->second->dwImageSize = dwLen;
		it->second->dwWidth = bmiHeader.biWidth;
		it->second->dwHeight = bmiHeader.biHeight;
		it->second->dwVideoActiveTime = GetTickCount();
	}
	::LeaveCriticalSection(&lpDlg->m_hMapSection);

}
/**
 *	音频数据回调函数
 */
void CALLBACK AudioData_CallBack(DWORD dwUserId, LPVOID lpBuf, DWORD dwLen, WAVEFORMATEX waveFormatEx, LPVOID lpUserValue)
{
	CAnyChatVideoMixerDlg*	lpDlg = (CAnyChatVideoMixerDlg*)lpUserValue;
	if(!lpDlg)
		return;
	// 只支持特定格式的音频数据合成
	if(waveFormatEx.nChannels != MIX_SUPPORT_CHANNELS || waveFormatEx.nSamplesPerSec != MIX_SUPPORT_SAMPLESPERSEC || waveFormatEx.wBitsPerSample != MIX_SUPPORT_BITSPERSAMPLE)
		return;

	::EnterCriticalSection(&lpDlg->m_hMapSection);
	std::map<DWORD, LPUSER_ITEM>::iterator it = lpDlg->m_UserItemMap.find(dwUserId);
	if(it != lpDlg->m_UserItemMap.end())
	{
		if(it->second->dwAudioBufSize == 0)
		{
			ASSERT(!it->second->lpAudioBuf);
			it->second->dwAudioBufSize = waveFormatEx.nSamplesPerSec;
			it->second->lpAudioBuf = (CHAR*)malloc(it->second->dwAudioBufSize);
			if(!it->second->lpAudioBuf)
			{
				::LeaveCriticalSection(&lpDlg->m_hMapSection);
				return;
			}
		}
		if(it->second->dwAudioOffset + dwLen >= it->second->dwAudioBufSize)
		{
			// 丢弃过期的数据
			it->second->dwAudioOffset = 0;
		}

		memcpy(it->second->lpAudioBuf + it->second->dwAudioOffset, lpBuf, dwLen);
		it->second->dwAudioOffset += dwLen;
	}
	::LeaveCriticalSection(&lpDlg->m_hMapSection);
}


BOOL CAnyChatVideoMixerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// 获取SDK的版本信息
	DWORD dwMainVer,dwSubVer;
	CHAR szCompileTime[100] = {0};
	BRAC_GetSDKVersion(dwMainVer,dwSubVer,szCompileTime,sizeof(szCompileTime));
	
	CString logstr;
	logstr.Format("AnyChat Core SDK Version:%d.%d(Build Time:%s)",dwMainVer,dwSubVer,szCompileTime);
	AppendLogString(logstr);
	
	// 打开（关闭）SDK的日志记录功能
	BRAC_ActiveCallLog(TRUE);
	
	// 设置SDK核心组件所在目录（注：demo程序只是设置为当前目录，项目中需要设置为实际路径）
	CHAR szCoreSDKPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,szCoreSDKPath,sizeof(szCoreSDKPath));
	(strrchr(szCoreSDKPath,'\\'))[1] = 0; 
	BRAC_SetSDKOption(BRAC_SO_CORESDK_PATH,szCoreSDKPath,strlen(szCoreSDKPath));
	
	// 根据BRAC_InitSDK的第二个参数：dwFuncMode，来告诉SDK该如何处理相关的任务（详情请参考开发文档）
	DWORD dwFuncMode = BRAC_FUNC_VIDEO_CBDATA | BRAC_FUNC_AUDIO_CBDATA | BRAC_FUNC_CHKDEPENDMODULE | 
		BRAC_FUNC_AUDIO_VOLUMECALC | BRAC_FUNC_NET_SUPPORTUPNP | BRAC_FUNC_FIREWALL_OPEN |
		BRAC_FUNC_AUDIO_AUTOVOLUME | BRAC_FUNC_CONFIG_LOCALINI;

	BRAC_InitSDK(this->GetSafeHwnd(),dwFuncMode);
	BRAC_SetVideoDataCallBack(BRAC_PIX_FMT_YUV420P,VideoData_CallBack,this);
	BRAC_SetAudioDataCallBack(AudioData_CallBack,this);

	// 设置外部音频、视频输入模式
	BOOL bExtVideoInput = 1;
	BRAC_SetSDKOption(BRAC_SO_CORESDK_EXTVIDEOINPUT, (CHAR*)&bExtVideoInput, sizeof(DWORD));
	BOOL bExtAudioInput = 1;
	BRAC_SetSDKOption(BRAC_SO_CORESDK_EXTAUDIOINPUT, (CHAR*)&bExtAudioInput, sizeof(DWORD));

	// 关闭P2P
	DWORD dwP2PPolitic = 0;
	BRAC_SetSDKOption(BRAC_SO_NETWORK_P2PPOLITIC,(const char*)&dwP2PPolitic,sizeof(DWORD));

	::InitializeCriticalSection(&m_hMapSection);
	m_hThread = NULL;
	m_bStopThread = FALSE;
	m_bInRoom = FALSE;

	RefreshLocalSettings();

	m_dwMixImageSize = g_localSettings.dwWidth * g_localSettings.dwHeight * 3 / 2;
	m_lpMixVideoBuf = (CHAR*)malloc(m_dwMixImageSize);
	m_dwLastVideoInputTime = 0;
	m_dwAudioStartTime = 0;
	m_dwAlreadInputAudioSamples = 0;
	m_dwSelectScheme = -1;

	InitMixScheme();
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CAnyChatVideoMixerDlg::OnPaint() 
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

HCURSOR CAnyChatVideoMixerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CAnyChatVideoMixerDlg::OnDestroy() 
{
	g_lpImageOverlayFunc = NULL;

	BRAC_Release();

	if(m_hThread)
	{
		m_bStopThread = TRUE;
		WaitForSingleObject(m_hThread,INFINITE);
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}

	ClearAllUserItem();

	if(m_lpMixVideoBuf)
	{
		free(m_lpMixVideoBuf);
		m_lpMixVideoBuf = NULL;
	}

	::DeleteCriticalSection(&m_hMapSection);
	CDialog::OnDestroy();	
}

// 清除所有用户单元数据
void CAnyChatVideoMixerDlg::ClearAllUserItem(void)
{
	::EnterCriticalSection(&m_hMapSection);
	while(m_UserItemMap.size())
	{
		std::map<DWORD, LPUSER_ITEM>::iterator it = m_UserItemMap.begin();
		ASSERT(it != m_UserItemMap.end());
		ReleaseUserItem(it->second);
		free(it->second);
		m_UserItemMap.erase(it);
	}
	::LeaveCriticalSection(&m_hMapSection);
}

// 初始化视频混合方案
void CAnyChatVideoMixerDlg::InitMixScheme(void)
{
	memset(m_MixSchemes, 0, MAX_MIX_VIDEO_NUM * sizeof(MIX_SCHEME));
	// 1 画面混合方案
	{
		m_MixSchemes[0].rect[0].Width = 1.0;
		m_MixSchemes[0].rect[0].Height = 1.0;

		m_MixSchemes[0].rect[0].X = 0.0;
		m_MixSchemes[0].rect[0].Y = 0.0;
	}
	// 4 画面混合方案
	{
		for (int i=0; i<4; i++)
		{
			m_MixSchemes[3].rect[i].Width = 1.0/2.0;
			m_MixSchemes[3].rect[i].Height = 1.0/2.0;

			m_MixSchemes[3].rect[i].X = (i%2) * (1.0/2.0);
			m_MixSchemes[3].rect[i].Y = (i/2) * (1.0/2.0);
		}
	}
	// 8 画面混合方案
	{
		m_MixSchemes[7].rect[0].Width = 3.0/4.0;
		m_MixSchemes[7].rect[0].Height = 3.0/4.0;

		m_MixSchemes[7].rect[0].X = 0.0;
		m_MixSchemes[7].rect[0].Y = 0.0;

		for (int i=0; i<4; i++)
		{
			// 右边布局
			m_MixSchemes[7].rect[i+1].Width = 1.0/4.0;
			m_MixSchemes[7].rect[i+1].Height = 1.0/4.0;

			m_MixSchemes[7].rect[i+1].X = 3.0/4.0;
			m_MixSchemes[7].rect[i+1].Y = i * (1.0/4.0);

			// 底部布局
			m_MixSchemes[7].rect[i+4].Width = 1.0/4.0;
			m_MixSchemes[7].rect[i+4].Height = 1.0/4.0;

			m_MixSchemes[7].rect[i+4].X = i * (1.0/4.0);
			m_MixSchemes[7].rect[i+4].Y = 3.0/4.0;
		}
	}

	// 9 画面混合方案
	{
		for (int i=0; i<9; i++)
		{
			m_MixSchemes[8].rect[i].Width = 1.0/3.0;
			m_MixSchemes[8].rect[i].Height = 1.0/3.0;

			m_MixSchemes[8].rect[i].X = (i%3) * (1.0/3.0);
			m_MixSchemes[8].rect[i].Y = (i/3) * (1.0/3.0);
		}
	}

	// 16 画面混合方案
	{
		for (int i=0; i<MAX_MIX_VIDEO_NUM; i++)
		{
			m_MixSchemes[15].rect[i].Width = 1.0/4.0;
			m_MixSchemes[15].rect[i].Height = 1.0/4.0;

			m_MixSchemes[15].rect[i].X = (i%4) * (1.0/4.0);
			m_MixSchemes[15].rect[i].Y = (i/4) * (1.0/4.0);
		}
	}
}

// 将指定用户的视频按指定的方案合成
void CAnyChatVideoMixerDlg::MixUserVideoByScheme(LPUSER_ITEM lpUserItem, DWORD dwSchemeIndex, DWORD dwSiteIndex)
{
	DWORD dwMixWidth = g_localSettings.dwWidth;
	DWORD dwMixHeight = g_localSettings.dwHeight;
	DWORD dwXPos = (DWORD)(m_MixSchemes[dwSchemeIndex].rect[dwSiteIndex].X * dwMixWidth);
	DWORD dwYPos = (DWORD)(m_MixSchemes[dwSchemeIndex].rect[dwSiteIndex].Y * dwMixHeight);
	DWORD dwDesWidth = (DWORD)(m_MixSchemes[dwSchemeIndex].rect[dwSiteIndex].Width * dwMixWidth);
	DWORD dwDesHeight = (DWORD)(m_MixSchemes[dwSchemeIndex].rect[dwSiteIndex].Height * dwMixHeight);

	if(g_lpImageOverlayFunc)
	{
		g_lpImageOverlayFunc(dwMixWidth, dwMixHeight, AC_PIX_FMT_YUV420P, (LPBYTE)m_lpMixVideoBuf, 
			lpUserItem->dwWidth, lpUserItem->dwHeight, AC_PIX_FMT_YUV420P, (LPBYTE)lpUserItem->lpImageBuf, dwXPos, dwYPos, dwDesWidth, dwDesHeight, RGB(128,128,128), 0);
	}
}

/**
 *	显示日志信息
 */
void CAnyChatVideoMixerDlg::AppendLogString(CString logstr)
{
	m_strLogInfo += (logstr + "\r\n");
	m_ctrlEditLog.SetWindowText(m_strLogInfo);
	m_ctrlEditLog.LineScroll(m_ctrlEditLog.GetLineCount());
}

void CAnyChatVideoMixerDlg::OnButtonStart() 
{
	BRAC_Connect(g_localSettings.szServer, g_localSettings.dwPort);
	BRAC_Login(g_localSettings.szUserName, g_localSettings.szPassWord, 0);
	BRAC_EnterRoom(g_localSettings.dwRoomId, "", 0);

	if(!m_hThread)
	{
		unsigned tid;
		m_hThread = (HANDLE)_beginthreadex( NULL, 0, VideoAndAudioMixThread, this, 0, &tid );
	}
}

void CAnyChatVideoMixerDlg::OnButtonConfig() 
{
	CConfigDlg dlg;
	if(dlg.DoModal() == IDOK)
	{
		::EnterCriticalSection(&m_hMapSection);
		if(m_lpMixVideoBuf)
		{
			free(m_lpMixVideoBuf);
			m_lpMixVideoBuf = NULL;
		}
		m_dwMixImageSize = g_localSettings.dwWidth * g_localSettings.dwHeight * 3 / 2;
		m_lpMixVideoBuf = (CHAR*)malloc(m_dwMixImageSize);
		::LeaveCriticalSection(&m_hMapSection);

		SetLocalVideoParamters();
		// 重新设置输入格式
		BRAC_SetInputVideoFormat(BRAC_PIX_FMT_YUV420P, g_localSettings.dwWidth, g_localSettings.dwHeight, g_localSettings.dwFrameRate, 0);
	
		m_dwAudioStartTime = 0;
		m_dwAlreadInputAudioSamples = 0;
	}
}

// 设置本地视频参数
void CAnyChatVideoMixerDlg::SetLocalVideoParamters(void)
{
	DWORD dwValue = 0;
	// 设置本地视频编码的码率
	dwValue = g_localSettings.dwBitrate;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_BITRATECTRL,(const char*)&dwValue,sizeof(DWORD));
	// 设置本地视频编码的质量因子
	dwValue = 3;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_QUALITYCTRL,(const char*)&dwValue,sizeof(DWORD));
	// 设置本地视频编码的关键帧间隔
	dwValue = g_localSettings.dwFrameRate*3;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_GOPCTRL,(const char*)&dwValue,sizeof(DWORD));
	// 设置本地视频编码的帧率
	dwValue = g_localSettings.dwFrameRate;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_FPSCTRL,(const char*)&dwValue,sizeof(DWORD));
	// 设置本地视频编码的预设参数
	dwValue = 3;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_PRESETCTRL,(const char*)&dwValue,sizeof(DWORD));
	// 设置本地视频采集的宽度
	dwValue = g_localSettings.dwWidth;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_WIDTHCTRL,(const char*)&dwValue,sizeof(DWORD));
	// 设置本地视频采集的高度
	dwValue = g_localSettings.dwHeight;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_HEIGHTCTRL,(const char*)&dwValue,sizeof(DWORD));

	// 使参数设置生效
	BOOL bUseAppParam = TRUE;
	BRAC_SetSDKOption(BRAC_SO_LOCALVIDEO_APPLYPARAM,(const char*)&bUseAppParam,sizeof(DWORD));
}


/**
 *	收到消息：客户端连接服务器
 *	@param wParam （BOOL）表示是否连接成功
 */
LRESULT CAnyChatVideoMixerDlg::OnGVClientConnect(WPARAM wParam, LPARAM lParam)
{
	CString str;
	if(lParam == 0)
		str = "Connect anychat server successed...";
	else
		str.Format("Connect anychat server failed(errorcode:%d)...", lParam);
	AppendLogString(str);
	return 0;
}
/**
 *	收到消息：客户端登录系统
 *	@param wParam （INT）表示自己的用户ID号
 *	@param lParam （INT）表示登录结果：0 成功，否则为出错代码，参考出错代码定义
 */
LRESULT CAnyChatVideoMixerDlg::OnGVClientLogin(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	DWORD dwUserID = wParam;
	if(lParam == 0)
	{
		// 获取画面叠加函数句柄
		if(!g_lpImageOverlayFunc)
		{
			DWORD dwMediaUtilLib = 0;
			if(BRAC_GetSDKOption(BRAC_SO_CORESDK_MEDIAUTILLIB, (CHAR*)&dwMediaUtilLib, sizeof(DWORD)) == 0)
				g_lpImageOverlayFunc = (ImageOverlayFunc)::GetProcAddress((HMODULE)dwMediaUtilLib, "BRMU_ImageOverlay");
		}

		CHAR username[30]={0};
		BRAC_GetUserName(dwUserID,username,sizeof(username));
		logstr.Format("Login system successed(userid:%d, username:%s)",wParam,username);
	}
	else
		logstr.Format("Login system failed!(errorcode:%d)",lParam);

	AppendLogString(logstr);
	return 0;
}
/**
 *	收到消息：客户端进入房间
 *	@param wParam （INT）表示所进入房间的ID号
 *	@param lParam （INT）表示是否进入房间：0成功进入，否则为出错代码
 */
LRESULT CAnyChatVideoMixerDlg::OnGVClientEnterRoom(WPARAM wParam, LPARAM lParam)
{
	CString logstr;
	INT roomid = (INT)wParam;
	if(lParam == 0)
	{
		logstr.Format("Enter room(id:%d) successed!", roomid);
		
		m_dwAudioStartTime = 0;
		m_dwAlreadInputAudioSamples = 0;
		m_dwLastVideoInputTime = 0;
		m_bInRoom = TRUE;

		SetLocalVideoParamters();
		// 设置输入视频格式
		BRAC_SetInputVideoFormat(BRAC_PIX_FMT_YUV420P, g_localSettings.dwWidth, g_localSettings.dwHeight, g_localSettings.dwFrameRate, 0);
		// 设置输入音频格式
		BRAC_SetInputAudioFormat(MIX_SUPPORT_CHANNELS, MIX_SUPPORT_SAMPLESPERSEC, MIX_SUPPORT_BITSPERSAMPLE, 0);
	}
	else
	{
		
		logstr.Format("Enter room(%d) failed!(errorcode:%d)",roomid, lParam);
	}
	AppendLogString(logstr);
	return 0;
}

/**
 *	收到当前房间的在线用户信息
 *	进入房间后触发一次
 *	@param wParam （INT）表示在线用户数（不包含自己）
 *	@param lParam （INT）表示房间ID
 */
LRESULT CAnyChatVideoMixerDlg::OnGVClientOnlineUser(WPARAM wParam, LPARAM lParam)
{
	DWORD dwUserNum = 0;
	BRAC_GetOnlineUser(NULL,dwUserNum);		///< 首先获取房间内在线人数
	if(!dwUserNum)
		return 0;
	
	LPDWORD lpdwUserList = (LPDWORD)malloc(sizeof(DWORD)*dwUserNum);
	BRAC_GetOnlineUser(lpdwUserList,dwUserNum);	///< 真正获取在线用户列表
	
	for(INT i=0; i< (INT)dwUserNum; i++)
	{
		DWORD userid = lpdwUserList[i];
		BRAC_UserCameraControl(userid,TRUE);
		BRAC_UserSpeakControl(userid,TRUE);

		CreateNewUserItem(userid);
	}
	free(lpdwUserList);

	return 0;
}
/**
 *	收到消息：用户进入（离开）房间
 *	@param wParam （INT）表示用户ID号
 *	@param lParam （BOOL）表示该用户是进入（TRUE）或离开（FALSE）房间
 */
LRESULT CAnyChatVideoMixerDlg::OnGVClientUserAtRoom(WPARAM wParam, LPARAM lParam)
{
	DWORD dwUserId = wParam;
	BOOL bEnterRoom = lParam;
	if(bEnterRoom)
	{
		BRAC_UserCameraControl(dwUserId, TRUE);
		BRAC_UserSpeakControl(dwUserId, TRUE);

		CreateNewUserItem(dwUserId);
	}
	else
	{
		::EnterCriticalSection(&m_hMapSection);
		std::map<DWORD, LPUSER_ITEM>::iterator it = m_UserItemMap.find(dwUserId);
		if(it != m_UserItemMap.end())
		{
			ReleaseUserItem(it->second);
			free(it->second);
			m_UserItemMap.erase(it);
		}
		::LeaveCriticalSection(&m_hMapSection);
	}
	return 0;
}

/**
 *	收到消息：网络连接已关闭
 *	该消息只有在客户端连接服务器成功之后，网络异常中断之时触发
 */
LRESULT CAnyChatVideoMixerDlg::OnGVClientLinkClose(WPARAM wParam, LPARAM lParam)
{
	ClearAllUserItem();

	m_bInRoom = FALSE;
	g_lpImageOverlayFunc = NULL;

	CString str;
	str.Format("Network link closed!(errorcode:%d)", lParam);
	AppendLogString(str);
	return 0;
}

// 释放用户单元资源
void CAnyChatVideoMixerDlg::ReleaseUserItem(LPUSER_ITEM lpUserItem)
{
	if(!lpUserItem)
		return;
	if(lpUserItem->lpImageBuf)
	{
		free(lpUserItem->lpImageBuf);
		lpUserItem->lpImageBuf = NULL;
		lpUserItem->dwImageSize = 0;
	}
	if(lpUserItem->lpAudioBuf)
	{
		free(lpUserItem->lpAudioBuf);
		lpUserItem->lpAudioBuf = NULL;
		lpUserItem->dwAudioBufSize = 0;
	}
}

// 创建一个新的用户单元
void CAnyChatVideoMixerDlg::CreateNewUserItem(DWORD dwUserId)
{
	::EnterCriticalSection(&m_hMapSection);
	std::map<DWORD, LPUSER_ITEM>::iterator it = m_UserItemMap.find(dwUserId);
	if(it == m_UserItemMap.end())
	{
		LPUSER_ITEM lpUserItem = (LPUSER_ITEM)malloc(sizeof(USER_ITEM));
		if(lpUserItem)
		{
			memset(lpUserItem, 0, sizeof(USER_ITEM));
			lpUserItem->dwUserId = dwUserId;
			m_UserItemMap.insert(std::make_pair(dwUserId, lpUserItem));
		}
	}
	::LeaveCriticalSection(&m_hMapSection);
}

// 音频数据混音
void CAnyChatVideoMixerDlg::AudioBufferMixUpdate(LONG* lpMixBuffer, DWORD dwFrameNum, SHORT* lpDesBuffer)
{
#define PCM_S16_MIN		((long)-32768)
#define PCM_S16_MAX		((long)32767)
#define FACTOR_COUNT	15

	static float AttenuationFactor[]={0.0625,0.125,0.1875,0.25,0.3125,0.375,0.4375,0.5,0.5625,0.625,0.6875,0.75,0.8125,0.875,0.9375,1};
	static int FactorIdx = FACTOR_COUNT;

	long mixValue,mixValue2;

	for(int i=0;i<(int)dwFrameNum;i++)
	{
		mixValue=(long)(lpMixBuffer[i]*AttenuationFactor[FactorIdx]);
		if(mixValue>PCM_S16_MAX || mixValue<PCM_S16_MIN)
		{
			FactorIdx = FACTOR_COUNT;
			do
			{
				FactorIdx--;
				mixValue2=(long)(mixValue*AttenuationFactor[FactorIdx]);
				if(FactorIdx == 0)
					break;
			}while(mixValue2>PCM_S16_MAX || mixValue2<PCM_S16_MIN);

			lpDesBuffer[i]=(SHORT)((lpMixBuffer[i]>0) ? PCM_S16_MAX : PCM_S16_MIN);
		}
		else
		{
			lpDesBuffer[i]=(SHORT)mixValue;
			if(FactorIdx < FACTOR_COUNT)
				FactorIdx++;
		}
	}
}

