#pragma once
#include "D3DGraphics.h"
#include "Component.h"

enum PRIMITIVEMESH
{
	PM_MESH = -1,
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
	void LoadPrimitive(const PRIMITIVEMESH meshtype,const CUSTOMVERTEX* PRM,
		const short* PRMIB,const UINT PRM_SIZE,
		const UINT PRMIB_SIZE);

	void FreeGFX();
	void RestoreGFX();

	void InitMaterial();
	void InitMesh();

	void Update();
	void Render(D3DGraphics& gfx);

	//INLINE

	PRIMITIVEMESH GetMeshType(){ return meshType; }
	LPDIRECT3DVERTEXBUFFER9 GetVB(){ return vb; }
	LPDIRECT3DINDEXBUFFER9 GetIB(){ return ib; }
	int GetNVerts(){ return nVerts; }
	int GetNTris(){ return nTris; }
	D3DMATERIAL9* GetMaterial(){ return &mat; }

private:
	CUSTOMVERTEX* vertexBuffer;
	short* indexBuffer;

	D3DMATERIAL9			mat;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9	ib;

	PRIMITIVEMESH meshType;

	int nVerts;
	int nTris;
	UINT vb_size;
	UINT ib_size;

	D3DGraphics& gfx;
};