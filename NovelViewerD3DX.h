#pragma once

struct TLVERTEX
{
        float x;
        float y;
        float z;
        float rhw;
        D3DCOLOR colour;
        float u;
        float v;
};

class NovelViewerD3DX {
public:
	NovelViewerD3DX();
	~NovelViewerD3DX();

	int InitalizeDevice(HWND hWnd);
	int ReleaseDevice();
	int OnResize();
	int RenderText(int x, int y, TCHAR *ch);
	int RenderText(ID3DXFont* fntObj, RECT *r, TCHAR *ch, int option);
	int RenderRect(RECT r, int clr);
	int RenderStart();
	int RenderEnd();

	void SetFont(TCHAR *fontName, int size, int fntClr, int bgClr);
	int UINTToD3DXClr(int clr);
	BOOL isInitalized();
private:
	BOOL isD3DXInitalized;
	HWND m_hWnd;
	
	ID3DXFont*     g_pFont;
	IDirect3D9*		pd3d9;
	IDirect3DDevice9* pd3dDevice;
	IDirect3DSurface9* BackBuff; 
	ID3DXSprite*     g_pRect;

	TCHAR _fntName[256];
	int _fntSize;
	int _fntClr;
	int _bgClr;
public:
	ID3DXFont*     g_pStatusFont;
};