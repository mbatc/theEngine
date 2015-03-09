#pragma once
#include "ScanDriver.h"
#include "Token.h"

class Lexer
{
public:
	Lexer(char* filename)
		:
		scanner(),
		token(Character(NULL,NULL,NULL,NULL,NULL),&scanner)
	{
		scanner.OpenFile(filename);
	}
	~Lexer(){}
	void ProcessTokens()
	{
		Character Char(NULL,NULL,NULL,NULL,NULL);
		Char = scanner.GetChar();
		token = Token(Char,&scanner);

		while (true)
		{
			cout << token.toString(false) << endl;
			Char = scanner.GetChar();
			token = Token(Char, &scanner);
			if (Char.cargo == ENDMARK)
				break;
		}
	}

private:
	Scanner scanner;
	Token token;
};