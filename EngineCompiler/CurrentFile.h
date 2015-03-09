#pragma once

#include <stdio.h>

class CurrentFile
{
public:
	CurrentFile(char* filename)
		:
		m_pFilename(filename)
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

		if (m_pSourceText)
			delete m_pSourceText;
		m_pSourceText = new char[fileLen + 1];

		fread(m_pSourceText, sizeof(char), fileLen, file);

		m_pSourceText[fileLen - nLines] = '\0';
		///////////////////////////////////
		fclose(file);
	}

	char* m_pSourceText;
	char* m_pFilename;

private:
	FILE* file;
};