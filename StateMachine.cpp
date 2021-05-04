#include "StateMachine.h"
#include "Token.h"
#include <iostream>

StateMachineClass::StateMachineClass() {
	// initialize mCurrentState
	mCurrentState = START_STATE;

	// filling mLegalMoves array with CANTMOVE_STATE
	for (int i = 0; i < LAST_STATE; i++) {
		for (int j = 0; j < LAST_CHAR; j++) {
			mLegalMoves[i][j] = CANTMOVE_STATE;
		}
	}

	// Fixing legal moves for the mLegalMoves array
	mLegalMoves[START_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[INTEGER_STATE][DIGIT_CHAR] = INTEGER_STATE;
	mLegalMoves[START_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	mLegalMoves[IDENTIFIER_STATE][LETTER_CHAR] = IDENTIFIER_STATE;
	// < Less than
	mLegalMoves[START_STATE][LESSTHAN_CHAR] = LESSTHAN_STATE;
	mLegalMoves[LESSTHAN_STATE][LESSTHAN_CHAR] = INSERTION_STATE;
	mLegalMoves[LESSTHAN_STATE][EQUAL_CHAR] = LESSEQUAL_STATE;
	// > greater than
	mLegalMoves[START_STATE][GREATERTHAN_CHAR] = GREATERTHAN_STATE;
	mLegalMoves[GREATERTHAN_STATE][EQUAL_CHAR] = GREATEREQUAL_STATE;
	mLegalMoves[GREATERTHAN_STATE][GREATERTHAN_CHAR] = ASSIGNMENT_STATE;
	// equal and not equal
	mLegalMoves[START_STATE][EQUAL_CHAR] = EQUAL_STATE;
	mLegalMoves[START_STATE][EXCLAMATION_CHAR] = EXCLAMATION_STATE;
	for (int i = 0; i < LAST_CHAR; i++)
		mLegalMoves[EXCLAMATION_STATE][i] = CANTMOVE_STATE;
	mLegalMoves[EXCLAMATION_STATE][EQUAL_CHAR] = NOTEQUAL_STATE;
	// symbols ()+-={}*/!;
	mLegalMoves[START_STATE][LPAREN_CHAR] = LPAREN_STATE;
	mLegalMoves[START_STATE][RPAREN_CHAR] = RPAREN_STATE;
	mLegalMoves[START_STATE][PLUS_CHAR] = PLUS_STATE;
	mLegalMoves[START_STATE][MINUS_CHAR] = MINUS_STATE;
	mLegalMoves[START_STATE][MULTIPLY_CHAR] = MULTIPLY_STATE;
	mLegalMoves[START_STATE][DIVIDE_CHAR] = DIVIDE_STATE;
	mLegalMoves[START_STATE][LCURLY_CHAR] = LCURLY_STATE;
	mLegalMoves[START_STATE][RCURLY_CHAR] = RCURLY_STATE;
	mLegalMoves[START_STATE][SEMICOLON_CHAR] = SEMICOLON_STATE;
	// whitespace
	mLegalMoves[START_STATE][ENDLINE_CHAR] = START_STATE;
	mLegalMoves[START_STATE][WHITESPACE_CHAR] = START_STATE;
	// block comment
	mLegalMoves[DIVIDE_STATE][MULTIPLY_CHAR] = COMMENT_STATE;
	for (int i = 0; i < LAST_CHAR; i++) { mLegalMoves[COMMENT_STATE][i] = COMMENT_STATE; } // '/*' + '!*'
	mLegalMoves[COMMENT_STATE][MULTIPLY_CHAR] = STARCOMMENT_STATE;
	for (int i = 0; i < LAST_CHAR; i++) { mLegalMoves[STARCOMMENT_STATE][i] = COMMENT_STATE; }// '/* *' + '!/'
	mLegalMoves[STARCOMMENT_STATE][DIVIDE_CHAR] = START_STATE;
	// line comment
	mLegalMoves[DIVIDE_STATE][DIVIDE_CHAR] = LCOMMENT_STATE;
	for (int i = 0; i < LAST_CHAR; i++) { mLegalMoves[LCOMMENT_STATE][i] = LCOMMENT_STATE; } // '//' + '!/n'
	mLegalMoves[LCOMMENT_STATE][ENDLINE_CHAR] = START_STATE;
	mLegalMoves[LCOMMENT_STATE][EOF_CHAR] = EOF_STATE;
	// other
	mLegalMoves[START_STATE][EOF_CHAR] = EOF_STATE;

	// filling correspondingTokenTypes with BAD_TOKEN
	for (int i = 0; i < LAST_STATE; i++) {
		mCorrespondingTokenTypes[i] = BAD_TOKEN;
	}
	// fixing correspondingTokenTypes with appropriate token
	mCorrespondingTokenTypes[INTEGER_STATE] = INTEGER_TOKEN;
	mCorrespondingTokenTypes[IDENTIFIER_STATE] = IDENTIFIER_TOKEN;
	mCorrespondingTokenTypes[LESSTHAN_STATE] = LESS_TOKEN;
	mCorrespondingTokenTypes[INSERTION_STATE] = INSERTION_TOKEN;
	mCorrespondingTokenTypes[LESSEQUAL_STATE] = LESSEQUAL_TOKEN;
	mCorrespondingTokenTypes[GREATERTHAN_STATE] = GREATER_TOKEN;
	mCorrespondingTokenTypes[GREATEREQUAL_STATE] = GREATEREQUAL_TOKEN;
	mCorrespondingTokenTypes[ASSIGNMENT_STATE] = ASSIGNMENT_TOKEN;
	mCorrespondingTokenTypes[LPAREN_STATE] = LPAREN_TOKEN;
	mCorrespondingTokenTypes[RPAREN_STATE] = RPAREN_TOKEN;
	mCorrespondingTokenTypes[PLUS_STATE] = PLUS_TOKEN;
	mCorrespondingTokenTypes[MINUS_STATE] = MINUS_TOKEN;
	mCorrespondingTokenTypes[MULTIPLY_STATE] = TIMES_TOKEN;
	mCorrespondingTokenTypes[DIVIDE_STATE] = DIVIDE_TOKEN;
	mCorrespondingTokenTypes[EQUAL_STATE] = EQUAL_TOKEN;
	mCorrespondingTokenTypes[NOTEQUAL_STATE] = NOTEQUAL_TOKEN;
	mCorrespondingTokenTypes[LCURLY_STATE] = LCURLY_TOKEN;
	mCorrespondingTokenTypes[RCURLY_STATE] = RCURLY_TOKEN;
	mCorrespondingTokenTypes[SEMICOLON_STATE] = SEMICOLON_TOKEN;
	mCorrespondingTokenTypes[EOF_STATE] = ENDFILE_TOKEN;
	// mCorrespondingTokenTypes[ENDLINE_STATE] = ENDLINE_TOKEN;
}

MachineState StateMachineClass::UpdateState(char currentCharacter, TokenType& correspondingTokenType) {
	CharacterType charType = BAD_CHAR; // initialize to BAD_CHAR

	// checking character type
	if (isdigit(currentCharacter))
		charType = DIGIT_CHAR;
	else if (isalpha(currentCharacter))
		charType = LETTER_CHAR;
	else if (currentCharacter == '\n')
		charType = ENDLINE_CHAR;
	else if (isspace(currentCharacter))
		charType = WHITESPACE_CHAR;
	else if (currentCharacter == '<')
		charType = LESSTHAN_CHAR;
	else if (currentCharacter == '>')
		charType = GREATERTHAN_CHAR;
	else if (currentCharacter == '=')
		charType = EQUAL_CHAR;
	else if (currentCharacter == '(')
		charType = LPAREN_CHAR;
	else if (currentCharacter == ')')
		charType = RPAREN_CHAR;
	else if (currentCharacter == '{')
		charType = LCURLY_CHAR;
	else if (currentCharacter == '}')
		charType = RCURLY_CHAR;
	else if (currentCharacter == '+')
		charType = PLUS_CHAR;
	else if (currentCharacter == '-')
		charType = MINUS_CHAR;
	else if (currentCharacter == ';')
		charType = SEMICOLON_CHAR;
	else if (currentCharacter == '*')
		charType = MULTIPLY_CHAR;
	else if (currentCharacter == '/')
		charType = DIVIDE_CHAR;
	else if (currentCharacter == '!')
		charType = EXCLAMATION_CHAR;
	else if (currentCharacter == EOF)
		charType = EOF_CHAR;

	correspondingTokenType = mCorrespondingTokenTypes[mCurrentState];
	mCurrentState = mLegalMoves[mCurrentState][charType];
	return mCurrentState;
}