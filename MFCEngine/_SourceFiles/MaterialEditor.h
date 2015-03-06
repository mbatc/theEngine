#pragma once

#include <afxwin.h>
#include <shlobj.h>
#include <afxeditbrowsectrl.h>
#include "D3DGraphics.h"
#include "Gameobject.h"
#include "Light.h"
#include "Component.h"
#include "Camera.h"
#include "Mesh.h"
#include "MeshRenderer.h"
#include "resource.h"

class MainWin;

struct COLOR_RGB
{
	int r, g, b;
	int a;
};

class Material
{
public:
	Material()
	{}
	~Material()
	{}

	int GetDiffuseR(){ return diffuse.r; }
	int GetDiffuseG(){ return diffuse.g; }
	int GetDiffuseB(){ return diffuse.b; }
	int GetDiffuseA(){ return diffuse.a; }

	int GetSpecularR(){ return specular.r; }
	int GetSpecularG(){ return specular.g; }
	int GetSpecularB(){ return specular.b; }
	int GetSpecularA(){ return diffuse.a; }

	int GetAmbientR(){ return ambient.r; }
	int GetAmbientG(){ return ambient.g; }
	int GetAmbientB(){ return ambient.b; }
	int GetAmbientA(){ return diffuse.a; }

	void GetDiffuseFloatRGBA(float* r, float* g, float* b, float* a);
	void GetSpecularFloatRGBA(float* r, float* g, float* b, float* a);
	void GetAmbientFloatRGBA(float* r, float* g, float* b, float* a);

	COLOR_RGB GetDiffuse(){ return diffuse; }
	COLOR_RGB GetSpecular(){ return specular; }
	COLOR_RGB GetAmbient(){ return ambient; }

	void SetDiffuse(int r, int g, int b, int a){ diffuse.a = a;; diffuse.r = r; diffuse.g = g; diffuse.b = b; }
	void SetAmbient(int r, int g, int b, int a){ ambient.a = a;; ambient.r = r; ambient.g = g; ambient.b = b; }
	void SetSpecular(int r, int g, int b, int a){ specular.a = a;; specular.r = r; specular.g = g; specular.b = b; }

	void SetDiffuse(float r, float g, float b, float a);
	void SetAmbient(float r, float g, float b, float a);
	void SetSpecular(float r, float g, float b, float a);

	void GetTextureName(char* buffer, int bufLen);
	void SetTextureName(char* buffer, int bufLen);

private:
	COLOR_RGB diffuse;
	COLOR_RGB specular;
	COLOR_RGB ambient;

	CString TextureName;
};

class MaterialEditor : public CDialog
{
public:
	MaterialEditor(MainWin* parent,int objID, D3DMATERIAL9 mat);
	~MaterialEditor();

private:
	UINT meshID;

	void Render();
	
	void UpdateView()
	{
		Mesh* mesh = (Mesh*)obj->GetComponent(meshID);
		D3DMATERIAL9 newMat;
		mat.GetAmbientFloatRGBA(&newMat.Ambient.r,
			&newMat.Ambient.g,
			&newMat.Ambient.b,
			&newMat.Ambient.a);
		mat.GetSpecularFloatRGBA(&newMat.Specular.r,
			&newMat.Specular.g,
			&newMat.Specular.b,
			&newMat.Specular.a);
		mat.GetDiffuseFloatRGBA(&newMat.Diffuse.r,
			&newMat.Diffuse.g,
			&newMat.Diffuse.b,
			&newMat.Diffuse.a);
		mesh->SetMaterial(newMat);

		light->Update();
		obj->Update();

		gfx->BeginFrame();
		Render();
		gfx->EndFrame();
	}

	afx_msg void OnDifR() { ONDIFR(); }
	afx_msg void OnDifG() { ONDIFG(); }
	afx_msg void OnDifB() { ONDIFB(); }
	afx_msg void OnSpecR(){ ONSPECR(); }
	afx_msg void OnSpecG(){ ONSPECG(); }
	afx_msg void OnSpecB(){ ONSPECB(); }
	afx_msg void OnAmbR() { ONAMBR(); }
	afx_msg void OnAmbG() { ONAMBG(); }
	afx_msg void OnAmbB() { ONAMBB(); }
	afx_msg void OnOk()		{ ONOK(); }
	afx_msg void OnCancel()	{ ONCANCEL(); }
	afx_msg void OnTexChange() { ONTEXCHANGE(); }

	void ONDIFR();
	void ONDIFG();
	void ONDIFB();
	void ONSPECR();
	void ONSPECG();
	void ONSPECB();
	void ONAMBR();
	void ONAMBG();
	void ONAMBB();
	void ONOK();
	void ONCANCEL();
	void ONTEXCHANGE();

	Material mat;
	D3DGraphics* gfx;

	Camera* camera;
	Gameobject* obj;
	Light* light;

	int ObjID;
	MainWin* parent;

	DECLARE_MESSAGE_MAP();
};