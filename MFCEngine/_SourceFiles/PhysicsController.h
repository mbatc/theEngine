#pragma once

#include "Vector.h"
#include "Component.h"

struct Collision
{
	bool col;
	Vector colDir;
	Vector3 colPoint;
};

class PhysicsController : public Component
{
public:
	PhysicsController(Gameobject* parent);
	~PhysicsController();
private:
	void Update();
	void Render(D3DGraphics& gfx);

	void SetMeshCollider(/*Collider* colMesh*/);

	Vector rotation;
	Vector movement;

	Collision colInfo;
};