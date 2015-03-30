#include "CustomBehaviour.h"

#include <stdio.h>
#include <string>

CustomBehaviour::CustomBehaviour(Gameobject* parent,char* filename)
	:
	Component(parent),
	filename(NULL),
	sourceText(NULL)
{
	int strLen = strlen(filename);
	this->filename = new char[strLen];

	for (int i = 0; i < strLen; i++)
	{
		this->filename[i] = filename[i];
	}

	FILE* pFile = fopen(filename, "r");

		fseek(pFile, 0, SEEK_END);
		int fileLen = ftell(pFile);
		rewind(pFile);
		sourceText = new char[fileLen];
		fread(sourceText, sizeof(char), fileLen, pFile);

	fclose(pFile);
}

void CustomBehaviour::Update()
{}

void CustomBehaviour::Render(D3DGraphics& gfx)
{}
