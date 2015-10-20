// BRAnyChatMeeting.h : main header file for the BRANYCHATMEETING application
//

#if !defined(AFX_BRANYCHATMEETING_H__625597E4_2748_4ACB_8A22_81C93CBE4E29__INCLUDED_)
#define AFX_BRANYCHATMEETING_H__625597E4_2748_4ACB_8A22_81C93CBE4E29__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CBRAnyChatMeetingApp:
// See BRAnyChatMeeting.cpp for the implementation of this class
//

class CBRAnyChatMeetingApp : public CWinApp
{
public:
	CBRAnyChatMeetingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBRAnyChatMeetingApp)
	public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CBRAnyChatMeetingApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BRANYCHATMEETING_H__625597E4_2748_4ACB_8A22_81C93CBE4E29__INCLUDED_)
