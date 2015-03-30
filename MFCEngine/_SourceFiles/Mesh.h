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
private:
	//STRUCTS THAT WILL BE USEFUL FOR STORING UNFORMATTED INFORMATION
	struct vector3 {
		float x;
		float y;
		float z;
	};

	struct UV {
		float U;
		float V;
	};

	struct faceVertex {
		int vertexIndex;
		int normalIndex;
		int textureIndex;
	};

	struct faceInfo {
		UINT nPoints;
		faceVertex* point;
	};

public:
	Mesh(Gameobject* object, D3DGraphics& gfx);
	~Mesh();

	//METHODS
	void LoadFromFile(const char* filename);
	void LoadPrimitive(const PRIMITIVEMESH meshtype,const CUSTOMVERTEX* PRM,
		const short* PRMIB,const UINT PRM_SIZE,
		const UINT PRMIB_SIZE);

	faceInfo* TriangulateFaces(faceInfo* faceIndex, UINT* nFaces);

	void GetTextureFilePath(char* buffer, const int buflen) const;

	void FreeGFX();
	void RestoreGFX();

	void InitMaterial();
	void LoadTextureFromFile(char* filepath);
	void RemoveTexture();
	void InitMesh();
	void SetMaterial(D3DMATERIAL9 newMat);

	void Update();
	void Render(D3DGraphics& gfx);

	//INLINE

	PRIMITIVEMESH GetMeshType(){ return meshType; }
	LPDIRECT3DVERTEXBUFFER9 GetVB(){ return vb; }
	LPDIRECT3DINDEXBUFFER9 GetIB(){ return ib; }
	int GetNVerts(){ return nVerts; }
	int GetNTris(){ return nTris; }
	D3DMATERIAL9* GetMaterial(){ return &mat; }
	LPDIRECT3DTEXTURE9 GetTexture(){ return tex; }

private:	
	CUSTOMVERTEX* vertexBuffer;
	short* indexBuffer;

	D3DMATERIAL9			mat;
	LPDIRECT3DVERTEXBUFFER9 vb;
	LPDIRECT3DINDEXBUFFER9	ib;
	LPDIRECT3DTEXTURE9		tex;

	PRIMITIVEMESH meshType;

	int nVerts;
	int nTris;
	UINT vb_size;
	UINT ib_size;

	char* TextureFilePath;

	D3DGraphics& gfx;
};