// NovelViewerFind.cpp : implementation file
//

#include "stdafx.h"
#include "NovelViewer10.h"
#include "NovelViewerFind.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerFind dialog


CNovelViewerFind::CNovelViewerFind(CWnd* pParent /*=NULL*/)
	: CDialog(CNovelViewerFind::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNovelViewerFind)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CNovelViewerFind::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNovelViewerFind)
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CNovelViewerFind, CDialog)
	//{{AFX_MSG_MAP(CNovelViewerFind)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerFind message handlers

void CNovelViewerFind::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	m_edit.GetWindowText(str);
}

BOOL CNovelViewerFind::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_edit.SetWindowText(str.GetBuffer(0));
	m_edit.SetFocus();
	return FALSE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
