#pragma once

class Scene;
class D3DGraphics;

class SceneRenderer
{
public:
	SceneRenderer();
	~SceneRenderer();

	//------------------------------------------
	//METHODS
	void Render(D3DGraphics& gfx, Scene* scene) const;

private:

};