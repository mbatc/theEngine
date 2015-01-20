#include "Scene.h"
#include "SceneRenderer.h"
#include "D3DGraphics.h"

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

int Scene::AddGameObject()
{
	//TODO: fill out adding game objects
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

void Scene::UpdateScene()
{
	//TODO: fill out scene update loops
}

void Scene::RenderScene(D3DGraphics& gfx)
{
	renderer.Render(gfx, this);
}