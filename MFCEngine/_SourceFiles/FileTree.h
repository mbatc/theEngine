#pragma once
#include "FileEngine.h"

class FileTree
{
public:
	FileTree();
	~FileTree();
	char* CurrentFilename();
	
	void AddFileToList(char* filename);
	void RemoveFileFromList(char* filename);

	void IncrementFile(){ _curFileIndex++; }

	int GetNumberOfFiles(){ return _nFiles; }

private:
	FileEngine* fileList;

	int _curFileIndex;
	int _nFiles;
};