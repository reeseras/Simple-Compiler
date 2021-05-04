#include "Token.h"
#include <string>
#include <iostream>

TokenClass::TokenClass() {
	mType = BAD_TOKEN;
	mLexeme = "";
	return;
}

TokenClass::TokenClass(TokenType type, const std::string& lexeme) {
	mType = type;
	mLexeme = lexeme;
}

// if lexeme == void or any other reserved word, change the token type from IDENTIFIER_TOKEN to the correct token type.
void TokenClass::CheckReserved() { // call at the end of the token constructor
	if (mLexeme == "void") {
		mType = VOID_TOKEN;
	}
	else if (mLexeme == "main") {
		mType = MAIN_TOKEN;
	}
	else if (mLexeme == "int") {
		mType = INT_TOKEN;
	}
	else if (mLexeme == "cout") {
		mType = COUT_TOKEN;
	}
}

std::ostream& operator<<(std::ostream& out, const TokenClass& tc) {
	out << tc.GetTokenTypeName() << ", " << tc.GetLexeme();
	return out;
}

