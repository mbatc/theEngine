#include "Component.h"
#include "D3DGraphics.h"

class CustomBehaviour : public Component
{
public:
	CustomBehaviour(Gameobject* parent, char* filename);

	char* GetFilename() { return filename; }
	char* GetSourceText() { return sourceText; }
	
	void Update();
	void Render(D3DGraphics& gfx);
private:

	char* sourceText;
	char* filename;
};