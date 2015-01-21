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