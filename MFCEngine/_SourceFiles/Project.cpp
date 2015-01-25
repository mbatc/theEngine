#include "Project.h"
#include "Scene.h"

Project::Project(char* filename, CreateState cs)
{
	switch (cs)
	{
	case CREATENEW:
		Nullify();
		break;
	case LOAD:
		if (!LoadProject(filename))
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

bool Project::LoadProject(char* filename)
{
	return true;
}