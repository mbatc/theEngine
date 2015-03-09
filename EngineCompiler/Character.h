#pragma once
#include <stdio.h>
#include "GlobalDefinitions.h"

class Character
{
public:
	Character(char c, int index, int column, int line, char* source):
		cargo(c),
		sourceIndex(index),
		sourceColumnIndex(column),
		sourceLineIndex(line),
		sourceText(source)
	{}

	Character():
		cargo(NULL),
		sourceIndex(NULL),
		sourceLineIndex(NULL),
		sourceColumnIndex(NULL),
		sourceText(NULL)
	{}

	char cargo;
	int sourceIndex;
	int sourceColumnIndex;
	int sourceLineIndex;
	char* sourceText;

	void GetCarge(char* c) const { *c = cargo; }
	//Returns the Column of the current Character
	int GetColumnIndex() const { return sourceColumnIndex; }
	//Returns the Line of the current Character
	int GetLineIndex() const { return sourceLineIndex; }

	char* toString()
	{
		char* tempCargo = new char[3];
		int tempCargoLen = 3;
		tempCargo[2] = '\0';
		tempCargo[1] = '\n';
		tempCargo[0] = cargo;

		if (tempCargo[0] == ' ')
		{ 
			char space[] = { "  space\n" };
			if (tempCargo)delete tempCargo; tempCargo = new char[9]; 
			for (int i = 0; i < 9; i++){ tempCargo[i] = space[i]; }
			tempCargoLen = 9;
		}
		else if (tempCargo[0] == '\n')
		{
			char space[] = { "  newline\n" };
			if (cargo)delete tempCargo; tempCargo = new char[11];
			for (int i = 0; i < 11; i++){ tempCargo[i] = space[i]; }
			tempCargoLen = 11;
		}
		else if (tempCargo[0] == '\0')
		{
			char space[] = { "  eof\n" };
			if (cargo)delete tempCargo; tempCargo = new char[7];
			for (int i = 0; i < 7; i++){ tempCargo[i] = space[i]; }
			tempCargoLen = 7;
		}

		char CharIndexC[512];
		char CharIndexL[512];
		char* temp;
		sprintf(CharIndexC,"%d\t",sourceColumnIndex);
		sprintf(CharIndexL, "%d\t", sourceLineIndex);

		int strLenC = 0;
		int strLenL = 0;
		int strLen = 1;

		for (; CharIndexC[strLenC] != '\0'; strLenC++);
		for (; CharIndexL[strLenL] != '\0'; strLenL++);
		strLenC;
		strLenL;
	
		strLen += strLenC + strLenL + tempCargoLen;

		temp = new char[strLen];
		
		for (int i = 0; i < strLenC; i++){ temp[i] = CharIndexC[i]; }
		for (int i = 0; i < strLenL; i++){ temp[i + strLenC] = CharIndexL[i]; }

		for (int i = 0; i < tempCargoLen; i++)
		{
			temp[i + strLenC + strLenL] = tempCargo[i];
		}

		return temp;
	}

private:

};