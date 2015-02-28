#include "GlobalPointers.h"
#include "Camera.h"

Camera::Camera()
	:
	Gameobject()
{
	if (type)
		delete type;
	type = new char[7];
	char name[] = { "CAMERA" };
	for (int i = 0; i < 7; i++)
	{
		type[i] = name[i];
	}

	transform->SetTranslation(0.0f, 0.0f, 10.0f);
}

Camera::~Camera()
{}

void Camera::Render(D3DGraphics& gfx) const
{
	D3DXMATRIX matView;
	D3DXMatrixLookAtLH(&matView, &D3DXVECTOR3(transform->GetTranslation().x,
		transform->GetTranslation().y,
		transform->GetTranslation().z),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
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
	float x = 0;
	float z = 0;
	if (kbd->KeyIsDown(VK_UP))
	{
		z -= 0.1f;
	}
	if (kbd->KeyIsDown(VK_DOWN))
	{
		z += 0.1f;
	}
	if (kbd->KeyIsDown(VK_LEFT))
	{
		x += 0.1f;
	}
	if (kbd->KeyIsDown(VK_RIGHT))
	{
		x -= 0.1f;
	}

	transform->SetTranslation(transform->GetTranslation().x + x,
		transform->GetTranslation().y,
		transform->GetTranslation().z + z);
}