#pragma once

#include "SceneRenderer.h" 

class D3DGraphics;
class Gameobject;

struct ObjectList
{
	int ID;
	char* name;
	Gameobject* object;
};

class Scene
{
public:
	Scene();
	~Scene();

	//------------------------------------------
	//METHODS
	int AddGameObject();
	int AddLightObject();
	void DeleteGameObject();
	void GetObjectName(char* nameBuffer, const int buflen, const int ID) const;
	void SetObjectName(const char* nameBuffer, const int ID);


	Gameobject * GetSceneObject(int ID);

	void UpdateScene();
	void RenderScene(D3DGraphics& gfx);

	//------------------------------------------
	//INLINE METHODS
	int GetNumberOfObjects(){ return nObjects; }
private:
	SceneRenderer renderer;

	ObjectList* sceneObjects;
	int nObjects;
};