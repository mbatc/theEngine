#include "Scene.h"
#include "SceneRenderer.h"
#include "Gameobject.h"
#include "D3DGraphics.h"
#include <stdio.h>

Scene::Scene()
	:
	renderer(),
	nObjects( NULL ),
	sceneObjects(NULL)
{
	
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

	}
	else
	{
		char name[11] = { "GameObject" };
		sceneObjects = new ObjectList[1];
		if (!sceneObjects)
			return 1;
		sceneObjects[0].ID = 0;
		sceneObjects[0].object = new Gameobject();
		sceneObjects[0].name = new char[11];
		for (int i = 0; i < 11; i++)
			sceneObjects[0].name[i] = name[i];

		if (!sceneObjects[0].object)
			return 1;
		nObjects = 1;
	}
	return 0;
}

int Scene::AddLightObject()
{
	//TODO: fill out adding light objects
	return 0;
}

void Scene::DeleteGameObject()
{
	//TODO: fill out deleting game and light 
}

void Scene::GetObjectName(char* namebuffer, const int buflen, const int ID) const
{
	int namelen = 0;

	for (int obji = 0; obji < nObjects; obji++)
	{
		if (sceneObjects[obji].ID == ID)
		{
			for (int i = 0; sceneObjects[obji].name[i] != '\0'; namelen++, i++); namelen++;

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