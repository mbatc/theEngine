#pragma once

#include "Scanner.h"
#include "Character.h"
#include"Token.h"

#include <iostream>

using namespace std;

class ScanDriver
{
public:
	ScanDriver(char* filename)
		:
	filename(filename)
	{}
	~ScanDriver(){}

	bool scan()
	{
		scanner.OpenFile(filename);
		Character Char = scanner.GetChar();

		while (true)
		{
			char* buffer = Char.toString();
			cout << buffer;
			if (Char.cargo == ENDMARK){ break; }
			Char = scanner.GetChar();
		}
		return true;
	}

private:
	Scanner scanner;
	char* filename;

};