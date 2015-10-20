// ==========================================================================
// ControlToolTip.h
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 26/07/2000
// Last modification : 27/07/2000
// ==========================================================================

#if !defined(AFX_CONTROLTOOLTIP_H__5939A9CF_62D5_11D4_BC44_0050BAA38233__INCLUDED_)
#define AFX_CONTROLTOOLTIP_H__5939A9CF_62D5_11D4_BC44_0050BAA38233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CControlToolTip window

class CControlToolTip : public CWnd
 {
  protected :
              CWnd     *m_pControl;
              CString   m_strText;
              CRect     m_rectText;
              int       m_iPosition; // 0 = OVER CONTROL
                                     // 1 = UNDER CONTROL
                                     // 2 = ABOVE CONTROL
              COLORREF  m_clrText;
              COLORREF  m_clrBkgnd;
              BOOL      m_bUseBgndColor;
              BOOL      m_bShowOnlyOnMouseClickDown;
              BOOL      m_bUseLeftButton;

              CSize GetMultiLineTextExtent(CClientDC *pDC, LPCTSTR lpszText);
              int   GetNumberOfLines(LPCTSTR lpszText = NULL);
              BOOL  IsMouseInControl();
              void  Show();

  public :
           CControlToolTip();
           virtual ~CControlToolTip();

           static void RegisterWindowClass();

           BOOL Attach(CWnd *pControl);
           BOOL Detach();

           void SetBkgndColor(BOOL bUse = FALSE, COLORREF clr = ::GetSysColor(COLOR_INFOBK));
           void SetPosition(int iPosition = 0);
           void SetText(LPCSTR lpszText = "");
           void SetTextColor(COLORREF clr = ::GetSysColor(COLOR_INFOTEXT));
           void ShowOnlyOnMouseClickDown(BOOL bShow);

           void UseLeftMouseButton(BOOL bUse);

           // INLINE
           int GetPosition() { return m_iPosition; }

           CString GetText() { return m_strText; }

           BOOL ShowOnlyOnMouseClickDown() { return m_bShowOnlyOnMouseClickDown; }

           BOOL IsAttached() { return (m_pControl != NULL); }

           BOOL IsLeftMouseButtonUsed() { return m_bUseLeftButton; }

  public :
	//{{AFX_VIRTUAL(CControlToolTip)
	//}}AFX_VIRTUAL

  protected :
	//{{AFX_MSG(CControlToolTip)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnPaint();
	//}}AFX_MSG
  
  DECLARE_MESSAGE_MAP()
 };

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLTOOLTIP_H__5939A9CF_62D5_11D4_BC44_0050BAA38233__INCLUDED_)
