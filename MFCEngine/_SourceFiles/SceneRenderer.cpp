#include "SceneRenderer.h"
#include "Scene.h"
#include "Gameobject.h"
#include "Camera.h"
#include "D3DGraphics.h"

SceneRenderer::SceneRenderer()
{

}

SceneRenderer::~SceneRenderer()
{

}

void SceneRenderer::Render(D3DGraphics& gfx, Scene* scene) const
{
	gfx.BeginFrame();
	gfx.GetDevice()->SetFVF(CUSTOMFVF);
	for (int i = 0; i < scene->GetNumberOfObjects(); i++)
	{
		Gameobject* curObj = scene->GetSceneObject(i);
		if (!strcmp(curObj->GetPointerToType(), "CAMERA"))
		{
			curObj->Render(gfx);
		}
	}
	for (int i = 0; i < scene->GetNumberOfObjects(); i++)
	{
		if (strcmp(scene->GetSceneObject(i)->GetPointerToType(), "CAMERA") != 0)
		{
			scene->GetSceneObject(i)->Render(gfx);
		}
	}
	gfx.EndFrame();
}