/************************************************************************ 
* 文件名：    SkinBtn.cpp 
* 文件描述：  图片按钮 
* 创建人：    黄锐坤(Nuk), 2006年08月22日
* 版本号：    1.0 
************************************************************************/ 
// SkinBtn.cpp : 实现文件
//
/************************************************************************ 
* 修改人：    张延锋(Nuk), 2007年10月20日
* 版本号：    2.0 
修改原因：VC6.0没CImage类，要从VC7.0移植到6.0
修改SetImage(CString strNormal, CString strHover, CString strDown, CString strDisable)及其它SetImage多态性相关FUN
修改DrawButton();
新增SetIcon(int iConIn,int iConOut)
************************************************************************/ 
#include "stdafx.h"
#include "SkinBtn.h"

#define   WM_BUTTON_FIRST_SELECT  (WM_USER + 103)
// CSkinBtn
#ifndef	BTNST_AUTO_GRAY
#define	BTNST_AUTO_GRAY					(HICON)(0xffffffff - 1L)
#endif
IMPLEMENT_DYNAMIC(CSkinBtn, CButton)

CSkinBtn::CSkinBtn()
{
	m_ShowState = 0;
	m_pFont = NULL;
	m_state = NORMAL;
	m_pFont=new CFont();
	m_pFont->CreatePointFont(90,_T("Arial"));
	m_fg = RGB(0, 0, 0);
	m_bg = RGB(255, 255, 255);
	m_bMouseOver = false;
	m_bEnabled = true;
	m_bDCStored = false;
	m_textPos = CPoint(21,0);
	m_iconRect = CRect(0,0,16,16);
	m_strTextOut = _T("");
	m_IconDraw = FALSE;
	m_IconIn = NULL;
	m_IconOut= NULL;
	m_SendTime = 0;
	m_bDrawRantage = FALSE;
    m_bDrawScroll = BUTTON_DEFAULT;
	m_bRePain = FALSE;
	m_BtnNum = -1;
//	m_ColorR = 0;
//	m_ColorG = 0;
//	m_ColorB = 0;
	
}

CSkinBtn::~CSkinBtn()
{
	if(m_pFont)
	  delete m_pFont;
	m_memDC.DeleteDC();
	m_imgNormal.DeleteObject();
	m_imgHover.DeleteObject();
	m_imgDown.DeleteObject();
	m_imgDisable.DeleteObject();
	m_imgScroll.DeleteObject();
}


BEGIN_MESSAGE_MAP(CSkinBtn, CButton)
	ON_WM_MOUSEMOVE()
	ON_WM_TIMER()
	ON_WM_ERASEBKGND()
	ON_WM_SETCURSOR()
	ON_WM_ENABLE()
END_MESSAGE_MAP()



void CSkinBtn::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{

	//// TODO:  添加您的代码以绘制指定项
	//CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	UINT state = lpDIS->itemState; 
	//CRect rect;
	//rect.CopyRect(&lpDIS->rcItem); 

	m_state = NORMAL;

	if (state & ODS_FOCUS)
	{
		if (state & ODS_SELECTED)
		{ 
			m_state = DOWN;
		}
		else
		{
			if(m_bMouseOver)
				m_state = HOVER;
		}
	}
	else
	{
		m_state = NORMAL;
	}
	if (state & ODS_DISABLED)
	{
		m_state = DISABLE;
		m_bEnabled = false;
	}
    switch(m_bDrawScroll)
	{
	case BUTTON_SCROLL:
		DrawButtonScroll();
		break;
	case BUTTON_TITLE:
		DrawButtonTitle();
		break;
	case BUTTON_NOPICTURE:
		DrawButtonNullPicture();
		break;
	default:
		DrawButton();
		break;
	}
   
	   
}


void CSkinBtn::DrawButtonTitle()
{
	if(m_bRePain == FALSE)
	{
		CClientDC  dc(this);

		CRect	rect;
		GetClientRect(&rect);

		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		CBitmap Screen;
		Screen.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&Screen);
		Screen.DeleteObject();


		//画背景 
		memDC.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);

	//	CString str(_T(""));
	//	GetWindowText(str);	

		memDC.SetBkMode(TRANSPARENT);
		memDC.SelectObject(m_pFont);

	//	CDC MemDC;
	//	MemDC.CreateCompatibleDC(&dc);

       
        CPen pen;
		
	//	CRgb textColor(255,255,255);
        
		switch(m_state)
		{
		case NORMAL:
			memDC.SetTextColor(RGB(97,113,197));
			pen.CreatePen(PS_SOLID , 1, RGB(255,0,0));
			break;
		case HOVER:
			memDC.SetTextColor(RGB(36,93,219));
			pen.CreatePen(PS_SOLID , 1, RGB(0,255,0));
			break;
		case DOWN:
			memDC.SetTextColor(GetBGColor());
			pen.CreatePen(PS_SOLID , 1, RGB(0,0,255));
			break;
		case DISABLE:
			memDC.SetTextColor(GetFGColor());
			pen.CreatePen(PS_SOLID , 1, RGB(225,225,225));
			break;
		default:
			break;
		}
        CPen* pOldPen = (CPen*)memDC.SelectObject(&pen);
		memDC.RoundRect(rect.left, rect.top, rect.Width(), rect.Height(),2,2);
		memDC.SelectObject(pOldPen);

		CPen pen0(PS_SOLID , 1, RGB(255, 255, 255));
		CPen* pOldPen0 = (CPen*)memDC.SelectObject(&pen);
		int nXpos = 0;
		int nYpos = 0;
		int n = 0;
		int m = 0;
		int nWidth = 0;
		int nHeight = 0;
		switch(m_BtnNum)
		{
			case 1://最小化
				
				nWidth = 13;
				nXpos = rect.left + 1;
		        nYpos = rect.top +  (nWidth/2 );
                for( n = nXpos + 3;n < nXpos + nWidth;n++)
				{
					//memDC.MoveTo(nXpos + nWidth/2 - 1,nYpos - 1);
					//memDC.LineTo(nXpos + nWidth/2+ 1 ,nYpos - 1);
					memDC.MoveTo(n,nXpos + 6);
		         	memDC.LineTo(n ,nXpos + 2 + 6);
					nYpos--;

				}
				break;
				
			case 2://还原
				nWidth = 7;
				nHeight = 7;
				nXpos = rect.left + 5;
		        nYpos = rect.top + 5;
				for(m = 0;m < 2;m++)
				{
					memDC.MoveTo(nXpos,nYpos);
					memDC.LineTo(nXpos + nWidth ,nYpos);

					memDC.MoveTo(nXpos,nYpos);
					memDC.LineTo(nXpos ,nYpos + nHeight);

					memDC.MoveTo(nXpos + nWidth,nYpos + nHeight);
					memDC.LineTo(nXpos ,nYpos + nHeight);

					memDC.MoveTo(nXpos + nWidth,nYpos + nHeight);
					memDC.LineTo(nXpos + nWidth ,nYpos);
					nXpos+=2;
					nYpos+=2;
				}
				break;
			case 3://关闭
				nWidth = 10;
				nXpos = rect.left + 4;
		        nYpos = rect.top + (nWidth - 1) + 4;
				for(n = nXpos;n < nXpos + 10;n++)
				{
					memDC.MoveTo(n,n);
					memDC.LineTo(n + 3,n);

					memDC.MoveTo(n,nYpos);
					memDC.LineTo(n + 3,nYpos);
					nYpos--;

				}
				break;
			case 4://下三角按妞
				nWidth = 9;
				nXpos = rect.left;
		        nYpos = rect.top ;
				for(m = 0;m < 5;m++)
				{
					memDC.MoveTo(nXpos + m + 3,nYpos + m + 3);
			        memDC.LineTo(nXpos + nWidth - m + 3  ,nYpos + m + 3);
				}
				break;
			case 5://加号按妞
		    	nWidth = 14;
				nXpos = rect.left + 1;
		        nYpos = rect.top +  (nWidth/2 );
                for( n = nXpos + 3;n < nXpos + nWidth;n++)
				{
					//memDC.MoveTo(nXpos + nWidth/2 - 1,nYpos - 1);
					//memDC.LineTo(nXpos + nWidth/2+ 1 ,nYpos - 1);
					memDC.MoveTo(n,nXpos + 6);
		         	memDC.LineTo(n ,nXpos + 2 + 6);

					memDC.MoveTo(nXpos + nWidth/2 - 1 + 1,nYpos - 1 + 7);
		            memDC.LineTo(nXpos + nWidth/2 + 1 + 1,nYpos - 1 + 7);
					nYpos--;

				}
				break;
			case 6://画下划线按妞
				memDC.SetBkColor(TRANSPARENT);
				nXpos = rect.left ;
		        nYpos = rect.top +5;
                memDC.TextOut(23,nYpos,m_strTextOut);
		        
				break;
			default:
				break;
		}
        memDC.SelectObject(pOldPen0);
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
		memDC.DeleteDC();
		//MemDC.DeleteDC();
	}
}
/*
void CSkinBtn::SetRGBColor(int R,int G,int B)//设置背景三个色调
{
//	m_ColorR = R;
//	m_ColorG = G;
//	m_ColorB = B;
}*/

void CSkinBtn::DrawButtonNullPicture()
{
	if(m_bRePain == FALSE)
	{
		CPoint posText(0,0);
		CClientDC  dc(this);

		CRect	rect;
		GetClientRect(&rect);

		

		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		CBitmap Screen;
		Screen.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&Screen);
		Screen.DeleteObject();

		//画背景 
		memDC.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);

		CString str(_T(""));
		GetWindowText(str);	

		int nLen = str.GetLength();
		if(nLen > 3)
		  posText.x = (rect.Width())/5;
		else
          posText.x = (rect.Width())/3;
		if(posText.x < 0)
           posText.x = 0;
		posText.y = (rect.Height() - 20)/2;
        if(posText.y < 0)
           posText.y = 0;

		memDC.SetBkMode(TRANSPARENT);
		memDC.SelectObject(m_pFont);
        
		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		switch(m_state)
			{
			case NORMAL:
				memDC.SetTextColor(GetBGColor());
				break;
			case HOVER:
				if(m_bDrawRantage)
				{
					memDC.SetTextColor(RGB(36,93,219));
					memDC.MoveTo(rect.left,rect.top);
					memDC.LineTo(rect.right,rect.top);
					memDC.MoveTo(rect.left,rect.top);
					memDC.LineTo(rect.left,rect.bottom);
					memDC.MoveTo(rect.left,rect.bottom - 1);
					memDC.LineTo(rect.right,rect.bottom - 1);
					memDC.MoveTo(rect.right - 1,rect.top);
					memDC.LineTo(rect.right - 1,rect.bottom);
				}
				break;
			case DOWN:				
				memDC.SetTextColor(GetBGColor());
				break;
			case DISABLE:
				 memDC.SetTextColor(GetFGColor());
	//			 memDC.TextOut(m_textPos.x,m_textPos.y,str);
				break;
			default:
				break;
			}

		    if(!str.IsEmpty())
			{
				memDC.TextOut(posText.x,posText.y,str);
			}
			dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

			memDC.DeleteDC();
			MemDC.DeleteDC();
		}
		
}

void CSkinBtn::DrawButtonScroll()
{
	if(m_bRePain == FALSE)
	{
		CClientDC  dc(this);

		CRect	rect;
		GetClientRect(&rect);

		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		CBitmap Screen;
		Screen.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&Screen);
		Screen.DeleteObject();

		//画背景 
		memDC.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);

		CString str(_T(""));
		GetWindowText(str);	

		memDC.SetBkMode(TRANSPARENT);
		memDC.SelectObject(m_pFont);

		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		int nX,nY,nW,nH;
        switch(m_BtnNum)
		{
			case 1://UP
				nX = 0;
				nY = 0;
				nW = 15;
				nH = 14;
				break;
			case 2:
				nX = 18;
				nY = 0;
				nW = 15;
				nH = 14;
				break;
			case 3:
				nX = 36;
				nY = 0;
				nW = 15;
				nH = 15;
				break;
			default:
				break;
		}

		switch(m_state)
		{
		case NORMAL:
			MemDC.SelectObject(&m_imgScroll);
		/*	if(m_BtnNum == 3)
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY,nW,
				nH,SRCCOPY);
			else*/
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY,nW,
				nH,SRCCOPY);
			break;
		case HOVER:
			MemDC.SelectObject(&m_imgScroll);
	/*		if(m_BtnNum == 3)
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY + 18,nW,
				nH,SRCCOPY);
			else*/
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY + 18,nW,
				nH,SRCCOPY);
			break;
		case DOWN:
			SetTimer(2,20,NULL);
			MemDC.SelectObject(&m_imgScroll);
	/*		if(m_BtnNum == 3)
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY + 36,nW,
				nH,SRCCOPY);
			else*/
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY + 36,nW,
				nH,SRCCOPY);
			break;
		case DISABLE:
			MemDC.SelectObject(&m_imgScroll);
	/*		if(m_BtnNum == 3)
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY,nW,
				nH,SRCCOPY);
			else*/
			    memDC.StretchBlt(0,0,nW,nH,&MemDC,nX,nY,nW,
				nH,SRCCOPY);
			break;
		default:
			break;
		}
   //     if(m_BtnNum == 3)
			    dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);
//		else
//		        dc.StretchBlt(rect.left, rect.top, nW, nH, &memDC, 0, 0,nW,nH, SRCCOPY);
		memDC.DeleteDC();
		MemDC.DeleteDC();
	}
}


void CSkinBtn::DrawButton()
{

	CPoint posText(0,0);
	if(m_bRePain == FALSE)
	{
		CClientDC  dc(this);

		CRect	rect;
		GetClientRect(&rect);

		CDC memDC;
		memDC.CreateCompatibleDC(&dc);

		CBitmap Screen;
		Screen.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());
		memDC.SelectObject(&Screen);
		Screen.DeleteObject();

		//画背景 
		memDC.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &m_memDC, 0, 0, SRCCOPY);

		CString str(_T(""));
		GetWindowText(str);	

		memDC.SetBkMode(TRANSPARENT);
		memDC.SelectObject(m_pFont);

		CDC MemDC;
		MemDC.CreateCompatibleDC(&dc);
		BITMAP bm;

		if(m_IconDraw)
		{
			CRect rImage;
			rImage.top = 0;
			rImage.left = 0;
			
			BOOL		bRetValue;
			ICONINFO	ii;
			::ZeroMemory(&ii, sizeof(ICONINFO));
			bRetValue = ::GetIconInfo(m_IconIn, &ii);
			if (bRetValue == FALSE)
			{
				if (m_IconIn)	::DestroyIcon(m_IconIn);
				rImage.bottom = 16;
	     		rImage.right = 16;
			} 
			else
			{
				rImage.right	= (DWORD)(ii.xHotspot * 2);
				rImage.bottom	= (DWORD)(ii.yHotspot * 2);
			}
			::DeleteObject(ii.hbmMask);
			::DeleteObject(ii.hbmColor);
			//int nXOffset = (rect.Width() - rImage.right)/2;
			int nYOffset = (rect.Height() - rImage.bottom)/2;//rect.Width(), rect.Height()
			if(nYOffset < 0)
				nYOffset = 0;
			rImage.top += nYOffset;
			posText.x = rImage.right + 2;
			posText.y = (rect.Height() - 20)/2;
            if(posText.y < 0)
               posText.y = 0;


			switch(m_state)
			{
			case NORMAL:
				// Ole'!
				memDC.DrawState(rImage.TopLeft(),
								rImage.Size(), 
								m_IconIn,
								DSS_NORMAL, 
								(CBrush*)NULL);
				memDC.SetTextColor(GetFGColor());
	//			memDC.TextOut(m_textPos.x,m_textPos.y,str);
				break;
			case HOVER:
				// Ole'!
				memDC.DrawState(rImage.TopLeft(),
								rImage.Size(), 
								m_IconOut,
								DSS_NORMAL, 
								(CBrush*)NULL);	
				memDC.SetTextColor(RGB(36,93,219));
	//			memDC.TextOut(m_textPos.x,m_textPos.y,str);
				if(m_bDrawRantage)
				{
					memDC.MoveTo(rect.left,rect.top);
					memDC.LineTo(rect.right,rect.top);
					memDC.MoveTo(rect.left,rect.top);
					memDC.LineTo(rect.left,rect.bottom);
					memDC.MoveTo(rect.left,rect.bottom - 1);
					memDC.LineTo(rect.right,rect.bottom - 1);
					memDC.MoveTo(rect.right - 1,rect.top);
					memDC.LineTo(rect.right - 1,rect.bottom);
				}
			//	memDC.SetBkColor(TRANSPARENT);
			//	memDC.Rectangle(rect);
				break;
			case DOWN:
				// Ole'!
//				SetTimer(2,20,NULL);
				memDC.DrawState(rImage.TopLeft(),
								rImage.Size(), 
								m_IconOut,
								DSS_NORMAL, 
								(CBrush*)NULL);	
				memDC.SetTextColor(GetBGColor());
	//			memDC.TextOut(m_textPos.x,m_textPos.y,str);
				break;
			case DISABLE:
				memDC.DrawState(rImage.TopLeft(),
								rImage.Size(), 
								m_IconIn,
								DSS_NORMAL, 
								(CBrush*)NULL);
				memDC.SetTextColor(GetFGColor());
	//			memDC.TextOut(m_textPos.x,m_textPos.y,str);
				break;
			default:
				break;
			}
		}
		else
		{
			CString ss;
			GetWindowText(ss);
			m_imgNormal.GetBitmap(&bm);
			int nYOffset = (rect.Height() - bm.bmHeight)/2;//rect.Width(), rect.Height()
			if(nYOffset < 0)
				nYOffset = 0;

			posText.x = rect.left + bm.bmWidth + 2;
			posText.y = (rect.Height() - 20)/2;
            if(posText.y < 0)
               posText.y = 0;

			posText = m_textPos;
			if(m_ShowState == 1)
			{//强制设成选取中状态
				m_imgDown.GetBitmap(&bm);
//				SetTimer(2,20,NULL);
				MemDC.SelectObject(&m_imgDown);
				if(bm.bmHeight>rect.bottom || bm.bmWidth>rect.right)
					memDC.StretchBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,bm.bmWidth,
					bm.bmHeight,SRCCOPY);
				else
					memDC.BitBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,SRCCOPY);
				memDC.SetTextColor(GetBGColor());

			}
			else
			{
				switch(m_state)
				{
				case NORMAL:
					m_imgNormal.GetBitmap(&bm);
					MemDC.SelectObject(&m_imgNormal);
					if(bm.bmHeight>rect.bottom || bm.bmWidth>rect.right)
						memDC.StretchBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,bm.bmWidth,
						bm.bmHeight,SRCCOPY);
					else
						memDC.BitBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,SRCCOPY);
					memDC.SetTextColor(GetFGColor());
		//			memDC.TextOut(m_textPos.x,m_textPos.y,str);
					break;
				case HOVER:
					m_imgHover.GetBitmap(&bm);
					MemDC.SelectObject(&m_imgHover);
					if(bm.bmHeight>rect.bottom || bm.bmWidth>rect.right)
						memDC.StretchBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,bm.bmWidth,
						bm.bmHeight,SRCCOPY);
					else
						memDC.BitBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,SRCCOPY);
					if(m_bDrawRantage)
					{
						memDC.SetTextColor(GetBGColor());
						memDC.TextOut(m_textPos.x,m_textPos.y,str);
						memDC.MoveTo(rect.left,rect.top);
						memDC.LineTo(rect.right,rect.top);
						memDC.MoveTo(rect.left,rect.top);
						memDC.LineTo(rect.left,rect.bottom);
						memDC.MoveTo(rect.left,rect.bottom - 1);
						memDC.LineTo(rect.right,rect.bottom - 1);
						memDC.MoveTo(rect.right - 1,rect.top);
						memDC.LineTo(rect.right - 1,rect.bottom);
					}
					break;
				case DOWN:
					m_imgDown.GetBitmap(&bm);
	//				SetTimer(2,20,NULL);
					MemDC.SelectObject(&m_imgDown);
					if(bm.bmHeight>rect.bottom || bm.bmWidth>rect.right)
						memDC.StretchBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,bm.bmWidth,
						bm.bmHeight,SRCCOPY);
					else
						memDC.BitBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,SRCCOPY);
					memDC.SetTextColor(GetBGColor());
		//			memDC.TextOut(m_textPos.x,m_textPos.y,str);
					break;
				case DISABLE:
					 m_imgDisable.GetBitmap(&bm);
	   				 MemDC.SelectObject(&m_imgDisable);
					 if(bm.bmHeight>rect.bottom || bm.bmWidth>rect.right)
		 				 memDC.StretchBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,bm.bmWidth,
						 bm.bmHeight,SRCCOPY);
					 else
						 memDC.BitBlt(0,0,rect.right,rect.bottom,&MemDC,0,0,SRCCOPY);
					 memDC.SetTextColor(GetFGColor());
		//			 memDC.TextOut(m_textPos.x,m_textPos.y,str);
					break;
				default:
					break;
				}
			}
		}
		if(!str.IsEmpty())
		{
			memDC.TextOut(posText.x,posText.y,str);
		}
		dc.BitBlt(rect.left, rect.top, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

		memDC.DeleteDC();
		MemDC.DeleteDC();
	}
}

void CSkinBtn::DrawFilledRect(CDC *DC, CRect R, COLORREF color)
{ 
	CBrush B;
	B.CreateSolidBrush(color);
	DC->FillRect(R, &B);
}

void CSkinBtn::DrawButtonText(CDC *DC, CRect R, CString str, COLORREF TextColor)
{
  /*  COLORREF prevColor = DC->SetTextColor(TextColor);
	DC->SetBkMode(TRANSPARENT);
	DC->SelectObject(m_pFont);
/*	if(m_hMouseOutIcon.IsNull()&&m_hMouseInIcon.IsNull())
	{
		//int iconwidth=::GetSystemMetrics(SM_CXICON);
		R.right=R.right-m_textPos.x;
		DC->DrawText( str, str.GetLength(), R, DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	else
	{
		DC->DrawText( str, str.GetLength(), R, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	}*/
//	str = _T("MyText");
/*	DC->DrawText( str, str.GetLength(), R, DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	DC->SetTextColor(prevColor);*/
}
void CSkinBtn::SetParentWnd(HWND hWnd)
{
	m_ParentWnd = hWnd;
	SetTimer(101,1000,NULL);
}
void CSkinBtn::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//if (nFlags & MK_LBUTTON && m_bMouseOver == FALSE) 
	//	return;
	if(!m_bMouseOver&&m_bEnabled)
	{
		m_bMouseOver=true;
		m_state = HOVER;

		CPoint	point;
		CRect	rect;
		GetWindowRect(&rect);	
		GetCursorPos(&point);
		if (!rect.PtInRect(point) && m_bMouseOver&&m_bEnabled)
		{
			SetTimer(1,10,NULL);
			return;
		}

		switch(m_bDrawScroll)
		{
		case BUTTON_SCROLL:
			DrawButtonScroll();
			break;
		case BUTTON_TITLE:
			DrawButtonTitle();
			break;
		case BUTTON_NOPICTURE:
			DrawButtonNullPicture();
			break;
		default:
			DrawButton();
			break;
		}
		
		SetTimer(1,10,NULL);
	}
	CButton::OnMouseMove(nFlags, point);
}

void CSkinBtn::SetRantageDraw(BOOL bDraw)
{
	m_bDrawRantage = bDraw;
}


void CSkinBtn::SetScrollDraw(int bDraw ,int nNum)
{
	HBITMAP szhBitmapNormal;
	szhBitmapNormal=HBITMAP(::LoadImage(AfxGetInstanceHandle(),_T("Image\\FolderScrollbar.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
	m_imgScroll.Attach(szhBitmapNormal);
	m_bDrawScroll = bDraw;
	m_BtnNum = nNum;
}

void CSkinBtn::SetMovePain(BOOL bDraw)
{
    m_bRePain = bDraw;
}

BOOL CSkinBtn::MoveWndBegin(fListMoveWnd lpfListMoveWnd,LPARAM lPARAM)
{
	if(m_state == DOWN)
	{
		CPoint	point;
		CRect	rect;
		GetWindowRect(&rect);	
		GetCursorPos(&point);
		m_SendTime++;
		lpfListMoveWnd(point,m_SendTime,lPARAM);
	}
	return TRUE;
}

void CSkinBtn::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CPoint	point;
	CRect	rect;
	GetWindowRect(&rect);	
	GetCursorPos(&point);
	switch(nIDEvent)
	{
	case(1):
		{
			if (!rect.PtInRect(point) && m_bMouseOver&&m_bEnabled)
			{
				KillTimer (1);
				m_bMouseOver=false;
				m_state = NORMAL;
				switch(m_bDrawScroll)
				{
				case BUTTON_SCROLL:
					DrawButtonScroll();
					break;
				case BUTTON_TITLE:
					DrawButtonTitle();
					break;
				case BUTTON_NOPICTURE:
					DrawButtonNullPicture();
					break;
				default:
					DrawButton();
					break;
				}
			}
		}
		break;
	case(2):
		{
			//发送消息给PARENT窗口
			m_SendTime++;
			if(m_SendTime == 1)
			{
               ::SendMessage(m_ParentWnd,WM_BUTTON_FIRST_SELECT,point.x,point.y);
//               ::SendMessage(m_ParentWnd,WM_BUTTON_SELECT,point.x,point.y);
			}
			
		}
		break;
	case(101):
		this->Invalidate(FALSE);
		break;
	default:
		break;
	}	
	if(m_state!=DOWN)
	{
		KillTimer (2);
		m_SendTime = 0;
//		::SendMessage(m_ParentWnd,WM_BUTTON_FIRST_SELECT,NULL,m_SendTime);
		
	}
	CButton::OnTimer(nIDEvent);
}

void CSkinBtn::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	SetOwnerDraw(true);

//	CButton::PreSubclassWindow();
}
void CSkinBtn::SetButtonText(CString str)
{
	m_strTextOut = str;
	SetWindowText(m_strTextOut);
}
void CSkinBtn::SetOwnerDraw(bool IsDraw)
{
	if(m_bRePain == FALSE)
	{
		if(IsDraw)
		{
			ModifyStyle(NULL, BS_OWNERDRAW); 
			Invalidate(FALSE);
		}
		else
		{
			ModifyStyle(BS_OWNERDRAW, NULL); 
			Invalidate(FALSE);
		}
	}
}
//IDB_BITMAP1,IDB_BITMAP2,IDB_BITMAP3,IDB_BITMAP1);//_
void CSkinBtn::SetImage(CString strNormal, CString strHover, CString strDown, CString strDisable)
{
	HBITMAP hBitmapNormal,hBitmapHover,hBitmapDown,hBitmapDisable;
	hBitmapNormal=HBITMAP(::LoadImage(AfxGetInstanceHandle(),strNormal,
		IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
	hBitmapHover=HBITMAP(::LoadImage(AfxGetInstanceHandle(),strHover,
		IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
	hBitmapDown=HBITMAP(::LoadImage(AfxGetInstanceHandle(),strDown,
		IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
	hBitmapDisable=HBITMAP(::LoadImage(AfxGetInstanceHandle(),strDisable,
		IMAGE_BITMAP,0,0,LR_LOADFROMFILE));
    this->SetImage(hBitmapNormal,hBitmapHover,hBitmapDown,hBitmapDisable);
}

void CSkinBtn::SetImage(HBITMAP nNormalID, HBITMAP nHoverID, HBITMAP nDownID, HBITMAP nDisableID)
{
	if(nNormalID==NULL)
		return;
	m_imgNormal.Attach(nNormalID);
	if(nHoverID==NULL)
		return;
	m_imgHover.Attach(nHoverID);
	if(nDownID==NULL)
		return;
	m_imgDown.Attach(nDownID);
	if(nDisableID==NULL)
		return;
	m_imgDisable.Attach(nDisableID);
}

void CSkinBtn::SetIcons(int nIconIn, int nIconOut,BOOL bDrawIcon)
{
	HICON		hIconIn			= NULL;
	HICON		hIconOut		= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(nIconIn), RT_GROUP_ICON);

	// Set icon when the mouse is IN the button
	hIconIn = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconIn), IMAGE_ICON, 0, 0, 0);
  	// Set icon when the mouse is OUT the button
	if (nIconOut)
	{
		if (nIconOut == (int)BTNST_AUTO_GRAY)
			hIconOut = BTNST_AUTO_GRAY;
		else
			hIconOut = (HICON)::LoadImage(hInstResource, MAKEINTRESOURCE(nIconOut), IMAGE_ICON, 0, 0, 0);
	} // if

	m_IconIn = hIconIn;
    m_IconOut = hIconOut;
	m_IconDraw = bDrawIcon;
}
void CSkinBtn::SetImage(UINT nNormalID, UINT nHoverID, UINT nDownID, UINT nDisableID)
{
	m_imgNormal.LoadBitmap(nNormalID);
	m_imgHover.LoadBitmap(nHoverID);
	m_imgDown.LoadBitmap(nDownID);
	m_imgDisable.LoadBitmap(nNormalID);

}

BOOL CSkinBtn::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(m_bRePain == FALSE)
	{
		if(!m_bDCStored)
		{
    		CRect  rect;
			GetClientRect(&rect);

			m_memDC.CreateCompatibleDC (pDC);
			CBitmap	btScreen;
			btScreen.CreateCompatibleBitmap (pDC,rect.Width(),rect.Height());
			m_memDC.SelectObject (&btScreen);

			m_memDC.BitBlt (0,0,rect.Width(),rect.Height(),pDC,0,0,SRCCOPY);

			m_bDCStored=true;

			CRgn rgn;
			rgn.CreateRectRgn (0, 0, rect.Width(), rect.Height());
			SetWindowRgn (rgn, TRUE);

			btScreen.DeleteObject();
		}
	}
	return TRUE;// CButton::OnEraseBkgnd(pDC);//
}

BOOL CSkinBtn::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
//	::SetCursor(AfxGetApp()->LoadCursor(IDC_CURSOR_HAND)); 
	return TRUE;
//	return CButton::OnSetCursor(pWnd, nHitTest, message);
}

void CSkinBtn::SetIcons(CString  strMouseOut,CString strMouseIn,BOOL bDrawIcon)
{
//	m_hMouseOutIcon.Load(strMouseOut);
//	m_hMouseInIcon.Load(strMouseIn);
	HICON		hIconIn			= NULL;
	HICON		hIconOut		= NULL;
	HINSTANCE	hInstResource	= NULL;

	// Find correct resource handle
	hInstResource = AfxFindResourceHandle(MAKEINTRESOURCE(hIconIn), RT_GROUP_ICON);

	// Set icon when the mouse is IN the button
	hIconIn = (HICON)::LoadImage(hInstResource, strMouseIn, IMAGE_ICON, 0, 0, 0);

  	// Set icon when the mouse is OUT the button
	if (strMouseOut)
	{
	//	if (hIconOut == (int)BTNST_AUTO_GRAY)
	//		hIconOut = BTNST_AUTO_GRAY;
	//	else
			hIconOut = (HICON)::LoadImage(hInstResource, strMouseOut, IMAGE_ICON, 0, 0, 0);
	} // if

	m_IconIn = hIconIn;
    m_IconOut = hIconOut;
	m_IconDraw = bDrawIcon;
}

void CSkinBtn::SetColor(COLORREF fgcolor,COLORREF bgcolor)
{
	m_fg = fgcolor;
	m_bg = bgcolor;
	switch(m_bDrawScroll)
	{
	case BUTTON_SCROLL:
		DrawButtonScroll();
		break;
	case BUTTON_TITLE:
		DrawButtonTitle();
		break;
	case BUTTON_NOPICTURE:
		DrawButtonNullPicture();
		break;
	default:
		DrawButton();
		break;
	}
}

void CSkinBtn::SetTextPos(CPoint point)
{
	m_textPos = point;
}
CRect CSkinBtn::GetRectInParent()
{
	CRect rcWindowParent;
	GetParent()->GetWindowRect(rcWindowParent);//client
	CRect rcWindow;
	GetWindowRect(&rcWindow);
	CRect rect;
	rect.left = rcWindow.left-rcWindowParent.left;
	rect.top = rcWindow.top-rcWindowParent.top;
	rect.right = rcWindow.right-rcWindowParent.left;
	rect.bottom = rcWindow.bottom-rcWindowParent.top;

	return rect;
}
void CSkinBtn::OnEnable(BOOL bEnable)
{
	CButton::OnEnable(bEnable);

	// TODO: 在此处添加消息处理程序代码
	if(bEnable)
		m_bEnabled = true;
	else
		m_bEnabled = false;
}





