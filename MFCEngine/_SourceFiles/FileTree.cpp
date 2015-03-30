#include "FileTree.h"

FileTree::FileTree()
	:
	_nFiles(0),
	_curFileIndex(0),
	fileList(NULL)
{}

FileTree::~FileTree()
{}

char* FileTree::CurrentFilename()
{
	return fileList[_curFileIndex].GetFilename();
}

void FileTree::AddFileToList(char* filename)
{
	FileEngine* temp = new FileEngine[_nFiles + 1];
	for (int i = 0; i < _nFiles; i++)
	{
		temp[i] = fileList[i];
	}

	temp[_nFiles] = FileEngine(filename);
	if (fileList)
		delete[] fileList;
	fileList = new FileEngine[_nFiles + 1];
	_nFiles++;

	for (int i = 0; i < _nFiles; i++)
	{
		fileList[i] = temp[i];
	}

	delete [] temp;
}

void FileTree::RemoveFileFromList(char* filename)
{

}