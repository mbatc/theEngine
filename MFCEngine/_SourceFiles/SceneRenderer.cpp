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

	scene->GetMainCam()->Render(gfx);
	for (int i = 0; i < scene->GetNumberOfObjects(); i++)
	{
		scene->GetSceneObject(i)->Render(gfx);
	}
	gfx.EndFrame();
}