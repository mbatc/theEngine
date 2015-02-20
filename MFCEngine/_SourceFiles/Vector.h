#pragma once
#include "Transform.h"

class Vector
{
public:
	Vector();
	~Vector();

private:
	float Velocity;
	float RotationSpeed;

	Vector3 RotatioScalar;
	Vector3 VelocityDir;
};