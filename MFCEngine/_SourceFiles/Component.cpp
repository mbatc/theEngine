#include "Component.h"
#include "Gameobject.h"

Component::Component(Gameobject* parent)
	:
	m_pParent(parent),
	m_type(CT_NOTSET)
{
	m_pCompIdentifier = new char[5];
	m_pCompIdentifier = { "NULL" };
}

void Component::GetName(char* pNameBuffer, int maxBufLen) const
{
	ZeroMemory(pNameBuffer, sizeof(char)*maxBufLen);
	if (m_pName)
	{
		for (int i = 0; i < maxBufLen && m_pName[i] != '\0'; i++)
		{
			pNameBuffer[i] = m_pName[i];
		}
	}
	else
	{
		char name[] = { "NULL" };
		for (int i = 0; i < 5 && i < maxBufLen; i++)
		{
			pNameBuffer[i] = name[i];
		}
	}
}

void Component::SetName(const char* pNameBuffer)
{

}