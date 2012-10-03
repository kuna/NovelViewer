#include "stdafx.h"
#include "NovelViewerCore.h"
#include "algorithm"

NVCore::NVCore()
{
	isOpened = false;
	bpreview = -1;
	GetCurrentDirectory(255, currDir);
	
	initfontWidth();
}
NVCore::~NVCore()
{
	releaseTxtFile();
}

void NVCore::defaultSetting()
{
	wcscpy(NVfont, L"맑은 고딕");
	NVfontSize = -21;
	NVfontLineIndent = 5;
	NVfontLineMargin = 10;
	NVEmptylineIgnore = true;
	NVfontTextMargin = -1;
	
	NVOpacity = 80;
	NVSmoothScroll = true;
	NVBorderMarginX = 10;
	NVBorderMarginY = 10;
	NVFullScreen = false;
	NVBackColor = 16777215;
	NVBmColor = 10790052;
	NVfontColor = 0;
	NVPageMargin = 20;
	NVPageCnt = 2;
	NVUseDirectX = true;

	scr_wid = 400;
	scr_hei = 320;
	scr_x = 0;
	scr_y = 0;
	NVScrolltype = 0;	// 가로스크롤
	NVlfQuality = 0;	
	NVfontBold = FW_NORMAL;

	createFontObject();
}

void NVCore::createFontObject()
{
	font.DeleteObject();
	ifont.DeleteObject();

	int lq;
	if (NVlfQuality == 0 || NVlfQuality == 1) lq = NONANTIALIASED_QUALITY;
	else if (NVlfQuality == 2) lq = ANTIALIASED_QUALITY;
	else if (NVlfQuality == 3) lq = DEFAULT_QUALITY;

		// set Font
	LOGFONT logfont;
	
	logfont.lfHeight=NVfontSize;               //문자열 높이
    logfont.lfWidth=0;                 //너비
    logfont.lfEscapement=0;            //문자열기울기
    logfont.lfOrientation=0;             //문자개별각도
    logfont.lfWeight=NVfontBold;     //굵기
    logfont.lfItalic=FALSE;             //이탤릭
    logfont.lfUnderline=FALSE; //밑줄
    logfont.lfStrikeOut=FALSE; //취소선
    logfont.lfCharSet=HANGUL_CHARSET; //필수
    logfont.lfOutPrecision=OUT_DEFAULT_PRECIS;               
    logfont.lfClipPrecision=CLIP_DEFAULT_PRECIS;     //가변폭폰트 고정폭폰트
    logfont.lfPitchAndFamily=DEFAULT_PITCH|FF_SWISS; //글꼴이름
	logfont.lfQuality = lq;
    wcscpy(logfont.lfFaceName, NVfont); 

	font.CreateFontIndirect(&logfont);



	if (NVlfQuality == 1) lq = NONANTIALIASED_QUALITY;
	else if (NVlfQuality == 0 || NVlfQuality == 2) lq = ANTIALIASED_QUALITY;
	else if (NVlfQuality == 3) lq = DEFAULT_QUALITY;

	logfont.lfHeight=-10;               //문자열 높이
    logfont.lfWidth=0;                 //너비
    logfont.lfEscapement=0;            //문자열기울기
    logfont.lfOrientation=0;             //문자개별각도
    logfont.lfWeight=FW_NORMAL;     //굵기
    logfont.lfItalic=FALSE;             //이탤릭
    logfont.lfUnderline=FALSE; //밑줄
    logfont.lfStrikeOut=FALSE; //취소선
    logfont.lfCharSet=HANGUL_CHARSET; //필수
    logfont.lfOutPrecision=OUT_DEFAULT_PRECIS;               
    logfont.lfClipPrecision=CLIP_DEFAULT_PRECIS;     //가변폭폰트 고정폭폰트
    logfont.lfPitchAndFamily=DEFAULT_PITCH|FF_SWISS; //글꼴이름
	logfont.lfQuality = lq;
    wcscpy(logfont.lfFaceName, L"Arial"); 

	ifont.CreateFontIndirect(&logfont);

	bgBrush.DeleteObject();
	bBrush.DeleteObject();
	bgBrush.CreateSolidBrush(NVBackColor);
	bBrush.CreateSolidBrush(NVBmColor);

	fontHeight=-NVfontSize;
	btmMargin=15;
}

bool NVCore::readPref(bool initalize)
{
	TCHAR path[255];	wsprintf(path, L"%s\\settings.dat", currDir);
	FILE *fp = _wfopen(path, L"r");
	if (fp == NULL) {
		defaultSetting();
		return true;
	}

	fread(recentPath, 1, sizeof(recentPath), fp);
	fread(NVfont, 1, sizeof(NVfont), fp);
	fread(&NVfontSize, 1, sizeof(int), fp);
	fread(&NVfontLineIndent, 1, sizeof(int), fp);
	fread(&NVfontLineMargin, 1, sizeof(int), fp);
	fread(&NVfontTextMargin, 1, sizeof(int), fp);
	fread(&NVEmptylineIgnore, 1, sizeof(bool), fp);
	fread(&NVOpacity, 1, sizeof(int), fp);
	fread(&NVSmoothScroll, 1, sizeof(bool), fp);

	fread(&NVBorderMarginX, 1, sizeof(int), fp);
	fread(&NVBorderMarginY, 1, sizeof(int), fp);
	fread(&NVFullScreen, 1, sizeof(bool), fp);
	fread(&NVBackColor, 1, sizeof(int), fp);
	fread(&NVfontColor, 1, sizeof(int), fp);

	fread(&scr_wid, 1, sizeof(int), fp);
	fread(&scr_hei, 1, sizeof(int), fp);
	fread(&scr_x, 1, sizeof(int), fp);
	fread(&scr_y, 1, sizeof(int), fp);
	fread(&NVScrolltype, 1, sizeof(int), fp);
	fread(&NVBmColor, 1, sizeof(int), fp);
	fread(&NVlfQuality, 1, sizeof(int),fp);
	fread(&NVfontBold, 1, sizeof(int), fp);
	fread(&NVPageMargin, 1, sizeof(int), fp);
	fread(&NVPageCnt, 1, sizeof(int), fp);
	fread(&NVUseDirectX, 1, sizeof(bool), fp);

	fclose(fp);

	if (initalize) createFontObject();

	return true;
}

bool NVCore::writePref()
{
	TCHAR path[255];	wsprintf(path, L"%s\\settings.dat", currDir);
	FILE *fp = _wfopen(path, L"w");
	if (fp == NULL) {
		return false;
	}

	wcscpy(recentPath ,fpath);
	fwrite(recentPath, 1, sizeof(recentPath), fp);
	fwrite(NVfont, 1, sizeof(NVfont), fp);
	fwrite(&NVfontSize, 1, sizeof(int), fp);
	fwrite(&NVfontLineIndent, 1, sizeof(int), fp);
	fwrite(&NVfontLineMargin, 1, sizeof(int), fp);
	fwrite(&NVfontTextMargin, 1, sizeof(int), fp);
	fwrite(&NVEmptylineIgnore, 1, sizeof(bool), fp);
	fwrite(&NVOpacity, 1, sizeof(int), fp);
	fwrite(&NVSmoothScroll, 1, sizeof(bool), fp);

	fwrite(&NVBorderMarginX, 1, sizeof(int), fp);
	fwrite(&NVBorderMarginY, 1, sizeof(int), fp);
	fwrite(&NVFullScreen, 1, sizeof(bool), fp);
	fwrite(&NVBackColor, 1, sizeof(int), fp);
	fwrite(&NVfontColor, 1, sizeof(int), fp);

	fwrite(&scr_wid, 1, sizeof(int), fp);
	fwrite(&scr_hei, 1, sizeof(int), fp);
	fwrite(&scr_x, 1, sizeof(int), fp);
	fwrite(&scr_y, 1, sizeof(int), fp);
	fwrite(&NVScrolltype, 1, sizeof(int), fp);
	fwrite(&NVBmColor, 1, sizeof(int), fp);
	fwrite(&NVlfQuality, 1, sizeof(int),fp);
	fwrite(&NVfontBold, 1, sizeof(int), fp);
	fwrite(&NVPageMargin, 1, sizeof(int), fp);
	fwrite(&NVPageCnt, 1, sizeof(int), fp);
	fwrite(&NVUseDirectX, 1, sizeof(bool), fp);

	fclose(fp);

	return true;
}

bool NVCore::readTxtPref(TCHAR *fn, int *p)
{
	*p = 0;
	TCHAR path[255];	wsprintf(path, L"%s\\recent.dat", currDir);
	FILE *fp = _wfopen(path, L"r");
	if (fp == NULL) { return false; }

	// def setting
	bmarkcnt=0;
	*p=0;

	_RECENT rec_dat;
	while (1) {
		int l = fread(&rec_dat, 1, sizeof(_RECENT), fp);
		if (l < sizeof(_RECENT)) break;
		if (wcscmp(rec_dat.fname, fn) == 0)
		{
			*p = rec_dat.pos;
			bmarkcnt = rec_dat.bmcnt;
			memcpy(bmark, rec_dat.bm, sizeof(int)*BOOKMARKMAX);
			fclose(fp);
			return true;
		}
	}

	fclose(fp);

	return true;
}

bool NVCore::writeTxtPref(TCHAR *fn, int *p)
{
	TCHAR path[255], npath[255];
	wsprintf(path, L"%s\\recent.dat", currDir);
	FILE *fp = _wfopen(path, L"r");
	//if (fp == NULL) { return false; }

	wsprintf(npath, L"%s\\recent.dat.tmp", currDir);
	FILE *fpo = _wfopen(npath, L"w");
	if (fpo == NULL) { fclose(fp); return false; }

	_RECENT rec_dat;
	bool is = false;
	while (fp) {
		int l = fread(&rec_dat, 1, sizeof(_RECENT), fp);
		if (l < sizeof(_RECENT)) break;

		if (wcscmp(rec_dat.fname, fn) == 0)
		{
			rec_dat.pos = *p;
			rec_dat.bmcnt = bmarkcnt;
			memcpy(rec_dat.bm, bmark, sizeof(int)*BOOKMARKMAX);
			rec_dat.cnt++;
			is = true;
		}

		fwrite(&rec_dat, 1, sizeof(_RECENT), fpo);
	}

	// add new record
	if (!is)
	{
		wcscpy(rec_dat.fname, fn);
		rec_dat.pos = *p;
		rec_dat.bmcnt = bmarkcnt;
		memcpy(rec_dat.bm, bmark, sizeof(int)*BOOKMARKMAX);
		rec_dat.cnt = 1;
		fwrite(&rec_dat, 1, sizeof(_RECENT), fpo);
	}

	if (fp) fclose(fp);
	fclose(fpo);

	_wremove(path);
	_wrename(npath, path);

	return true;
}

bool NVCore::writeTxtPref()
{
	return writeTxtPref(fpath , &nowPos);
}

bool NVCore::readTxtFile(TCHAR *fn)
{
	if (wcslen(fn) <= 0) return false;
	FILE *fp = _wfopen(fn, L"r");
	if (fp == NULL) return false;
	
	if (isOpened) writeTxtPref(), releaseTxtFile();
	wcscpy(fpath,fn);
	int i;
	for (i=wcslen(fpath)-1; i>=0; i--)
		if (fpath[i] == L'\\') break;
	wcscpy(fname, fpath+i+1);
	readTxtPref(fn, &nowPos);

	// 읽는 과정
	fseek(fp, 0, SEEK_END);
	finPos = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	fileData = (char*)malloc(finPos);
	finPos = fread(fileData, 1, finPos, fp);
	fclose(fp);

	// !! 유니코드 처리과정 추가 !!
	int iLen = ::MultiByteToWideChar(CP_ACP, 0, fileData, -1, fileText, 0);
	fileText = new TCHAR[iLen+1];
	::MultiByteToWideChar(CP_ACP, 0, fileData, -1, fileText, iLen);
	finPos = iLen;
	
	off_x=off_y=0;

	isOpened = true;
	return true;
}

bool NVCore::writeTxtFile(TCHAR *fn)
{
	if (wcslen(fn) ==0 ) return false;
	FILE *fp = _wfopen(fn, L"w");
	if (!fp) return false;
	fwrite(fileData, 1, finPos, fp);
	fclose(fp);
	return true;
}

bool NVCore::releaseTxtFile()
{
	if (isOpened)
		delete fileData;
	return true;
}

int NVCore::getTxtdata(TCHAR *p, int sPos, int len)
{
	if (sPos + len > finPos) len = finPos - sPos;
	memcpy(p, fileData+sPos, len);
	p[len] = '\0';
	return len;
}

int NVCore::setTxtdata(TCHAR *p, int sPos, int len)
{
	if (sPos + len > finPos) len = finPos - sPos;
	int ndlen = wcslen(p);
	int ndfinPos = finPos - len + ndlen;

	char *t  = (char*)malloc(ndfinPos+10);
	memcpy(t, fileData, sPos);
	memcpy(t+sPos, p, ndlen);
	memcpy(t+sPos+ndlen, fileData+sPos+len, finPos-sPos-len);
	t[ndfinPos]='\0';

	delete fileData;
	fileData=t;

	finPos = finPos - len + ndlen;
	return len;
}

void NVCore::drawText(CDC *pDC, CBitmap *pBack)
{
	drawText(pDC, pBack, 0, NVBorderMarginX, NVBorderMarginY, NVBackColor);
}

void NVCore::drawTextDX(CDC *pDC, CBitmap *pBack, NovelViewerD3DX* nvD3DX)
{
	drawText(pDC, pBack, nvD3DX, NVBorderMarginX, NVBorderMarginY, NVBackColor);
}

// CDC와 Bitmap은 Create~에서 Object연동과정까지 끝나있어야함!
void NVCore::drawText(CDC *pDC, CBitmap *pBack, NovelViewerD3DX* nvD3DX, int x, int y, int backClr)
{
	// use DirectX?
	if (nvD3DX) {
		nvD3DX->RenderStart();
		_nvD3DX = nvD3DX;
	} else {
		_nvD3DX = NULL;
	}

	if (backClr >= 0) {	// when uses clr
		CRect bgRect;	bgRect.SetRect(0,0,scr_wid, scr_hei);
		pDC->FillRect(bgRect, &bgBrush);
	}

	if (wcslen(fpath)==0) return;

	pDC->SelectObject(&font);
	pDC->SetBkMode( TRANSPARENT );
	pDC->SetTextColor(NVfontColor);

	CSize size;


	if (off_x != 0) procOffsetX(pDC);
	else if (off_y != 0) procOffsetY(pDC);

	int npos = nowPos;
	if (bpreview >= 0) npos = previewPos;	// is preview mode?

	int drawMore = 0;
	for (int i=0; i<NVPageCnt+drawMore; i++) {
		// start drawing till (scr_wid, scr_hei)
		// except : padding
		int ghei = scr_hei - 2*NVBorderMarginY - btmMargin*(NVScrolltype != 1); // 세로스크롤일때는 화면 끝까지 그리기
		int gwid = (float)(scr_wid - 2*NVBorderMarginX - NVPageMargin*(NVPageCnt-1)) / NVPageCnt + 0.5f;	// 소수점 위로 올려야 하는데.
		int wid, hei, offx, offy;
		wid=hei=0;

		offx = NVBorderMarginX + gwid*i+ NVPageMargin*i;
		offy = NVBorderMarginY;
		offy += off_y;
		offx += off_x;

		int k = (ghei + NVfontLineMargin) / (fontHeight + NVfontLineMargin)
			+ (NVScrolltype == 1)*2;	// 줄 수
		for (int i=0; i<k ; i++) {
			/*** exception! ***/
			if (npos > finPos) npos = finPos;
			if (npos < 0) npos = 0;

			npos += nextlineChar(pDC, npos, true, offx, offy+(fontHeight+NVfontLineMargin)*i);
		
			// off_x가 0 이하이면서 끝까지 다 그렸으면, 뒤부분에 추가적으로 한번 더 그려주기
			if (off_x < 0 && i==k-1 && offx <= NVBorderMarginX) {
				drawMore=NVPageCnt;
			}
		}


		// 북마크 체크 부분
		isBookmark = false;
		int _bm;

		for (_bm = 0; _bm<bmarkcnt; _bm++) {
			if (bpreview<0/*preview undelable*/ && nowPos <= bmark[_bm] && bmark[_bm] < npos)
				isBookmark=true;
		}
		// 왼쪽의 북마크들 그리기
		for (_bm=0; _bm<bmarkcnt; _bm++)
		{
			int cal = (float)bmark[_bm] / (float)finPos * scr_hei;
			CRect r;
			r.SetRect(0, cal, ((_bm==bpreview)?30:10), cal+3);
			if (npoint.x<30) {
				if (nvD3DX)
					nvD3DX->RenderRect((RECT)r, NVBmColor);
				else
					pDC->FillRect(&r, &bBrush);
			}
		}
	}

	if (isBookmark)
	{
		if (nvD3DX) {
			CRect r;
			r.SetRect(scr_wid-10, 10, scr_wid+10, 80);
			nvD3DX->RenderRect((RECT)r, NVBmColor);
		} else {
			CRgn brgn;
			brgn.CreateRoundRectRgn(scr_wid-10, 10, scr_wid+10, 80, 5, 5);
			pDC->FillRgn(&brgn, &bBrush);
		}
		
	} 

	// 가로스크롤모드일때만 퍼센트 표시
	if (NVScrolltype != 1) {
		pDC->SelectObject(&ifont);
		float percentage = (float)((bpreview>=0)?previewPos:nowPos) / (float)finPos * 100;
		CString cTitle;	cTitle.Format(L"%s, %.2f%%", fname, percentage);
		CRect r;	r.SetRect(0,scr_hei-15,scr_wid,scr_hei);
		if (nvD3DX)
			nvD3DX->RenderText(nvD3DX->g_pStatusFont, &r, cTitle.GetBuffer(0), DT_VCENTER || DT_BOTTOM);
		else
			pDC->DrawText(cTitle, r, DT_VCENTER || DT_BOTTOM);
	}

	setParentTitle();

	if (nvD3DX) nvD3DX->RenderEnd();
}

void NVCore::procOffsetX(CDC *pDC)
{
	// 최적화 조건
	if (nowPos == 0 && off_x > 0)
		off_x = 0;
	if (off_x <= 0 && off_x > -(scr_wid-NVBorderMarginX)) return;


	/*off_x 처리...*/
	CSize size;
	int wid, hei, offx, offy;
	wid=hei=0;
	int npos = nowPos;

	offx = NVBorderMarginX;
	offy = NVBorderMarginY;

	// 양수면 이전 페이지를 보여주도록 함 (음수로 만든다)
	while (off_x > 0) {
		for (int i=0; i<NVPageCnt;i ++)
			npos -= prevpageChar(pDC, npos);
		off_x -= scr_wid - NVBorderMarginX;
	}


	// 음수면 너무 큰 값이 되지 않도록 조절
	const int scr = scr_wid - NVBorderMarginX;
	while (off_x < 0)
	{
		if (-off_x < scr)
		{
			break;
		}

		for (int i=0; i<NVPageCnt;i ++)
			npos += nextpageChar(pDC, npos);
		off_x += scr;
	}

	nowPos = npos;
	if (nowPos > finPos) nowPos = finPos;
	if (nowPos < 0) nowPos = 0;
}

void NVCore::procOffsetY(CDC *pDC)
{
	// 최적화 조건
	if (off_y > 0 && nowPos == 0)
		off_y = 0;
	if (nowPos >= finPos && off_y < 0)
		off_y = 0;
	if (off_y == 0) return;


	/*off_y 처리...*/
	int ghei = scr_hei - 2*NVBorderMarginY - btmMargin*(NVScrolltype != 1);
	int hei=0;
	int npos = nowPos;
	int v = fontHeight + NVfontLineMargin;

	// off_y가 양수(밑으로)면 음수(0<=)가 될 때까지 앞쪽 줄로 이동시킨다.
	while (off_y > 0) {
		npos -= prevlineChar(pDC, npos);
		off_y -= v;
	}
	
	// off_y가 음수(위로)면 너무 값이 크지 않도록 조절.
	while (off_y < 0) {
		// 굳이 올릴 필요가 없을 정도의 off_y면 루틴을 돌리지 않는다.
		if (-off_y < v)
		{
			break;
		}
		npos += nextlineChar(pDC, npos);
		off_y += v;
	}

	nowPos = npos;
}

double NVCore::movePosX(int p)
{
	off_x+=p;

	// 원래는 퍼센트 계산 후 리턴..
	return 0;
}

double NVCore::movePosY(int p)
{
	off_y+=p;

	// 원래는 퍼센트 계산 후 리턴..
	return 0;
}

void NVCore::searchfile(bool prev)
{
	// find number
	int slen = wcslen(fpath);
	if (slen <= 0) return;

	int nn = 1;
	int ns = 0;
	int ncnt=0;
	for (int i=slen-1 ; i>=0; i--) {
		if (fpath[i] >= '0' && fpath[i] <= '9') {
			ns += (fpath[i]-'0')*nn, nn*=10, ncnt++;
		} else {
			if (nn > 1)
			{
				// check for next file
				FILE *fp;
				TCHAR nPath[255];
				wcscpy(nPath, fpath);
				if (prev && ns > 0) ns--; else ns++;
				char num[20];
				itoa(ns, num, 10);
				for (int j=strlen(num); j>0; j--)
					nPath[i+ncnt-1+j] = num[j-1];
				fp = _wfopen(nPath, L"r");
				if (fp) {
					fclose(fp);
					readTxtFile(nPath);
					if (prev) nowPos = finPos;
					else nowPos = 0;
					return;
				}
			}

			nn=1;
			ns=0;
			ncnt=0;
		}
	}

	// cannot find file!
}

void NVCore::setParenthWnd(HWND h)
{
	if (!IsWindow(h)) return;
	mainWnd = h;
	GetWindowText(h, orgTitle, 255);
}

void NVCore::setParentTitle()
{
	if (!IsWindow(mainWnd)) return;
	CString buf;
	if (isOpened)
		buf.Format(L"%s, %.2f%% - %s", fname, (float)nowPos / (float)finPos * 100, orgTitle);
	else
		buf.Format (L"%s", orgTitle);
	SetWindowText(mainWnd, buf.GetBuffer(0));
}

bool _bmarkcomp(int x, int y)
{
	if (x>y) return 1;
	else return 0;
}

int NVCore::OnLbtndown(CPoint x)
{
	isPressing = true;
	return 0;
}

int NVCore::OnLbtnup(CPoint x)
{
	// bookmark move!
	if (bpreview >= 0) {
		nowPos = previewPos;
	}

	isPressing = false;
	return 0;
}

int NVCore::OnMousemove(CPoint x)
{
	// check mouse point (bookmark)
	for (int i=0; i<bmarkcnt; i++) {
		int cal = (float)bmark[i] / (float)finPos * scr_hei;
		if (x.x < 30 && cal-2 <= x.y && x.y <= cal+5) {
			int t = bpreview;
			bpreview = i;
			previewPos = bmark[i];
			if (t < 0)
				InvalidateRect(mainWnd, NULL, FALSE);

			return 0;
		}
	}

	if (bpreview >= 0) InvalidateRect(mainWnd, NULL, FALSE);
	bpreview = -1;

	if ((x.x<30&&npoint.x>=30) || (x.x>30&&npoint.x<=30)) InvalidateRect(mainWnd, NULL, FALSE);

	npoint = x;

	return 0;
}

int NVCore::OnRbtndown(CPoint x)
{
	return 0;
}

int NVCore::OnRbtnup(CPoint x)
{
	// add/remove bookmark
	std::sort(bmark, bmark+bmarkcnt, _bmarkcomp);


	if (isBookmark) {
		for (int i=bmarkcnt-1; i>=0; i--)
			if (bmark[i] >= nowPos) {
				bmark[i] = 0;
				std::sort(bmark, bmark+bmarkcnt, _bmarkcomp);
				bmarkcnt--;
				break;
			}
	} else if (bpreview<0/*nopreview*/) {
		if (	bmarkcnt >= BOOKMARKMAX)
			return -1;

		bmark[bmarkcnt] = nowPos;
		std::sort(bmark, bmark+bmarkcnt, _bmarkcomp);
		bmarkcnt++;
	}

	InvalidateRect(mainWnd, NULL, FALSE);
	return 0;
}

int NVCore::nextlineChar(CDC *pDC, int sPos, bool print, int x, int y)
{
	CSize size;
	int gwid = (float)(scr_wid - 2*NVBorderMarginX - NVPageMargin*(NVPageCnt-1)) / NVPageCnt + 0.5f;
	int wid=0;
	int npos = sPos;
	TCHAR buf[10];

	if (npos > finPos || npos < 0) return 0;


	if (fileText[npos] == L'\n') {	/* 다음줄로*/
		wid = NVfontLineIndent;
		npos ++;
		while (NVEmptylineIgnore && fileText[npos] == L'\n' && npos < finPos) npos++;
	}

	while (fileText[npos] != L'\n' && npos < finPos)
	{
		int _p = npos;
		if (fileText[npos] < 0)
			memcpy(buf, fileText+npos, 2*2), buf[2]=L'\0', npos+=2;
		else
			memcpy(buf, fileText+npos, 1*2), buf[1]=L'\0', npos++;
		int size = getfontWidth(pDC, buf[0]);

		// 화면보다 더 그린 글자가 크면 exit
		if (wid > gwid - size)
		{
			npos = _p;
			break;
		}


		if (print && (x+wid+size>=0 && x+wid<=scr_wid)) {
			if (!_nvD3DX)
				pDC->TextOut(x+wid, y, buf);
			else
				_nvD3DX->RenderText(x+wid, y, buf);
		}
		wid += size + NVfontTextMargin;
	}

	return (npos - sPos);
}

int NVCore::prevlineChar(CDC *pDC, int sPos)
{
	CSize size;
	int gwid = (float)(scr_wid - 2*NVBorderMarginX - NVPageMargin*(NVPageCnt-1)) / NVPageCnt + 0.5f;
	int wid=0;
	int npos = sPos;
	TCHAR buf[10];

	if (npos > finPos || npos < 0) return 0;

	// 줄처리는 구조상의 한계로 어쩔 수 없음!
	if (fileText[npos] == L'\n') {
		npos --;
		while (NVEmptylineIgnore && fileText[npos] == L'\n' && npos > 0) npos--;
		if (npos < 0) {
			npos = 0;
		}
		wid=NVfontLineIndent;
	}

	while (fileText[npos] != L'\n' && npos > 0)
	{
		int _p = npos;
		npos--;
		if (npos > 0 && fileText[npos-1] < 0 && fileText[npos] < 0)
			memcpy(buf, fileText+npos-1, 2*2), buf[2]=L'\0', npos--;
		else
			memcpy(buf, fileText+npos, 1*2), buf[1]=L'\0';
		int size = getfontWidth(pDC, buf[0]);
		
		if (wid > gwid - size)
		{
			npos = _p;
			break;
		}
		
		wid += size + NVfontTextMargin;
	}

	return (sPos - npos);
}

int NVCore::nextpageChar(CDC *pDC, int sPos)
{
	int r=sPos;
	int ghei = scr_hei - 2*NVBorderMarginY - btmMargin*(NVScrolltype != 1);
	int k = (ghei+NVfontLineMargin) / (NVfontLineMargin+fontHeight);
	for (int i=0; i<k; i++)
		r += nextlineChar(pDC, r);
	return (r - sPos);
}

int NVCore::prevpageChar(CDC *pDC, int sPos)
{
	int r=sPos;
	int ghei = scr_hei - 2*NVBorderMarginY - btmMargin*(NVScrolltype != 1);
	int k = (ghei+NVfontLineMargin) / (NVfontLineMargin+fontHeight);
	for (int i=0; i<k; i++)
		r -= prevlineChar(pDC, r);
	return (sPos - r);
}

int NVCore::searchText(TCHAR *p, int s, int e)
{
	int len = wcslen(p);
	if (len == 0 || len > finPos || len > e-s) return -1;
	for (int i=s; i<finPos-len && i<e-len; i++)
		if (memcmp(fileData+i, p, len) == 0)
			return i;
	return -1;
}

void NVCore::initfontWidth()
{
	initfontWidth(0, 256*256-1, 0);
}

void NVCore::initfontWidth(int s, int e, int val)
{
	for (int i=s; i<=e; i++) {
		fontWidth[i] = val;
	}
}

int NVCore::getfontWidth(CDC *pDC, TCHAR wchar) {
	int n = (int)wchar;

	// http://blog.arzz.com/401
	if (fontWidth[n] == 0) {
		int wid = pDC->GetTextExtent(wchar).cx;
		if (n >= 44032 && n <= 55203) {
			initfontWidth(44032, 55203, wid);
		} else {
			fontWidth[n] = wid;
		}
	}

	return fontWidth[n];
}