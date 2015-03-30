#include "Parser.h"
#include "LanguageDefinitions.h"
#include "GlobalPointers.h"

#include <stdio.h>
#include <string>

Parser::Parser(char* filename)
	:
	lxer(filename)
{
	lxer.ProcessTokens();
	_TokenList = lxer.GetTokenTree();
}

Parser::~Parser()
{}

Token Parser::GetToken()
{
	Token tk = _TokenList[_TokenIndex];
	_TokenIndex++;

	_TokenLineIndex = tk.GetLineIndex();
	_TokenColumnIndex = tk.GetColumnIndex();
	_TokenSourceIndex = tk.GetSourceIndex();

	return tk;
}

void Parser::PrintError(char* msg)
{
	Console->Output(msg);
}

void Parser::_Parse_File(char* filename)
{
	_CurToken = GetToken();
	char prevType[128] = { 0 };
	_CurToken.GetType(prevType);
	while (strcmp(prevType, ENDOFFILE))
	{
		_Parse_Block();
	}
}

bool Parser::_Is_Token(char* tk)
{
	if (!strcmp(tk, _CurToken.GetCargo()))
		return true;
	return false;
}

bool Parser::_Is_Expected(char* tk)
{
	if (_Is_Token(tk))
		return true;
	else
		;//OUTPUT SYNTAX ERROR MESSAGE
}

bool Parser::_Parse_Expression()
{
	return true;
}

bool Parser::_Parse_Condition()
{
	return true;
}

bool Parser::_Parse_Statement()
{
	return true;
}

bool Parser::_Parse_Block()
{
	return true;	
}