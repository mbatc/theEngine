#include "D3DGraphics.h"
#include <assert.h>

D3DGraphics::D3DGraphics(HWND hwnd, UINT w_width, UINT w_height)
	:
	pDevice(NULL),
	pDirect3D(NULL),
	width(w_width),
	height(w_height)
{
	HRESULT result;
	
	pDirect3D = Direct3DCreate9(D3D_SDK_VERSION);
	assert(pDirect3D != NULL);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferHeight = w_height;
	d3dpp.BackBufferWidth = w_width;
	d3dpp.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_ONE;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	
	result = pDirect3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hwnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &d3dpp, &pDevice);
	assert(!FAILED(result));

	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, FALSE);
	pDevice->SetRenderState(D3DRS_AMBIENT, D3DCOLOR_XRGB(50, 50, 50));
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
}

D3DGraphics::~D3DGraphics()
{
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pDirect3D)
	{
		pDirect3D->Release();
		pDirect3D = NULL;
	}
}

BOOL D3DGraphics::BeginFrame()
{
	HRESULT result;

	result = pDevice->Clear(0, NULL, D3DCLEAR_TARGET, 0xFF333366, 1.0f, 0);
	assert(!FAILED(result));
	result = pDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0xFF333366, 1.0f, 0);
	assert(!FAILED(result));

	result = pDevice->BeginScene();
	assert(!FAILED(result));

	return TRUE;
}

BOOL D3DGraphics::EndFrame()
{
	HRESULT result;

	result = pDevice->EndScene();
	assert(!FAILED(result));	
	result = pDevice->Present(NULL, NULL, NULL, NULL);
	assert(!FAILED(result));

	return TRUE;
}

