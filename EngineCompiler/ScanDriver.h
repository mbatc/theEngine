#pragma once

#include "Scanner.h"
#include "Character.h"
#include <iostream>

using namespace std;

class ScanDriver
{
public:
	ScanDriver(){}
	~ScanDriver(){}

	bool scan()
	{
		scanner.OpenFile("text.txt");

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

};