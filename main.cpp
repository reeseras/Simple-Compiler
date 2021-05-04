#include "Scanner.h"
#include "Token.h"
#include "StateMachine.h"
#include <string>
#include <iostream>
#include "Symbol.h"

int main() {
	/*Scanner scanner("testScan.txt");

	while (true) {
		TokenClass tc = scanner.GetNextToken();
		std::cout << scanner.GetLineNumber() << " " << tc << std::endl;
		if (tc.GetTokenType() == ENDFILE_TOKEN)
			break;
	}*/

	SymbolTableClass SymbolTable;

	SymbolTable.AddEntry("Symbol1");
	SymbolTable.AddEntry("Symbol2");
	SymbolTable.SetValue("Symbol1", 1);
	SymbolTable.SetValue("Symbol2", 2);
	if (SymbolTable.Exists("Symbol1"))
		std::cout << "Symbol1 Exists. Value: " << SymbolTable.GetValue("Symbol1") << std::endl;
	std::cout << "Symbol2 Value: " << SymbolTable.GetValue("Symbol2") << " Index: " << SymbolTable.GetIndex("Symbol2") << std::endl;
	if (!SymbolTable.Exists("Symbol3"))
		std::cout << "Symbol3 does not exist" << std::endl;
	std::cout << "There are " << SymbolTable.GetCount() << " symbols on the list." << std::endl;

}