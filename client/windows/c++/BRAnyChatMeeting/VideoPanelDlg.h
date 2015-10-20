#if !defined(AFX_VIDEOPANELDLG_H__15023AD4_E5B0_4A48_B448_699AD60A72DD__INCLUDED_)
#define AFX_VIDEOPANELDLG_H__15023AD4_E5B0_4A48_B448_699AD60A72DD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ctrls/GradientProgressCtrl.h"
#include "FullScreenDlg.h"

#define INVALID_USERID		0xFFFFFFFF			///< 非法用户ID

/**
 *	视频面板对话框
 *	显示指定用户的视频、音量大小，并提供相关的控制操作
 */
class CVideoPanelDlg : public CDialog
{
// Construction
public:
	CVideoPanelDlg(CWnd* pParent = NULL);   // standard constructor


private:
	CPicture	m_vfTopLeftPic;					///< 左上角图片
	CPicture	m_vfTopMiddlePic;				///< 上部中间图片
	CPicture	m_vfTopRightPic;				///< 右上角图片
	CPicture	m_vfLeftPic;					///< 左边框图片
	CPicture	m_vfRightPic;					///< 右边框图片
	CPicture	m_vfBottomLeftPic;				///< 底部左边图片
	CPicture	m_vfBottomMiddlePic;			///< 底部中间图片
	CPicture	m_vfBottomRightPic;				///< 底部右边图片

	CPicture	m_NetStatusPic;					///< 网络状态图片
	CRect		m_rcNetStatus;					///< 网络状态图标显示区域

	CPicture	m_VideoBkPic;					///< 视频背景区域图片
	CBrush		m_bkBrush;						///< 背景颜色刷
	BOOL		m_bNeedShowBkPic;				///< 是否需要显示背景图片

	CString		m_strTitle;						///< 标题字符串
	CRect		m_rcTitle;						///< 标题区域
	CRect		m_rcMainDisp;					///< 主显示区域
	CRect		m_rcVideoDisp;					///< 视频显示区域
	BOOL		m_bRegualShowVideo;				///< 按规则显示视频（保持视频不变形）

	DWORD		m_dwUserId;						///< 当前视频显示面板所关联的用户ID
	BOOL		m_bVideoState;					///< 本地视频状态
	BOOL		m_bAudioState;					///< 本地音频状态

	PCHAR		m_pLastVideoBuf;				///< 最后保留的视频帧数据
	DWORD		m_dwLastVideoLen;				///< 最后保留的视频帧长度
	BITMAPINFOHEADER	m_bmiLastVideo;			///< 最后保留的视频头信息
	CRITICAL_SECTION	m_hBufSection;			///< 视频缓冲区临界量

	DWORD		m_dwWidth;						///< 当前用户视频宽度
	DWORD		m_dwHeight;						///< 当前用户视频高度

	CFullScreenDlg*	m_pFullScreenDlg;			///< 视频全屏对话框

private:
	// 重新定位界面控件
	void RelocateControls();
	// 初始化按钮
	void InitSTButton(CButtonST& btn, INT bitmapID, LPCTSTR lpTooltip);
	// 规整视频显示区域，让视频按一定的比例显示
	void AdjustVideoDispRect(CRect& rc);


public:
	// 设置标题显示
	void SetPanelTitle(CString strTitle);
	// 设置关联用户编号
	void SetRelateUserId(DWORD dwUserId);
	// 获取当前关联的用户编号
	DWORD GetUserId(void)			{	return m_dwUserId;		}

	// 收到回调视频数据
	void OnRecvCallBackVideoData(LPVOID lpBuf, DWORD dwLen, BITMAPINFOHEADER bmiHeader);
	// 用户视频分辨率变化
	void OnVideoSizeChange(DWORD dwWidth, DWORD dwHeight);

// Dialog Data
	//{{AFX_DATA(CVideoPanelDlg)
	enum { IDD = IDD_DIALOG_VIDEOPANEL };
	CButtonST	m_btnVideoCtrl;
	CButtonST	m_btnSnapshot;
	CButtonST	m_btnRecord;
	CButtonST	m_btnAudioCtrl;
	CGradientProgressCtrl	m_ctrlAudioVolume;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoPanelDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoPanelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnButtonVideoControl();
	afx_msg void OnButtonAudioControl();
	afx_msg void OnButtonSnapshot();
	afx_msg void OnButtonRecord();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg LRESULT OnRefreshButtonState(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnRefreshVideo(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnExitFullScreen(WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOPANELDLG_H__15023AD4_E5B0_4A48_B448_699AD60A72DD__INCLUDED_)
