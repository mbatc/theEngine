#include "MaterialEditor.h"
#include "MainWin.h"
#include "PrimitiveDefinitions.h"
#include "resource.h"

void Material::SetTextureName(char* buffer, int bufLen)
{
	TextureName.SetString(buffer);
}

void Material::GetDiffuseFloatRGBA(float* r, float* g, float* b, float* a)
{
	*a = (float)diffuse.a / (float)255;
	*r = (float)diffuse.r / (float)255;
	*g = (float)diffuse.g / (float)255;
	*b = (float)diffuse.b / (float)255;
}
void Material::GetSpecularFloatRGBA(float* r, float* g, float* b, float* a)
{

	*a = (float)specular.a / (float)255;
	*r = (float)specular.r / (float)255;
	*g = (float)specular.g / (float)255;
	*b = (float)specular.b / (float)255;
}
void Material::GetAmbientFloatRGBA(float* r, float* g, float* b, float* a)
{

	*a = (float)ambient.a / (float)255;
	*r = (float)ambient.r / (float)255;
	*g = (float)ambient.g / (float)255;
	*b = (float)ambient.b / (float)255;
}

void Material::SetDiffuse(float r, float g, float b, float a)
{
	diffuse.a = a * 255;
	diffuse.r = r * 255;
	diffuse.g = g * 255;
	diffuse.b = b * 255;
}
void Material::SetAmbient(float r, float g, float b, float a)
{
	ambient.a = a * 255;
	ambient.r = r * 255;
	ambient.g = g * 255;
	ambient.b = b * 255;
}
void Material::SetSpecular(float r, float g, float b, float a)
{
	specular.a = a * 255;
	specular.r = r * 255;
	specular.g = g * 255;
	specular.b = b * 255;
}

void Material::GetTextureName(char* buffer, int bufLen)
{
	ZeroMemory(buffer, sizeof(char)*bufLen);

	int nameLen = TextureName.GetLength();
	for (int i = 0; i < bufLen && i < nameLen; i++)
	{
		buffer[i] = (TextureName.GetBuffer())[i];
	}
}

BEGIN_MESSAGE_MAP(MaterialEditor,CDialog)
	ON_EN_KILLFOCUS(IDC_DIF_R, OnDifR)
	ON_EN_KILLFOCUS(IDC_DIF_G, OnDifG)
	ON_EN_KILLFOCUS(IDC_DIF_B, OnDifB)
	ON_EN_KILLFOCUS(IDC_SPEC_R, OnSpecR)
	ON_EN_KILLFOCUS(IDC_SPEC_G, OnSpecG)
	ON_EN_KILLFOCUS(IDC_SPEC_B, OnSpecB)
	ON_EN_KILLFOCUS(IDC_AMB_R, OnAmbR)
	ON_EN_KILLFOCUS(IDC_AMB_G, OnAmbG)
	ON_EN_KILLFOCUS(IDC_AMB_B, OnAmbB)

	ON_EN_KILLFOCUS(IDC_TEXBROWSE, OnTexChange)

	ON_COMMAND(IDC_OKBT,OnOk)
	ON_COMMAND(IDC_CANCELBT,OnCancel)
END_MESSAGE_MAP()

MaterialEditor::MaterialEditor(MainWin* parent, int objID, D3DMATERIAL9 tMat)
	:
	gfx(NULL),
	ObjID(objID),
	parent(parent)
{
	Create(IDD_MATERIALDIALOG,parent);
	ShowWindow(SW_SHOW);
	CWnd* view = GetDlgItem(IDC_MATVIEW);
	HWND viewWnd = view->m_hWnd;
	CRect tr;
	view->GetClientRect(&tr);
	gfx = new D3DGraphics(viewWnd,tr.Width(),tr.Height());

	camera = new Camera();
	camera->GetTransform()->SetTranslation(0.0f, 0.0f, 2.5f);
	obj = new Gameobject();
	meshID = obj->AddComponent((Component*)new Mesh(obj, *gfx));
	int RendererID = obj->AddComponent((Component*)new MeshRenderer(obj));
	((MeshRenderer*)obj->GetComponent(RendererID))->SetMeshPointer((Mesh*)obj->GetComponent(meshID), meshID );

	light = new Light(*gfx, 0);
	light->GetTransform()->SetTranslation(0.0f, 2.5f, 5.0f);

	mat.SetAmbient(tMat.Ambient.r, tMat.Ambient.g, tMat.Ambient.b, tMat.Ambient.a);
	mat.SetDiffuse(tMat.Diffuse.r, tMat.Diffuse.g, tMat.Diffuse.b, tMat.Diffuse.a);
	mat.SetSpecular(tMat.Specular.r, tMat.Specular.g, tMat.Specular.b, tMat.Specular.a);

	CEdit* difR = (CEdit*)GetDlgItem(IDC_DIF_R);
	CEdit* difG = (CEdit*)GetDlgItem(IDC_DIF_G);
	CEdit* difB = (CEdit*)GetDlgItem(IDC_DIF_B);

	CEdit* ambR = (CEdit*)GetDlgItem(IDC_AMB_R);
	CEdit* ambG = (CEdit*)GetDlgItem(IDC_AMB_G);
	CEdit* ambB = (CEdit*)GetDlgItem(IDC_AMB_B);

	CEdit* specR = (CEdit*)GetDlgItem(IDC_SPEC_R);
	CEdit* specG = (CEdit*)GetDlgItem(IDC_SPEC_G);
	CEdit* specB = (CEdit*)GetDlgItem(IDC_SPEC_B);

	char t_difR[256]  = {0};
	char t_difG[256]  = {0};
	char t_difB[256]  = {0};
	char t_ambR[256]  = {0};
	char t_ambG[256]  = {0};
	char t_ambB[256]  = {0};
	char t_specR[256] = {0};
	char t_specG[256] = {0};
	char t_specB[256] = {0};

	sprintf(t_difR, "%d\0",  mat.GetDiffuseR());
	sprintf(t_difG, "%d\0",  mat.GetDiffuseG());
	sprintf(t_difB, "%d\0",  mat.GetDiffuseB());
	sprintf(t_specR, "%d\0", mat.GetSpecularR());
	sprintf(t_specG, "%d\0", mat.GetSpecularG());
	sprintf(t_specB, "%d\0", mat.GetSpecularB());
	sprintf(t_ambR, "%d\0",  mat.GetAmbientR());
	sprintf(t_ambG, "%d\0",  mat.GetAmbientG());
	sprintf(t_ambB, "%d\0",  mat.GetAmbientB());

	difR->SetWindowTextA(t_difR);
	difG->SetWindowTextA(t_difG);
	difB->SetWindowTextA(t_difB);
	ambR->SetWindowTextA(t_ambR);
	ambG->SetWindowTextA(t_ambG);
	ambB->SetWindowTextA(t_ambB);
	specR->SetWindowTextA(t_specR);
	specG->SetWindowTextA(t_specG);
	specB->SetWindowTextA(t_specB);

	UpdateView();
}

MaterialEditor::~MaterialEditor()
{}

void MaterialEditor::Render()
{
	gfx->GetDevice()->SetFVF(CUSTOMFVF);
	camera->Render(*gfx);
	obj->Render(*gfx);
}

void MaterialEditor::ONDIFR() 
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_DIF_R);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetDiffuse(num, mat.GetDiffuseG(), mat.GetDiffuseB(), mat.GetDiffuseA());
	UpdateView();
}
void MaterialEditor::ONDIFG()
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_DIF_G);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetDiffuse(mat.GetDiffuseR(), num, mat.GetDiffuseB(), mat.GetDiffuseA());
	UpdateView();
}
void MaterialEditor::ONDIFB()
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_DIF_B);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetDiffuse(mat.GetDiffuseR(), mat.GetDiffuseG(), num, mat.GetDiffuseA());
	UpdateView();
}
void MaterialEditor::ONSPECR()
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_SPEC_R);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetSpecular(num, mat.GetSpecularG(), mat.GetSpecularB(), mat.GetSpecularA());
	UpdateView();
}
void MaterialEditor::ONSPECG()
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_SPEC_G);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetSpecular(mat.GetSpecularR(), num, mat.GetSpecularB(), mat.GetSpecularA());
	UpdateView();
}
void MaterialEditor::ONSPECB()
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_SPEC_B);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetSpecular(mat.GetSpecularR(), mat.GetSpecularG(), num, mat.GetSpecularA());
	UpdateView();
}
void MaterialEditor::ONAMBR() 
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_AMB_R);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetAmbient(num, mat.GetAmbientG(), mat.GetAmbientB(), mat.GetAmbientA());
	UpdateView();
}
void MaterialEditor::ONAMBG() 
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_AMB_G);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetAmbient(mat.GetAmbientR(), num, mat.GetAmbientB(), mat.GetAmbientA());
	UpdateView();
}
void MaterialEditor::ONAMBB() 
{
	CEdit* edit = (CEdit*)GetDlgItem(IDC_AMB_B);
	char text[256];
	edit->GetWindowTextA(text, 256);
	int num = atoi(text);
	mat.SetAmbient(mat.GetAmbientR(), mat.GetAmbientG(), num, mat.GetAmbientA());
	UpdateView();
}
void MaterialEditor::ONCANCEL() 
{
	this->~MaterialEditor();
}
void MaterialEditor::ONOK() 
{
	Mesh* mesh = (Mesh*)obj->GetComponent(meshID);
	char buffer[512] = { 0 };
	mat.GetTextureName(buffer, 512);
	parent->OnMaterialEditorOK(*mesh->GetMaterial(),buffer, ObjID);
	this->~MaterialEditor();
}

void MaterialEditor::ONTEXCHANGE()
{
	CMFCEditBrowseCtrl* edit = (CMFCEditBrowseCtrl*)GetDlgItem(IDC_TEXBROWSE);
	char text[256];
	edit->GetWindowTextA(text, 256);
	mat.SetTextureName(text, 256);
	((Mesh*)obj->GetComponent(meshID))->LoadTextureFromFile(text);
	UpdateView();
}