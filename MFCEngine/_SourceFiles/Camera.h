#pragma once
#include "Gameobject.h"
#include "D3DGraphics.h"

class Camera : public Gameobject
{
public:
	Camera();
	~Camera(); 

	void Update();
	void Render(D3DGraphics& gfx) const;

	void Move(float speed, Vector3 axis );

private:
	Vector3 LookAt;
	int LookAtDist;
};