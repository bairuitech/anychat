// SlideBar.cpp : implementation file
//

#include <afxwin.h>
#include "SlideBar.h"
#include <Windowsx.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSlideBar

CSlideBar::CSlideBar()
{
	m_hbmpFace1=0;
	m_hbmpFace2=0;
	m_iPos=0;
	m_crBg=0x00a2a2a2;
	m_crLine=0x00ff8080;
}

CSlideBar::~CSlideBar()
{
	if(m_hbmpFace1)
		DeleteObject(m_hbmpFace1);
	if(m_hbmpFace2)
		DeleteObject(m_hbmpFace2);
	m_hbmpFace1=0;
	m_hbmpFace2=0;
}


BEGIN_MESSAGE_MAP(CSlideBar, CWnd)
	//{{AFX_MSG_MAP(CSlideBar)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSlideBar message handlers

BOOL CSlideBar::Create(RECT &rc, CWnd* hParent, UINT uID)
{
	return CWnd::Create(NULL,NULL,WS_CHILD|WS_VISIBLE,rc,hParent,uID,0);
}

void CSlideBar::SetPos(int iPos)
{
	m_iPos=iPos;
	InvalidateRect(0,FALSE);
}

int CSlideBar::GetPos()
{
	return m_iPos;
}

void CSlideBar::MakeBmp(HDC hdc)
{
	if(m_hbmpFace1)
		DeleteObject(m_hbmpFace1);
	if(m_hbmpFace2)
		DeleteObject(m_hbmpFace2);

	HDC hMemDC=CreateCompatibleDC(hdc);
	HPEN hp=CreatePen(PS_SOLID,1,m_crBg);
	HPEN hop=(HPEN)SelectObject(hMemDC,hp);
	CRect rc;
	::GetClientRect(m_hWnd,&rc);
	m_hbmpFace1=CreateCompatibleBitmap(hdc,rc.Width(),rc.Height());
	m_hbmpFace2=CreateCompatibleBitmap(hdc,rc.Width(),rc.Height());

	HBITMAP hob=(HBITMAP)SelectObject(hMemDC,m_hbmpFace1);
	FillSolidRectX(hMemDC,CRect(0,0,rc.Width(),rc.Height()),m_crLine);
	
	for(int i=0;i<rc.Width()/2;i++)
	{
		MoveToEx(hMemDC,i*2,0,0);
		LineTo(hMemDC,i*2,rc.Height());
	}	

	SelectObject(hMemDC,m_hbmpFace2);
	FillSolidRectX(hMemDC,CRect(0,0,rc.Width(),rc.Height()),m_crLine);

	SelectObject(hMemDC,hop);
	DeleteObject(hp);
	hp=CreatePen(PS_SOLID,1,0x00ffeeee);
	SelectObject(hMemDC,hp);

	for(i=0;i<rc.Width()/2;i++)
	{
		MoveToEx(hMemDC,i*2,0,0);
		LineTo(hMemDC,i*2,rc.Height());
	}

	SelectObject(hMemDC,hop);
	DeleteObject(hp);
	
	SelectObject(hMemDC,hob);
	DeleteDC(hMemDC);
}

void CSlideBar::FillSolidRectX(HDC hDC, const RECT &rect, COLORREF cr)
{
	HBRUSH hb;
	hb=CreateSolidBrush(cr);
	FillRect(hDC,&rect,hb);
	DeleteObject(hb);
}

void CSlideBar::OnPaint() 
{
//	CPaintDC dc(this); // device context for painting
	
	PAINTSTRUCT ps;
	BeginPaint(&ps);
	HDC hdc=ps.hdc;
//	if(!m_hbmpFace1)
//	{
		MakeBmp(hdc);
//	}
	CRect rc;
	GetClientRect(&rc);
	HDC hMemDC=CreateCompatibleDC(hdc);

    HBITMAP hob=(HBITMAP)SelectObject(hMemDC,m_hbmpFace2);
	int p=rc.Width()*m_iPos/100;
	BitBlt(hdc,rc.left,rc.top,p,rc.Height(),hMemDC,0,0,SRCCOPY);
	SelectObject(hMemDC,m_hbmpFace1);
	BitBlt(hdc,rc.left+p,rc.top,rc.Width()-p,rc.Height(),hMemDC,p,0,SRCCOPY);
	
	SelectObject(hMemDC,hob);

	DeleteDC(hMemDC);
	EndPaint(&ps);	
	// Do not call CWnd::OnPaint() for painting messages
}

void CSlideBar::OnLButtonDown(UINT nFlags, CPoint point) 
{
	::SetCapture(m_hWnd);
	CRect rc;
	GetClientRect(&rc);
	SetPos(point.x*100/rc.Width());
	::SendMessage(GetParent()->m_hWnd,m_dwNotifyMsg,m_iPos,(LPARAM)m_hWnd);
	MSG msg;
	while(GetMessage(&msg, NULL, 0, 0))
	{
		
		if (::GetCapture()!=m_hWnd)
		{
			DispatchMessage(&msg);
			break;
		}
		
		switch (msg.message)
		{
			
		case WM_MOUSEMOVE:
			SetPos(GET_X_LPARAM(msg.lParam)*100/rc.Width());
			::SendMessage(GetParent()->m_hWnd,m_dwNotifyMsg,m_iPos,(LPARAM)m_hWnd);
			break;
		case WM_LBUTTONUP:
			
			goto EXITLOOP;
				
		default:
			DispatchMessage(&msg);
			break;
		}
	}
	
EXITLOOP:
		
	ReleaseCapture();	
	CWnd::OnLButtonDown(nFlags, point);
}

void CSlideBar::SetBgColor(COLORREF cr)
{
	m_crBg = cr;
	InvalidateRect(0,FALSE);
	return;
}

void CSlideBar::SetLineColor(COLORREF cr)
{
	m_crLine = cr;
	InvalidateRect(0,FALSE);
	return;
}
