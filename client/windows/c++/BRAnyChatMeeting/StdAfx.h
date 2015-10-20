// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A8A3ACB9_38E8_4C26_B5ED_DAB9B0822D10__INCLUDED_)
#define AFX_STDAFX_H__A8A3ACB9_38E8_4C26_B5ED_DAB9B0822D10__INCLUDED_

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

#include <afxsock.h>

#include "Ctrls/Picture.h"
#include "Ctrls/memdc.h"
#include "Ctrls/BtnST.h"
//#include "Ctrls/NewLabel.h"

#include <BRAnyChatCoreSDK.h>
#pragma comment(lib,"BRAnyChatCore.lib")

BOOL IsFileExist(LPCTSTR lpFilePath);

#define   _HRC_USE_SKIN_					///< 是否使用皮肤

//=======================
#ifdef _HRC_USE_SKIN_
#include "Ctrls\\SkinPPWTL.h"
#pragma comment(lib,"Ctrls\\SkinPPWTL.lib")
#endif
//========================

#define SUB_PATH_SKINFILE		_T("Skins")					///< 皮肤文件子目录
#define DEFAULT_SKIN_FILENAME	_T("AlphaOS.ssk")			///< 默认皮肤文件名

#define DEFAULT_CONFIG_FILENAME _T("AnyChatSDK.ini")		///< 默认本地配置文件名
#define DEFAULT_CONFIG_SECTION	_T("Custom Settings")		///< 自定义设置

#define DEFAULT_SERVER_IPADDR	_T("demo.anychat.cn")		///< 默认服务器IP地址
#define DEFAULT_SERVER_PORT		8906						///< 默认服务器端口号

#define MAX_DEMO_ROOM_NUM		4							///< 最大演示房间数
#define MAX_VIDEOPANEL_NUM		4							///< 最大视频面板数


//摄像头状态定义
#define GV_CAMERA_STATE_NULL	0				///< 没有摄像头
#define GV_CAMERA_STATE_NORMAL	1				///< 有摄像头但没有打开
#define GV_CAMERA_STATE_OPEN	2				///< 摄像头已打开



//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A8A3ACB9_38E8_4C26_B5ED_DAB9B0822D10__INCLUDED_)
