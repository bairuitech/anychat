// ==========================================================================
// CNewLabel.cpp
//
// Author : Marquet Mike
//          mike.marquet@altavista.net
//
// Date of creation  : 20/07/2000
// Last modification : 07/08/2000
// ==========================================================================

// ==========================================================================
// Les Includes
// ==========================================================================

//#include "stdafx.h"
#include <afxwin.h>
#include <commctrl.h>
#include "NewLabel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ==========================================================================
// Les Defines
// ==========================================================================

#define BEVELLINE_SPACE   6

/////////////////////////////////////////////////////////////////////////////
// class CTextRotator

CTextRotator::CTextRotator(HDC hSourceDC, LPCTSTR lpszText, UINT uiHorzAlignment, UINT uiVertAlignment)
 {
  m_hSourceDC       = hSourceDC;
  m_hRotatedMemDC   = NULL;
  m_uiHorzAlignment = uiHorzAlignment;
  m_uiVertAlignment = uiVertAlignment;
  m_bDisabled       = FALSE;
  m_bDrawBevelLine  = FALSE;
  m_uiAngle         = 0;
  m_strText         = lpszText;
  m_clrBackground   = ::GetSysColor(COLOR_3DFACE);
  m_clrText         = ::GetSysColor(COLOR_WINDOWTEXT);
 }

// --------------------------------------------------------------------------

CTextRotator::~CTextRotator()
 {
  Clear();
 }

// --------------------------------------------------------------------------
// PROTECTED MEMBER FUNCTIONS
// --------------------------------------------------------------------------

void CTextRotator::AngleBlt(HDC hSourceDC, HDC hDestDC, RECT rectSource, UINT uiAngle)
 {
  int iSourceWidth  = rectSource.right - rectSource.left;
  int iSourceHeight = rectSource.bottom - rectSource.top;

  if (uiAngle == 0) // Don't need to rotate text
   {
    BitBlt(hDestDC,
           0,
           0,
           iSourceWidth,
           iSourceHeight,
           hSourceDC,
           0,
           0,
           SRCCOPY);

    return;
   }

  if ( CNewLabel::IsWindowsNT2000() ) // Windows NT/2000
   {
    POINT stPoints[3];

    switch(uiAngle)
     {
      case  90 :
                 stPoints[0].x = iSourceHeight;
                 stPoints[0].y = 0;
                 stPoints[1].x = iSourceHeight;
                 stPoints[1].y = iSourceWidth;
                 stPoints[2].x = 0;
                 stPoints[2].y = 0;
                 break;

      case 180 :
                 stPoints[0].x = iSourceWidth;
                 stPoints[0].y = iSourceHeight;
                 stPoints[1].x = 0;
                 stPoints[1].y = iSourceHeight;
                 stPoints[2].x = iSourceWidth;
                 stPoints[2].y = 0;
                 break;

      case 270 :
                 stPoints[0].x = 0;
                 stPoints[0].y = iSourceWidth;
                 stPoints[1].x = 0;
                 stPoints[1].y = 0;
                 stPoints[2].x = iSourceHeight;
                 stPoints[2].y = iSourceWidth;
                 break;

      default  :
                 stPoints[0].x = 0;
                 stPoints[0].y = 0;
                 stPoints[1].x = iSourceWidth;
                 stPoints[1].y = 0;
                 stPoints[2].x = 0;
                 stPoints[2].y = iSourceHeight;
                 break;
     } // switch(uiAngle)

    // Rotate the memory DC (Works only on Windows NT)
    PlgBlt(hDestDC,
           (const POINT *)&stPoints,
           hSourceDC,
           0,
           0,
           iSourceWidth,
           iSourceHeight,
           NULL,
           0,
           0);

    return;
   }

  // Windows 95/98
  int I, J;

  switch(uiAngle)
   {
    case  90 :
               for (I=0; I<iSourceWidth; I++)
                 for (J=0; J<iSourceHeight; J++)
                   {
                    SetPixel(hDestDC,
                             iSourceHeight - J - 1,
                             I,
                             GetPixel(hSourceDC,
                                      I,
                                      J));
                   }
               break;

    case 180 :
               for (I=0; I<iSourceWidth; I++)
                 for (J=0; J<iSourceHeight; J++)
                   {
                    SetPixel(hDestDC,
                             I,
                             J,
                             GetPixel(hSourceDC,
                                      iSourceWidth - I - 1,
                                      iSourceHeight - J - 1));
                   }
               break;

    case 270 :
               for (I=0; I<iSourceWidth; I++)
                 for (J=0; J<iSourceHeight; J++)
                   {
                    SetPixel(hDestDC,
                             J,
                             I,
                             GetPixel(hSourceDC,
                                      iSourceWidth - I - 1,
                                      J));
                   }
               break;

    default  :
               for (I=0; I<iSourceWidth; I++)
                 for (J=0; J<iSourceHeight; J++)
                   {
                    SetPixel(hDestDC,
                             I,
                             J,
                             GetPixel(hSourceDC,
                                      I,
                                      J));
                   }
               break;
   } // switch(uiAngle)
 }

// --------------------------------------------------------------------------

void CTextRotator::Clear()
 {
  DeleteDC(m_hRotatedMemDC);

  m_hRotatedMemDC = NULL;

  m_rectRotated.SetRectEmpty();

  m_uiAngle = 0;
 }

// --------------------------------------------------------------------------

CSize CTextRotator::GetLengthlyTextSize(HDC hDC, CStringArray *parrayText)
 {
  CSize cMaxSize(0,0);

  for (int I=0; I<parrayText->GetSize(); I++)
   {
    CString str = parrayText->GetAt(I);
    SIZE    stSize;

    if (!GetTextExtentPoint32(hDC, str, str.GetLength(), &stSize)) continue;

    if (cMaxSize.cx < stSize.cx) cMaxSize.cx = stSize.cx;
    if (cMaxSize.cy < stSize.cy) cMaxSize.cy = stSize.cy;
   }

  return cMaxSize;
 }

// --------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS
// --------------------------------------------------------------------------

BOOL CTextRotator::BitBltText(int X, int Y)
 {
  if (!m_hRotatedMemDC) return FALSE;

  return BitBlt(m_hSourceDC,
                X,
                Y,
                m_rectRotated.Width(),
                m_rectRotated.Height(),
                m_hRotatedMemDC,
                0,
                0,
                SRCCOPY);
 }

// --------------------------------------------------------------------------

BOOL CTextRotator::BitBltText(CRect rectSource)
 {
  if (!m_hRotatedMemDC) return FALSE;

  CRect rectRotatedSave = m_rectRotated;

  // Change rotated rectangle size to fit in source rectangle
  if (rectSource.Width() < m_rectRotated.Width()) m_rectRotated.right = rectSource.Width();

  if (rectSource.Height() < m_rectRotated.Height()) m_rectRotated.bottom = rectSource.Height();

  // Calculate left/top position to draw the text block
  int X = 0;
  int Y = 0;

  if (m_uiHorzAlignment == DT_CENTER)
   {
    X = (rectSource.Width() - m_rectRotated.Width()) / 2;
   }
  else if (m_uiHorzAlignment == DT_RIGHT)
        {
         X = rectSource.Width() - m_rectRotated.Width();
        }

  if (m_uiVertAlignment == 1) // CENTER
   {
    Y = (rectSource.Height() - m_rectRotated.Height()) / 2;
   }
  else if (m_uiVertAlignment == 2) // BOTTOM
        {
         Y = rectSource.Height() - m_rectRotated.Height();
        }

  BOOL bRet = BitBltText(X,Y); // Draw Text

  if (m_bDrawBevelLine) // DRAW BEVEL LINES (If Wanted)
   {
    RECT stRect;

    if (m_uiAngle == 0 || m_uiAngle == 180)
     {
      if (m_uiVertAlignment == 0) // TOP
       {
        stRect.top = stRect.bottom = m_rectRotated.Height() / 2;
       }
      else if (m_uiVertAlignment == 1) // CENTER
       {
        stRect.top = stRect.bottom = rectSource.Height() / 2;
       }
      else if (m_uiVertAlignment == 2) // BOTTOM
       {
        stRect.top = stRect.bottom = rectSource.Height() - m_rectRotated.Height() / 2;
       }

      if (m_uiHorzAlignment == DT_LEFT)
       {
        stRect.left  = m_rectRotated.Width() + BEVELLINE_SPACE;
        stRect.right = rectSource.Width() - BEVELLINE_SPACE;

        DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_TOP);
       }

      else if (m_uiHorzAlignment == DT_CENTER)
       {
        stRect.left  = BEVELLINE_SPACE;
        stRect.right = rectSource.Width() / 2 - m_rectRotated.Width() / 2 - BEVELLINE_SPACE;

        DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_TOP);

        stRect.left  = rectSource.Width() / 2 + m_rectRotated.Width() / 2 + BEVELLINE_SPACE;
        stRect.right = rectSource.Width() - BEVELLINE_SPACE;

        DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_TOP);
       }

      else if (m_uiHorzAlignment == DT_RIGHT)
       {
        stRect.left  = BEVELLINE_SPACE;
        stRect.right = rectSource.Width() - m_rectRotated.Width() - BEVELLINE_SPACE;

        DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_TOP);
       }
     }
    else {
          if (m_uiHorzAlignment == DT_LEFT)
           {
            stRect.left = stRect.right = m_rectRotated.Width() / 2;
           }
          else if (m_uiHorzAlignment == DT_CENTER)
           {
            stRect.left = stRect.right = rectSource.Width() / 2;
           }
          else if (m_uiHorzAlignment == DT_RIGHT)
           {
            stRect.left = stRect.right = rectSource.Width() - m_rectRotated.Width() / 2;
           }

          if (m_uiVertAlignment == 0) // TOP
           {
            stRect.top    = m_rectRotated.Height() + BEVELLINE_SPACE;
            stRect.bottom = rectSource.Height() - BEVELLINE_SPACE;

            DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_LEFT);
           }

          else if (m_uiVertAlignment == 1) // CENTER
           {
            stRect.top    = BEVELLINE_SPACE;
            stRect.bottom = rectSource.Height() / 2 - m_rectRotated.Height() / 2 - BEVELLINE_SPACE;
            
            DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_LEFT);

            stRect.top    = rectSource.Height() / 2 + m_rectRotated.Height() / 2 + BEVELLINE_SPACE;
            stRect.bottom = rectSource.Height() - BEVELLINE_SPACE;

            DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_LEFT);
           }

          else if (m_uiVertAlignment == 2) // BOTTOM
           {
            stRect.top    = BEVELLINE_SPACE;
            stRect.bottom = rectSource.Height() - m_rectRotated.Height() - BEVELLINE_SPACE;

            DrawEdge(m_hSourceDC, &stRect, EDGE_ETCHED, BF_LEFT);
           }
         }
   }

  m_rectRotated = rectRotatedSave;

  return bRet;
 }

// --------------------------------------------------------------------------

void CTextRotator::GetRotatedDC(CDC *pDC)
 {
  if (pDC) pDC->m_hDC = m_hRotatedMemDC;
 }

// --------------------------------------------------------------------------

void CTextRotator::GetRotatedRect(RECT *pstRect)
 {
  RECT rect = m_rectRotated;

  if (pstRect) memcpy(pstRect, &rect, sizeof(RECT));
 }

// --------------------------------------------------------------------------

BOOL CTextRotator::RotateText(UINT uiAngle)
 {
  Clear(); // Reset all preview memory DC

  m_uiAngle = uiAngle;

  // Split text into a list of text lines (for multiline support)
  int           iLineCounter = 0;
  char         *pszText      = new char[m_strText.GetLength() + 1];
  CStringArray  arrayText;

  if (!pszText) return FALSE;

  strcpy(pszText, m_strText);

  char *psz = strtok(pszText, "\n");

  while (psz)
   {
    arrayText.Add(psz);
    iLineCounter++;
    psz = strtok(NULL, "\n");
   }

  delete pszText;

  // Calculate the size of the lenghtly text of the text list
  CSize sizeText = GetLengthlyTextSize(m_hSourceDC, &arrayText);

  // Set Full rectangle size
  CRect rectFull;

  rectFull.left   = 0;
  rectFull.top    = 0;
  rectFull.right  = sizeText.cx;
  rectFull.bottom = sizeText.cy * iLineCounter;

  // Create an empty memory DC for rotation operation
  int iMax = rectFull.Width();

  if (iMax < rectFull.Height()) iMax = rectFull.Height();

  HBITMAP hEmptyBitmap1 = CreateCompatibleBitmap(m_hSourceDC, iMax, iMax);

  if (!hEmptyBitmap1) return FALSE;

  HBITMAP hEmptyBitmap2 = CreateCompatibleBitmap(m_hSourceDC, iMax, iMax);

  if (!hEmptyBitmap2)
   {
    DeleteObject(hEmptyBitmap1);
    return FALSE;
   }

  HDC hMemDC = CreateCompatibleDC(m_hSourceDC);

  if (!hMemDC)
   {
    DeleteObject(hEmptyBitmap2);
    DeleteObject(hEmptyBitmap1);
    return FALSE;
   }

  m_hRotatedMemDC = CreateCompatibleDC(m_hSourceDC);

  if (!m_hRotatedMemDC)
   {
    DeleteObject(m_hRotatedMemDC);
    DeleteDC(hMemDC);
    DeleteObject(hEmptyBitmap2);
    DeleteObject(hEmptyBitmap1);
    return FALSE;
   }

  ::SelectObject(hMemDC, hEmptyBitmap1); // Put the empty bitmap in memory DC

  ::SelectObject(m_hRotatedMemDC, hEmptyBitmap2); // Put the empty bitmap in rotated memory DC

  ::SelectObject(hMemDC, GetCurrentObject(m_hSourceDC,OBJ_FONT)); // Select same font as source DC 

  ::SetBkMode(hMemDC, TRANSPARENT);

  HBRUSH hBrush = CreateSolidBrush(m_clrBackground);

  ::SelectObject(hMemDC, hBrush);
  
  ::FillRect(hMemDC, rectFull, hBrush);

  ::FillRect(m_hRotatedMemDC, rectFull, hBrush);

  ::SetTextColor(hMemDC, m_clrText);

  // Draw the list of text into memory DC
  for (int I=0; I<arrayText.GetSize(); I++)
   {
    RECT stRect;

    stRect.left   = 0;
    stRect.top    = I * sizeText.cy;
    stRect.right  = stRect.left + sizeText.cx;
    stRect.bottom = stRect.top  + sizeText.cy;

    if (m_bDisabled)
     {
      ::SetTextColor(hMemDC, GetSysColor(COLOR_3DHIGHLIGHT));

      CRect rect = stRect;

      rect.left   += 1;
      rect.top    += 1;
      rect.right  += 1;
      rect.bottom += 1;

      ::DrawText(hMemDC, arrayText.GetAt(I), -1, &rect, DT_SINGLELINE | DT_VCENTER | m_uiHorzAlignment);

      ::SetTextColor(hMemDC, GetSysColor(COLOR_3DSHADOW));
     }

    ::DrawText(hMemDC, arrayText.GetAt(I), -1, &stRect, DT_SINGLELINE | DT_VCENTER | m_uiHorzAlignment);
   }

  AngleBlt(hMemDC, m_hRotatedMemDC, rectFull, uiAngle);

  DeleteObject(hEmptyBitmap2); // Delete temporary empty bitmap 2
  DeleteObject(hEmptyBitmap1); // Delete temporary empty bitmap 1

  DeleteObject(hBrush);

  DeleteDC(hMemDC);

  if (uiAngle == 90 || uiAngle == 270)
   {
    m_rectRotated.left   = 0;
    m_rectRotated.top    = 0;
    m_rectRotated.right  = rectFull.Height();
    m_rectRotated.bottom = rectFull.Width();
   }
  else {
        m_rectRotated.left   = 0;
        m_rectRotated.top    = 0;
        m_rectRotated.right  = rectFull.Width();
        m_rectRotated.bottom = rectFull.Height();
       }

  return TRUE;
 }

/////////////////////////////////////////////////////////////////////////////
// CNewLabel

CNewLabel::CNewLabel()
 {
  m_clrBackColor                    = ::GetSysColor(COLOR_3DFACE);
  m_clrTextBackColor                = ::GetSysColor(COLOR_3DFACE);
  m_clrTextColor                    = ::GetSysColor(COLOR_WINDOWTEXT);
  m_clrSaveTextColor                = m_clrTextColor;
  m_clrHightLight                   = ::GetSysColor(COLOR_HIGHLIGHT);
  m_hBackBrush                      = ::CreateSolidBrush(m_clrBackColor);
  m_bForceNoOwnerDraw               = FALSE;
  m_bUseDefaultBackColor            = TRUE;
  m_bUseDefaultTextBackColor        = TRUE;
  m_bUseDefaultTextColor            = TRUE;
  m_bLink                           = FALSE;
  m_bUseBevelLine                   = FALSE;
  m_bUseHighLighting                = FALSE;
  m_bVerticalText                   = FALSE;
  m_bInside                         = FALSE;
  m_bTextFlash                      = FALSE;
  m_bBackFlash                      = FALSE;
  m_bFlashTextState                 = FALSE;
  m_bFlashBackState                 = FALSE;
  m_bUseToolTip                     = FALSE;
  m_bUseHighLightingOnlyWithToolTip = FALSE;
  m_bBlockMessage                   = FALSE;
  m_bLowerCase                      = FALSE;
  m_bUpperCase                      = FALSE;
  m_bStretchBitmap                  = FALSE;
  m_hCursor                         = NULL;
  m_hBackImage                      = NULL;
  m_uiAlignment                     = HORZ_LEFT | VERT_TOP;
  m_uiAngle                         = 0; // 0°

  ::GetObject((HFONT)GetStockObject(DEFAULT_GUI_FONT), sizeof(m_stLF), &m_stLF);

  m_cFont.CreateFontIndirect(&m_stLF);
 }

// --------------------------------------------------------------------------

CNewLabel::~CNewLabel()
 {
  if (m_hBackImage) DeleteObject(m_hBackImage);

  m_cFont.DeleteObject();

  DeleteObject(m_hBackBrush);
 }

// --------------------------------------------------------------------------
// PROTECTED MEMBER FUNCTIONS
// --------------------------------------------------------------------------

void CNewLabel::DrawAlignedText(CDC *pDC, LPCSTR lpszText, RECT stRect, UINT uiAlignment)
 {
  UINT uiFormat = 0;

  if ((m_uiAlignment & HORZ_LEFT  ) == HORZ_LEFT  ) uiFormat |= DT_LEFT;
  if ((m_uiAlignment & HORZ_CENTER) == HORZ_CENTER) uiFormat |= DT_CENTER;
  if ((m_uiAlignment & HORZ_RIGHT ) == HORZ_RIGHT ) uiFormat |= DT_RIGHT;

  BOOL bSingleLine = !IsMultiLineString(lpszText);
  BOOL bIsVTop     = ((m_uiAlignment & VERT_TOP   ) == VERT_TOP   );
  BOOL bIsVCenter  = ((m_uiAlignment & VERT_CENTER) == VERT_CENTER);
  BOOL bIsVBottom  = ((m_uiAlignment & VERT_BOTTOM) == VERT_BOTTOM);

  if (bSingleLine || (!bSingleLine && bIsVTop))
   {
    CRect rect = stRect;

    if (bIsVCenter) uiFormat |= DT_VCENTER | DT_SINGLELINE;
    
    if (bIsVBottom)
     {
      CSize cSize = pDC->GetTextExtent(lpszText);

      rect.top += (stRect.bottom - stRect.top) - cSize.cy;
     }

    pDC->DrawText(lpszText, -1, &rect, uiFormat);

    return;
   }

  // MultiLine Drawing (TOP or BOTTOM)
  pDC->DrawText("**********", -1, &stRect, uiFormat);
 }

// --------------------------------------------------------------------------

int CNewLabel::GetWindowText(LPTSTR lpszStringBuf, int nMaxCount)
 {
  m_bBlockMessage = TRUE;

  int iRet = CStatic::GetWindowText(lpszStringBuf, nMaxCount);

  m_bBlockMessage = FALSE;

  return iRet;
 }

// --------------------------------------------------------------------------

void CNewLabel::GetWindowText(CString &rString)
 {
  m_bBlockMessage = TRUE;
  CStatic::GetWindowText(rString);
  m_bBlockMessage = FALSE;
 }

// --------------------------------------------------------------------------

BOOL CNewLabel::IsMultiLineString(LPCSTR lpszText)
 {
  for (unsigned int I=0; I<strlen(lpszText); I++)
   {
    if (lpszText[I] == '\n') return TRUE;
   }

  return FALSE;
 }

// --------------------------------------------------------------------------

CString CNewLabel::MakeVerticalText(LPCSTR lpszText)
 {
  CString strSource, strDest;

  strSource = (lpszText) ? lpszText : m_strText;

  for (int I=0; I<strSource.GetLength(); I++)
   {
    if (I > 0) strDest += '\n';
    
    strDest += strSource[I];
   }

  return strDest;
 }

// --------------------------------------------------------------------------

BOOL CNewLabel::ReconstructFont()
 {
  m_cFont.DeleteObject();

  BOOL bRet = m_cFont.CreateFontIndirect(&m_stLF);

  RedrawWindow();

  return bRet;
 }

// --------------------------------------------------------------------------

void CNewLabel::SetWindowText(LPCTSTR lpszString)
 {
  m_bBlockMessage = TRUE;
  CStatic::SetWindowText(lpszString);
  m_bBlockMessage = FALSE;
 }

// --------------------------------------------------------------------------

void CNewLabel::TrackMouse(BOOL bHover, BOOL bLeave)
 {
  TRACKMOUSEEVENT stTME;

  stTME.cbSize      = sizeof(stTME);
  stTME.dwFlags     = 0;
  stTME.hwndTrack   = GetSafeHwnd();
  stTME.dwHoverTime = 50;

  if (bHover) stTME.dwFlags |= TME_HOVER;

  //if (!bHover) stTME.dwFlags |= TME_HOVER | TME_CANCEL;

  if (bLeave) stTME.dwFlags |= TME_LEAVE;

  //if (!bLeave) stTME.dwFlags |= TME_LEAVE | TME_CANCEL;

  _TrackMouseEvent(&stTME);
 }

// --------------------------------------------------------------------------
// STATIC PUBLIC MEMBER FUNCTIONS
// --------------------------------------------------------------------------

BOOL CNewLabel::IsWindowsNT2000()
 {
  if ((HIWORD(GetVersion()) & 0x8000) == 0x8000) return FALSE; // Under Windows 95/98

  return TRUE; // Under Windows NT/2000
 }

// --------------------------------------------------------------------------
// PUBLIC MEMBER FUNCTIONS
// --------------------------------------------------------------------------

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// COLOR FUNCTIONS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CNewLabel &CNewLabel::SetBkColor(COLORREF clr)
 {
  m_bUseDefaultBackColor = FALSE;
  m_clrBackColor         = clr;

  DeleteObject(m_hBackBrush);

  m_hBackBrush = CreateSolidBrush(m_clrBackColor);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetDefaultBkColor()
 {
  m_bUseDefaultBackColor = TRUE;
  m_clrBackColor         = ::GetSysColor(COLOR_3DFACE);

  DeleteObject(m_hBackBrush);

  m_hBackBrush = CreateSolidBrush(m_clrBackColor);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetDefaultTextBackColor()
 {
  m_bUseDefaultTextBackColor = TRUE;
  m_clrTextBackColor         = ::GetSysColor(COLOR_3DFACE);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetDefaultTextColor()
 {
  m_bUseDefaultTextColor = TRUE;
  m_clrTextColor         = ::GetSysColor(COLOR_WINDOWTEXT);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetHighLightColor(COLORREF clr)
 {
  m_clrHightLight = clr;

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetTextBackColor(COLORREF clr)
 {
  m_bUseDefaultTextBackColor = FALSE;
  m_clrTextBackColor         = clr;

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetTextColor(COLORREF clr)
 {
  m_bUseDefaultTextColor = FALSE;
  m_clrTextColor         = clr;

  RedrawWindow();

  return *this;
 }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// FONT FUNCTIONS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CNewLabel &CNewLabel::SetFontBold(BOOL bBold)
 {
  m_stLF.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
  ReconstructFont();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetFontItalic(BOOL bItalic)
 {
  m_stLF.lfItalic = bItalic;
  ReconstructFont();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetFontName(LPCTSTR szFaceName)
 {
  strcpy(m_stLF.lfFaceName, szFaceName);
  ReconstructFont();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetFontSize(BOOL iSize)
 {
  m_stLF.lfHeight = iSize;
  ReconstructFont();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetFontUnderline(BOOL bUnderline)
 {
  m_stLF.lfUnderline = bUnderline;
  ReconstructFont();
  return *this;
 }


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// OTHER FUNCTIONS
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

CNewLabel &CNewLabel::FlashBackground(BOOL bActivate, UINT uiTime)
 {
  if (m_bBackFlash) KillTimer(2);
  
  if (bActivate) SetTimer(2, uiTime, NULL);
  else InvalidateRect(NULL, FALSE);

  m_bBackFlash = bActivate;

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::FlashText(BOOL bActivate, UINT uiTime)
 {
  if (m_bTextFlash)
   {
    SetWindowText(m_strText);
    KillTimer(1);
   }

  if (bActivate)
   {
    SetTimer(1, uiTime, NULL);
   }
  else InvalidateRect(NULL, FALSE);

  m_bTextFlash = bActivate;

  return *this;
 }

// --------------------------------------------------------------------------

void CNewLabel::ForceNoOwnerDraw(BOOL bForce)
 {
  m_bForceNoOwnerDraw = bForce;
  RedrawWindow();
 }

// --------------------------------------------------------------------------

BOOL CNewLabel::GetBorder()
 {
  return ((GetStyle() & WS_BORDER) == WS_BORDER) ? TRUE : FALSE;
 }

// --------------------------------------------------------------------------

UINT CNewLabel::GetHorzAlignment()
 {
  if ((m_uiAlignment & HORZ_LEFT) == HORZ_LEFT) return HORZ_LEFT;

  if ((m_uiAlignment & HORZ_CENTER) == HORZ_CENTER) return HORZ_CENTER;
 
  if ((m_uiAlignment & HORZ_RIGHT) == HORZ_RIGHT) return HORZ_RIGHT;

  return 0;
 }

// --------------------------------------------------------------------------

UINT CNewLabel::GetHorzAlignmentIndex()
 {
  if ((m_uiAlignment & HORZ_LEFT) == HORZ_LEFT) return 0;

  if ((m_uiAlignment & HORZ_CENTER) == HORZ_CENTER) return 1;
 
  if ((m_uiAlignment & HORZ_RIGHT) == HORZ_RIGHT) return 2;

  return 0;
 }

// --------------------------------------------------------------------------

BOOL CNewLabel::GetSunken()
 {
  return (GetExStyle() & WS_EX_STATICEDGE == WS_EX_STATICEDGE) ? TRUE : FALSE;
 }

// --------------------------------------------------------------------------

CString CNewLabel::GetText()
 {
  return m_strText;
 }

// --------------------------------------------------------------------------

UINT CNewLabel::GetVertAlignment()
 {
  if ((m_uiAlignment & VERT_TOP) == VERT_TOP) return VERT_TOP;

  if ((m_uiAlignment & VERT_CENTER) == VERT_CENTER) return VERT_CENTER;
 
  if ((m_uiAlignment & VERT_BOTTOM) == VERT_BOTTOM) return VERT_BOTTOM;

  return 0;
 }

// --------------------------------------------------------------------------

UINT CNewLabel::GetVertAlignmentIndex()
 {
  if ((m_uiAlignment & VERT_TOP) == VERT_TOP) return 0;

  if ((m_uiAlignment & VERT_CENTER) == VERT_CENTER) return 1;
 
  if ((m_uiAlignment & VERT_BOTTOM) == VERT_BOTTOM) return 2;

  return 0;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetAlignment(UINT uiAlign)
 {
  DWORD dwRemove = 0;
  DWORD dwHorz = 0;
  DWORD dwVert = 0;
  
  if ((uiAlign & HORZ_RIGHT) == HORZ_RIGHT)
   {
    dwHorz        = SS_RIGHT;
    dwRemove      = SS_LEFT | SS_CENTER;
    m_uiAlignment = HORZ_RIGHT;
   }
  
  if ((uiAlign & HORZ_CENTER) == HORZ_CENTER)
   {
    dwHorz        = SS_CENTER;
    dwRemove      = SS_LEFT | SS_RIGHT;
    m_uiAlignment = HORZ_CENTER;
   }

  if ((uiAlign & HORZ_LEFT) == HORZ_LEFT)
   {
    dwHorz        = SS_LEFT;
    dwRemove      = SS_RIGHT | SS_CENTER;
    m_uiAlignment = HORZ_LEFT;
   }

  ModifyStyle(dwRemove, dwHorz);

  if ((uiAlign & VERT_TOP   ) == VERT_TOP   ) dwVert = VERT_TOP;
  if ((uiAlign & VERT_CENTER) == VERT_CENTER) dwVert = VERT_CENTER;
  if ((uiAlign & VERT_BOTTOM) == VERT_BOTTOM) dwVert = VERT_BOTTOM;

  m_uiAlignment |= dwVert;

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetAngle(UINT uiAngle)
 {
  m_uiAngle = uiAngle;
  RedrawWindow();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetBackImage(UINT nID)
 {
  if (m_hBackImage) DeleteObject(m_hBackImage);

  m_hBackImage = NULL;

  if (nID != -1)
   {
    m_hBackImage = LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(nID));
   }

  InvalidateRect(NULL, TRUE);

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetBorder(BOOL bSet)
 {
  ModifyStyle(bSet ? 0 : WS_BORDER,
              bSet ? WS_BORDER : 0,
              SWP_DRAWFRAME);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetCursor(HCURSOR hCursor)
 {
  m_hCursor = hCursor;
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetCursor(UINT uiCursorID)
 {
  m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(uiCursorID));
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetDisabled(BOOL bSet)
 {
  ModifyStyle(bSet ? 0 : WS_DISABLED,
              bSet ? WS_DISABLED : 0,
              0);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetLink(BOOL bSet)
 {
  m_bLink = bSet;
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetLinkCursor(HCURSOR hCursor)
 {
  m_hCursor = hCursor;
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetLinkCursor(UINT uiCursorID)
 {
  m_hCursor = LoadCursor(AfxGetInstanceHandle(), MAKEINTRESOURCE(uiCursorID));
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetLowerCase(BOOL bSet)
 {
  m_bLowerCase = bSet;
  m_bUpperCase = FALSE;
  RedrawWindow();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetText(LPCTSTR szText)
 {
  m_strText = szText;

  if (m_bVerticalText)
   {
    SetWindowText( MakeVerticalText(szText) );
   }
  else SetWindowText(szText);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetSunken(BOOL bSet)
 {
  ModifyStyleEx(bSet ? 0 : WS_EX_STATICEDGE,
                bSet ? WS_EX_STATICEDGE : 0,
                SWP_DRAWFRAME);

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetToolTipPosition(int iPosition)
 {
  m_cControlToolTip.SetPosition(iPosition);
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetToolTipText(LPCTSTR lpszText)
 {
  m_cControlToolTip.SetText(lpszText);
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetUpperCase(BOOL bSet)
 {
  m_bLowerCase = FALSE;
  m_bUpperCase = bSet;
  RedrawWindow();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::SetVerticalText(BOOL bSet)
 {
  if (bSet && !m_bVerticalText)
   {
    SetWindowText( MakeVerticalText(m_strText) );
   }
  else if (m_bVerticalText) SetWindowText(m_strText);

  m_bVerticalText = bSet;

  RedrawWindow();

  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::ShowToolTipOnlyOnMouseClick(BOOL bUse)
 {
  m_cControlToolTip.ShowOnlyOnMouseClickDown(bUse);
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::StretchBitmap(BOOL bStretch)
 {
  m_bStretchBitmap = bStretch;
  if (m_hBackImage) RedrawWindow();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::UseBevelLine(BOOL bUse)
 {
  m_bUseBevelLine = bUse;
  RedrawWindow();
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::UseHighLighting(BOOL bUse)
 {
  m_bUseHighLighting = bUse;
  
  if (!bUse) SetTextColor(m_clrSaveTextColor);
  
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::UseHighLightingOnlyWithToolTip(BOOL bUse)
 {
  m_bUseHighLightingOnlyWithToolTip = bUse;
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::UseLeftMouseButtonForToolTip(BOOL bUse)
 {
  m_cControlToolTip.UseLeftMouseButton(bUse);
  return *this;
 }

// --------------------------------------------------------------------------

CNewLabel &CNewLabel::UseToolTip(BOOL bUse)
 {
  m_bUseToolTip = bUse;

  if (bUse)
   {
    m_cControlToolTip.Attach(this);
   }
  else {
        m_cControlToolTip.Detach();
       }

  return *this;
 }

// --------------------------------------------------------------------------
// --------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CNewLabel, CStatic)
	//{{AFX_MSG_MAP(CNewLabel)
	ON_WM_ENABLE()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_LBUTTONDOWN()
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNewLabel message handlers

BOOL CNewLabel::DestroyWindow() 
 {
  return CStatic::DestroyWindow();
 }

// --------------------------------------------------------------------------

HBRUSH CNewLabel::CtlColor(CDC *pDC, UINT nCtlColor)
 {
  if (!m_bForceNoOwnerDraw) return NULL;

  if (CTLCOLOR_STATIC == nCtlColor)
   {
    pDC->SelectObject(&m_cFont);
    pDC->SetTextColor(!m_bUseDefaultTextColor ? m_clrTextColor : ::GetSysColor(COLOR_WINDOWTEXT));
    pDC->SetBkMode(TRANSPARENT);
   }

  return m_hBackBrush;
 }

// --------------------------------------------------------------------------

void CNewLabel::PreSubclassWindow() 
 {
  CStatic::PreSubclassWindow();

  ModifyStyle(0, SS_NOTIFY);

  if ((GetStyle() & SS_CENTER) == SS_CENTER) m_uiAlignment = GetVertAlignment() | HORZ_CENTER;

  if ((GetStyle() & SS_RIGHT) == SS_RIGHT) m_uiAlignment = GetVertAlignment() | HORZ_RIGHT;

  if ((GetStyle() & SS_CENTERIMAGE) == SS_CENTERIMAGE) m_uiAlignment = GetHorzAlignment() | VERT_CENTER;

  GetWindowText(m_strText);
 }

// --------------------------------------------------------------------------

LRESULT CNewLabel::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
 {
  if (message == WM_MOUSEHOVER)
   {
    if (m_bUseHighLighting)
     {
      m_clrSaveTextColor = m_clrTextColor;

      CString str = m_cControlToolTip.GetText();

      if (!m_bUseHighLightingOnlyWithToolTip ||
          (m_bUseHighLightingOnlyWithToolTip && m_bUseToolTip && !str.IsEmpty()))
       {
        SetTextColor(m_clrHightLight);
       }
     }
   }
	
  else if (message == WM_MOUSELEAVE)
   {
    // Determine if mouse pointer is within control when tooltip is used
    // because when mouse go over tooltip, this message is sended.
    TrackMouse(TRUE, FALSE);

    m_bInside = FALSE;

    if (m_bUseHighLighting) SetTextColor(m_clrSaveTextColor);
   }

  else if (message == WM_SETTEXT)
   {
    if (!m_bBlockMessage)
     {
      m_strText = (LPCTSTR)lParam;
     }
   }

  else if (message == WM_GETTEXT)
   {
    if (!m_bBlockMessage)
     {
      int iCount = (int)wParam;

      memset((char *)lParam, 0, iCount + 1);
      memcpy((char *)lParam, m_strText, iCount);
      return TRUE;
     }
   }

  return CStatic::WindowProc(message, wParam, lParam);
 }

// --------------------------------------------------------------------------

void CNewLabel::OnEnable(BOOL bEnable) 
 {
  SetRedraw(FALSE);
  CStatic::OnEnable(bEnable);
  SetRedraw(TRUE);
  Invalidate();
 }

// --------------------------------------------------------------------------

BOOL CNewLabel::OnEraseBkgnd(CDC* pDC) 
 {
  return CStatic::OnEraseBkgnd(pDC);
 }

// --------------------------------------------------------------------------

void CNewLabel::OnLButtonDown(UINT nFlags, CPoint point) 
 {
  if (m_bLink)
   {
    ShellExecute(NULL, "open", m_strText, NULL, NULL, SW_SHOWNORMAL);
   }
	
  CStatic::OnLButtonDown(nFlags, point);
 }

// --------------------------------------------------------------------------

void CNewLabel::OnMouseMove(UINT nFlags, CPoint point) 
 {
  if (!m_bInside)
   {
    m_bInside = TRUE;
    TrackMouse(TRUE, TRUE);
   }

  CStatic::OnMouseMove(nFlags, point);
 }

// --------------------------------------------------------------------------

BOOL CNewLabel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
 {
  if (m_hCursor)
   {
    ::SetCursor(m_hCursor);
    return TRUE;
   }
	
  return CStatic::OnSetCursor(pWnd, nHitTest, message);
 }

// --------------------------------------------------------------------------

void CNewLabel::OnTimer(UINT nIDEvent) 
 {
  switch(nIDEvent)
   {
    case 1 : // TEXT FLASH
             if (!m_bTextFlash) break;

             m_bFlashTextState = !m_bFlashTextState;

             SetWindowText(m_bFlashTextState ? "" : m_strText);

             if (!m_bFlashTextState) InvalidateRect(NULL, FALSE);

             if (!m_bUseDefaultBackColor &&
                 m_clrBackColor != GetSysColor(COLOR_3DFACE))
              {
               InvalidateRect(NULL, FALSE);
              }
             break;

    case 2 : // BACK FLASH
             if (!m_bBackFlash) break;

             m_bFlashBackState = !m_bFlashBackState;

             InvalidateRect(NULL, TRUE);
             break;
   }

  CStatic::OnTimer(nIDEvent);
 }

// --------------------------------------------------------------------------

void CNewLabel::OnPaint() 
 {
  if (m_bForceNoOwnerDraw)
   {
    CStatic::OnPaint();
    return;
   }

  CPaintDC dc(this); // device context for painting
  CRect    rectClient;
  CString  strText = (!m_bVerticalText) ? m_strText : MakeVerticalText(m_strText);

  if (m_bLowerCase) strText.MakeLower();

  if (m_bUpperCase) strText.MakeUpper();

  GetClientRect(&rectClient);

  // Get Horz & Vert Alignment
  UINT uiHorzAlignment = DT_LEFT;
  UINT uiVertAlignment = 0;

  if ((m_uiAlignment & HORZ_CENTER) == HORZ_CENTER) uiHorzAlignment = DT_CENTER;

  if ((m_uiAlignment & HORZ_RIGHT) == HORZ_RIGHT) uiHorzAlignment = DT_RIGHT;

  if ((m_uiAlignment & VERT_CENTER) == VERT_CENTER) uiVertAlignment = 1;

  if ((m_uiAlignment & VERT_BOTTOM) == VERT_BOTTOM) uiVertAlignment = 2;

  // Set current font
  CFont *pOldFont = dc.SelectObject(&m_cFont);

  // Set Back Mode
  int iOldMode = dc.SetBkMode(TRANSPARENT);

  // Init Text rotation class
  CTextRotator cTextRotator(dc.GetSafeHdc(), strText, uiHorzAlignment, uiVertAlignment);

  cTextRotator.SetTextColor(m_clrTextColor);

  cTextRotator.SetDisabledText((GetStyle() & WS_DISABLED) == WS_DISABLED);

  cTextRotator.DrawBevelLine(m_bUseBevelLine);

  cTextRotator.SetBackgroundColor(!m_bUseDefaultTextBackColor ? m_clrTextBackColor : m_bUseDefaultBackColor ? ::GetSysColor(COLOR_3DFACE) : m_clrBackColor);

  // Erase background
  CBrush cBrush(::GetSysColor(COLOR_3DFACE));

  if (!m_bUseDefaultBackColor)
   {
    cBrush.DeleteObject();
    cBrush.CreateSolidBrush(m_clrBackColor);
   }

  if (m_bBackFlash && m_bFlashBackState)
   {
    COLORREF clr = m_bUseDefaultBackColor ? m_clrBackColor / 2 : ::GetSysColor(COLOR_3DFACE);

    cBrush.DeleteObject();
    cBrush.CreateSolidBrush(clr);

    cTextRotator.SetBackgroundColor(clr);
   }

  dc.FillRect(rectClient, &cBrush);

  cBrush.DeleteObject();

  if (m_hBackImage)
   {
    BITMAP stBitmap;

    GetObject(m_hBackImage, sizeof(stBitmap), &stBitmap);
    
    CDC memDC;

    memDC.CreateCompatibleDC(&dc);

    memDC.SelectObject(m_hBackImage);

    if (m_bStretchBitmap)
     {
      dc.StretchBlt(0,
                    0,
                    rectClient.Width(),
                    rectClient.Height(),
                    &memDC,
                    0,
                    0,
                    stBitmap.bmWidth,
                    stBitmap.bmHeight,
                    SRCCOPY);
     }
    else {
          int X = (rectClient.Width() - stBitmap.bmWidth) / 2;
          int Y = (rectClient.Height() - stBitmap.bmHeight) / 2;
          int W = rectClient.Width();
          int H = rectClient.Height();

          if (X < 0)
           {
            X = -X / 2;
            W = rectClient.Width() - X;
           }
          
          if (Y < 0)
           {
            Y = -Y / 2;
            H = rectClient.Height() - Y;
           }
          
          dc.BitBlt(X,
                    Y,
                    W,
                    H,
                    &memDC,
                    0,
                    0,
                    SRCCOPY);
         }

    memDC.DeleteDC();
   }

  // Rotate Text
  if (m_hBackImage &&
      m_uiAngle == 0 &&
      (!IsMultiLineString(strText) || (IsMultiLineString(strText) && GetVertAlignment() == VERT_TOP)))
   {
    dc.SetTextColor(!m_bUseDefaultTextColor ? m_clrTextColor : ::GetSysColor(COLOR_WINDOWTEXT));

    DrawAlignedText(&dc, strText, rectClient, m_uiAlignment);
   }
  else {
        BOOL bRet = cTextRotator.RotateText(m_uiAngle);

        if (bRet)
         {
          CRect rectRotated = cTextRotator.GetRotatedRect();

          // Draw Text
          cTextRotator.BitBltText(rectClient);
         }
       }

  // Restore
  dc.SelectObject(pOldFont);
  dc.SetBkMode(iOldMode);
 }

// --------------------------------------------------------------------------
