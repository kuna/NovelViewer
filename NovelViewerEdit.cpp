// NovelViewerEdit.cpp : implementation file
//

#include "stdafx.h"
#include "NovelViewer10.h"
#include "NovelViewerEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerEdit dialog


CNovelViewerEdit::CNovelViewerEdit(CWnd* pParent /*=NULL*/)
	: CDialog(CNovelViewerEdit::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNovelViewerEdit)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNovelViewerEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNovelViewerEdit)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNovelViewerEdit, CDialog)
	//{{AFX_MSG_MAP(CNovelViewerEdit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerEdit message handlers

BOOL CNovelViewerEdit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_edit.SetWindowText(fd);
	m_edit.SetFocus();
	
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CNovelViewerEdit::DestroyWindow() 
{
	m_edit.GetWindowText(fd);
	
	return CDialog::DestroyWindow();
}
