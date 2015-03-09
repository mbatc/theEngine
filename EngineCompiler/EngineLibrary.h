#pragma once

#include "Character.h"

void CharacterToChar(const Character* Chars,const int nChars, char* tempChars)
{
	if (tempChars)
		delete tempChars;
	tempChars = new char[nChars];

	for (int i = 0; i < nChars; i++)
	{
		tempChars[i] = Chars[i].cargo;
	}
}