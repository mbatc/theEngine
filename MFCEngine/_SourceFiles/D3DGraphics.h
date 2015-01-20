#pragma once

#include <d3d9.h>

#pragma comment(lib,"d3d9.lib")

class D3DGraphics
{
public:
	D3DGraphics(HWND hwnd, UINT w_width, UINT w_height);
	~D3DGraphics();

	//------------------------------------------
	//METHODS
	BOOL BeginFrame();
	BOOL EndFrame();

	void OnResize(int n_width, int n_height);

	//------------------------------------------
	//INLINE METHODS
	UINT GetWidth(){ return width; }
	UINT GetHeight(){ return height; }

	LPDIRECT3DDEVICE9 GetDevice(){ return pDevice; }

private:
	//------------------------------------------
	//DATA MEMBERS
	LPDIRECT3D9			pDirect3D;
	LPDIRECT3DDEVICE9	pDevice;

	UINT	width;
	UINT	height;
};