#pragma once
#include <stdio.h>
#include "LanguageDefinitions.h"

class Character
{
public:
	Character(char c, int index, int column, int line, char* source);
	Character();

	char cargo;
	int sourceIndex;
	int sourceColumnIndex;
	int sourceLineIndex;
	char* sourceText;

	//Returns the char stored in the class
	void GetCargo(char* c) const;
	//Returns the Column of the current Character
	int GetColumnIndex() const;
	//Returns the Line of the current Character
	int GetLineIndex() const;

	char* toString();

private:

};