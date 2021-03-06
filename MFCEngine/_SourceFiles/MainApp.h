#include <afxwin.h>
#include <atomic>

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

	int		LockKBD();
	void	UnlockKBD();

	int		LockMSE();
	void	UnlockMSE();

protected:
	//------------------------------------------
	//DATA MEMBERS
	D3DGraphics * gfx;
	Project* curProject;

	//------------------------------------------
	//METHODS
	void LoadProject(char* filepath = NULL);
	void InitVariables();

	std::atomic<bool> isLocked;
	std::atomic<bool> kbdLocked;
	std::atomic<bool> mseLocked;
};

class GameUdt : public CWinThread
{
public:
	GameUdt(MainApp* WinApp){ winApp = WinApp; }
	MainApp* winApp;
private:
};