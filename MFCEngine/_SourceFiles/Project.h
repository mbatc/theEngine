#pragma once

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
	Project(char* filename, CreateState cs = CreateState::CREATENEW);
	~Project();

	//------------------------------------------
	//METHODS
	void Update();

	void Nullify();
	bool LoadProject(char* filename );
	//------------------------------------------
	//INLINE METHODS
	Scene* GetScene(){ return curScene; }
private:
	//------------------------------------------
	//DATA MEMBERS
	SceneInfo* sceneDB;
	Scene* curScene;
};