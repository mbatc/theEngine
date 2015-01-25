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
	Mesh(Gameobject* object, D3DGraphics& gfx);
	~Mesh();

	//METHODS
	void LoadFromFile(const char* filename);
	void LoadPrimitive(PRIMITIVEMESH PM);
	void InitMaterial();
	void InitMesh();

	void Update();
	void Render(D3DGraphics& gfx);

	LPDIRECT3DVERTEXBUFFER9 GetVB(){ return vb; }
	LPDIRECT3DINDEXBUFFER9 GetIB(){ return ib; }
	int GetNVerts(){ return nVerts; }
	int GetNTris(){ return nTris; }
	D3DMATERIAL9* GetMaterial(){ return &mat; }

private:
	CUSTOMVERTEX* vertexBuffer;

	D3DMATERIAL9			mat;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9	ib;

	int nVerts;
	int nTris;

	D3DGraphics& gfx;
};