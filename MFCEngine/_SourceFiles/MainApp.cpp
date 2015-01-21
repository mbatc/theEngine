#include "MainApp.h"
#include "MainWin.h"
#include "MainView.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
#include "resource.h"

IMPLEMENT_DYNCREATE(MainView, CView);
IMPLEMENT_DYNCREATE(MainDoc, CDocument);

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

	return TRUE;
}

inline int MainApp::OnIdle(LONG ICount)
{
	Update();
	Render();
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

MainApp mainApp;