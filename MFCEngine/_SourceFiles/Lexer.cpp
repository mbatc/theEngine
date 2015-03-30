#include "Lexer.h"

#include <stdio.h>
#include <string>
Lexer::Lexer(char* filename)
	:
	scanner(),
	token(Character(NULL, NULL, NULL, NULL, NULL), &scanner, NULL)
{
	scanner.OpenFile(filename);
}

Lexer::~Lexer()
{}

void Lexer::ProcessTokens()
{
	Character Char(NULL, NULL, NULL, NULL, NULL);
	Char = scanner.GetChar();
	token = Token(Char, &scanner, NULL);

	while (true)
	{
		char prevToken[256];
		token.GetType(prevToken);

		if (strcmp(prevToken, WHITESPACE))
			AddToTree(token);

		Char = scanner.GetChar();
		if (Char.cargo == ENDMARK)
			break;

		token = Token(Char, &scanner, prevToken);
	}
}

void Lexer::AddToTree(Token addToken)
{
	Token* temp = new Token[_nTokens + 1];
	for (int i = 0; i < _nTokens; i++)
	{
		temp[i] = _tokenTree[i];
	}

	temp[_nTokens] = addToken;

	if (_tokenTree)
		delete _tokenTree;
	_tokenTree = new Token[_nTokens + 1];

	_nTokens++;

	for (int i = 0; i < _nTokens; i++)
	{
		_tokenTree[i] = temp[i];
	}

	delete temp;
}

Token* Lexer::GetTokenTree()
{
	return _tokenTree;
}

int Lexer::GetNumberOfTokens()
{
	return _nTokens;
}