#pragma once
#include "Token.h"
#include "Lexer.h"
#include "Scanner.h"
#include "Character.h"

typedef enum {ident, number, lparen, rparen, times, slash, plus, minus, eql, neq, lss, leq,
gtr,geq, callsym, beginsym, semicolon, endsym, ifsym, whilesym, becomes, thensym, dosym, constsym,
comma, intsym, charsym, procsym, peroid, oddsym} Symbol;

enum LANGUAGE
{
	THEENGINE = 0,
	CSHARP = 1,
	JAVA = 2,
};

class Parser
{
public:
	Parser(char* filename);
	~Parser();

	Token GetToken();
	void PrintError(char* msg);


	void _Parse_File(char* filename);

	bool _Is_Token(char* tk);
	bool _Is_Expected(char* tk);

	bool _Parse_Expression();
	bool _Parse_Condition();
	bool _Parse_Statement();
	bool _Parse_Block();
	
private:

	Symbol sym;
	Lexer lxer;

	Token* _TokenList;
	Token _CurToken;
	
	int _TokenIndex;
	int _TokenLineIndex;
	int _TokenColumnIndex;
	int _TokenSourceIndex;
};