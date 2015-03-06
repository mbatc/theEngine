#pragma once
#include "D3DGraphics.h"

class Scene;

enum CreateState
{
	LOAD,
	CREATENEW
};

struct SceneInfo
{
	int ID;
	char* filePath;
	char* name;
};

class Project
{
public:
	Project(char* filename, D3DGraphics& gfx, CreateState cs = CreateState::CREATENEW);
	~Project();

	//------------------------------------------
	//METHODS
	int LockScene();
	void UnlockScene();

	void Update();

	void ProcessFileID(FILE* pFile,D3DGraphics& gfx, char* ID, int* objID);

	void Nullify();
	bool LoadProject(char* filename, D3DGraphics& gfx );

	bool SaveScene(char* filename);
	bool SaveProject(char* filename);
	bool SaveComponentInfo(FILE* pFile, char* ID, int compNum, int objNum);

	//------------------------------------------
	//INLINE METHODS
	Scene* GetScene(){ return curScene; }
private:
	//------------------------------------------
	//DATA MEMBERS
	volatile bool sceneLocked;

	SceneInfo* sceneDB;
	Scene* curScene;
};