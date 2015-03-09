
#include <iostream>

#include "Scanner.h"
#include "Character.h"
#include "ScanDriver.h"
#include "Lexer.h"

int main()
{
	Lexer lexer("text.txt");
	lexer.ProcessTokens();

	system("pause");
	return 1;
}