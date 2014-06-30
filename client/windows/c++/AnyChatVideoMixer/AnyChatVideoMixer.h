// AnyChatVideoMixer.h : main header file for the ANYCHATVIDEOMIXER application
//

#if !defined(AFX_ANYCHATVIDEOMIXER_H__E98A6781_2B40_4336_9CF2_F2CCA4FD6799__INCLUDED_)
#define AFX_ANYCHATVIDEOMIXER_H__E98A6781_2B40_4336_9CF2_F2CCA4FD6799__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnyChatVideoMixerApp:
// See AnyChatVideoMixer.cpp for the implementation of this class
//

class CAnyChatVideoMixerApp : public CWinApp
{
public:
	CAnyChatVideoMixerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnyChatVideoMixerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnyChatVideoMixerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYCHATVIDEOMIXER_H__E98A6781_2B40_4336_9CF2_F2CCA4FD6799__INCLUDED_)
