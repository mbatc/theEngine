#pragma once

#include "GlobalPointers.h"
#include "CustomBehaviour.h"
#include "Gameobject.h"
#include "Component.h"
#include "Transform.h"

class PlayerControl : public CustomBehaviour
{
public:
	PlayerControl(Gameobject* parent)
		:
		CustomBehaviour(parent)
	{
		grav = 0.025f;
		floorHeight = -2.0f;
	}
	~PlayerControl()
	{

	}

	void Update()
	{
		float x, y, z;
		x = m_pParent->GetTransform()->GetTranslation().x;
		y = m_pParent->GetTransform()->GetTranslation().y;
		z = m_pParent->GetTransform()->GetTranslation().z;

		switch (isGrounded)
		{
		case true:
			vSpeed = 0;
			if (kbd->KeyIsDown(VK_SPACE))
			{
				vSpeed = 0.3f;
			}
			if (kbd->KeyIsDown('A'))
			{
				hSpeed += .02f;
			}
			if (kbd->KeyIsDown('D'))
			{
				hSpeed -= .02f;
			}

			if (hSpeed > .5f){ hSpeed = .5f; }
			else if (hSpeed < -.5f){ hSpeed = -.5f; }

			isGrounded = false;
			if (y > floorHeight){ isGrounded = true; break; }
			break;
		case false:
			vSpeed -= grav;
			if (y <= floorHeight)
			{
				y = floorHeight;
				vSpeed = 0;
				isGrounded = true;
			}
			break;
		}

		if (!kbd->KeyIsDown('A') && !kbd->KeyIsDown('D'))
		{
			if (hSpeed < 0)
			{
				hSpeed += .02f;
			}
			else if (hSpeed > 0)
			{
				hSpeed -= .02f;
			}
			if (hSpeed > -.02f && hSpeed < .02f)
			{
				hSpeed = 0.0f;
			}
		}

		x += hSpeed;
		y += vSpeed;
		m_pParent->GetTransform()->SetTranslation(x, y, z);
	}

private:
	bool isGrounded;
	float vSpeed;
	float hSpeed;
	float grav;
	float floorHeight;
};