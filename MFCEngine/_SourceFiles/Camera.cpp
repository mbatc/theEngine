#include "GlobalPointers.h"
#include "Camera.h"
#include "Component.h"

#define _USE_MATH_DEFINES
#include <math.h>

Camera::Camera()
	:
	Gameobject()
{
	LookAtDist = -10;

	if (type)
		delete type;
	type = new char[7];
	char name[] = { "CAMERA" };
	for (int i = 0; i < 7; i++)
	{
		type[i] = name[i];
	}

	transform->SetTranslation(0.0f, 0.0f, 10.0f);
	LookAt.x = 0.0f;
	LookAt.y = 0.0f;
	LookAt.z = 0.0f;
}

Camera::~Camera()
{}

void Camera::Render(D3DGraphics& gfx) const
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(transform->GetTranslation().x,
		transform->GetTranslation().y,
		transform->GetTranslation().z),
		&D3DXVECTOR3(LookAt.x,LookAt.y,LookAt.z),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	gfx.GetDevice()->SetTransform(D3DTS_VIEW, &matView);

	float aspect = (float)gfx.GetWidth() / (float)gfx.GetHeight();

	D3DXMATRIX matProjection;
	D3DXMatrixPerspectiveFovLH(&matProjection, D3DXToRadian(60),
		aspect, 0.1f,1000.0f);
	gfx.GetDevice()->SetTransform(D3DTS_PROJECTION, &matProjection);
}

void Camera::Update()
{
	for (int i = 0; i < nComponents; i++)
	{
		componentsList[i].component->Update();
	}

	float x = 0;
	float z = 0;
	float y = 0;

	float yRot = 0;
	float xRot = 0;
	float moveSpeed = 0;

	if (kbd->KeyIsDown(VK_UP))
	{
		if (kbd->KeyIsDown(VK_SHIFT))
		{
			y += 0.1f;
		}
		else if ( kbd->KeyIsDown(VK_CONTROL) )
		{
			xRot -= 0.5f;
		}
		else
		{
			moveSpeed += 0.01f;
		}
	}
	if (kbd->KeyIsDown(VK_DOWN))
	{
		if (kbd->KeyIsDown(VK_SHIFT))
		{
			y -= 0.1f;
		}
		else if (kbd->KeyIsDown(VK_CONTROL))
		{
			xRot += 0.5f;
		}
		else
		{
			moveSpeed -= 0.01f;
		}
	}
	if (kbd->KeyIsDown(VK_LEFT))
	{
		if (kbd->KeyIsDown(VK_SHIFT))
		{
			yRot -= 0.5f;
		}
		else
		{
			x += 0.1f;
		}
	}
	if (kbd->KeyIsDown(VK_RIGHT))
	{
		if (kbd->KeyIsDown(VK_SHIFT))
		{
			yRot += 0.5f;
		}
		else
		{
			x -= 0.1f;
		}
	}

/*
	if (mouse->isLeftMBDown())
	{
		z -= mouse->GetMouseY() - mouse->GetPreviousMouseY();
	}*/
	
	transform->SetTranslation(transform->GetTranslation().x + x,
		transform->GetTranslation().y + y,
		transform->GetTranslation().z + z);
	transform->SetRotation(transform->GetRotation().x + xRot,
		transform->GetRotation().y + yRot,
		transform->GetRotation().z);
	Vector3 axis;
	axis.x = 1.0f;
	axis.z = 1.0f;
	axis.y = 0.0f;
	Move(moveSpeed, axis);


	LookAt.x = transform->GetTranslation().x + LookAtDist * sin(transform->GetRotation().y * M_PI / 180);

	LookAt.y = transform->GetTranslation().y + LookAtDist * sin(transform->GetRotation().x * M_PI / 180);

	LookAt.z = transform->GetTranslation().z + LookAtDist * cos(transform->GetRotation().y * M_PI / 180);
}	

void Camera::Move(float Speed, Vector3 axis)
{
	float x, y, z;
	x = LookAt.x;
	y = LookAt.y;
	z = LookAt.z;

	x -= transform->GetTranslation().x;
	y -= transform->GetTranslation().y;
	z -= transform->GetTranslation().z;

	x *= Speed * axis.x;
	y *= Speed * axis.y;
	z *= Speed * axis.z;

	transform->SetTranslation(transform->GetTranslation().x + x,
		transform->GetTranslation().y + y,
		transform->GetTranslation().z + z);
}