#pragma once
#include "Token.h"

class Lexer
{
public:
	Lexer(char* filename);
	~Lexer();

	void ProcessTokens();
	
	void AddToTree(Token addToken);
	Token* GetTokenTree();
	int GetNumberOfTokens();

private:
	Scanner scanner;
	Token token;

	Token* _tokenTree;
	int _nTokens;
};