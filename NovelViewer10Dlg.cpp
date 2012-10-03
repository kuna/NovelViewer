// NovelViewer10Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "NovelViewer10.h"
#include "NovelViewer10Dlg.h"
#include "NovelViewerSetting.h"
#include "NovelViewerEdit.h"
#include "NovelViewerCore.h"
#include "NovelViewerFind.h"
#include "NovelViewerD3DX.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// directx object
NovelViewerD3DX nvD3DX;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelViewer10Dlg dialog

CNovelViewer10Dlg::CNovelViewer10Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNovelViewer10Dlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CNovelViewer10Dlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNovelViewer10Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CNovelViewer10Dlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CNovelViewer10Dlg, CDialog)
	//{{AFX_MSG_MAP(CNovelViewer10Dlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNovelViewer10Dlg message handlers

NVCore nvc;

BOOL CNovelViewer10Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	afxAmbientActCtx = FALSE;	// unknown reason ... bug

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
			pSysMenu->AppendMenu(MF_STRING, IDM_SETTINGS, L"설정(&S)");
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra ( 
	DragAcceptFiles();

	nvc.setParenthWnd(m_hWnd);
	nvc.readPref();

	// tmp

	SetWindowPos(NULL, nvc.scr_x, nvc.scr_y, 0,0,SWP_NOSIZE);
	SetClientRect(nvc.scr_wid, nvc.scr_hei);
	if (nvc.NVFullScreen) resetBorder(true);

	nvc.readTxtFile(nvc.recentPath);

	if (nvc.NVUseDirectX) {
		nvD3DX.SetFont( nvc.NVfont, nvc.NVfontSize, nvc.NVfontColor, nvc.NVBackColor );
		int r = nvD3DX.InitalizeDevice(m_hWnd);
		if (!r)
			AfxMessageBox(L"Failed to Initalize DirectX");
	}

	Invalidate(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}


void CNovelViewer10Dlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR szFullPath[512] = {0,};
	//int iCount = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);	// 드래그앤드롭한 파일갯수획득
	/*for(int i=0; i<iCount; i++)
	{
		DragQueryFile(hDropInfo, i, szFullPath, sizeof(szFullPath));
		AfxMessageBox(szFullPath);
	}*/
	DragQueryFile(hDropInfo, 0, szFullPath, sizeof(szFullPath));
	nvc.readTxtFile(szFullPath);

	Invalidate(FALSE);

	CDialog::OnDropFiles(hDropInfo);
}

void CNovelViewer10Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	} else if (nID == IDM_SETTINGS) {
		// 설정창 열고 설정
		CNovelViewerSetting cnvs;

		wcscpy( cnvs.fontFace, nvc.NVfont );
		cnvs.fontSize = nvc.NVfontSize;
		cnvs.fontColor = nvc.NVfontColor;
		cnvs.backColor = nvc.NVBackColor;
		cnvs.bmColor = nvc.NVBmColor;
		cnvs.scroll = nvc.NVScrolltype;
		cnvs.borderMarginX = nvc.NVBorderMarginX;
		cnvs.borderMarginY = nvc.NVBorderMarginY;
		cnvs.fontLineMargin = nvc.NVfontLineMargin;
		cnvs.fontIndent = nvc.NVfontLineIndent;
		cnvs.fontMargin = nvc.NVfontTextMargin;
		cnvs.ignoreEmptyline = nvc.NVEmptylineIgnore;
		
		cnvs.pageCnt = nvc.NVPageCnt;
		cnvs.pageMargin = nvc.NVPageMargin;
		cnvs.useDX = nvc.NVUseDirectX;

		cnvs.lfquality = nvc.NVlfQuality;
		cnvs.fontBold = nvc.NVfontBold;
			
		if (cnvs.DoModal() == IDOK)
		{
			wcscpy( nvc.NVfont, cnvs.fontFace );
			nvc.NVfontSize = cnvs.fontSize;
			nvc.NVfontColor = cnvs.fontColor;
			nvc.NVBackColor = cnvs.backColor;
			nvc.NVBmColor = cnvs.bmColor;
			nvc.NVScrolltype = cnvs.scroll;
			nvc.NVBorderMarginX = cnvs.borderMarginX;
			nvc.NVBorderMarginY = cnvs.borderMarginY;
			nvc.NVfontLineMargin = cnvs.fontLineMargin;
			nvc.NVfontLineIndent = cnvs.fontIndent;
			nvc.NVfontTextMargin = cnvs.fontMargin;
			nvc.NVEmptylineIgnore = cnvs.ignoreEmptyline;
			
			nvc.NVPageCnt = cnvs.pageCnt;
			nvc.NVPageMargin = cnvs.pageMargin;
			nvc.NVUseDirectX = cnvs.useDX;

			nvc.NVlfQuality = cnvs.lfquality;
			nvc.NVfontBold = cnvs.fontBold;

			nvc.createFontObject();
			nvc.off_x = nvc.off_y = 0;	// 스크롤버그
			
			// DX Initalize
			if (nvc.NVUseDirectX) {
				nvD3DX.SetFont( nvc.NVfont, nvc.NVfontSize, nvc.NVfontColor, nvc.NVBackColor );
				nvD3DX.OnResize();	// reset device
				int r = nvD3DX.InitalizeDevice(m_hWnd);
				if (!r)
					AfxMessageBox(L"Failed to Initalize DirectX");
			} else {
				nvD3DX.ReleaseDevice();
			}

			nvc.initfontWidth();
			Invalidate(FALSE);
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNovelViewer10Dlg::OnPaint() 
{
	CPaintDC dc(this);

	CDC mDC;
	CBitmap mBitmap;

	// 더블버퍼링 : MDC와 비트맵에 현재 dc를 정의 및 설정
	mDC.CreateCompatibleDC(&dc);
	mBitmap.CreateCompatibleBitmap(&dc, nvc.scr_wid, nvc.scr_hei);
	mDC.SelectObject(&mBitmap);

	/*if (nvD3DX.isInitalized()) {
		// use DirectX
		nvc.drawTextDX(&mDC, &mBitmap, &nvD3DX);
	} else {*/
		// use GDI
	if (!nvD3DX.isInitalized()) {
		nvc.drawText(&mDC, &mBitmap);
		dc.BitBlt(0, 0, nvc.scr_wid, nvc.scr_hei, &mDC, 0, 0, SRCCOPY);
	}
	//}

}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNovelViewer10Dlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

	const int spd = 3;
	const int acelspd = 4;
int goalOffset = 0, _ng;

void CNovelViewer10Dlg::OnTimer(UINT nIDEvent) 
{
	int m = 0;

	// X Scroll mode
	if (nvc.NVScrolltype == 0) {
		// autofit
		if (goalOffset==0){
		m = 0;
		if (-nvc.off_x < (nvc.NVBorderMarginX + nvc.scr_wid)/2) {
			m = -nvc.off_x / acelspd;
			if (m<=spd) m=spd;
			nvc.off_x += m;
			if (nvc.off_x > 0)
			{
				nvc.off_x = 0;
				KillTimer(NULL);
			}
		} else {
			m = (nvc.NVBorderMarginX + nvc.scr_wid + nvc.off_x) / acelspd;
			if (m <= spd) m = spd;
			nvc.off_x -= m;
			if (nvc.off_x < -(nvc.NVBorderMarginX + nvc.scr_wid))
			{
				nvc.off_x = -(nvc.NVBorderMarginX + nvc.scr_wid);
				KillTimer(NULL);
			}
		}
		//if (nvc.off_y) {
		//}
		}

		// accl
		m = 0;
		if (goalOffset!=0)
		{
			_ng=goalOffset;

			if(goalOffset<0 && -goalOffset/acelspd<spd){
				goalOffset+=spd;
				if(goalOffset>0) goalOffset=0;
				m=1;
			}
			if(goalOffset>0 && goalOffset/acelspd<spd){
				goalOffset-=spd;
				if(goalOffset<0) goalOffset=0;
				m=1;
			}

			if(!m) {
				goalOffset = goalOffset - goalOffset/acelspd;
			}
			nvc.off_x -= goalOffset-_ng;

			if(goalOffset==0) KillTimer(NULL);
		}
	}

	// Y Scroll type
	if (nvc.NVScrolltype == 1) {
		// autofit
		if (goalOffset==0){
		m = 0;
		if (-nvc.off_y < (nvc.NVBorderMarginY + nvc.scr_hei)/2) {
			m = -nvc.off_y / acelspd;
			if (m<=spd) m=spd;
			nvc.off_y += m;
			if (nvc.off_y > 0)
			{
				nvc.off_y = 0;
				KillTimer(NULL);
			}
		} else {
			m = (nvc.NVBorderMarginY + nvc.scr_hei + nvc.off_y) / acelspd;
			if (m <= spd) m = spd;
			nvc.off_y -= m;
			if (nvc.off_y < -(nvc.NVBorderMarginY + nvc.scr_hei))
			{
				nvc.off_y = -(nvc.NVBorderMarginY + nvc.scr_hei);
				KillTimer(NULL);
			}
		}
		//if (nvc.off_y) {
		//}
		}

		// accl
		m = 0;
		if (goalOffset!=0)
		{
			_ng=goalOffset;

			if(goalOffset<0 && -goalOffset/acelspd<spd){
				goalOffset+=spd;
				if(goalOffset>0) goalOffset=0;
				m=1;
			}
			if(goalOffset>0 && goalOffset/acelspd<spd){
				goalOffset-=spd;
				if(goalOffset<0) goalOffset=0;
				m=1;
			}

			if(!m) {
				goalOffset = goalOffset - goalOffset/acelspd;
			}
			nvc.off_y -= goalOffset-_ng;

			if(goalOffset==0) KillTimer(NULL);
		}
	}
	
	vaildateWnd();

	CDialog::OnTimer(nIDEvent);
}

bool isMoving = false;
bool isPress=false;
CPoint f_pos;
int p_b;
const int sensitivity = 10;

bool isScrolling=false;
bool isScrollbarShow=false;

void CNovelViewer10Dlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	if ((abs(f_pos.x-point.x)>sensitivity || abs(f_pos.y-point.y)>sensitivity) && !isMoving&& isPress) {
		isMoving=true;
	}

	if (isPress &&isMoving) {
		switch (nvc.NVScrolltype) {
		case 0:// 가로스크롤
			nvc.movePosX(point.x - p_b);
			p_b = point.x;
			break;
		case 1://세로스크롤
			nvc.movePosY(point.y - p_b);
			p_b = point.y;
			break;
		}
	
		vaildateWnd();
	}

	if (nvc.scr_wid - point.x<30){
		isScrollbarShow = true;
		SetScrollRange(1, 0, nvc.finPos);
		SetScrollPos(1, nvc.nowPos);

		ShowScrollBar(1, TRUE);
	} else if (!isScrolling){
		isScrollbarShow = false;
		ShowScrollBar(1, FALSE);
	}
	
	nvc.OnMousemove(point);

	CDialog::OnMouseMove(nFlags, point);
}

void CNovelViewer10Dlg::OnLButtonDown(UINT nFlags, CPoint point) 
{

	isPress = true;
	isMoving = false;

	f_pos=point;
	if (nvc.NVScrolltype==0) p_b = point.x;
	if (nvc.NVScrolltype==1) p_b = point.y;

	nvc.OnLbtndown(point);

	CDialog::OnLButtonDown(nFlags, point);
}

void CNovelViewer10Dlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (isPress && !isMoving) {
		switch (nvc.NVScrolltype) {
		case 1: // 세로스크롤
			if (f_pos.y>nvc.scr_hei/2 && f_pos.x>30) moveNext();
			else if (f_pos.y<=nvc.scr_hei/2 && f_pos.x>30) movePrev();
			break;
		default:	// 가로스크롤
			if (f_pos.x>nvc.scr_wid/2) moveNext();
			else if (f_pos.x<=nvc.scr_wid/2 && f_pos.x>30) movePrev();
			break;
		}
	}
	if (isMoving) // autofit!!
		SetTimer(NULL, 30, NULL);

	isPress=false;
	isMoving = false;
	
	nvc.OnLbtnup(point);
	vaildateWnd(); // refresh

	CDialog::OnLButtonUp(nFlags, point);
}

void CNovelViewer10Dlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//scroll offset

	CRect nowRect;
	GetWindowRect(&nowRect);
	nvc.scr_x = nowRect.left;
	nvc.scr_y = nowRect.top;
	nvc.scr_wid=org_wid;
	nvc.scr_hei=org_hei;

	nvc.writeTxtPref();
	nvc.writePref();

	nvD3DX.ReleaseDevice();
}

void CNovelViewer10Dlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	nvc.scr_wid = cx + isScrollbarShow*15;
	nvc.scr_hei = cy;

	if(!nvc.NVFullScreen){
		org_wid=cx;
		org_hei = cy;
	}

	nvD3DX.OnResize();
	if (!nvD3DX.isInitalized())
		Invalidate(FALSE);
}

void CNovelViewer10Dlg::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// tip From : http://blog.naver.com/charsyam?Redirect=Log&logNo=20011891826
	if (!isScrolling)
		isScrolling=true;	// 스크롤 중에는 

	
	SCROLLINFO scrollInfo;
	scrollInfo.cbSize = sizeof(SCROLLINFO);
	GetScrollInfo(SB_VERT,&scrollInfo);

	int m_pos = GetScrollPos(1);//scrollInfo.nPos;

	switch(nSBCode)
	{
	case SB_PAGEUP:
		m_pos -= nvc.prevpageChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
		break;
	case SB_PAGEDOWN:
		m_pos += nvc.nextpageChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
		break;
	case SB_LINEUP:
		m_pos -= nvc.prevlineChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
		break;
	case SB_LINEDOWN:
		m_pos += nvc.nextlineChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
		break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION :
		m_pos = scrollInfo.nTrackPos;
		vaildateWnd();
		break;
	case SB_ENDSCROLL:
		/* 있으나 없으나 큰 상관이..*/
		// 스크롤 끝
		//nvc.nowPos = m_pos = nPos;
		isScrolling = false;
		vaildateWnd();
		return;
	}

	if ( m_pos > nvc.finPos ) m_pos = nvc.finPos;
	else if ( m_pos < 0 ) m_pos = 0;
 
	nvc.nowPos = m_pos;
	vaildateWnd();
	SetScrollPos(1, m_pos);

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CNovelViewer10Dlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// toggle Full Screen
	if (nvc.NVFullScreen)
		resetBorder(false);
	else
		resetBorder(true);

	CDialog::OnLButtonDblClk(nFlags, point);
}

BOOL CNovelViewer10Dlg::PreTranslateMessage(MSG* pMsg)
{
	// 키입력 처리부분
	if(pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_DOWN || pMsg->wParam == VK_RIGHT))
	{
		moveNext();
	} else if (pMsg->message == WM_KEYDOWN && (pMsg->wParam == VK_UP || pMsg->wParam == VK_LEFT))
	{
		movePrev();
	} else if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN) {
		
		TCHAR szFilter[] = L"Text File (*.txt)|*.txt|모든 파일|*.*|";
		CFileDialog dlg(TRUE, L"*.txt", NULL, OFN_HIDEREADONLY, szFilter);
		if (dlg.DoModal() == IDOK) {
			TCHAR buf[255];
			wcscpy(buf, dlg.GetPathName().GetBuffer(0));
			nvc.readTxtFile(buf);
			vaildateWnd();
		}

		pMsg->message = 0;
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void CNovelViewer10Dlg::resetBorder(bool full)
{
nvc.NVFullScreen = full;


	CRect desktopRect, nowRect;
	GetDesktopWindow()->GetWindowRect(&desktopRect);
	GetWindowRect(&nowRect);
		
	// border style을 설정한다?
	int windowstyle = WS_VISIBLE;//SW_SHOWNOACTIVATE;

	if (full)
		windowstyle = windowstyle | 0;	// SAME!
	else
		windowstyle = windowstyle | WS_OVERLAPPEDWINDOW;

	if (full) 	
	{
		nvc.scr_x = nowRect.left;
		nvc.scr_y = nowRect.top;
		// SWP_NOSIZE
		SetWindowPos(&wndTopMost, 0, 0, desktopRect.Width(), desktopRect.Height(), NULL);
	} else {
		SetWindowPos(&wndNoTopMost, nvc.scr_x, nvc.scr_y, org_wid, org_hei, 0);
	}

	SetWindowLong(m_hWnd, GWL_EXSTYLE, /*WS_EX_LAYERED | */WS_EX_ACCEPTFILES);
	SetWindowLong(m_hWnd, GWL_STYLE, windowstyle);

	/*
	// 반투명 처리
	//ModifyStyleEx(0, WS_EX_LAYERED);
	SLWA pSetLayeredWindowAttributes = NULL;
	HINSTANCE hmodUSER32 = LoadLibrary("USER32.DLL");
	pSetLayeredWindowAttributes = (SLWA)GetProcAddress(hmodUSER32, "SetLayeredWindowAttributes");
	pSetLayeredWindowAttributes(m_hWnd, 0, (255 * Opacity) / 100, LWA_ALPHA);
*/

	// 창 다시고침
	SendMessage(WM_NCPAINT,1,0);
	Invalidate();
	ShowScrollBar(1, TRUE);	//bugFix

}

BOOL CNovelViewer10Dlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	if (zDelta < 0) {
		moveNext();
	} else {
		movePrev();
	}

	return CDialog::OnMouseWheel(nFlags, zDelta, pt);
}

void CNovelViewer10Dlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnRButtonDown(nFlags, point);
}

void CNovelViewer10Dlg::OnRButtonUp(UINT nFlags, CPoint point) 
{
	nvc.OnRbtnup(point);
	CDialog::OnRButtonUp(nFlags, point);
}

void CNovelViewer10Dlg::SetClientRect(int wid, int hei)
{
	CRect r1, r2;
	GetWindowRect(&r1);
	GetClientRect (&r2);

	int wg = r1.Width() - r2.Width();
	int hg = r1.Height() - r2.Height();

	SetWindowPos(NULL, 0,0,wid+wg, hei+hg,SWP_NOMOVE); 
}

void CNovelViewer10Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == 17) {	// 'ctrl' 키
		// edit window
		// 잠깐.. pretranslatemessages에서는 창을 열면 안된단다

		CNovelViewerEdit cnve;
		int sPos = nvc.nowPos;
		int len = nvc.nextpageChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
		TCHAR *p = (TCHAR*)malloc(len*2+10); /*여분 필수!*/
		len = nvc.getTxtdata(p, sPos, len);
		cnve.fd.Format(L"%s", p);
		cnve.fd.Replace(L"\r\n", L"\n");
		cnve.fd.Replace(L"\n", L"\r\n");

		if (cnve.DoModal() == IDOK) {			
			cnve.fd.Replace(L"\r\n", L"\n");
			int nlen = cnve.fd.GetLength();
			nvc.setTxtdata(cnve.fd.GetBuffer(0), sPos, len);
			nvc.writeTxtFile(nvc.fpath);
		}

		delete p;
	}

	// 씨쁘트 키 - 검색
	if (nChar == 16) {
		CNovelViewerFind cnvf;
		cnvf.str = fs;
		if (cnvf.DoModal() == IDOK)
		{
			fs = cnvf.str;
			int i = nvc.searchText(cnvf.str.GetBuffer(0), nvc.nowPos+1, nvc.finPos);
			if (i<0) i = nvc.searchText(cnvf.str.GetBuffer(0), 0, nvc.nowPos);
			if (i<0) {
				AfxMessageBox(L"문자열을 찾을 수 없습니다.");
			} else {
				nvc.nowPos = i;
				vaildateWnd();
			}
		}
	}

	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CNovelViewer10Dlg::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{

	CDialog::OnChar(nChar, nRepCnt, nFlags);
}

void CNovelViewer10Dlg::moveNext()
{
	if (nvc.nowPos >= nvc.finPos) {
		nvc.searchfile(false);
		vaildateWnd();
	} else {
		switch (nvc.NVScrolltype) {
		case 0:	// 가로스크롤
			goalOffset -= nvc.scr_wid-nvc.NVBorderMarginX;
			break;
		case 1: // 세로스크롤
			goalOffset -= ((nvc.scr_hei-nvc.NVBorderMarginY+nvc.NVfontLineMargin)/
				(nvc.fontHeight+nvc.NVfontLineMargin))*
				(nvc.fontHeight+nvc.NVfontLineMargin);
			break;
		case 2:
			nvc.nowPos += nvc.nextlineChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
			vaildateWnd();
			return;
		case 3:
			nvc.nowPos += nvc.nextpageChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
			vaildateWnd();
			return;
		}
		SetTimer(NULL, 30, NULL);
	}
}

void CNovelViewer10Dlg::movePrev()
{
	if (nvc.nowPos == 0) {
		nvc.searchfile(true);
			vaildateWnd();
	} else {
		switch (nvc.NVScrolltype) {
		case 0:	// 가로스크롤
			goalOffset += nvc.scr_wid-nvc.NVBorderMarginX;
			break;
		case 1: // 세로스크롤
			goalOffset += ((nvc.scr_hei-nvc.NVBorderMarginY+nvc.NVfontLineMargin)/
				(nvc.fontHeight+nvc.NVfontLineMargin))*
				(nvc.fontHeight+nvc.NVfontLineMargin);
			break;
		case 2:
			nvc.nowPos -= nvc.prevlineChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
			vaildateWnd();
			return;
		case 3:
			nvc.nowPos -= nvc.prevpageChar(GetDesktopWindow()->GetDC(), nvc.nowPos);
			vaildateWnd();
			return;
		}
		SetTimer(NULL, 30, NULL);
	}
}

void CNovelViewer10Dlg::vaildateWnd() {
	if (nvD3DX.isInitalized()) {
		CDC pDC;
		pDC.CreateCompatibleDC(this->GetDC());
		CBitmap mBitmap;
		nvc.drawTextDX(&pDC, &mBitmap, &nvD3DX);
	} else {
		Invalidate(FALSE);
	}
}