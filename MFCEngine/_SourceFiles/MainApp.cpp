#include "MainApp.h"
#include "MainWin.h"
#include "MainView.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
#include "GlobalPointers.h"
#include "KeyboardInput.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(MainView, CView);
IMPLEMENT_DYNCREATE(MainDoc, CDocument);

UINT _cdecl GameUpdateThread(LPVOID pParam)
{
	GameUdt* gameThread = (GameUdt*)pParam;
	if (gameThread == NULL || !gameThread->IsKindOf(RUNTIME_CLASS(GameUdt)) )
		return 1;

	while (1 != 2)
	{
		char msg[512];
		int nCycles = gameThread->winApp->GetProject()->LockScene();

		gameThread->winApp->LockKBD();
		gameThread->winApp->LockMSE();
		gameThread->winApp->Update();

		if (nCycles > 0)
		{
			sprintf(msg, "CPU Cycles To Lock Scene: %d", nCycles);
			Console->Output(msg);
		}

		((MainWin*)gameThread->winApp->m_pMainWnd)->kServ->Update();
		((MainWin*)gameThread->winApp->m_pMainWnd)->mServ->Update();
		gameThread->winApp->UnlockKBD();
		gameThread->winApp->UnlockMSE();

		nCycles = gameThread->winApp->LockGFX();
		gameThread->winApp->Render();
		gameThread->winApp->UnlockGFX();

		gameThread->winApp->GetProject()->UnlockScene();

		if (nCycles > 0)
		{
			sprintf(msg, "CPU Cycles To Lock D3DGraphics: %d", nCycles);
			Console->Output(msg);
		}

	}
}

MainApp::MainApp()
	:
	isLocked(false),
	mseLocked(false),
	kbdLocked(false)
{
	InitVariables();
}

MainApp::~MainApp()
{

}

inline BOOL MainApp::InitInstance()
{
	CWinApp::InitInstance();

	MainWin* mainWin = new MainWin(this);

	if (!mainWin)
		return FALSE;
	this->m_pMainWnd = mainWin;
	mainWin->ShowWindow(m_nCmdShow);
	mainWin->UpdateWindow();

	gfx = mainWin->InitD3DView();
	curProject = new Project("scene_0.scene", *gfx /*,CreateState::LOAD*/);
	mainWin->UpdateObjectList();

	GameUdt* object = new GameUdt(this);

	LockKBD();
	kbd->ServerRef(mainWin->kServ);
	UnlockKBD();

	LockMSE();
	mouse->SetServerPointer(mainWin->mServ);
	UnlockMSE();

	AfxBeginThread(GameUpdateThread, object);

	return TRUE;
}

inline int MainApp::OnIdle(LONG ICount)
{
	CWnd* pPane = ((MainWin*)m_pMainWnd)->m_mainSplitter.GetPane(0, 0);
	RECT wr;
	pPane->GetWindowRect(&wr);
	int width = wr.right - wr.left;
	int height = wr.bottom - wr.top;
	if (width != gfx->GetWidth() || height != gfx->GetHeight())
	{
		LockGFX();
		gfx->OnResize(width, height, curProject->GetScene()->GeObjectList(), curProject->GetScene()->GetNumberOfObjects());
		UnlockGFX();
	}

	return CWinApp::OnIdle(ICount);
}

void MainApp::LoadProject(char* filepath)
{
	/*if (filepath = NULL)
	{
		curProject = new Project("Project", CreateState::CREATENEW);
	}
	else
	{
		FILE * pFile = NULL;
		pFile = fopen("Project.theEngine", "r");
		if (pFile)
		{

		}
		else
		{
			MessageBox(NULL, "Failed To Open Project File!", "Error!", 
				MB_OK | MB_ICONERROR);
			curProject = NULL;
			return;
		}
		fclose(pFile);
	}*/
}

void MainApp::InitVariables()
{

}

void MainApp::Update() 
{
	curProject->Update();
}

void MainApp::Render()
{
	curProject->GetScene()->RenderScene(*gfx);
}

int MainApp::LockGFX()
{
	int nCycles = 0;
	if (isLocked == false)
	{
		isLocked = true;
		return 0;
	}
	do
	{
		nCycles += 1;
	} while (isLocked == true);
	isLocked = true;
	return nCycles;
}

void MainApp::UnlockKBD()
{
	if (kbdLocked)
		kbdLocked = false;
}

int MainApp::LockKBD()
{
	int nCycles = 0;
	if (kbdLocked == false)
	{
		kbdLocked = true;
		return 0;
	}
	do
	{
		nCycles += 1;
	} while (kbdLocked == true);
	kbdLocked = true;
	return nCycles;
}

void MainApp::UnlockGFX()
{
	if (isLocked)
		isLocked = false;
}

int MainApp::LockMSE()
{
	int nCycles = 0;
	if (mseLocked == false)
	{
		mseLocked = true;
		return 0;
	}
	do
	{
		nCycles += 1;
	} while (mseLocked == true);
	mseLocked = true;
	return nCycles;
}

void MainApp::UnlockMSE()
{
	if (mseLocked)
		mseLocked = false;
}

MainApp mainApp;