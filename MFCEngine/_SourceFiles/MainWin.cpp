#include "MainApp.h"
#include "MainView.h"
#include "MainWin.h"
#include "D3DGraphics.h"
#include "Project.h"
#include "Scene.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(MainWin,CFrameWnd)
	ON_COMMAND(ID_FILE_EXIT, MenuExit)
	ON_COMMAND(ID_GAMEOBJECTADDNEW_EMPTY, AddnewEmpty )
	ON_COMMAND(ID_WINDOW_OBJECTPROPERTIES, WindowObjProperties)

	ON_COMMAND(IDC_XPOS, op_xpos )
	ON_COMMAND(IDC_YPOS, op_ypos )
	ON_COMMAND(IDC_ZPOS, op_zpos )
	ON_COMMAND(IDC_XROT, op_xrot )
	ON_COMMAND(IDC_YROT, op_yrot )
	ON_COMMAND(IDC_ZROT, op_zrot )
	ON_COMMAND(IDC_XSCL, op_xscl )
	ON_COMMAND(IDC_YSCL, op_yscl )
	ON_COMMAND(IDC_ZSCL, op_zscl )

	ON_COMMAND(IDC_OBJLIST, ol_objlist )

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
	
	InitDialogControls();
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
	pObjProp = new CDialogBar();
	if (!pObjProp)
		return FALSE;
	pObjList = new CDialogBar();
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

BOOL MainWin::InitDialogControls()
{
	//Set Up Pointers
	pObjXPOS = (CEdit *)GetDlgItem(IDC_XPOS);
	pObjYPOS = (CEdit *)GetDlgItem(IDC_YPOS);
	pObjZPOS = (CEdit *)GetDlgItem(IDC_ZPOS);
	if (!pObjXPOS || !pObjYPOS || !pObjZPOS)
		return FALSE;

	pObjXROT = (CEdit *)GetDlgItem(IDC_XROT);
	pObjYROT = (CEdit *)GetDlgItem(IDC_YROT);
	pObjZROT = (CEdit *)GetDlgItem(IDC_ZROT);
	if (!pObjXROT || !pObjYROT || !pObjZROT)
		return FALSE;

	pObjXSCL = (CEdit *)GetDlgItem(IDC_XSCL);
	pObjYSCL = (CEdit *)GetDlgItem(IDC_YSCL);
	pObjZSCL = (CEdit *)GetDlgItem(IDC_ZSCL);
	if (!pObjXSCL || !pObjYSCL || !pObjZSCL)
		return FALSE;

	pMFCBT = (CButton *)GetDlgItem(IDC_MFCBUTTON1);
	pNMLBT = (CButton *)GetDlgItem(IDC_BUTTON1);
	if (!pMFCBT || !pNMLBT)
		return FALSE;

	pObjLIST = (CListBox *)GetDlgItem(IDC_OBJLIST);
	if (!pObjLIST)
		return FALSE;

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

void MainWin::OP_XPOS(){}
void MainWin::OP_YPOS(){}
void MainWin::OP_ZPOS(){}
void MainWin::OP_XROT(){}
void MainWin::OP_YROT(){}
void MainWin::OP_ZROT(){}
void MainWin::OP_XSCL(){}
void MainWin::OP_YSCL(){}
void MainWin::OP_ZSCL(){}
void MainWin::OL_OBJLIST(){}