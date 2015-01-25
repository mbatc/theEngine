#include "DialogObjProp.h"
#include "DialogObjList.h"
#include "MainWin.h"
#include "MainApp.h"
#include "Project.h"
#include "Scene.h"
#include "Gameobject.h"
#include "Transform.h"
#include "resource.h"

BEGIN_MESSAGE_MAP(DialogObjProp,CDialogBar)
	ON_EN_KILLFOCUS(IDC_XPOS,op_xpos)
	ON_EN_KILLFOCUS(IDC_YPOS,op_ypos)
	ON_EN_KILLFOCUS(IDC_ZPOS,op_zpos)

	ON_EN_KILLFOCUS(IDC_XROT, op_xrot)
	ON_EN_KILLFOCUS(IDC_YROT, op_yrot)
	ON_EN_KILLFOCUS(IDC_ZROT, op_zrot)

	ON_EN_KILLFOCUS(IDC_XSCL, op_xscl)
	ON_EN_KILLFOCUS(IDC_YSCL, op_yscl)
	ON_EN_KILLFOCUS(IDC_ZSCL, op_zscl)

	ON_EN_KILLFOCUS(IDC_OBJNME, op_objnme)
END_MESSAGE_MAP()

void DialogObjProp::OP_XPOS()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_XPOS);
	char s_xpos[512];
	pXPos->GetWindowTextA(s_xpos,512);
	float xPos = atof(s_xpos);
	float yPos = objtransform->GetTranslation().y;
	float zPos = objtransform->GetTranslation().z;
	
	objtransform->SetTranslation(xPos, yPos, zPos);
}
void DialogObjProp::OP_YPOS()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_YPOS);
	char s_ypos[512];
	pXPos->GetWindowTextA(s_ypos, 512);
	float xPos = objtransform->GetTranslation().x;
	float yPos = atof(s_ypos);
	float zPos = objtransform->GetTranslation().z;

	objtransform->SetTranslation(xPos, yPos, zPos);
}
void DialogObjProp::OP_ZPOS()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_ZPOS);
	char s_zpos[512];
	pXPos->GetWindowTextA(s_zpos, 512);
	float xPos = objtransform->GetTranslation().x;
	float yPos = objtransform->GetTranslation().y;
	float zPos = atof(s_zpos);

	objtransform->SetTranslation(xPos, yPos, zPos);
}
void DialogObjProp::OP_XROT()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_XROT);
	char s_xrot[512];
	pXPos->GetWindowTextA(s_xrot, 512);
	float xRot = atof(s_xrot);
	float yRot = objtransform->GetRotation().y;
	float zRot = objtransform->GetRotation().z;

	objtransform->SetRotation(xRot, yRot, zRot);
}
void DialogObjProp::OP_YROT()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_YROT);
	char s_yrot[512];
	pXPos->GetWindowTextA(s_yrot, 512);
	float xRot = objtransform->GetRotation().x;
	float yRot = atof(s_yrot);
	float zRot = objtransform->GetRotation().z;

	objtransform->SetRotation(xRot, yRot, zRot);
}

void DialogObjProp::OP_ZROT()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject ->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_ZROT);
	char s_zrot[512];
	pXPos->GetWindowTextA(s_zrot, 512);
	float xRot = objtransform->GetRotation().x;
	float yRot = objtransform->GetRotation().y;
	float zRot = atof(s_zrot);

	objtransform->SetRotation(xRot, yRot, zRot);
}
void DialogObjProp::OP_XSCL()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_XSCL);
	char s_xscl[512];
	pXPos->GetWindowTextA(s_xscl, 512);
	float xScl = atof(s_xscl);
	float yScl = objtransform->GetScale().y;
	float zScl = objtransform->GetScale().z;

	objtransform->SetScale(xScl, yScl, zScl);
}
void DialogObjProp::OP_YSCL()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_YSCL);
	char s_yscl[512];
	pXPos->GetWindowTextA(s_yscl, 512);
	float xScl = objtransform->GetScale().x;
	float yScl = atof(s_yscl);
	float zScl = objtransform->GetScale().z;

	objtransform->SetScale(xScl, yScl, zScl);
}

void DialogObjProp::OP_ZSCL()
{
	CListBox* pObjList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	if (pObjList->GetCurSel() == LB_ERR)
	{
		MessageBox("No Object Selected.", "Notice.");
		return;
	}

	int ID = pObjList->GetCurSel();

	Transform* objtransform = parentWnd->theApp->curProject->GetScene()->GetSceneObject(ID)->GetTransform();
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_ZSCL);
	char s_zscl[512];
	pXPos->GetWindowTextA(s_zscl, 512);
	float xScl = objtransform->GetScale().x;
	float yScl = objtransform->GetScale().y;
	float zScl = atof(s_zscl);

	objtransform->SetScale(xScl, yScl, zScl);
}

void DialogObjProp::OP_OBJNME()
{
	CListBox*	pObjList	= (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	CEdit*		pObjNme		= (CEdit*)GetDlgItem(IDC_OBJNME);
	int ID = pObjList->GetCurSel();

	char name[512];
	pObjNme->GetWindowTextA(name, 512);
	parentWnd->theApp->curProject->GetScene()->SetObjectName(name, ID);
	if (!parentWnd->UpdateObjectList())
		MessageBox("Failed To Update Object List After Name Change!", "Error!");
}