#include "StdAfx.h"
#include "NovelViewerD3DX.h"

NovelViewerD3DX::NovelViewerD3DX()
{
	isD3DXInitalized = FALSE;
}

NovelViewerD3DX::~NovelViewerD3DX()
{
}

int NovelViewerD3DX::OnResize() {
	if (!isInitalized()) return FALSE;
	isD3DXInitalized = FALSE;
	
	BackBuff->Release();
	g_pFont->Release();
	g_pStatusFont->Release();
	
	D3DFORMAT format=D3DFMT_R5G6B5; //For simplicity we'll hard-code this for now.
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp,sizeof(D3DPRESENT_PARAMETERS));
	pp.BackBufferCount= 1;  //We only need a single back buffer
	pp.MultiSampleType=D3DMULTISAMPLE_NONE; //No multi-sampling
	pp.MultiSampleQuality=0;                //No multi-sampling
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // Throw away previous frames, we don't need them
	pp.hDeviceWindow=m_hWnd;  //This is our main (and only) window
	pp.Windowed = TRUE;
	pp.Flags=0;            //No flags to set
	pp.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT; //Default Refresh Rate
	pp.PresentationInterval=D3DPRESENT_INTERVAL_DEFAULT;   //Default Presentation rate
	pp.BackBufferFormat=format;      //Display format
	pp.EnableAutoDepthStencil=FALSE; //No depth/stencil buffer
	pd3dDevice->Reset(&pp);

	CRect r;
	GetWindowRect(m_hWnd, &r);
	pd3dDevice->CreateOffscreenPlainSurface(r.Width(), r.Height(), D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &BackBuff, NULL);
	
    D3DXCreateFont( pd3dDevice,            // D3D device
                         _fntSize,               // Height
                         0,                     // Width
                         FW_NORMAL,               // Weight
                         1,                     // MipLevels, 0 = autogen mipmaps
                         FALSE,                 // Italic
                         DEFAULT_CHARSET,       // CharSet
                         OUT_DEFAULT_PRECIS,    // OutputPrecision
                         ANTIALIASED_QUALITY,       // Quality
                         DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
                         _fntName,              // pFaceName
                         &g_pFont);              // ppFont
    D3DXCreateFont( pd3dDevice,            // D3D device
                         10,               // Height
                         0,                     // Width
                         FW_NORMAL,               // Weight
                         1,                     // MipLevels, 0 = autogen mipmaps
                         FALSE,                 // Italic
                         DEFAULT_CHARSET,       // CharSet
                         OUT_DEFAULT_PRECIS,    // OutputPrecision
                         ANTIALIASED_QUALITY,       // Quality
                         DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
                         L"Arial",              // pFaceName
                         &g_pStatusFont);              // ppFont

	isD3DXInitalized = TRUE;
	return TRUE;
}

int NovelViewerD3DX::InitalizeDevice(HWND hWnd) {
	if (isInitalized()) return TRUE;

	m_hWnd = hWnd;
	HRESULT hr;

	// IDirect9 Initalize
	pd3d9 = Direct3DCreate9(D3D_SDK_VERSION);
	if (!pd3d9) return FALSE;

	// IDirectx9 Device Initalize
	D3DFORMAT format=D3DFMT_R5G6B5; //For simplicity we'll hard-code this for now.
	D3DPRESENT_PARAMETERS pp;
	ZeroMemory(&pp,sizeof(D3DPRESENT_PARAMETERS));
	pp.BackBufferCount= 1;  //We only need a single back buffer
	pp.MultiSampleType=D3DMULTISAMPLE_NONE; //No multi-sampling
	pp.MultiSampleQuality=0;                //No multi-sampling
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;  // Throw away previous frames, we don't need them
	pp.hDeviceWindow=hWnd;  //This is our main (and only) window
	pp.Windowed = TRUE;
	pp.Flags=0;            //No flags to set
	pp.FullScreen_RefreshRateInHz=D3DPRESENT_RATE_DEFAULT; //Default Refresh Rate
	pp.PresentationInterval=D3DPRESENT_INTERVAL_DEFAULT;   //Default Presentation rate
	pp.BackBufferFormat=format;      //Display format
	pp.EnableAutoDepthStencil=FALSE; //No depth/stencil buffer


	hr = pd3d9->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&pp,
		&pd3dDevice);
	if (FAILED(hr)) return FALSE;

	CRect r;
	GetWindowRect(hWnd, &r);
	pd3dDevice->CreateOffscreenPlainSurface(r.Width(), r.Height(), D3DFMT_A8R8G8B8, D3DPOOL_DEFAULT, &BackBuff, NULL);

    hr = D3DXCreateFont( pd3dDevice,            // D3D device
                         _fntSize,               // Height
                         0,                     // Width
                         FW_NORMAL,               // Weight
                         1,                     // MipLevels, 0 = autogen mipmaps
                         FALSE,                 // Italic
                         DEFAULT_CHARSET,       // CharSet
                         OUT_DEFAULT_PRECIS,    // OutputPrecision
                         ANTIALIASED_QUALITY,       // Quality
                         DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
                         _fntName,              // pFaceName
                         &g_pFont);              // ppFont
    D3DXCreateFont( pd3dDevice,            // D3D device
                         10,               // Height
                         0,                     // Width
                         FW_NORMAL,               // Weight
                         1,                     // MipLevels, 0 = autogen mipmaps
                         FALSE,                 // Italic
                         DEFAULT_CHARSET,       // CharSet
                         OUT_DEFAULT_PRECIS,    // OutputPrecision
                         ANTIALIASED_QUALITY,       // Quality
                         DEFAULT_PITCH | FF_DONTCARE, // PitchAndFamily
                         L"Arial",              // pFaceName
                         &g_pStatusFont);              // ppFont
	if (FAILED(hr)) return FALSE;

	isD3DXInitalized = TRUE;
	return TRUE;
}

int NovelViewerD3DX::ReleaseDevice() {
	if (!isInitalized()) return FALSE;
	isD3DXInitalized = FALSE;
	
	BackBuff->Release();
	g_pFont->Release();
	g_pStatusFont->Release();
	pd3dDevice->Release();
	pd3d9->Release();

	return TRUE;
}

BOOL NovelViewerD3DX::isInitalized()
{
	return isD3DXInitalized;
}

int NovelViewerD3DX::RenderStart() {
	pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET, _bgClr, 1.0f, 0L );
    if( SUCCEEDED( pd3dDevice->BeginScene() ) )
	{
		return TRUE;
	}
	return FALSE;
}

int NovelViewerD3DX::RenderText(int x, int y, TCHAR *ch) {
	RECT rc;
	SetRect(&rc, x, y, 0, 0 );        
	return RenderText(g_pFont, &rc, ch, DT_NOCLIP);
}

int NovelViewerD3DX::RenderText(ID3DXFont* fntObj, RECT *r, TCHAR *ch, int option) {
	fntObj->DrawText( NULL, ch, -1, r, option, _fntClr);
	return TRUE;
}

int NovelViewerD3DX::RenderEnd() {
	pd3dDevice->EndScene();
	pd3dDevice->Present(0, 0, 0, 0);
	return TRUE;
}

void NovelViewerD3DX::SetFont(TCHAR *fontName, int size, int fntClr, int bgClr) {
	wcscpy(_fntName, fontName);
	_fntSize = size;
	_fntClr = UINTToD3DXClr(fntClr);
	_bgClr = UINTToD3DXClr(bgClr);
}

int NovelViewerD3DX::UINTToD3DXClr(int clr) {
	int r = (clr >> 16) & 0xff;
	int g = (clr >> 8) & 0xff;
	int b = clr & 0xff;
	return D3DXCOLOR((float)r/256.0f, (float)g/256.0f, (float)b/256.0f, 1.0f);
}

int NovelViewerD3DX::RenderRect(RECT r, int clr)
{
    pd3dDevice->Clear( 1, (D3DRECT *)&r, D3DCLEAR_TARGET,
            UINTToD3DXClr(clr), 1.0f, 0);
	return TRUE;
}