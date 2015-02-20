#include "CustomBehaviour.h"
#include "Gameobject.h"
#include "Transform.h"

class Rotation : CustomBehaviour
{
public:
	Rotation(Gameobject* parent) : CustomBehaviour(parent){}
	void Update()
	{
		float rotX, rotY, rotZ;
		rotX = m_pParent->GetTransform()->GetRotation().x + 2;
		rotY = m_pParent->GetTransform()->GetRotation().y;
		rotZ = m_pParent->GetTransform()->GetRotation().z;
		m_pParent->GetTransform()->SetRotation(rotX,rotY,rotZ);
	}
};