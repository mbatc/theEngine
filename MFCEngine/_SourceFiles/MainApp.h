#include <afxwin.h>

class Project;
class D3DGraphics;

class MainApp : public CWinApp
{
	//Overides
	protected:
		BOOL InitInstance();
		int OnIdle(LONG ICount);

public:
	MainApp();
	~MainApp();

protected:
	D3DGraphics * gfx;
	Project* curProject;

	void LoadProject(char* filepath = NULL);
	void Update();
	void Render();
	void InitVariables();
};