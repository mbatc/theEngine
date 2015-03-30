#pragma once

#include "Character.h"
#include "Scanner.h"
#include "LanguageDefinitions.h"

class Token
{
public:
	Token(Character startChar, Scanner* scanner, char* prevTokenType);
	Token();

	void GetType(char* buffer);

	//*************************************************
	//Determines the type of token ie. Keyword, Symbol. 
	//This is called in the toString Function.
	//*************************************************
	bool DetermineType();

	//*********************************************************
	//Returns a pointer to a string representation of the class
	//if printPosition = true returns ("Col Row Token Type")
	//if printPosition = false returns ("Token Type")
	//*********************************************************
	char* toString(bool printPosition);

	//****************************************************
	//Constructs the class form a string
	//Must be a string returned from the toString Function
	//****************************************************
	void ConstructFromString(char* string);

	int GetLineIndex(){ return m_lineIndex; }
	int GetColumnIndex(){ return m_columnIndex; }
	int GetSourceIndex(){ return m_sourceIndex; }

	char* GetCargo();

private:
	Scanner* scanner;


	Character* m_cargo;

	char* m_sourceText;
	int m_sourceIndex;
	int m_lineIndex;
	int m_columnIndex;

	int m_cargoLen = 0;

	char m_type[128];
};