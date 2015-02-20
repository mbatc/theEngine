#include "Component.h"
#include "D3DGraphics.h"

class CustomBehaviour : public Component
{
public:
	CustomBehaviour(Gameobject* parent);
	
	void Update();
	void Render(D3DGraphics& gfx);
private:
};