#include "DialogObjList.h"
#include "DialogObjProp.h"
#include "MainWin.h"
#include "MainApp.h"
#include "Gameobject.h"
#include "Transform.h"
#include "Project.h"
#include "Scene.h"
#include "resource.h"
BEGIN_MESSAGE_MAP(DialogObjList,CDialogBar)
	ON_LBN_SELCHANGE(IDC_OBJLIST,ol_objlist)
END_MESSAGE_MAP()

void DialogObjList::OL_OBJLIST()
{
	int ID = ((CListBox*)GetDlgItem(IDC_OBJLIST))->GetCurSel();

	CEdit* pXPOS = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_XPOS);
	CEdit* pYPOS = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_YPOS);
	CEdit* pZPOS = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_ZPOS);

	CEdit* pXROT = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_XROT);
	CEdit* pYROT = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_YROT);
	CEdit* pZROT = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_ZROT);

	CEdit* pXSCL = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_XSCL);
	CEdit* pYSCL = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_YSCL);
	CEdit* pZSCL = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_ZSCL);

	CEdit* pNAME = (CEdit*)parentWnd->GetObjProp()->GetDlgItem(IDC_OBJNME);

	Transform * curTrans = parentWnd->theApp->curProject->GetScene()->GetSceneObject( ID )->GetTransform();
	
	char xpos[512];
	char ypos[512];
	char zpos[512];
	char xrot[512];
	char yrot[512];
	char zrot[512];
	char xscl[512];
	char yscl[512];
	char zscl[512];
	char name[512];

	sprintf_s(xpos, "%g\0", curTrans->GetTranslation().x);
	sprintf_s(ypos, "%g\0", curTrans->GetTranslation().y);
	sprintf_s(zpos, "%g\0", curTrans->GetTranslation().z);
	sprintf_s(xrot, "%g\0", curTrans->GetRotation().x	);
	sprintf_s(yrot, "%g\0", curTrans->GetRotation().y	);
	sprintf_s(zrot, "%g\0", curTrans->GetRotation().z	);
	sprintf_s(xscl, "%g\0", curTrans->GetScale().x		);
	sprintf_s(yscl, "%g\0", curTrans->GetScale().y		);
	sprintf_s(zscl, "%g\0", curTrans->GetScale().z		);
	parentWnd->theApp->curProject->GetScene()->GetObjectName(name, 512, ID);

	pXPOS->SetWindowText(xpos);
	pYPOS->SetWindowText(ypos);
	pZPOS->SetWindowText(zpos);
	pXROT->SetWindowText(xrot);
	pYROT->SetWindowText(yrot);
	pZROT->SetWindowText(zrot);
	pXSCL->SetWindowText(xscl);
	pYSCL->SetWindowText(yscl);
	pZSCL->SetWindowText(zscl);
	pNAME->SetWindowText(name);
}