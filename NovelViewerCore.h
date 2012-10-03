#define MAX 65535
#define PATHMAX 255
#define BOOKMARKMAX 50

#include "NovelViewerD3DX.h"

struct _RECENT {
	TCHAR fname[PATHMAX];
	int pos;
	int cnt;
	int bmcnt;
	int bm[BOOKMARKMAX];		// bookmark
};

class NVCore {
public:
	NVCore();
	~NVCore();
	bool readPref(bool initalize=true);
	bool writePref();
	bool readTxtPref(TCHAR *fn, int *p);
	bool writeTxtPref(TCHAR *fn, int *p);
	bool writeTxtPref();

	bool readTxtFile(TCHAR *fn);
	bool writeTxtFile(TCHAR *fn);
	bool releaseTxtFile();

	int getTxtdata(TCHAR *p, int sPos, int len);
	int setTxtdata(TCHAR *p, int sPos, int len);

	int nextlineChar(CDC *pDC, int sPos, bool print=false, int x=0, int y=0); 
	int prevlineChar(CDC *pDC, int sPos); 
	int nextpageChar(CDC *pDC, int sPos); 
	int prevpageChar(CDC *pDC, int sPos); 
	double movePosX(int p);
	double movePosY(int p);

	void drawText(CDC *pDC, CBitmap *pBack);
	void drawText(CDC *pDC, CBitmap *pBack, NovelViewerD3DX* nvD3DX, int x, int y, int backClr=-1);
	void drawTextDX(CDC *pDC, CBitmap *pBack, NovelViewerD3DX* nvD3DX);
	void procOffsetX(CDC *pDC);
	void procOffsetY(CDC *pDC);

	// 파일의 끝까지 읽어들이지 않는 방식의 다이나믹 로드 방식을 쓴다
	// 파일 현재 크기 / 파일 전체 크기
	int nowPos;
	int finPos;
	int scr_wid;
	int scr_hei;
	int scr_x, scr_y;
	
	TCHAR NVfont[255];
	int NVfontSize;
	int NVfontTextMargin;
	int NVfontLineMargin;
	int NVfontLineIndent;
	bool NVEmptylineIgnore;
	int NVfontColor;
	int NVBmColor;

	int NVBorderMarginX;
	int NVBorderMarginY;
	int NVOpacity;
	bool NVFullScreen;
	int NVBackColor;
	int NVSmoothScroll;
	int NVScrolltype;
	int NVlfQuality;
	int NVfontBold;
	int NVPageMargin;
	int NVPageCnt;
	bool NVUseDirectX;
	TCHAR recentPath[PATHMAX];

	void createFontObject();
private:
	CFont font;
	CFont ifont;
	CBrush bgBrush;	
	CBrush bBrush;
	void defaultSetting();

	// 파일 전체 텍스트 갈무리
	char *fileData;
	TCHAR *fileText;
	bool isOpened;
	TCHAR currDir[255];

public:
	void searchfile(bool prev);
	int fontHeight;
	int btmMargin;

	TCHAR fpath[PATHMAX];
	TCHAR fname[255];
	int off_x;
	int off_y;


private:
	// bookmark
	int bmarkcnt;
	int bmark[BOOKMARKMAX];

	int previewPos;
	int bpreview;

	NovelViewerD3DX *_nvD3DX;

public:
	// event part
	int OnMousemove(CPoint x);
	int OnLbtndown(CPoint x);
	int OnLbtnup(CPoint x);
	int OnRbtnup(CPoint x);
	int OnRbtndown(CPoint x);

	bool isPressing;
	bool isBookmark;

	CPoint npoint;

public:
	HWND mainWnd;
	TCHAR orgTitle[255];
	void setParenthWnd(HWND h);
	void setParentTitle();
	int searchText(TCHAR *p, int s, int e);
	
	void initfontWidth();
private:
	int fontWidth[256*256];
	void initfontWidth(int s, int e, int val);
	int getfontWidth(CDC *pDC, TCHAR wchar);
};
