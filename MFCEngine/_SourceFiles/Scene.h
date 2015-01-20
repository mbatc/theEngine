#pragma once

#include "SceneRenderer.h"

class D3DGraphics;
class SceneRenderer;

struct ObjectList
{
	int ID;
	char* name;
	//Gameobject* object;
};

class Scene
{
public:
	Scene();
	~Scene();

	//Methods
	int AddGameObject();
	int AddLightObject();
	void DeleteGameObject();


	//Gameobject * GetSceneObject(int ID);

	void UpdateScene();
	void RenderScene(D3DGraphics& gfx);

	//Inline Methods
	int GetNumberOfObjects(){ return nObjects; }
private:
	SceneRenderer renderer;

	ObjectList* sceneObjects;
	int nObjects;
};