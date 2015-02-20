#pragma once
#include "Component.h"
#include "D3DGraphics.h"

class Mesh;

class MeshRenderer : public Component
{
public:
	MeshRenderer(Gameobject* object)
		:
		Component(object),
		mesh(NULL),
		meshID( -1 )
	{
		m_type = CT_GFX; m_pCompIdentifier = CTYPE_MESHRENDERER;m_pName = new char[14];m_pName = { "Mesh Renderer" };
	}
	~MeshRenderer();

	int GetMeshID(){ return meshID; }

	void Render(D3DGraphics& gfx);
	void SetMeshPointer(Mesh* newMesh, int ID);

	void FreeGFX();
	void RestoreGFX();
private:
	int meshID;
	Mesh* mesh;
};