// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__437D8C32_A189_455C_8628_D2609FFB4FF7__INCLUDED_)
#define AFX_STDAFX_H__437D8C32_A189_455C_8628_D2609FFB4FF7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT


/**
 *	本地配置参数
 */
struct LOCAL_SETTINGS
{
	CHAR	szServer[100];
	DWORD	dwPort;
	CHAR	szUserName[100];
	CHAR	szPassWord[100];
	DWORD	dwRoomId;

	DWORD	dwWidth;
	DWORD	dwHeight;
	DWORD	dwBitrate;
	DWORD	dwFrameRate;

	DWORD	dwAudioMix;
};


extern LOCAL_SETTINGS	g_localSettings;


// 刷新本地配置信息
void RefreshLocalSettings(void);
// 更新本地配置参数到配置文件中
void UpdateLocalSettings2IniFile(void);



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__437D8C32_A189_455C_8628_D2609FFB4FF7__INCLUDED_)
