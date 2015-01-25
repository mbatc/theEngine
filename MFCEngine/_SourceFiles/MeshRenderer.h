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
		mesh(NULL)
	{m_type = CT_GFX;}
	~MeshRenderer();

	void Render(D3DGraphics& gfx);
	void SetMeshPointer(Mesh* newMesh);
private:
	Mesh* mesh;
};