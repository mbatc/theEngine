#include "MainApp.h"
#include "MainView.h"
#include "MainWin.h"
#include "GlobalPointers.h"
#include "PlayerControl.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
#include "Gameobject.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "PrimitiveDefinitions.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(MainWin,CFrameWnd)
	ON_COMMAND(ID_FILE_EXIT, MenuExit)

	ON_COMMAND(ID_GAMEOBJECTADDNEW_CUBE, AddnewCube)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_LIGHT, AddnewLight)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_EMPTY, AddnewEmpty)
	ON_COMMAND(IDC_DELETEOBJECT, DeleteObject)
	ON_COMMAND(ID_FILESAVEAS_SCENE, FilesaveasScene)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_PLANE, AddnewPlane)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_MESHFROMFILE, AddnewMeshFromFile)

	ON_COMMAND(ID_CONTROL_PLAYERCONTROL, AddComp_PlayerControl)

	ON_COMMAND(ID_WINDOW_OBJECTPROPERTIES, WindowObjProperties)

	ON_COMMAND(ID_EDIT_MATERIALEDITOR, EditMaterialEditor )
END_MESSAGE_MAP()

MainWin::MainWin(MainApp * app)
	:
	theApp(app),
	m_mainSplitter(),
	materialEditor(NULL)
{
	kServ = new KeyboardServer();
	mServ = new MouseServer();

	m_bInitMainSplitter = FALSE;
	CRect tr(0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
	Create(NULL, "TheEngine",WS_MAXIMIZE | WS_BORDER | WS_CAPTION | WS_SYSMENU | 
		WS_THICKFRAME | WS_MAXIMIZEBOX | WS_MINIMIZEBOX,
		tr);
	if (!InitDialogPointers())
		MessageBox("Control Pointers Failed To Initialise!", "Error!");

	pMenu->LoadMenuA(IDR_MENU1);
	SetMenu(pMenu);

	m_mainSplitter.SetAppPointer(theApp);

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

	if (!m_mainSplitter.CreateView(0, 0, RUNTIME_CLASS(MainView),
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
	theApp->curProject->GetScene()->SetObjectName("New Cube", ID);

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
	theApp->curProject->GetScene()->SetObjectName("New Plane", ID);

	theApp->curProject->UnlockScene();

	if (!UpdateObjectList())
		MessageBox("Failed To Update Object List!", "Error!");
}

void MainWin::ADDMESHFROMFILE()
{
	//Used so that the scene class is not accessed between threads!!
	CFileDialog fileDialog(TRUE,NULL,NULL,6UL,"Wavefront OBJ (*.obj)|*.obj||");
	fileDialog.DoModal();
	OPENFILENAME& ofn = fileDialog.GetOFN();
	char filepath[512] = { 0 };
	sprintf_s(filepath, sizeof(filepath), "%s", fileDialog.GetPathName().GetString());

	if (filepath[0] == '\0')
		return;

	int nameStart = 0;
	for (nameStart = sizeof(filepath) / sizeof(char);
		nameStart <= 0 || filepath[nameStart] != '\\';
		nameStart--);

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
	if (filepath)
	{
		((Mesh*)obj->GetComponent(meshID))->LoadFromFile(filepath);
		theApp->curProject->GetScene()->SetObjectName(&filepath[nameStart + 1], ID);
	}
	else { MessageBox("Failed To Open File!", "Error!"); }


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

void MainWin::ADDCOMP_PLAYERCONTROL()
{
	int curSel = ((CListBox*)pObjList->GetDlgItem(IDC_OBJLIST))->GetCurSel();

	theApp->GetProject()->LockScene();
	Gameobject* obj = theApp->GetProject()->GetScene()->GetSceneObject(curSel);
	obj->AddComponent((Component*)new PlayerControl(obj));
	theApp->GetProject()->UnlockScene();
}

void MainWin::EDITMATERIALEDITOR()
{
	int ID = ((CListBox*)pObjList->GetDlgItem(IDC_OBJLIST))->GetCurSel();
	if (ID == -1)
	{
		MessageBox("No Object Selected!","Notice!");
		return;
	}
	Gameobject* obj = theApp->GetProject()->GetScene()->GetSceneObject(ID);
	int MeshID = -1;
	for (int i = 0; i < obj->GetNumberOfComponent(); i++)
	{
		if (!strcmp(obj->GetComponent(i)->GetIdentifier(), CTYPE_MESH))
		{
			MeshID = i;
			break;
		}
	}

	if (MeshID != -1)
	{
		materialEditor = new MaterialEditor(this, ID, *((Mesh*)obj->GetComponent(MeshID))->GetMaterial());
		if (!materialEditor)
			MessageBoxA("Could Not Initialize Material Editor!", "Error!");
	}
	else
	{
		MessageBox("No Mesh Exists On Selected Object!", "Notice!");
	}
}

void MainWin::OnMaterialEditorOK(D3DMATERIAL9 mat,char* textureName, int ObjID)
{
	Gameobject* obj = theApp->GetProject()->GetScene()->GetSceneObject(ObjID);
	int MeshID = -1;
	for (int i = 0; i < obj->GetNumberOfComponent(); i++)
	{
		if (!strcmp(obj->GetComponent(i)->GetIdentifier(), CTYPE_MESH))
		{
			MeshID = i;
			break;
		}
	}
	if (MeshID != -1)
	{
		((Mesh*)obj->GetComponent(MeshID))->SetMaterial(mat);
		((Mesh*)obj->GetComponent(MeshID))->LoadTextureFromFile(textureName);
	}
	else
		MessageBox("No Mesh On Selected Object!", "Notice!");
}