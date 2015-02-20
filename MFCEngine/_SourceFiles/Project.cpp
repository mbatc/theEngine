#include <stdio.h>
#include <iostream>
#include "PrimitiveDefinitions.h"
#include "Project.h"
#include "MeshRenderer.h"
#include "Mesh.h"
#include "Scene.h"
#include "Gameobject.h"
#include "Component.h"

Project::Project(char* filename, D3DGraphics& gfx, CreateState cs)
	:
	sceneLocked(false)
{
	switch (cs)
	{
	case CREATENEW:
		Nullify();
		break;
	case LOAD:
		if (!LoadProject(filename, gfx))
		{

		}
		break;
	}
}

Project::~Project()
{

}

void Project::Nullify()
{
	if (sceneDB)
	{
		delete sceneDB;
		sceneDB = nullptr;
	}

	curScene = new Scene();
}

void Project::Update()
{ 
	curScene->UpdateScene();
}

bool Project::LoadProject(char* filename, D3DGraphics& gfx)
{
	Nullify();
	int currentObj = 0;
	int nObjects = 0;
	FILE* pFile;
	fopen_s(&pFile,filename, "r");
	do
	{
		if (!feof(pFile))
		{
			char buffer[1024] = { 0 };
			fscanf(pFile, "%s", buffer);
			if (strcmp(buffer, "*") == 0)
			{
				fscanf(pFile, "%s", buffer);
				if (strcmp(buffer, "SCENE") == 0)
				{
					fscanf(pFile, "%s", buffer);
					curScene->SetName(buffer);
				}
				else if (strcmp(buffer, "GAMEOBJECTS") == 0)
				{
					fscanf(pFile, "%d", &nObjects);
				}
			}
			else if (strcmp(buffer, "~") == 0)
			{
				fscanf(pFile, "%s", buffer);
				ProcessFileID(pFile, gfx, buffer, &currentObj);
			}
		}
	} while (!feof(pFile));
	fclose(pFile);

	return true;
}

void Project::ProcessFileID(FILE* pFile, D3DGraphics& gfx, char* ID, int* objID)
{
	char buffer[512] = { 0 };
	if (strcmp(ID, "object") == 0)
	{

		fscanf(pFile, "%s", buffer);
		if (strcmp(buffer, "GAMELIGHT") == 0)
		{
			curScene->AddLightObject(gfx);
		}
		else if (strcmp(buffer, "GAMEOBJECT") == 0)
		{
			curScene->AddGameObject();
		}
		fscanf(pFile, "%s", buffer);
		curScene->SetObjectName(buffer, *	objID);
		return;
	}
	else if (strcmp(ID, "/object") == 0)
	{
		*objID += 1;
		return;
	}
	else if (strcmp(ID, "transform") == 0)
	{
		Transform* t = curScene->GetSceneObject(*objID)->GetTransform();
		float xPos = 0.0f, 
			yPos = 0.0f, 
			zPos = 0.0f, 
			xRot = 0.0f, 
			yRot = 0.0f, 
			zRot = 0.0f, 
			xScl = 0.0f, 
			yScl = 0.0f, 
			zScl = 0.0f;

		fscanf(pFile, "%f%f%f%f%f%f%f%f%f",&xPos, &yPos, &zPos, &xRot, &yRot, &zRot, &xScl, &yScl, &zScl);
		t->SetTranslation(xPos, yPos, zPos);
		t->SetRotation(xRot, yRot, zRot );
		t->SetScale(xScl, yScl, zScl);
		return;
	}
	else if (strcmp(ID, "C_MESH") == 0)
	{
		int type = 0;
		Gameobject* obj = curScene->GetSceneObject(*objID);
		int compID = obj->AddComponent(new Mesh(obj, gfx));
		fscanf(pFile, "%s", buffer);
		if (strcmp(buffer, "TYPE"))
		{
			fscanf(pFile, "%d", &type);
			switch (type)
			{
			case (int)PM_CUBE:
				((Mesh*)obj->GetComponent(compID))->LoadPrimitive((PRIMITIVEMESH)type,
					PRM_CUBE,
					PRMIB_CUBE, 
					sizeof(PRM_CUBE)/sizeof(CUSTOMVERTEX),
					sizeof(PRMIB_CUBE)/sizeof(short));
			case (int)PM_PLANE:
				((Mesh*)obj->GetComponent(compID))->LoadPrimitive((PRIMITIVEMESH)type,
					PRM_PLANE,
					PRMIB_PLANE,
					sizeof(PRM_PLANE) / sizeof(CUSTOMVERTEX),
					sizeof(PRMIB_PLANE) / sizeof(short));
			case (int)PM_MESH:
				MessageBox(NULL, "Mesh Not Supported Yet", "Notice", MB_OK | MB_ICONINFORMATION);
			}
		}
		return;
	}
	else if (strcmp(ID, "C_MESHRENDERER") == 0)
	{
		Gameobject* obj = curScene->GetSceneObject(*objID);
		int meshID = 0;
		fscanf(pFile, "%s", buffer);
		if (strcmp(buffer, "MESH-ID") == 0)
		{
			fscanf(pFile, "%d", &meshID);
			Mesh* mesh = (Mesh*)obj->GetComponent(meshID);
			int rendererID = obj->AddComponent(new MeshRenderer(obj));
			((MeshRenderer*)obj->GetComponent(rendererID))->SetMeshPointer(mesh, meshID);
		}
		return;
	}
}

bool Project::SaveScene(char* filename)
{
	//FILE OUTLINE
	/**scenename name

		* gameobjects nObjects

			~object name
			~Transform 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0 1.0
			~components nComponents
				~COMP_TYPE COMP_INFO
				~COMP_TYPE COMP_INFO
			~/ object
			~object name
			~/ object*/
	FILE* pFile;
	fopen_s(&pFile,filename, "w");
	if (!pFile)
		return false;
	//Scene Name
	fprintf(pFile, "* SCENE ");
	fprintf(pFile, "%s\n", curScene->GetSceneName() );
	fprintf(pFile, "* GAMEOBJECTS %d\n",curScene->GetNumberOfObjects());

	for (int iObj = 0; iObj < GetScene()->GetNumberOfObjects();iObj++)
	{
		Gameobject* curObj = GetScene()->GetSceneObject(iObj);
		Transform* tran = curObj->GetTransform();
		char objName[512] = { 0 };
		int nCmp = GetScene()->GetSceneObject(iObj)->GetNumberOfComponent();
		GetScene()->GetObjectName(objName, 512, iObj);
		char* type = GetScene()->GetSceneObject(iObj)->GetPointerToType();
		fprintf(pFile, "\t~ object %s %s -\n",type ,objName);
		fprintf(pFile, "\t\t~ transform \t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f -\n",
			tran->GetTranslation().x,
			tran->GetTranslation().y,
			tran->GetTranslation().z,
			tran->GetRotation().x,
			tran->GetRotation().y,
			tran->GetRotation().z,
			tran->GetScale().x,
			tran->GetScale().y,
			tran->GetScale().z );
		for (int iCmp = 0; iCmp < nCmp; iCmp++)
		{
			fprintf(pFile, "\t\t~ %s", curObj->GetComponent(iCmp)->GetIdentifier() );
			SaveComponentInfo(pFile, curObj->GetComponent(iCmp)->GetIdentifier(), iCmp, iObj);
		}
		fprintf(pFile, "\t~ /object\n");
	}

	fclose(pFile);
	return true;
}

bool Project::SaveComponentInfo(FILE* pFile, char* ID, int compNum, int objNum)
{	
	if (!pFile)
	{
		MessageBox(NULL, "File Not Initialized!", "Error!", MB_OK | MB_ICONEXCLAMATION);
		fprintf(pFile, " -\n");
		return false;
	}

	if (strcmp(ID, "NULL") == 0)
	{
		fprintf(pFile, " -\n");
		return true;
	}
	else if (strcmp(ID, CTYPE_MESH) == 0)
	{
		int meshType = ((Mesh*)GetScene()->GetSceneObject(objNum)->GetComponent(compNum))->GetMeshType();
		if (meshType == -1)
			fprintf(pFile, "\tTYPE %d %s", meshType, "FILENAME");
		else
			fprintf(pFile, "\tTYPE %d", meshType);

		fprintf(pFile, " -\n");
		return true;
	}
	else if (strcmp(ID, CTYPE_MESHRENDERER) == 0)
	{
		int meshID = ((MeshRenderer*)GetScene()->GetSceneObject(objNum)->GetComponent(compNum))->GetMeshID();
		fprintf(pFile, "\tMESH-ID %d", meshID);

		fprintf(pFile, " -\n");
		return true;
	}
	return false;
}

int Project::LockScene()
{
	int nCycles = 0;
	if (sceneLocked == false)
	{
		sceneLocked = true;
		return 0;
	}
	do
	{
		nCycles += 1;
	} while (sceneLocked == true);
	sceneLocked = true;
	return nCycles;
}

void Project::UnlockScene()
{
	if (sceneLocked)
		sceneLocked = false;
	else
		MessageBox(NULL, "Scene Was Not Locked", "Notice", MB_OK);
}
