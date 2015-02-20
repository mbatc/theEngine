#pragma once

#include "Gameobject.h"
#include "D3DGraphics.h"

class Light : public Gameobject
{
public:
	Light(D3DGraphics& gfx, int index);
	~Light();

	void SetDiffuse(D3DXCOLOR color);
	void SetDirection(D3DXVECTOR3 direction);
	void SetRange(float range);
	void SetAttenuation(int type, float attenuation);
	void SetState(bool state);
	void SetIndex(int i){ index = i; };

	void Update();
	void Render(D3DGraphics& gfx);

	void FreeGFX();
	void RestoreGFX();

private:
	int index;
	bool lightState;
	D3DGraphics& gfx;
	D3DLIGHT9 light;
};