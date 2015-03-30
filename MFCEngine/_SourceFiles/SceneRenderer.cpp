#include "GlobalPointers.h"
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
		if (curObj)
		{
			if (!strcmp(curObj->GetPointerToType(), "CAMERA"))
			{
				curObj->Render(gfx);
			}
		}
		else
		{
			char msg[256] = { 0 };
			sprintf(msg, "Object: %d | Error: Unable to be processed for rendering! \n|CAMERA RENDER LOOP|\0",i);
			Console->Output(msg);
		}
	}
	for (int i = 0; i < scene->GetNumberOfObjects(); i++)
	{
		Gameobject* obj = scene->GetSceneObject(i);
		if (obj)
		{
			if (strcmp(scene->GetSceneObject(i)->GetPointerToType(), "CAMERA") != 0)
			{
				scene->GetSceneObject(i)->Render(gfx);
			}
		}
		else
		{
			char msg[256] = { 0 };
			sprintf(msg, "Object: %d | Error: Unable to be processed for rendering! \n|OBJECT RENDER LOOP|\0", i);
			Console->Output(msg);
		}
	}
	gfx.EndFrame();
}