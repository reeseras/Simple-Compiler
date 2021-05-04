#include "Scanner.h"
#include "Debug.h"
#include <string>
#include <fstream>
#include <iostream>

Scanner::Scanner(std::string filename) {
	mFin.open(filename);
	if (!mFin) {
		std::cout << "Cannot open " << filename << std::endl;
		exit(1);
	}
	mLineNumber = 1;
}

Scanner::~Scanner() {
	mFin.close();
}

TokenClass Scanner::GetNextToken() {
	StateMachineClass stateMachine;
	TokenType currentTokenType;
	std::string lexeme = "";
	char c;
	MachineState currentState = START_STATE;

	do {
		c = mFin.get();
		if (c == '\n')
			mLineNumber += 1;
		lexeme += c;
		currentState = stateMachine.UpdateState(c, currentTokenType);
		if (currentState == START_STATE || currentState == EOF_STATE)
			lexeme = "";
	} while (currentState != CANTMOVE_STATE);

	if (currentTokenType == BAD_TOKEN) {
		std::cout << "ERROR: GetNextToken() BAD_TOKEN. Lexeme: " << lexeme << std::endl;
		exit(1);
	}

	// Removing the last character from the lexeme
	lexeme.pop_back();

	// Returning last character to mFin
	if (c == '\n')
		mLineNumber -= 1;
	mFin.unget();

	TokenClass token = TokenClass(currentTokenType, lexeme);
	token.CheckReserved();
	return token;
}