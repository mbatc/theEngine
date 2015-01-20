#pragma once
#include "D3DGraphics.h"
#include "Component.h"

enum PRIMITIVEMESH
{
	PM_CUBE,
	PM_PLANE,
	PM_SPHERE,
	PM_CYLINDER
};

class Mesh : public Component
{
public:
	Mesh();
	~Mesh();

	//METHODS
	void LoadFromFile(const char* filename);
	void LoadPrimitice(PRIMITIVEMESH PM);

private:
	D3DMATERIAL9			mat;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9	ib;
};