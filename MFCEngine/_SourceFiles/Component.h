#pragma once
#include "D3DGraphics.h"

#define CTYPE_MESH "C_MESH"
#define CTYPE_MESHRENDERER "C_MESHRENDERER"

class Gameobject;

enum ComponentType
{
	CT_GFX,
	CT_SOUND,
	CT_DATA,
	CT_BEHAVIOUR,
	CT_NOTSET
};

class Component
{
public:
	Component(Gameobject* parent);

	//------------------------------------------
	//METHODS
	void GetName(char* pNameBuffer, int maxBufLen) const;
	void SetName(const char* pNameBuffer);

	//------------------------------------------
	//INLINE
	ComponentType GetType(){ return m_type; }
	char* GetIdentifier() const { return m_pCompIdentifier; }

	//------------------------------------------
	//OVERIDE

	//The function called once every frame used to update all derived components
	virtual void Update() {}
	virtual void Render(D3DGraphics& gfx) {}
	virtual void FreeGFX() {}
	virtual void RestoreGFX() {}

protected:
	//------------------------------------------
	//DATA MEMBERS
	ComponentType	m_type;

	char*			m_pName;
	char*			m_pCompIdentifier;
	Gameobject *	m_pParent;
};