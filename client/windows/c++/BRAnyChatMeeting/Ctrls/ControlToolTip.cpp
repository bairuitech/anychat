// ==========================================================================
// ControlToolTip.cpp
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 26/07/2000
// Last modification : 27/07/2000
// ==========================================================================

// ==========================================================================
// Les Includes
// ==========================================================================

#include "stdafx.h"
#include "ControlToolTip.h"
#include "Debug.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ==========================================================================
// Les defines
// ==========================================================================

#define CONTROLTOOLTIP_CLASSNAME  "ControlToolTip"

/////////////////////////////////////////////////////////////////////////////
// CControlToolTip

CControlToolTip::CControlToolTip()
 {
  m_pControl                  = NULL;
  m_iPosition                 = 0;
  m_clrText                   = ::GetSysColor(COLOR_INFOTEXT);
  m_clrBkgnd                  = ::GetSysColor(COLOR_INFOBK);
  m_bUseBgndColor             = FALSE;
  m_bShowOnlyOnMouseClickDown = TRUE;
  m_bUseLeftButton            = TRUE;

  RegisterWindowClass(); // Register window class if not already registered.
 }

// --------------------------------------------------------------------------

CControlToolTip::~CControlToolTip()
 {
  Detach();
 }

// --------------------------------------------------------------------------
// PROTECTED MEMBER FUNCTIONS
// --------------------------------------------------------------------------

CSize CControlToolTip::GetMultiLineTextExtent(CClientDC *pDC, LPCTSTR lpszText)
 {
  CSize cSize      = pDC->GetTextExtent(lpszText);
  int   iLineCount = GetNumberOfLines(lpszText);

  if (iLineCount == 1) return cSize;

  cSize.cx  = 0;
  cSize.cy *= iLineCount;

  char  sz[1024];
  CSize size;

  strcpy(sz, lpszText);

  char *psz = strtok(sz,"\n");

  while (psz != NULL)
   {
    size = pDC->GetTextExtent(psz);

    if (cSize.cx < size.cx) cSize.cx = size.cx;
    
    psz = strtok(NULL, "\n");
   }

  return cSize;
 }

// --------------------------------------------------------------------------

int CControlToolTip::GetNumberOfLines(LPCTSTR lpszText)
 {
  int     iLines = 1;
  CString str    = lpszText ? lpszText : m_strText;

  for (int I=0; I<str.GetLength(); I++)
   {
    if (str[I] == '\n') iLines++;
   }

  return iLines;
 }

// --------------------------------------------------------------------------

BOOL CControlToolTip::IsMouseInControl()
 {
  if (!m_pControl) return FALSE;

  CRect rect;

  m_pControl->GetWindowRect(&rect);

  POINT stPoint;
  
  GetCursorPos(&stPoint); // Get Mouse Position (in screen coordinates)

  if (rect.left <= stPoint.x && stPoint.x <= rect.right &&
      rect.top  <= stPoint.y && stPoint.y <= rect.bottom)
   {
    return TRUE;
   }

  return FALSE;
 }

// --------------------------------------------------------------------------

void CControlToolTip::Show()
 {
  if (m_strText.IsEmpty())
   {
    ShowWindow(SW_HIDE);
    return;
   }
  
  CRect rectControl;
  
  m_pControl->GetClientRect(&rectControl);

  CPoint pt(0,0);

  if (m_iPosition == 1) pt.y = rectControl.Height();

  if (m_iPosition == 2) pt.y = -m_rectText.Height();

  m_pControl->ClientToScreen(&pt);

  SetWindowPos(&wndTop,
               pt.x,
               pt.y,
               m_rectText.Width(),
               m_rectText.Height(),
               SWP_SHOWWINDOW | SWP_NOACTIVATE);

  RedrawWindow();
 }

// --------------------------------------------------------------------------
// STATIC PUBLIC MEMBER FUNCTIONS
// --------------------------------------------------------------------------

void CControlToolTip::RegisterWindowClass()
 {
  WNDCLASS  stWndClass;
  HINSTANCE hInst = AfxGetInstanceHandle();

  if ( !(::GetClassInfo(hInst,CONTROLTOOLTIP_CLASSNAME,&stWndClass)) )
   {
    stWndClass.style         = CS_SAVEBITS | CS_DBLCLKS;
    stWndClass.lpfnWndProc   = ::DefWindowProc;
    stWndClass.cbClsExtra    = 0;
    stWndClass.cbWndExtra    = 0;
    stWndClass.hInstance     = hInst;
    stWndClass.hIcon         = NULL;
    stWndClass.hCursor       = LoadCursor(hInst, IDC_ARROW);
    stWndClass.hbrBackground = (HBRUSH)(COLOR_INFOBK + 1);
    stWndClass.lpszMenuName  = NULL;
    stWndClass.lpszClassName = CONTROLTOOLTIP_CLASSNAME;

    if ( !AfxRegisterClass(&stWndClass) ) AfxThrowResourceException();
   }
 }

// --------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS
// --------------------------------------------------------------------------

BOOL CControlToolTip::Attach(CWnd *pControl)
 {
  if (m_hWnd)
   {
    if (Detach() == FALSE) return FALSE; // Failed to detach preview control
   }

  m_pControl = pControl;

  BOOL bRet = CreateEx(WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
                       CONTROLTOOLTIP_CLASSNAME,
                       NULL,
                       WS_BORDER | WS_POPUP,
                       0,
                       0,
                       0,
                       0,
                       NULL,
                       NULL,
                       NULL);

  if (!bRet) return FALSE;

  SetText(m_strText);

  SetTimer(1, 100, NULL);

  return TRUE;
 }

// --------------------------------------------------------------------------

BOOL CControlToolTip::Detach()
 {
  if (!m_hWnd) return TRUE;

  ShowWindow(SW_HIDE);

  KillTimer(1);

  m_pControl = NULL;

  return DestroyWindow();
 }

// --------------------------------------------------------------------------

void CControlToolTip::SetBkgndColor(BOOL bUse, COLORREF clr)
 {
  m_bUseBgndColor = bUse;

  if (bUse) m_clrBkgnd = clr;

  if ( !IsWindowVisible() ) return;

  RedrawWindow();
 }

// --------------------------------------------------------------------------

void CControlToolTip::SetPosition(int iPosition)
 {
  if (iPosition < 0 || iPosition > 2) return;

  m_iPosition = iPosition;

  if (!m_hWnd) return;

  if ( !IsWindowVisible() ) return;
  
  Show();
 }

// --------------------------------------------------------------------------

void CControlToolTip::SetText(LPCSTR lpszText)
 {
  m_strText = lpszText;

  if (!m_hWnd) return;
  
  CClientDC dc(this);
  int       iSaveDC = dc.SaveDC();

  dc.SelectObject( (HFONT)GetStockObject(DEFAULT_GUI_FONT) );

  CSize sizeText = GetMultiLineTextExtent(&dc, m_strText);

  dc.RestoreDC(iSaveDC);

  m_rectText.left   = 0;
  m_rectText.top    = 0;
  m_rectText.right  = m_rectText.left + sizeText.cx + 4;
  m_rectText.bottom = m_rectText.top  + sizeText.cy + 4;

  if ( !IsWindowVisible() ) return;
  
  Show();
 }

// --------------------------------------------------------------------------

void CControlToolTip::SetTextColor(COLORREF clr)
 {
  m_clrText = clr;

  if ( !m_bUseBgndColor || !IsWindowVisible() ) return;

  RedrawWindow();
 }

// --------------------------------------------------------------------------

void CControlToolTip::ShowOnlyOnMouseClickDown(BOOL bShow)
 {
  m_bShowOnlyOnMouseClickDown = bShow;
 }

// --------------------------------------------------------------------------

void CControlToolTip::UseLeftMouseButton(BOOL bUse)
 {
  m_bUseLeftButton = bUse;
 }

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CControlToolTip, CWnd)
	//{{AFX_MSG_MAP(CControlToolTip)
	ON_WM_TIMER()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CControlToolTip message handlers

void CControlToolTip::OnTimer(UINT nIDEvent) 
 {
  if (nIDEvent == 1 && m_pControl)
   {
    CWnd *pFocusWnd = GetFocus();

    if (pFocusWnd) pFocusWnd = pFocusWnd->GetParent();

    BOOL bClick = TRUE;

    if (m_bShowOnlyOnMouseClickDown)
     {
      SHORT nVal = GetKeyState(m_bUseLeftButton ? VK_LBUTTON : VK_RBUTTON);

      bClick = (nVal >> 1) != 0;
     }

    if ( IsMouseInControl() && bClick )
     {
      if ( !IsWindowVisible() && m_pControl->GetParent() == pFocusWnd ) Show();

      if ( IsWindowVisible() && m_pControl->GetParent() != pFocusWnd ) ShowWindow(SW_HIDE);
     }
    else {
          if ( IsWindowVisible() ) ShowWindow(SW_HIDE);
         }
   }
	
  CWnd::OnTimer(nIDEvent);
 }

// --------------------------------------------------------------------------

void CControlToolTip::OnPaint() 
 {
  CPaintDC dc(this); // device context for painting

  HFONT hOldFont = (HFONT)dc.SelectObject( (HFONT)GetStockObject(DEFAULT_GUI_FONT) );

  dc.SetBkMode(TRANSPARENT);

  if (m_bUseBgndColor)
   {
    dc.FillSolidRect(m_rectText, m_clrBkgnd);
    dc.SetTextColor(m_clrText);
   }

  dc.DrawText(m_strText, -1, m_rectText, DT_LEFT);

  dc.SelectObject(hOldFont);
 }

// --------------------------------------------------------------------------
