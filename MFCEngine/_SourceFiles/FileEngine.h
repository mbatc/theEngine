#pragma once

#include <string>
enum FILETYPE
{
	UNSUPPORTED = -1,
	//SCRIPTS
	TES,
	//3D MODELS
	OBJ,
	//IMAGES

};

class FileEngine
{
public:
	FileEngine(char* filename);
	FileEngine();
	~FileEngine();

	char GetCharacter(const int charIndex) const;
	void GetString(const int stringIndex, const int stringLen) const;
	char* GetFilename(){ return _filename; }

	//If false could not identify file type
	//Or file type is not supported
	bool DetermineType();

	char* GetSourceText();

private:
	int			_nameLen;
	char*		_filename;
	int			_fileLength;
	char*		_sourceText;
	FILETYPE	_fileType;
};