#pragma once

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
	void GetName( char* pNameBuffer) const;
	void SetName(const char* pNameBuffer);

	//------------------------------------------
	//INLINE
	ComponentType GetType(){ return m_type; }

	//------------------------------------------
	//OVERIDE

	//The function called once every frame used to update all derived components
	virtual void Update() = 0;

protected:
	//------------------------------------------
	//DATA MEMBERS
	ComponentType	m_type;

	char*			m_pName;
	Gameobject *	m_pParent;
};