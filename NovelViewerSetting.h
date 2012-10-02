#include "afxwin.h"
#if !defined(AFX_NOVELVIEWERSETTING_H__70128C1A_B394_4AE7_9629_F2560A0412D3__INCLUDED_)
#define AFX_NOVELVIEWERSETTING_H__70128C1A_B394_4AE7_9629_F2560A0412D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NovelViewerSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerSetting dialog

class CNovelViewerSetting : public CDialog
{
// Construction
public:
	CNovelViewerSetting(CWnd* pParent = NULL);   // standard constructor

	int fontSize;
	int fontColor;
	int backColor;
	int bmColor;
	TCHAR fontFace[255];
	int scroll;
	int lfquality;

	int fontIndent;
	int fontLineMargin;
	int fontMargin;
	int fontBold;
	int borderMarginX;
	int borderMarginY;
	int pageMargin;
	int pageCnt;
	
	bool ignoreEmptyline;
	bool useDX;

	virtual BOOL OnInitDialog();

// Dialog Data
	//{{AFX_DATA(CNovelViewerSetting)
	enum { IDD = IDD_SETTINGS };
	CComboBox	m_lfquality;
	CEdit	m_bordermarginy;
	CButton	m_ignoreemptyline;
	CEdit	m_bordermargin;
	CEdit	m_fontindent;
	CEdit	m_fontlinemargin;
	CEdit	m_fontmargin;
	CComboBox	m_scroll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelViewerSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNovelViewerSetting)
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnEditchangeCombo1();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnButton4();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_pagecnt;
	CEdit m_pagemargin;
	CButton m_usedx;
	afx_msg void OnBnClickedOk();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVELVIEWERSETTING_H__70128C1A_B394_4AE7_9629_F2560A0412D3__INCLUDED_)
