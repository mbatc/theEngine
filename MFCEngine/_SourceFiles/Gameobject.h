#pragma once

#include "Transform.h"

class D3DGraphics;
class Component;
class Scene;

struct ComponentList
{
	int ID;
	Component * component;
};

class Gameobject
{
public:
	Gameobject();
	~Gameobject();

	//------------------------------------------
	//METHODS
	virtual void Update();
	virtual void Render(D3DGraphics& gfx) const;
	
	void FreeGFX();
	void RestoreGFX();

	//Returns new components ID. Returns -1 if component was not added.
	int AddComponent( Component * newComponent );
	void RemoveComponent(const unsigned int ID);

	Component* GetComponent( int ID ) const;

	//------------------------------------------
	//INLINE METHODS
	char* GetPointerToType() const { return type; }
	Transform* GetTransform() const { return transform; }
	int GetNumberOfComponent() const { return nComponents; }

protected:
	//------------------------------------------
	//DATA MEMBERS
	char *			type;
	char *			objectName;
	unsigned int	nComponents;
	ComponentList * componentsList;
	Transform *		transform;

};