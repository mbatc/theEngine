#pragma once
#include <stdio.h>
#include "Character.h"

class Scanner
{
public:
	Scanner()
		:
		Char(NULL,0,0,0,NULL),
		m_sourceIndex(0),
		m_lastIndex(0),
		m_columnIndex(0),
		m_lineIndex(0),
		m_sourceText(NULL)
	{}

	~Scanner(){}

	void OpenFile(char* filename)
	{ 
		file = fopen(filename, "r");
		//////////////////////////////////
		
		char temp = '\0';
		int nLines = 0;
		fread(&temp, sizeof(char),1,file);
		while (temp != '\0')
		{
			if (!fread(&temp, sizeof(char), 1, file)) break;
			if (temp == '\n') nLines++;
			if (feof(file)) break;
		}

		long fileLen = ftell(file);
		rewind(file);

		if (m_sourceText)
			delete m_sourceText;
		m_sourceText = new char[fileLen + 1];

		fread(m_sourceText, sizeof(char), fileLen, file);

		m_sourceText[fileLen - nLines] = '\0';
		///////////////////////////////////
		fclose(file);

		m_lastIndex = fileLen - 1;
	}

	Character GetChar()
	{
		m_sourceIndex++;

		if (m_sourceIndex > 0)
		{
			if (m_sourceText[m_sourceIndex - 1] == '\n')
			{
				m_lineIndex++;
				m_columnIndex = -1;
			}
		}
		m_columnIndex++;

		if (m_columnIndex > m_lastIndex)
		{
			Char = Character(ENDMARK, m_sourceIndex, m_columnIndex, m_lineIndex, m_sourceText);
		}
		else
		{
			Char = Character(m_sourceText[m_sourceIndex],
				m_sourceIndex, m_columnIndex, m_lineIndex,
				m_sourceText);
		}

		return Char;
	}

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