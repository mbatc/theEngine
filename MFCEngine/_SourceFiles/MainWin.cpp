#include "MainApp.h"
#include "MainView.h"
#include "MainWin.h"
#include "GlobalPointers.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
#include "Gameobject.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "Rotation.h"
#include "PrimitiveDefinitions.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(MainWin,CFrameWnd)
	ON_COMMAND(ID_FILE_EXIT, MenuExit)

	ON_COMMAND(ID_GAMEOBJECTADDNEW_CUBE, AddnewCube)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_LIGHT, AddnewLight)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_EMPTY, AddnewEmpty )
	ON_COMMAND(IDC_DELETEOBJECT, DeleteObject)
	ON_COMMAND(ID_FILESAVEAS_SCENE, FilesaveasScene)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_PLANE, AddnewPlane )

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
		CSize(cr.Width(), (cr.Height() - 200)/2), pContext))
	{
		MessageBox("Failed To Create Splitter View!", "Error!",
			MB_OK | MB_ICONERROR);
		return FALSE;
	}
	if (!m_mainSplitter.CreateView(1, 0, RUNTIME_CLASS(MainView),
		CSize(cr.Width(), (cr.Height() - 200)/2), pContext) )
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
	pConsoleWindow = new CDialogBar();
	if (!pConsoleWindow)
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
		m_mainSplitter.SetColumnInfo(0, cx, 0);
		m_mainSplitter.SetRowInfo(0, cr.Height() / 2, 50);
		m_mainSplitter.SetRowInfo(1, cr.Height() / 2, 50);
		m_mainSplitter.RecalcLayout();
	}
}

BOOL MainWin::InitDockablePanels()
{
	EnableDocking(CBRS_ALIGN_ANY);
	if (!pObjProp->Create(this, IDD_OBJPROPERTIES, 
		CBRS_FLYBY | CBRS_RIGHT | CBRS_SIZE_DYNAMIC, IDD_OBJPROP))
	{
		MessageBox("Failed To Create Properties Dialog Box!", "Error!");
		return FALSE;
	}
	pObjProp->ShowWindow(SW_SHOW);
	pObjProp->EnableDocking(CBRS_ALIGN_ANY);
	pObjProp->UpdateWindow();

	RECT br;
	br.top = 275;
	br.left = 40;
	br.bottom = br.top + 155;
	br.right = br.left + 120;
	CButton* tempButton = new CButton();
	tempButton->Create("STUFF", WS_VISIBLE, br, pObjProp, pObjProp->TEMPID_0);
	tempButton->ShowWindow(SW_SHOW);

	if (!pObjList->Create(this, IDD_OBJLIST, 
		CBRS_FLYBY | CBRS_LEFT | CBRS_SIZE_DYNAMIC, IDD_OBJLIST))
	{
		MessageBox("Failed To Create Object List Dialog Box", "Error!");
		return FALSE;
	}
	pObjList->ShowWindow(SW_SHOW);
	pObjList->EnableDocking(CBRS_ALIGN_ANY);
	pObjList->UpdateWindow();

	pConsoleWindow->Create(this, IDD_CONSOLE, CBRS_BOTTOM | CBRS_SIZE_DYNAMIC, ID_CONSOLE);
	pConsoleWindow->ShowWindow(SW_SHOW);
	
	InitConsoleWindow();
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

void MainWin::InitConsoleWindow()
{
	CRect tr;
	pConsoleWindow->GetClientRect(tr);

	tr.top += 5;
	tr.left += 5;
	tr.right -= 5;
	tr.bottom -= 5;

	CEdit* consoleEdit = (CEdit*)pConsoleWindow->GetDlgItem(ID_CONSOLEEDIT);
	consoleEdit->SetWindowText("Welcome To The Engines Console!");

	Console->SetEditPointer(pConsoleWindow);
	Console->Output("Console Object Created!");
}

void MainWin::MENUEXIT()
{
	PostQuitMessage(0);
}

void MainWin::ADDNEWEMPTY()
{

	theApp->curProject->LockScene();
	int ID = theApp->curProject->GetScene()->AddGameObject();
	char nb[] = { "New Empty Gameobject" };
	theApp->curProject->GetScene()->SetObjectName(nb, ID);
	theApp->curProject->UnlockScene();

	if (!UpdateObjectList())
		MessageBox("Failed To Update Object List!", "Error!");
}

void MainWin::ADDNEWLIGHT()
{
	theApp->curProject->LockScene();
	theApp->curProject->GetScene()->AddLightObject(*gfx);
	theApp->curProject->UnlockScene();

	CListBox * pObjLIST = (CListBox *)pObjList->GetDlgItem(IDC_OBJLIST);

	if (!UpdateObjectList())
		MessageBox("Failed To Update Object List!", "Error!");

	int curSelected = pObjLIST->GetCurSel();
	pObjLIST->SetCurSel(curSelected + 1);
}

void MainWin::ADDNEWCUBE()
{
	//Used so that the scene class is not accessed between threads!!
	theApp->curProject->LockScene();

	int ID = theApp->curProject->GetScene()->AddGameObject();
	if (ID == -1)
	{
		MessageBox("Failed To Create New Gameobject!", "Error!");
		return;
	}
	Gameobject* obj = theApp->curProject->GetScene()->GetSceneObject(ID);
	int meshID =		obj->AddComponent((Component*)new Mesh(obj, *gfx));
	int meshRendID =	obj->AddComponent((Component*)new MeshRenderer(obj));
	((MeshRenderer*)obj->GetComponent(meshRendID))->SetMeshPointer((Mesh*)obj->GetComponent(meshID),meshID);
	((Mesh*)obj->GetComponent(meshID))->LoadFromFile("TestObj.obj");

	theApp->curProject->UnlockScene();

	if (!UpdateObjectList())
		MessageBox("Failed To Update Object List!", "Error!");
}

void MainWin::ADDNEWPLANE()
{
	theApp->curProject->LockScene();
	int ID = theApp->curProject->GetScene()->AddGameObject();
	if (ID == -1)
	{
		MessageBox("Failed To Create New Gameobject!", "Error!");
		return;
	}
	Gameobject* obj = theApp->curProject->GetScene()->GetSceneObject(ID);
	int meshID = obj->AddComponent((Component*)new Mesh(obj, *gfx));
	int meshRendID = obj->AddComponent((Component*)new MeshRenderer(obj));
	((MeshRenderer*)obj->GetComponent(meshRendID))->SetMeshPointer((Mesh*)obj->GetComponent(meshID), meshID);
	((Mesh*)obj->GetComponent(meshID))->LoadPrimitive(PM_PLANE, PRM_PLANE, PRMIB_PLANE,
		sizeof(PRM_PLANE) / sizeof(CUSTOMVERTEX), sizeof(PRMIB_PLANE) / sizeof(short));

	theApp->curProject->UnlockScene();

	if (!UpdateObjectList())
		MessageBox("Failed To Update Object List!", "Error!");
}

void MainWin::DELETEOBJECT()
{
	CListBox* ObjList = (CListBox*)pObjList->GetDlgItem(IDC_OBJLIST);
	int ID = ObjList->GetCurSel();

	theApp->GetProject()->LockScene();
	theApp->GetProject()->GetScene()->DeleteGameObject(ID);
	UpdateObjectList();
	theApp->GetProject()->UnlockScene();

	ObjList->SetCurSel(ID);
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

void MainWin::FILESAVEASSCENE()
{
	CFileDialog fileDialog(FALSE);
	fileDialog.DoModal();
	OPENFILENAME& ofn = fileDialog.GetOFN();
	ofn.lpstrDefExt = ".scene";
	char filepath[512] = { 0 };
	sprintf_s(filepath,sizeof(filepath),"%s",fileDialog.GetPathName().GetString() );
	if (filepath)
		theApp->GetProject()->SaveScene(filepath);
	else
		MessageBox("Could Not Save To That Directory!", "Error!");
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
	if (pObjLIST->GetCount() == 0)
		pObjProp->ResetContent();
	return true;
}