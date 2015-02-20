#include "Camera.h"

Camera::Camera()
{
	transform->SetTranslation(0.0f, 0.0f, 10.0f);
}

Camera::~Camera()
{}

void Camera::Render(D3DGraphics& gfx)
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
{}