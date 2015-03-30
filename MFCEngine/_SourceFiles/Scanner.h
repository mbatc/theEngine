#pragma once

#include <stdio.h>
#include "Character.h"

class Scanner
{
public:
	Scanner();
	~Scanner();

	void SetIndex(int sourceIndex, int columnIndex, int lineIndex);

	void OpenFile(char* filename);

	Character GetChar();

private:
	FILE* file;
	char buffer;

	Character Char;

	char* m_sourceText;
	int m_sourceIndex;
	int m_lastIndex;
	int m_columnIndex;
	int m_lineIndex;
};