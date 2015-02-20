#include "Transform.h"
#include <Windows.h>

Transform::Transform()
{
	ZeroMemory(&Translation, sizeof(Vector3));
	ZeroMemory(&Rotation, sizeof(Vector3));
	Scale.x = 1;
	Scale.y = 1;
	Scale.z = 1; 
}

void Transform::Update()
{
	if (Rotation.x > 360.0f)
	{
		int rotMult = Rotation.x / 360.0f;
		Rotation.x -= 360.0f * rotMult;
	}
	if (Rotation.y > 360.0f)
	{
		int rotMult = Rotation.y / 360.0f;
		Rotation.y -= 360.0f * rotMult;
	}
	if (Rotation.z > 360.0f)
	{
		int rotMult = Rotation.z / 360.0f;
		Rotation.z -= 360.0f * rotMult;
	}
}