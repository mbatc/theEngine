#pragma once

#include "SceneRenderer.h" 

class D3DGraphics;
class Gameobject;
class Camera;

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
	int AddLightObject(D3DGraphics& gfx);
	int AddCameraObject();
	void DeleteGameObject( int ID );
	void GetObjectName(char* nameBuffer, const int buflen, const int ID) const;
	void SetObjectName(const char* nameBuffer, const int ID);
	void SetName(char* newName);

	ObjectList* GeObjectList(){ return sceneObjects; }


	Gameobject * GetSceneObject(int ID);

	void UpdateScene();
	void RenderScene(D3DGraphics& gfx);

	void SaveScene(char* filepath);

	//------------------------------------------
	//INLINE METHODS
	int GetNumberOfObjects(){ return nObjects; }
	char* GetSceneName(){ return name; }

private:
	char* name;

	SceneRenderer renderer;

	ObjectList* sceneObjects;
	int nObjects;
	int nLights;
};