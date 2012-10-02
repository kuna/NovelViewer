// NovelViewerSetting.cpp : implementation file
//

#include "stdafx.h"
#include "NovelViewer10.h"
#include "NovelViewerSetting.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerSetting dialog


CNovelViewerSetting::CNovelViewerSetting(CWnd* pParent /*=NULL*/)
	: CDialog(CNovelViewerSetting::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNovelViewerSetting)
	//}}AFX_DATA_INIT
}


void CNovelViewerSetting::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNovelViewerSetting)
	DDX_Control(pDX, IDC_COMBO2, m_lfquality);
	DDX_Control(pDX, IDC_EDIT5, m_bordermarginy);
	DDX_Control(pDX, IDC_CHECK1, m_ignoreemptyline);
	DDX_Control(pDX, IDC_EDIT4, m_bordermargin);
	DDX_Control(pDX, IDC_EDIT3, m_fontindent);
	DDX_Control(pDX, IDC_EDIT2, m_fontlinemargin);
	DDX_Control(pDX, IDC_EDIT1, m_fontmargin);
	DDX_Control(pDX, IDC_COMBO1, m_scroll);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT6, m_pagecnt);
	DDX_Control(pDX, IDC_EDIT7, m_pagemargin);
	DDX_Control(pDX, IDC_CHECK2, m_usedx);
}


BEGIN_MESSAGE_MAP(CNovelViewerSetting, CDialog)
	//{{AFX_MSG_MAP(CNovelViewerSetting)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_CBN_EDITCHANGE(IDC_COMBO1, OnEditchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CNovelViewerSetting::OnBnClickedOk)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelViewerSetting message handlers

CString Int2Str(int num)
{
	CString _tmp;
	_tmp.Format(L"%d", num);
	return _tmp;
}

BOOL CNovelViewerSetting::OnInitDialog()
{

	CDialog::OnInitDialog();
	
	m_bordermargin.SetWindowText(Int2Str(borderMarginX));
	m_bordermarginy.SetWindowText(Int2Str(borderMarginY));
	m_fontlinemargin.SetWindowText(Int2Str(fontLineMargin));
	m_fontmargin.SetWindowText(Int2Str(fontMargin));
	m_fontmargin.SetWindowText(Int2Str(fontMargin));
	m_fontindent.SetWindowText(Int2Str(fontIndent));
	m_ignoreemptyline.SetCheck( ignoreEmptyline);

	m_pagemargin.SetWindowText(Int2Str(pageMargin));
	m_pagecnt.SetWindowText(Int2Str(pageCnt));
	m_usedx.SetCheck( useDX);

	m_scroll.AddString(L"가로로 보기(책넘기듯이)");
	m_scroll.AddString(L"세로로 보기(스크롤하듯이)");
	m_scroll.AddString(L"효과 없음(한줄씩)");
	m_scroll.AddString(L"효과 없음(한페이지씩)");
	m_scroll.SetCurSel(scroll);

	m_lfquality.AddString(L"하단 텍스트만 안티앨리어싱! (빠름)");
	m_lfquality.AddString(L"안티안먹여 (빠름)");
	m_lfquality.AddString(L"올 안티앨리어싱! (느림, 고품질)");
	m_lfquality.AddString(L"시스템 기본값");
	m_lfquality.SetCurSel(lfquality);
	
	return TRUE;
}


void CNovelViewerSetting::OnButton1() 
{
	LOGFONT lf;
	memset(&lf, 0, sizeof(LOGFONT));

	CClientDC dc(this);
	lf.lfHeight = fontSize;
	lf.lfWeight = fontBold;
	wcscpy(lf.lfFaceName, fontFace);

	CFontDialog dlg(&lf);
	
	if (dlg.DoModal() == IDOK)
	{
		wcscpy(fontFace, lf.lfFaceName);
		fontSize = lf.lfHeight;
		fontBold = lf.lfWeight;
	}
}

void CNovelViewerSetting::OnButton2() 
{
	CColorDialog dlg(fontColor, CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
		fontColor = dlg.GetColor();
}

void CNovelViewerSetting::OnButton3() 
{
	CColorDialog dlg(backColor, CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
		backColor = dlg.GetColor();
}

void CNovelViewerSetting::OnEditchangeCombo1() 
{
}

void CNovelViewerSetting::OnSelchangeCombo1() 
{
	// TODO: Add your control notification handler code here
if (m_scroll.GetCurSel() == 1) // 세로라면
m_bordermarginy.SetWindowText(L"0");
	
}

void CNovelViewerSetting::OnButton4() 
{
	CColorDialog dlg(bmColor, CC_FULLOPEN);
	if (dlg.DoModal() == IDOK)
		bmColor = dlg.GetColor();
}


void CNovelViewerSetting::OnBnClickedOk()
{
	TCHAR buf[255];
	m_bordermargin.GetWindowText(buf, 255), borderMarginX=_wtoi(buf);
	m_bordermarginy.GetWindowText(buf, 255), borderMarginY=_wtoi(buf);
	m_fontlinemargin.GetWindowText(buf, 255), fontLineMargin=_wtoi(buf);
	m_fontmargin.GetWindowText(buf, 255), fontMargin=_wtoi(buf);
	m_fontindent.GetWindowText(buf, 255), fontIndent=_wtoi(buf);
	ignoreEmptyline=m_ignoreemptyline.GetCheck();
	scroll = m_scroll.GetCurSel();
	lfquality = m_lfquality.GetCurSel();
	
	m_pagecnt.GetWindowText(buf, 255), pageCnt=_wtoi(buf);
	m_pagemargin.GetWindowText(buf, 255), pageMargin=_wtoi(buf);
	useDX=m_usedx.GetCheck();

	CDialog::OnOK();
}
