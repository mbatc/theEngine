#include "Transform.h"
#include <Windows.h>

Transform::Transform()
{
	ZeroMemory(&Translation, sizeof(Vector3));
	ZeroMemory(&Rotation, sizeof(Vector3));
	ZeroMemory(&Scale, sizeof(Vector3));
}