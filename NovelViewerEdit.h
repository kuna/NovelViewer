#if !defined(AFX_NOVELVIEWEREDIT_H__5E1952EF_7788_4A98_9BC3_8F4F71C23654__INCLUDED_)
#define AFX_NOVELVIEWEREDIT_H__5E1952EF_7788_4A98_9BC3_8F4F71C23654__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NovelViewerEdit.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerEdit dialog

class CNovelViewerEdit : public CDialog
{
// Construction
public:
	CNovelViewerEdit(CWnd* pParent = NULL);   // standard constructor
	CString fd;

// Dialog Data
	//{{AFX_DATA(CNovelViewerEdit)
	enum { IDD = IDD_EDIT };
	CEdit	m_edit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNovelViewerEdit)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CNovelViewerEdit)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NOVELVIEWEREDIT_H__5E1952EF_7788_4A98_9BC3_8F4F71C23654__INCLUDED_)
