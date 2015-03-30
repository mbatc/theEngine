#include "FileEngine.h"
#include <afxwin.h>

FileEngine::FileEngine()
	:
	_filename(NULL),
	_fileLength(0),
	_sourceText(NULL)
{}

FileEngine::FileEngine(char* filename)
	:
	_filename(NULL),
	_fileLength(0),
	_sourceText(NULL)
{
	_nameLen = strlen(filename);
	_filename = new char[_nameLen];
	strcpy(_filename, filename);

	FILE* pfile = fopen(filename, "r");
		fseek(pfile, 0, SEEK_END);
		_fileLength = ftell(pfile);
		rewind(pfile);
	
		_sourceText = new char[_fileLength];
	
		fread(_sourceText, sizeof(char), _fileLength, pfile);
	fclose(pfile);

	if (!DetermineType() || _fileType == FILETYPE::UNSUPPORTED )
	{
		char* msg = new char[strlen(_filename), strlen("File Type Not Supported!\nFile: ")];
		sprintf(msg, "File Type Not Supported!\nFile: %s", _filename);
		MessageBox(NULL, msg, "Error!", 
			MB_OK | MB_ICONEXCLAMATION);
	}
}

FileEngine::~FileEngine()
{}

bool FileEngine::DetermineType()
{
	int extensionIndex = -1;

	for (int i = _nameLen; i >= 0; i--)
	{
		if (_filename[i] == '.')
		{
			extensionIndex = i;
			break;
		}
	}
	if (_nameLen == 0)
		return false;

	if (extensionIndex == -1)
		return false;

	if (!strcmp(&_filename[extensionIndex], ".tes"))
	{
		_fileType = FILETYPE::TES;
	}
	else if (!strcmp(&_filename[extensionIndex], ".obj"))
	{
		_fileType = FILETYPE::OBJ;
	}
	else
	{
		_fileType = FILETYPE::UNSUPPORTED;
		return false;
	}

	return true;
}