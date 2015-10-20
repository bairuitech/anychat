#if !defined(AFX_SLIDEBAR_H__01C8C75B_34B2_4313_87E2_B1A92C4484CE__INCLUDED_)
#define AFX_SLIDEBAR_H__01C8C75B_34B2_4313_87E2_B1A92C4484CE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SlideBar.h : header file
//


/////////////////////////////////////////////////////////////////////////////
// CSlideBar window

class CSlideBar : public CStatic
{
// Construction
public:
	CSlideBar();

	DWORD	m_dwNotifyMsg;

// Attributes
public:
	// 设置通知消息
	void SetNotifyMsg(DWORD dwMsg)	{	m_dwNotifyMsg = dwMsg;	}

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSlideBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetLineColor(COLORREF cr);
	void SetBgColor(COLORREF cr);
	int GetPos();
	void SetPos(int iPos);
	BOOL Create(RECT &rc,CWnd* hParent,UINT uID);
	virtual ~CSlideBar();

	// Generated message map functions
protected:
	void MakeBmp(HDC hdc);
	//{{AFX_MSG(CSlideBar)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	int m_iID;
	HBITMAP m_hbmpFace2;
	int m_iPos;
	HBITMAP m_hbmpFace1;
	COLORREF m_crLine;	//画线的颜色
	COLORREF m_crBg;	//背景颜色
private:
	void FillSolidRectX( HDC hDC, const RECT& rect, COLORREF cr );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SLIDEBAR_H__01C8C75B_34B2_4313_87E2_B1A92C4484CE__INCLUDED_)
