#include "SceneRenderer.h"
#include "Scene.h"
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
	//scene->GetMainCam()->Update();
	for (int i = 0; i < scene->GetNumberOfObjects(); i++)
	{
		//scene->GetSceneObject()->Render(gfx);
	}
	gfx.EndFrame();
}