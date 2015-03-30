#include "Token.h"

#include <stdio.h>
#include <string>

Token::Token(Character startChar, Scanner* scanner, char* prevTokenType)
	:
	scanner(scanner)
{
	m_type[0] = '\0';

	if (startChar.sourceText)
	{

		m_sourceText = startChar.sourceText;
		m_sourceIndex = startChar.sourceIndex;
		m_lineIndex = startChar.sourceLineIndex;
		m_columnIndex = startChar.sourceColumnIndex;

		m_cargoLen = 0;

		m_cargo = new Character[1];
		m_cargo[0] = startChar;
	}

	if (m_cargo)
		DetermineType();
}

char* Token::GetCargo()
{
	char* temp = new char[m_cargoLen];
	for (int i = 0; i < m_cargoLen; i++)
	{
		temp[i] = m_cargo[i].cargo;
	}

	return temp;
}

Token::Token()
	:
	scanner(NULL)
{}

void Token::GetType(char* buffer)
{
	strcpy(buffer, m_type);
}


bool Token::DetermineType()
{
	bool oneCharSymbol = false;
	bool twoCharSymbol = false;
	bool keyword = false;
	bool whitespace = false;

	for (int i = 0; i < sizeof(WHITESPACECHARS) / sizeof(char); i++)
	{
		if (m_cargo[0].cargo == WHITESPACECHARS[i])
		{
			whitespace = true;
			strcpy(m_type, WHITESPACE);
			return true;
		}
	}

	Character Char(NULL, NULL, NULL, NULL, NULL);

	int nChars = 1;

	//**************************************
	//LOADING THE CHARACTERS TO BE PROCESSED
	//**************************************
	while (true)
	{
		bool isWhitespace = false;

		Character* temp = new Character[nChars + 1];
		for (int i = 0; i < nChars; i++)
		{
			temp[i] = m_cargo[i];
		}

		Character Char = scanner->GetChar();
		for (int i = 0; i < sizeof(WHITESPACECHARS) / sizeof(char); i++)
		{
			if (Char.cargo == WHITESPACECHARS[i])
			{
				isWhitespace = true;
				break;
			}
		}

		if (m_cargo)
			delete m_cargo;
		m_cargo = new Character[nChars + 1];
		for (int i = 0; i < nChars; i++)
		{
			m_cargo[i] = temp[i];
		}

		m_cargo[nChars] = Char;

		if (isWhitespace)
			break;

		nChars++;
	}

	m_cargoLen = nChars;

	//*******************************************
	//PROCCESSING THE CHARACTERS AND SETTING TYPE
	//*******************************************
	for (int i = 0; i < N_ONECHARSYMBOLS; i++)
	{
		if (m_cargo[0].cargo == ONECHARSYMBOL[i][0])
		{
			oneCharSymbol = true;
			twoCharSymbol = false;
			strcpy(m_type, SYMBOL);
			break;
		}
	}

	for (int i = 0; i < N_TWOCHARSYMBOLS; i++)
	{
		if (m_cargo[0].cargo == TWOCHARSYMBOL[i][0] &&
			m_cargo[1].cargo == TWOCHARSYMBOL[i][1])
		{
			twoCharSymbol = true;
			oneCharSymbol = false;
			scanner->SetIndex(m_cargo[2].sourceIndex, m_cargo[2].sourceColumnIndex,
				m_cargo[2].sourceLineIndex);
			strcpy(m_type, SYMBOL);
			break;
		}
	}
	
	int symbolIndex = -1;
	for (int i = 0; i < m_cargoLen; i++)
	{
		for (int s_i = 0; s_i < N_ONECHARSYMBOLS; s_i++)
		{
			if (m_cargo[i].cargo == ONECHARSYMBOL[s_i][0])
			{
				symbolIndex = i;
				break;
			}
		}
		for (int s_i = 0; s_i < N_TWOCHARSYMBOLS; s_i++)
		{
			if (i < m_cargoLen - 1)
				if (m_cargo[i].cargo == TWOCHARSYMBOL[s_i][0] &&
					m_cargo[i + 1].cargo == TWOCHARSYMBOL[s_i][1])
				{
					symbolIndex = i;
				}
		}
		if (symbolIndex != -1)
			break;
	}

	if (symbolIndex != -1)
	{
		scanner->SetIndex(m_cargo[symbolIndex].sourceIndex,
			m_cargo[symbolIndex].sourceColumnIndex,
			m_cargo[symbolIndex].sourceLineIndex);
		m_cargoLen = symbolIndex;

	}

	for (int i = 0; i < N_KEYWORDS; i++)
	{
		int keywordLen = strlen(KEYWORDS[i]);
		int nSameChars = 0;
		for (int c_i = 0; c_i < keywordLen; c_i++)
		{
			if (KEYWORDS[i][c_i] == m_cargo[c_i].cargo)
			{
				nSameChars++;
			}
		}
		if (nSameChars == keywordLen && m_cargoLen == keywordLen)
		{
			keyword = true;
			break;
		}
	}
	//*****************************************************
	//DOING A BIT OF 'HOUSE KEEPING' AFTER DETERMINING TYPE
	//*****************************************************
	if (keyword == true)
	{
		oneCharSymbol = false;
		twoCharSymbol = false;
		strcpy(m_type, KEYWORD);
	}
	else if (twoCharSymbol == true)
	{
		scanner->SetIndex(m_cargo[2].sourceIndex,
			m_cargo[2].sourceColumnIndex,
			m_cargo[2].sourceLineIndex);
		Character temp[2];
		temp[0] = m_cargo[0];
		temp[1] = m_cargo[1];

		delete m_cargo;
		m_cargo = new Character[2];
		m_cargo[0] = temp[0];
		m_cargo[1] = temp[1];
		m_cargoLen = 2;

		//**********************************
		//CHECKING FOR COMMENTS AND SKIPPING
		//**********************************
		if (m_cargo[0].cargo == '/' &&
			m_cargo[1].cargo == '/')
		{
			Character Char = scanner->GetChar();
			while (Char.cargo != '\n')
			{
				Char = scanner->GetChar();
			}
		}
		else if (m_cargo[0].cargo == '/' &&
			m_cargo[1].cargo == '*')
		{
			while (true)
			{
				Character Char = scanner->GetChar();
				if (Char.cargo == '*')
				{
				COMMENTCHECK:
					Char = scanner->GetChar();
					if (Char.cargo == '/')
						break;
					else if (Char.cargo == '*')
						goto COMMENTCHECK;
				}
			}
		}
		//**************************************************
	}
	else if (oneCharSymbol == true)
	{
		scanner->SetIndex(m_cargo[1].sourceIndex,
			m_cargo[1].sourceColumnIndex,
			m_cargo[1].sourceLineIndex);
		Character temp[1];
		temp[0] = m_cargo[0];

		delete m_cargo;
		m_cargo = new Character[1];
		m_cargo[0] = temp[0];
		m_cargoLen = 1;
	}
	else
	{
		bool allNumbers = true;
		for (int i = 0; i < m_cargoLen; i++)
		{
			if (!(m_cargo[i].cargo >= '0' && m_cargo[i].cargo <= '9'))
			{
				allNumbers = false;
			}
		}
		if (allNumbers)
		{
			strcpy(m_type, CONSTANTNUMBER);
			return true;
		}

		strcpy(m_type, IDENTIFIER);
	}

	return true;
}


char* Token::toString(bool printPosition)
{
	char* temp = NULL;

	//****************************************
	//FORMATTING STRING THAT WILL BE RETURNED
	//****************************************
	int typeLen = 0;
	for (; m_type[typeLen] != '\0'; typeLen++);
	typeLen++;

	int strLenC = 0;
	int strLenL = 0;
	int strLen = 1;

	if (printPosition)
	{
		char CharIndexC[512];
		char CharIndexL[512];
		sprintf(CharIndexC, "%d\t", m_columnIndex);
		sprintf(CharIndexL, "%d\t", m_lineIndex);

		for (; CharIndexC[strLenC] != '\0'; strLenC++);
		for (; CharIndexL[strLenL] != '\0'; strLenL++);
		strLenC;
		strLenL;

		strLen += strLenC + strLenL + m_cargoLen;

		if (temp)
			delete temp;
		temp = new char[strLen];

		for (int i = 0; i < strLenC; i++){ temp[i] = CharIndexC[i]; }
		for (int i = 0; i < strLenL; i++){ temp[i + strLenC] = CharIndexL[i]; }
	}
	else
	{
		if (temp)
			delete temp;
		temp = new char[m_cargoLen + typeLen + 1];
	}

	for (int i = 0; i < m_cargoLen; i++)
	{
		temp[i + strLenC + strLenL] = m_cargo[i].cargo;
	}
	temp[strLenC + strLenL + m_cargoLen] = '\t';
	for (int i = 0; i < typeLen; i++)
	{
		temp[strLenC + strLenL + m_cargoLen + i + 1] = m_type[i];
	}

	temp[strLenC + strLenL + m_cargoLen + typeLen + 1] = '\n';

	return temp;
}

void Token::ConstructFromString(char* string)
{
	int StrLen = 0;
	for (; string[StrLen] != '\0'; StrLen++);

	int ColIndex = 0;
	int RowIndex = 0;
	int TokenIndex = 0;
	int TypeIndex = 0;

	for (RowIndex = 1; string[RowIndex] != '\t'; RowIndex++); RowIndex++;
	for (TokenIndex = RowIndex; string[TokenIndex] != '\t'; TokenIndex++); TokenIndex++;
	for (TypeIndex = TokenIndex; string[TypeIndex] != '\t'; TypeIndex++); TypeIndex++;

	int ColLen = RowIndex - 1;
	int RowLen = TokenIndex - RowIndex - 1;
	int TokenLen = TypeIndex - TokenIndex - 1;
	int TypeLen = StrLen - TypeIndex - 1;

	char* _Col = new char[ColLen];
	char* _Row = new char[RowLen];
	char* _Token = new char[TokenLen];
	char* _Type = new char[TypeLen];

	for (int i = 0; i < ColLen; i++){ _Col[i] = string[i]; }
	for (int i = 0; i < RowLen; i++){ _Row[i] = string[i + ColLen]; }
	for (int i = 0; i < TokenLen; i++){ _Token[i] = string[i + ColLen + RowLen]; }
	for (int i = 0; i < TypeLen; i++){ _Type[i] = string[i + ColLen + RowLen + TokenLen]; }

	m_lineIndex = atoi(_Row);
	m_columnIndex = atoi(_Col);

	strcpy(m_type, _Type);

	if (m_cargo)
		delete m_cargo;
	m_cargo = new Character[TokenLen];

	for (int i = 0; i < TokenLen; i++)
	{
		m_cargo[i].cargo = _Token[i];
	}
}