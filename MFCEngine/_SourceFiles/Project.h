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

	void Update(){}

	void Nullify();
	bool LoadProject(char* filename );
	
	Scene* GetScene(){ return curScene; }
private:
	SceneInfo* sceneDB;
	Scene* curScene;
};