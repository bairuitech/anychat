// Hello AnyChat.h : main header file for the HELLO ANYCHAT application
//

#if !defined(AFX_HELLOANYCHAT_H__05B31768_AF41_494F_A2B4_83B493206AAB__INCLUDED_)
#define AFX_HELLOANYCHAT_H__05B31768_AF41_494F_A2B4_83B493206AAB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHelloAnyChatApp:
// See Hello AnyChat.cpp for the implementation of this class
//

class CHelloAnyChatApp : public CWinApp
{
public:
	CHelloAnyChatApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHelloAnyChatApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CHelloAnyChatApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HELLOANYCHAT_H__05B31768_AF41_494F_A2B4_83B493206AAB__INCLUDED_)
