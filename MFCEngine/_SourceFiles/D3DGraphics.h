#pragma once

#include <d3dx9.h>
#include <d3d.h>

#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")

#define CUSTOMFVF (D3DFVF_XYZ | D3DFVF_NORMAL )

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	D3DVECTOR NORMAL;
};

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