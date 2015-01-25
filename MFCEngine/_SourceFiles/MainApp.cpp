#include "MainApp.h"
#include "MainWin.h"
#include "MainView.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
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
		gameThread->winApp->Update();
		int nCycles = gameThread->winApp->LockGFX();
		gameThread->winApp->Render();
		gameThread->winApp->UnlockGFX();

		if (nCycles > 0)
		{
			char msg[512];
			sprintf_s(msg, "%i CPU Cycles To Lock GFX", nCycles);
			MessageBox(NULL, msg, "",
				MB_OK | MB_ICONINFORMATION);
		}
	}
}

MainApp::MainApp()
{
	InitVariables();
	curProject = new Project(NULL);
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

	GameUdt* object = new GameUdt(this);
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
		gfx->OnResize(width, height);
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
		if (isLocked == false)
			isLocked = true;
		nCycles += 2;
	} while (isLocked == false);
	return nCycles;
}

void MainApp::UnlockGFX()
{
	if (isLocked)
		isLocked = false;
}

MainApp mainApp;