#include "Light.h"
#include "Component.h"
#include "Transform.h"


Light::Light(D3DGraphics& gfx, int index)
	:
	gfx(gfx),
	index(index)
{
	ZeroMemory(&light, sizeof(light));
	
	light.Type = D3DLIGHT_POINT;
	light.Attenuation0 = 0.0f;
	light.Attenuation1 = 0.125f;
	light.Attenuation2 = 0.0f;
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	light.Direction = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	light.Position = D3DXVECTOR3(transform->GetTranslation().x,
		transform->GetTranslation().y,
		transform->GetTranslation().z);
	light.Range = 100.0f;

	gfx.GetDevice()->SetLight(index, &light);
	gfx.GetDevice()->LightEnable(index, TRUE);
}

void Light::SetDiffuse(D3DXCOLOR color)
{
	light.Diffuse = color;
	gfx.GetDevice()->SetLight(index, &light);
}

void Light::SetDirection(D3DXVECTOR3 direction)
{
	light.Direction = direction;
	gfx.GetDevice()->SetLight(index, &light);
}

void Light::SetAttenuation(int type, float attenuation)
{
	switch (type)
	{
	case 0:
		light.Attenuation0 = attenuation;
		break;
	case 1:
		light.Attenuation1 = attenuation;
		break;
	case 2:
		light.Attenuation2 = attenuation;
		break;
	default:
		break;
	}

	gfx.GetDevice()->SetLight(index, &light);
}

void Light::SetState(bool state)
{
	gfx.GetDevice()->SetLight(index, &light);
	gfx.GetDevice()->LightEnable(index, state);
}

void Light::Update()
{
	light.Position = D3DXVECTOR3(transform->GetTranslation().x,
		transform->GetTranslation().y,
		transform->GetTranslation().z);
	gfx.GetDevice()->SetLight(index, &light);

	for (int i = 0; i < nComponents; i++)
	{
		componentsList[i].component->Update();
	}
}

void Light::Render(D3DGraphics& grfx)
{
	for (int i = 0; i < nComponents; i++)
	{
		componentsList[i].component->Render(gfx);
	}
}