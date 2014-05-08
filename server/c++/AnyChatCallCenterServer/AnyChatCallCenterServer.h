// AnyChatCallCenterServer.h : main header file for the ANYCHATCALLCENTERSERVER application
//

#if !defined(AFX_ANYCHATCALLCENTERSERVER_H__147D5C91_F945_4EDD_84F8_386DB459A818__INCLUDED_)
#define AFX_ANYCHATCALLCENTERSERVER_H__147D5C91_F945_4EDD_84F8_386DB459A818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnyChatCallCenterServerApp:
// See AnyChatCallCenterServer.cpp for the implementation of this class
//

class CAnyChatCallCenterServerApp : public CWinApp
{
public:
	CAnyChatCallCenterServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnyChatCallCenterServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnyChatCallCenterServerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYCHATCALLCENTERSERVER_H__147D5C91_F945_4EDD_84F8_386DB459A818__INCLUDED_)
