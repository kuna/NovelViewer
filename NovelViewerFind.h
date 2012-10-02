#if !defined(AFX_NOVELVIEWERFIND_H__BFCB3170_1382_4C28_B6F1_2B3AA7FA49EA__INCLUDED_)
#define AFX_NOVELVIEWERFIND_H__BFCB3170_1382_4C28_B6F1_2B3AA7FA49EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NovelViewerFind.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerFind dialog

class CNovelViewerFind : public CDialog
{
// Construction
public:
	CNovelViewerFind(CWnd* pParent = NULL);   // standard constructor
	CString str;

// Dialog Data
	//{{AFX_DATA(CNovelViewerFind)
	enum { IDD = IDD_SEARCH };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelViewerFind)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNovelViewerFind)
	afx_msg void OnDestroy();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVELVIEWERFIND_H__BFCB3170_1382_4C28_B6F1_2B3AA7FA49EA__INCLUDED_)
