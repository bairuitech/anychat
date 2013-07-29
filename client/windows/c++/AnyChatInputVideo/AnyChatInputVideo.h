// AnyChatInputVideo.h : main header file for the ANYCHATINPUTVIDEO application
//

#if !defined(AFX_ANYCHATINPUTVIDEO_H__1D2E8949_8456_4F49_9D6B_B94924D9DC74__INCLUDED_)
#define AFX_ANYCHATINPUTVIDEO_H__1D2E8949_8456_4F49_9D6B_B94924D9DC74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnyChatInputVideoApp:
// See AnyChatInputVideo.cpp for the implementation of this class
//

class CAnyChatInputVideoApp : public CWinApp
{
public:
	CAnyChatInputVideoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnyChatInputVideoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnyChatInputVideoApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYCHATINPUTVIDEO_H__1D2E8949_8456_4F49_9D6B_B94924D9DC74__INCLUDED_)
