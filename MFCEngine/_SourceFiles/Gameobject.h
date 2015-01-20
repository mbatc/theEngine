#pragma once

#include "Transform.h"

class D3DGraphics;
class Component;

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
	
	void AddComponent( Component * newComponent );
	void RemoveComponent( const unsigned int ID );

	void GetObjectName( char* nameBuffer ) const;
	void SetObjectName( const char* nameBuffer );

	Component* GetComponent( int ID ) const;

	//------------------------------------------
	//INLINE METHODS
	Transform* GetTransform() const { return transform; }

private:
	//------------------------------------------
	//DATA MEMBERS
	char *			objectName;
	unsigned int	nComponents;
	ComponentList * componentsList;
	Transform *		transform;

};