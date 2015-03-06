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
		aspect, 1.0f, 100.0f);
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
	if (kbd->KeyIsDown(VK_UP))
	{
		if (kbd->KeyIsDown(VK_SHIFT))
		{
			y += 0.1f;
		}
		else
		{
			z -= 0.1f;
		}
	}
	if (kbd->KeyIsDown(VK_DOWN))
	{
		if (kbd->KeyIsDown(VK_SHIFT))
		{
			y -= 0.1f;
		}
		else
		{
			z += 0.1f;
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
	transform->SetRotation(transform->GetRotation().x,
		transform->GetRotation().y + yRot,
		transform->GetRotation().z);


	LookAt.x = transform->GetTranslation().x + LookAtDist * sin(transform->GetRotation().y * M_PI / 180);

	LookAt.y = transform->GetTranslation().y + LookAtDist * sin(transform->GetRotation().x * M_PI / 180);

	LookAt.z = transform->GetTranslation().z + LookAtDist * cos(transform->GetRotation().y * M_PI / 180);
}	