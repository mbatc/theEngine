#include "MainApp.h"
#include "MainView.h"
#include "MainWin.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
#include "Gameobject.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(MainWin,CFrameWnd)
	ON_COMMAND(ID_FILE_EXIT, MenuExit)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_EMPTY, AddnewEmpty )
	ON_COMMAND(ID_WINDOW_OBJECTPROPERTIES, WindowObjProperties)
END_MESSAGE_MAP()

MainWin::MainWin(MainApp * app)
	:
	theApp(app)
{
	m_bInitMainSplitter = FALSE;
	Create(NULL, "TheEngine");
	if (!InitDialogPointers())
		MessageBox("Control Pointers Failed To Initialise!", "Error!");

	pMenu->LoadMenuA(IDR_MENU1);
	SetMenu(pMenu);
	InitDockablePanels();
}

MainWin::~MainWin()
{

}

BOOL MainWin::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext * pContext)
{
	CRect cr;
	GetClientRect(&cr);

	if (!m_mainSplitter.CreateStatic(this,2,1))
	{
		MessageBox("Failed To Initialize Splitter Frames!", "Error!");
		return FALSE;
	}

	if (!m_mainSplitter.CreateView(0,0, RUNTIME_CLASS(MainView),
		CSize(cr.Width(), cr.Height()/2), pContext))
	{
		MessageBox("Failed To Create Splitter View!", "Error!",
			MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (!m_mainSplitter.CreateView(1, 0, RUNTIME_CLASS(MainView),
		CSize(cr.Width(), cr.Height()/2), pContext) )
	{
		MessageBox("Failed To Create Splitter View!", "Error!",
			MB_OK | MB_ICONERROR);
		return FALSE;
	}

	m_bInitMainSplitter = TRUE;
	return TRUE;
}

BOOL MainWin::InitDialogPointers()
{
	pMenu = new CMenu();
	if (!pMenu)
		return FALSE;
	pObjProp = new DialogObjProp(this);
	if (!pObjProp)
		return FALSE;
	pObjList = new DialogObjList(this);
	if (!pObjList)
		return FALSE;
	return TRUE;
}

void MainWin::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	CRect cr;
	GetWindowRect(&cr);

	if (m_bInitMainSplitter && nType != SIZE_MINIMIZED)
	{
		m_mainSplitter.SetRowInfo(0, cy, 0);
		m_mainSplitter.SetColumnInfo(0, cr.Width() / 2, 50);
		m_mainSplitter.SetColumnInfo(1, cr.Width() / 2, 50);

		m_mainSplitter.RecalcLayout();
	}
}

BOOL MainWin::InitDockablePanels()
{
	EnableDocking(CBRS_ALIGN_ANY);
	if (!pObjProp->Create(this, IDD_OBJPROP, 
		CBRS_FLYBY | CBRS_RIGHT | CBRS_SIZE_DYNAMIC, IDD_OBJPROP))
	{
		MessageBox("Failed To Create Properties Dialog Box!", "Error!");
		return FALSE;
	}
	pObjProp->ShowWindow(SW_SHOW);
	pObjProp->EnableDocking(CBRS_ALIGN_ANY);
	pObjProp->UpdateWindow();

	if (!pObjList->Create(this, IDD_OBJLIST, 
		CBRS_FLYBY | CBRS_LEFT | CBRS_SIZE_DYNAMIC, IDD_OBJLIST))
	{
		MessageBox("Failed To Create Object List Dialog Box", "Error!");
		return FALSE;
	}
	pObjList->ShowWindow(SW_SHOW);
	pObjList->EnableDocking(CBRS_ALIGN_ANY);
	pObjList->UpdateWindow();

	return TRUE;
}

D3DGraphics* MainWin::InitD3DView()
{
	if (!m_bInitMainSplitter)
		return FALSE;
	CWnd* pPane = m_mainSplitter.GetPane(0, 0);
	
	RECT wr;
	pPane->GetWindowRect(&wr);

	gfx = NULL;

	gfx = new D3DGraphics(pPane->m_hWnd, wr.right - wr.left, wr.bottom - wr.top);
	if (gfx)
		return gfx;
	else
		return NULL;
}

void MainWin::MENUEXIT()
{
	PostQuitMessage(0);
}

void MainWin::ADDNEWEMPTY()
{
	theApp->curProject->GetScene()->AddGameObject();
	if (!UpdateObjectList())
		MessageBox("Failed To Update Object List!", "Error!");
}

void MainWin::WINDOWOBJPROPERTIES()
{
	if (pMenu->CheckMenuItem(ID_WINDOW_OBJECTPROPERTIES, MF_CHECKED) == MF_UNCHECKED)
	{
		EnableDocking(CBRS_ALIGN_RIGHT);
		pObjProp->ShowWindow(SW_SHOW);
		DockControlBar(pObjProp);
	}
	else if (pMenu->CheckMenuItem(ID_WINDOW_OBJECTPROPERTIES, MF_UNCHECKED) == MF_CHECKED)
	{
		
		CPoint point(100, 100);
		FloatControlBar(pObjProp, point);
	}
	else
	{
		MessageBox("An Unknown Non-Fatal Error Occured");
	}
}

BOOL MainWin::UpdateObjectList()
{
	int nSceneObjects = theApp->curProject->GetScene()->GetNumberOfObjects();
	CListBox * pObjLIST = (CListBox *)pObjList->GetDlgItem(IDC_OBJLIST);
	int curSelected = pObjLIST->GetCurSel();

	if (pObjLIST)
	{
		pObjLIST->ResetContent();
		for (int ID = 0; ID < nSceneObjects; ID++)
		{
			char objName[512];
			Scene* scene = theApp->curProject->GetScene();
			if (scene)
				scene->GetObjectName(objName, 512, ID);
			if (pObjLIST->AddString(objName) == LB_ERR)
			{
				char errorMsg[512];
				sprintf_s(errorMsg, "Error Adding Object '%s' To List", objName);
				MessageBox(errorMsg, "Error!");
				return false;
			}
		}
	}
	else
		return false;
	pObjLIST->SetCurSel(curSelected);
	return true;
}