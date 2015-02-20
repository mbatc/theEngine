#include <afxcmn.h>
#include "DialogObjProp.h"
#include "DialogObjList.h"
#include "MainWin.h"
#include "MainApp.h"
#include "Project.h"
#include "Scene.h"
#include "Gameobject.h"
#include "Component.h"
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

	ON_CBN_SELCHANGE(IDC_CBCOMPONENT, op_compcb)
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

void DialogObjProp::ResetContent()
{
	CEdit* pXPos = (CEdit*)GetDlgItem(IDC_XPOS);
	if (!pXPos)
		return;
		pXPos->SetWindowText(NULL);
	CEdit* pYPos = (CEdit*)GetDlgItem(IDC_YPOS);
	if (!pYPos)
		return;
		pYPos->SetWindowText(NULL);
	CEdit* pZPos = (CEdit*)GetDlgItem(IDC_ZPOS);
	if (!pZPos)
		return;
		pZPos->SetWindowText(NULL);
	CEdit* pXRot = (CEdit*)GetDlgItem(IDC_XROT);
	if (!pXRot)
		return;
		pXRot->SetWindowText(NULL);
	CEdit* pYRot = (CEdit*)GetDlgItem(IDC_YROT);
	if (!pYRot)
		return;
		pYRot->SetWindowText(NULL);
	CEdit* pZRot = (CEdit*)GetDlgItem(IDC_ZROT);
	if (!pZRot)
		return;
		pZRot->SetWindowText(NULL);
	CEdit* pXScl = (CEdit*)GetDlgItem(IDC_XSCL);
	if (!pXScl)
		return;
		pXScl->SetWindowText(NULL);
	CEdit* pYScl = (CEdit*)GetDlgItem(IDC_YSCL);
	if (!pYScl)
		return;
		pYScl->SetWindowText(NULL);
	CEdit* pZScl = (CEdit*)GetDlgItem(IDC_ZSCL);
	if (!pZScl)
		return;
		pZScl->SetWindowText(NULL);
	CEdit* pName = (CEdit*)GetDlgItem(IDC_OBJNME);
	if (!pName)
		return;
		pName->SetWindowText(NULL);
	CComboBox* pCList = (CComboBox*)GetDlgItem(IDC_CBCOMPONENT);
	if (!pCList)
		return;
		pCList->ResetContent();	
}

void DialogObjProp::OP_COMPCB()
{
	CComboBox* complb = (CComboBox*)GetDlgItem(IDC_CBCOMPONENT);
	CListBox* objList = (CListBox*)parentWnd->GetObjList()->GetDlgItem(IDC_OBJLIST);
	int curSel = complb->GetCurSel() ;
	Gameobject* obj = parentWnd->theApp->GetProject()->GetScene()->GetSceneObject(objList->GetCurSel());
	Component* compSel = obj->GetComponent(curSel);
	if (strcmp(compSel->GetIdentifier(),CTYPE_MESHRENDERER))
	{
		ClearTempIDS();

		RECT tr;

		tr.top = 275;
		tr.left = 40;
		tr.bottom = tr.top + 20;
		tr.right = tr.left + 120;

		CStatic* text = new CStatic();
		text->Create("Linked Mesh: ",WS_VISIBLE,tr,this,TEMPID_0);
		text->ShowWindow(SW_SHOW);

		tr.top = 300;
		tr.bottom = tr.top + 30;
		CComboBoxEx* cb = new CComboBoxEx();
		cb->Create(WS_VISIBLE,tr,this,TEMPID_1);
		cb->ShowWindow(SW_SHOW);
		for (int i = 0, ListItem = 1; i < obj->GetNumberOfComponent(); i++)
		{
			if (strcmp(obj->GetComponent(i)->GetIdentifier(), CTYPE_MESH) )
			{
				char name[512];
				obj->GetComponent(i)->GetName(name, 512);
				cb->AddString(name);
				cb->SetItemData(ListItem, i);
				ListItem++;
			}
		}
	}
}

void DialogObjProp::ClearTempIDS()
{
	CWnd* tempWnd_0 = GetDlgItem(TEMPID_0);
	CWnd* tempWnd_1 = GetDlgItem(TEMPID_1);
	CWnd* tempWnd_2 = GetDlgItem(TEMPID_2);
	CWnd* tempWnd_3 = GetDlgItem(TEMPID_3);
	CWnd* tempWnd_4 = GetDlgItem(TEMPID_4);
	CWnd* tempWnd_5 = GetDlgItem(TEMPID_5);
	CWnd* tempWnd_6 = GetDlgItem(TEMPID_6);
	if (tempWnd_0)
	{
		tempWnd_0->DestroyWindow();
		delete tempWnd_0;
		tempWnd_0 = NULL;
	}

	if (tempWnd_1)
	{
		tempWnd_1->DestroyWindow();
		delete tempWnd_1;
		tempWnd_1 = NULL;
	}


	if (tempWnd_2)
	{
		tempWnd_2->DestroyWindow();
		delete tempWnd_2;
		tempWnd_2 = NULL;
	}


	if (tempWnd_3)
	{
		tempWnd_3->DestroyWindow();
		delete tempWnd_3;
		tempWnd_3 = NULL;
	}

	if (tempWnd_4)
	{
		tempWnd_4->DestroyWindow();
		delete tempWnd_4;
		tempWnd_4 = NULL;
	}

	if (tempWnd_5)
	{
		tempWnd_5->DestroyWindow();
		delete tempWnd_5;
		tempWnd_5 = NULL;
	}

	if (tempWnd_6)
	{
		tempWnd_6->DestroyWindow();
		delete tempWnd_6;
		tempWnd_6 = NULL;
	}
}