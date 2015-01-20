#include "Component.h"
#include "Gameobject.h"

Component::Component(Gameobject* parent)
	:
	m_pParent(parent),
	m_type(CT_NOTSET)
{}

void Component::GetName(char* pNameBuffer) const
{

}

void Component::SetName(const char* pNameBuffer)
{

}