#include "Gameobject.h"
#include "Component.h"
#include "Transform.h"
#include "D3DGraphics.h"

Gameobject::Gameobject()
	:
	objectName(NULL),
	componentsList(NULL)
{
	transform = new Transform();
}

Gameobject::~Gameobject()
{
	if (objectName)
	{
		delete [] objectName;
		objectName = NULL;
	}
	if (componentsList)
	{
		delete [] componentsList;
		componentsList = NULL;
	}
	if (transform)
	{
		delete transform;
		transform = NULL;
	}
}

void Gameobject::Update()
{
	for (int i = 0; i < nComponents; i++)
	{
		componentsList[i].component->Update();
	}

	transform->SetRotation(transform->GetRotation().x,
		transform->GetRotation().y + 2, transform->GetRotation().z);
}

void Gameobject::Render(D3DGraphics& gfx) const
{
	for (int i = 0; i < nComponents; i++)
	{
		componentsList[i].component->Render( gfx );
	}
}

int Gameobject::AddComponent( Component * newComponent )
{
	if (componentsList)
	{
		ComponentList* tempList = new ComponentList[nComponents + 1];
		if (!tempList)
		{
			MessageBox(NULL, "Failed To Add New Component!", "Error!", MB_OK | MB_ICONEXCLAMATION);
			return -1;
		}

		for (int i = 0; i < nComponents; i++)
		{
			tempList[i].ID = componentsList[i].ID;
			tempList[i].component = componentsList[i].component;
		}
		tempList[nComponents].ID = nComponents;
		tempList[nComponents].component = newComponent;
		nComponents++;

		delete [] componentsList;
		componentsList = NULL;
		componentsList = new ComponentList[nComponents];

		for (int i = 0; i < nComponents; i++)
		{
			componentsList[i].ID = tempList[i].ID;
			componentsList[i].component = tempList[i].component;
		}

		if (tempList)
		{
			delete[] tempList;
			tempList = NULL;
		}
		return nComponents - 1;
	}
	else
	{
		componentsList = new ComponentList[1];
		componentsList[0].ID = 0;
		componentsList[0].component = newComponent;
		nComponents = 1;
		return 0;
	}
	return -1;
}

void Gameobject::RemoveComponent(const unsigned int ID)
{
	int compPlace = 0;
	for (int i = 0; i < nComponents; i++)
	{
		if (componentsList[i].ID = ID)
		{
			compPlace = i;
			break;
		}
	}

	delete componentsList[compPlace].component;
	componentsList[compPlace].component = NULL;

	ComponentList * tempList = new ComponentList[nComponents];
	for (int i = 0; i < nComponents; i++)
	{
		if (i != compPlace)
		{
			tempList[i].ID = componentsList[i].ID;
			tempList[i].component = componentsList[i].component;
		}
	}
	nComponents--;

	delete[] componentsList;
	componentsList = new ComponentList[nComponents];
	for (int i = 0; i < nComponents; i++)
	{
		componentsList[i].ID = i;
		componentsList[i].component = tempList[i].component;
	}

	delete [] tempList;
	tempList = NULL;
}

Component * Gameobject::GetComponent(int ID) const
{
	for (int i = 0; i < nComponents; i++)
	{
		if (componentsList[i].ID == ID)
		{
			return componentsList[i].component;
		}
	}
	return NULL;
}