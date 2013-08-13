// AnyChatBusinessServer.h : main header file for the ANYCHATBUSINESSSERVER application
//

#if !defined(AFX_ANYCHATBUSINESSSERVER_H__147D5C91_F945_4EDD_84F8_386DB459A818__INCLUDED_)
#define AFX_ANYCHATBUSINESSSERVER_H__147D5C91_F945_4EDD_84F8_386DB459A818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CAnyChatBusinessServerApp:
// See AnyChatBusinessServer.cpp for the implementation of this class
//

class CAnyChatBusinessServerApp : public CWinApp
{
public:
	CAnyChatBusinessServerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAnyChatBusinessServerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CAnyChatBusinessServerApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ANYCHATBUSINESSSERVER_H__147D5C91_F945_4EDD_84F8_386DB459A818__INCLUDED_)
