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

	Project* GetProject(){ return curProject; }
	void Update();
	void Render();
	int	 LockGFX();
	void UnlockGFX();

protected:
	//------------------------------------------
	//DATA MEMBERS
	D3DGraphics * gfx;
	Project* curProject;

	//------------------------------------------
	//METHODS
	void LoadProject(char* filepath = NULL);
	void InitVariables();

	bool isLocked;
};

class GameUdt : public CWinThread
{
public:
	GameUdt(MainApp* WinApp){ winApp = WinApp; }
	MainApp* winApp;
private:
};