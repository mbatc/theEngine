#include "Scene.h"
#include "SceneRenderer.h"
#include "Gameobject.h"
#include "Camera.h"
#include "D3DGraphics.h"
#include "Light.h"
#include <stdio.h>

Scene::Scene()
	:
	renderer(),
	nObjects( NULL ),
	sceneObjects(NULL),
	nLights(NULL)
{
	AddCameraObject();
	char t[] = { "Scene_0" };
	name = new char[8];

	for (int i = 0; i < 8; i++)
	{
		name[i] = t[i];
	}

	//TODO: add initialization code
}

Scene::~Scene()
{

}

Gameobject * Scene::GetSceneObject( int ID )
{
	if (nObjects)
	{
		for (int i = 0; i < nObjects; i++)
		{
			if (sceneObjects[i].ID == ID)
			{
				return sceneObjects[i].object;
			}
		}
		char errorMsg[512];
		sprintf_s(errorMsg, "No Object Found With The ID : %d", ID);
		MessageBox(NULL, errorMsg, "Notice!",
			MB_OK | MB_ICONINFORMATION);
		return NULL;
	}
	return NULL;
}

int Scene::AddGameObject()
{
	if (sceneObjects)
	{
		ObjectList* tempList = new ObjectList[nObjects + 1];
		ZeroMemory(tempList, sizeof(ObjectList)*(nObjects + 1));

		for (int i = 0; i < nObjects; i++)
		{
			tempList[i].ID		= sceneObjects[i].ID;
			tempList[i].object	= sceneObjects[i].object;
			tempList[i].name	= new char[512];
			ZeroMemory(tempList[i].name, sizeof(char) * 512);

			GetObjectName(tempList[i].name, 512, i);
		}
		tempList[nObjects].ID		= nObjects;
		tempList[nObjects].object	= new Gameobject();
		tempList[nObjects].name		= new char[15];
		char name[15] = { "New GameObject" };
		for (int i = 0; i < 15; i++)
		{
			tempList[nObjects].name[i] = name[i];
		}

		delete sceneObjects;
		nObjects++;

		sceneObjects = new ObjectList[nObjects];
		ZeroMemory(sceneObjects, sizeof(ObjectList)*(nObjects));
		for (int i = 0; i < nObjects; i++)
		{
			sceneObjects[i].ID = tempList[i].ID;
			sceneObjects[i].object = tempList[i].object;
			sceneObjects[i].name = new char[512];
			SetObjectName(tempList[i].name, i);
		}
		return nObjects - 1;
	}
	else
	{
		char name[15] = { "New GameObject" };
		sceneObjects = new ObjectList[1];
		if (!sceneObjects)
			return -1;
		sceneObjects[0].ID = 0;
		sceneObjects[0].object = new Gameobject();
		sceneObjects[0].name = new char[15];
		for (int i = 0; i < 15; i++)
			sceneObjects[0].name[i] = name[i];

		if (!sceneObjects[0].object)
			return -1;
		nObjects = 1;
		return 0;
	}
	return -1;
}

int Scene::AddCameraObject()
{
	if (sceneObjects)
	{
		ObjectList* tempList = new ObjectList[nObjects + 1];
		ZeroMemory(tempList, sizeof(ObjectList)*(nObjects + 1));

		for (int i = 0; i < nObjects; i++)
		{
			tempList[i].ID = sceneObjects[i].ID;
			tempList[i].object = sceneObjects[i].object;
			tempList[i].name = new char[512];
			ZeroMemory(tempList[i].name, sizeof(char) * 512);

			GetObjectName(tempList[i].name, 512, i);
		}
		tempList[nObjects].ID = nObjects;
		tempList[nObjects].object = (Gameobject*)new Camera();
		tempList[nObjects].name = new char[15];
		char name[15] = { "New Camera" };
		for (int i = 0; i < 15; i++)
		{
			tempList[nObjects].name[i] = name[i];
		}

		delete sceneObjects;
		nObjects++;

		sceneObjects = new ObjectList[nObjects];
		ZeroMemory(sceneObjects, sizeof(ObjectList)*(nObjects));
		for (int i = 0; i < nObjects; i++)
		{
			sceneObjects[i].ID = tempList[i].ID;
			sceneObjects[i].object = tempList[i].object;
			sceneObjects[i].name = new char[512];
			SetObjectName(tempList[i].name, i);
		}
		return nObjects - 1;
	}
	else
	{
		char name[15] = { "New Camera" };
		sceneObjects = new ObjectList[1];
		if (!sceneObjects)
			return -1;
		sceneObjects[0].ID = 0;
		sceneObjects[0].object = (Gameobject*)new Camera();
		sceneObjects[0].name = new char[15];
		for (int i = 0; i < 15; i++)
			sceneObjects[0].name[i] = name[i];

		if (!sceneObjects[0].object)
			return -1;
		nObjects = 1;
		return 0;
	}
	return -1;
}


int Scene::AddLightObject(D3DGraphics& gfx)
{
	if (sceneObjects)
	{
		ObjectList* tempList = new ObjectList[nObjects + 1];
		ZeroMemory(tempList, sizeof(ObjectList)*(nObjects + 1));

		for (int i = 1; i < nObjects + 1; i++)
		{
			tempList[i] = sceneObjects[i - 1];
			tempList[i].ID += 1;
			sceneObjects[i - 1].name = NULL;
			sceneObjects[i - 1].object = NULL;
		}
		tempList[0].ID			= 0;
		tempList[0].object		= (Gameobject*)new Light(gfx,nLights);
		tempList[0].name		= new char[10];
		tempList[0].name		= { "New Light" };

		delete sceneObjects;
		sceneObjects = new ObjectList[nObjects + 1];
		nObjects++;
		nLights++;

		ZeroMemory(sceneObjects, sizeof(ObjectList)*(nObjects));
		for (int i = 0; i < nObjects; i++)
		{
			sceneObjects[i] = tempList[i];
			sceneObjects[i].name = NULL;
			SetObjectName(tempList[i].name, i);

			tempList[i].name = NULL;
			tempList[i].object = NULL;
		}
		delete[] tempList;
		tempList = NULL;

		/*for (int i = 0; i < nLights; i++)
		{
			int iobj = 0;
			for (; iobj < nObjects; iobj++)
			{
				if (strcmp(sceneObjects[iobj].object->GetPointerToType(), "GAMELIGHT"))
					break;
				((Light*)sceneObjects[iobj].object)->SetIndex(i);
			}
		}*/

		return 0;
	}
	else
	{
		sceneObjects = new ObjectList[1];
		if (!sceneObjects)
			return -1;
		sceneObjects[0].ID = 0;
		sceneObjects[0].object = (Gameobject*) new Light(gfx,0);
		sceneObjects[0].name = new char[10];
		sceneObjects[0].name = { "New Light" };

		if (!sceneObjects[0].object)
			return -1;

		nObjects = 1;
		nLights = 1;
		return 0;
	}
	MessageBox(NULL, "An Unknown Error Occured When Adding The Object!", "Error!",
		MB_OK | MB_ICONEXCLAMATION);
	return -1;
}

void Scene::DeleteGameObject(int ID)
{
	bool isLight;
	if (sceneObjects)
	{
		if (ID < 0)
			return;
		if (sceneObjects[ID].object)
		{
			ObjectList* temp = new ObjectList[nObjects - 1];
			for (int i = 0; i < nObjects; i++)
			{
				if (i < ID)
				{
					temp[i] = sceneObjects[i];
					sceneObjects[i].name = NULL;
					sceneObjects[i].object = NULL;
				}
				else if (i > ID)
				{
					temp[i - 1] = sceneObjects[i];
					temp[i - 1].ID -= 1;
					sceneObjects[i].name = NULL;
					sceneObjects[i].object = NULL;
				}
				else
				{
					if (!strcmp(sceneObjects[ID].object->GetPointerToType(), "GAMELIGHT"))
						isLight = true;
					else
						isLight = false;
					if (isLight)
						((Light*)sceneObjects[ID].object)->~Light();
					else
						sceneObjects[ID].object->~Gameobject();
					sceneObjects[ID].name = NULL;
					sceneObjects[ID].object = NULL;
				}
			}
			delete sceneObjects;
			sceneObjects = new ObjectList[nObjects - 1];
			for (int i = 0; i < nObjects - 1; i++)
			{
				sceneObjects[i] = temp[i];
			}
			delete [] temp;
			temp = NULL;

			if (isLight)
				nLights--;
			nObjects -= 1;
/*
			for (int i = 0; i < nLights; i++)
			{
				int iobj = 0;
				for (; iobj < nObjects; iobj++)
				{
					if (strcmp(sceneObjects[iobj].object->GetPointerToType(), "GAMELIGHT"))
					{
						((Light*)sceneObjects[iobj].object)->SetIndex(i);
						break;
					}
				}				
			}*/
		}
		else
			MessageBox(NULL, "Object Selected Does Not Exist!", "Notice",
				MB_OK | MB_ICONINFORMATION);
	}
	else
		MessageBox(NULL, "No Gameobjects Exist!", "Notice!",
			MB_OK | MB_ICONINFORMATION);
}

void Scene::GetObjectName(char* namebuffer, const int buflen, const int ID) const
{
	int namelen = 0;

	for (int obji = 0; obji < nObjects; obji++)
	{
		if (sceneObjects[obji].ID == ID)
		{
			if (name)
				for (int i = 0; sceneObjects[obji].name[i] != '\0'; namelen++, i++);

			ZeroMemory(namebuffer, sizeof(char)*buflen);
			for (int chari = 0; chari < namelen && chari < buflen; chari++)
			{
				namebuffer[chari] = sceneObjects[obji].name[chari];
			}
			break;
		}
	}
}

void Scene::SetObjectName(const char* namebuffer, const int ID)
{
	int namelen = 0;
	for (int i = 0; namebuffer[i] != '\0'; i++, namelen++); namelen++;

	for (int obji = 0; obji < nObjects; obji++)
	{
		if (sceneObjects[obji].ID == ID)
		{
			if (sceneObjects[obji].name)
				delete sceneObjects[obji].name;
			sceneObjects[obji].name = new char[namelen];

			for (int i = 0; i < namelen; i++)
				sceneObjects[obji].name[i] = namebuffer[i];
		}
	}
}

void Scene::UpdateScene()
{
	for (int i = 0; i < nObjects; i++)
	{
		sceneObjects[i].object->Update();
	}
}

void Scene::RenderScene(D3DGraphics& gfx)
{
	renderer.Render(gfx, this);
}

void Scene::SaveScene(char* filepath)
{
}

void Scene::SetName(char* newName)
{
	int namelen = 0;
	for (; newName[namelen] != '\0'; namelen++);

	if (name)
		delete name;
	name = NULL;

	name = new char[namelen];

	for (int i = 0; i < namelen; i++)
		name[i] = newName[i];
}