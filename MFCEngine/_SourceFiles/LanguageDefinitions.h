#pragma once

//*************************************************
//ENGINE LANGUAGE
#define ENDMARK '\0'

#define WHITESPACECHARS " \n\t"
#define STRINGSTART "'"+'"'

#define STATEMENTEND ';'

#define ONECHARLEN 2
#define TWOCHARLEN 3
#define N_ONECHARSYMBOLS 16
#define N_TWOCHARSYMBOLS 17
#define N_KEYWORDS 15

static const char ONECHARSYMBOL[16][2] =
{
	{ "(" }, { ")" },
	{ "{" }, { "}" },
	{ "<" }, { ">" }, { "=" },
	{ "/" }, { "*" }, { "-" }, { "+" },
	{ "!" }, { "&" }, { "|" },
	{ "." }, { ";" },
};

static const char TWOCHARSYMBOL[17][3] =
{
	{ "==" }, { "!=" },
	{ "<=" }, { ">=" }, { "<>" },
	{ "++" }, { "--" }, { "**" },
	{ "+=" }, { "-=" }, { "*=" }, { "/=" },
	{ "||" }, { "&&" },
	{ "//" }, { "/*" }, { "*/" },
};

static const char KEYWORDS[15][20] =
{
	{ "if" },
	{ "else" },
	{ "while" },
	{ "for" },
	{ "do" },
	{ "break" },
	{ "return" },
	{ "new" },
	{ "delete" },
	{ "using" },
	{ "operator" },
	{ "typedef" },
	{ "using" },
	{ "public" },
	{ "private" },
};

class VARIABLETYPES
{
public:
	VARIABLETYPES();


	static const char CONST_TYPES[10][4];
private:

};

//Engine Language Grammar Definition


//******************************************
//LEXICAL ANALYSER TOKEN TYPES
//******************************************

#define SYMBOL				"SYMBOL"
#define VARIABLE			"VARIABLE"
#define KEYWORD				"KEYWORD"
#define STRING				"STRING"
#define IDENTIFIER			"IDENTIFIER"
#define CONSTANTNUMBER		"CONSTANTNUMBER"
#define WHITESPACE			"WHITESPACE"
#define COMMENT				"COMMENT"
#define ENDOFFILE			"EOF"