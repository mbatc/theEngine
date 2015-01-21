#include <afxwin.h>

class Project;
class D3DGraphics;
class MainWin;
class DialogObjProp;
class DialogObjList;

class MainApp : public CWinApp
{
	friend DialogObjProp;
	friend DialogObjList;
	friend MainWin;
	//Overides
	protected:
		BOOL InitInstance();
		int OnIdle(LONG ICount);

public:
	MainApp();
	~MainApp();

protected:
	//------------------------------------------
	//DATA MEMBERS
	D3DGraphics * gfx;
	Project* curProject;

	//------------------------------------------
	//METHODS
	void LoadProject(char* filepath = NULL);
	void Update();
	void Render();
	void InitVariables();
};