#ifndef STATE_MACHINE
#define STATE_MACHINE

#include "Token.h"

enum MachineState { // finite automata circles
	START_STATE, IDENTIFIER_STATE, INTEGER_STATE, CANTMOVE_STATE,
	LESSTHAN_STATE, LESSEQUAL_STATE, INSERTION_STATE,
	GREATERTHAN_STATE, GREATEREQUAL_STATE, ASSIGNMENT_STATE,
	EQUAL_STATE, PLUS_STATE, MINUS_STATE, DIVIDE_STATE, MULTIPLY_STATE, NOTEQUAL_STATE, EXCLAMATION_STATE,
	LPAREN_STATE, RPAREN_STATE, LCURLY_STATE, RCURLY_STATE, SEMICOLON_STATE, COMMENT_STATE, STARCOMMENT_STATE, LCOMMENT_STATE,
	ENDLINE_STATE, EOF_STATE,
	LAST_STATE
};

enum CharacterType { // finit automata arrows
	LETTER_CHAR, DIGIT_CHAR, WHITESPACE_CHAR, BAD_CHAR,
	LESSTHAN_CHAR, GREATERTHAN_CHAR,
	EQUAL_CHAR, PLUS_CHAR, MINUS_CHAR, DIVIDE_CHAR, MULTIPLY_CHAR,
	LPAREN_CHAR, RPAREN_CHAR, LCURLY_CHAR, RCURLY_CHAR, SEMICOLON_CHAR, EXCLAMATION_CHAR,
	ENDLINE_CHAR, EOF_CHAR,
	LAST_CHAR
};

class StateMachineClass {
public:
	StateMachineClass();
	MachineState UpdateState(char currentCharacter, TokenType& correspondingTokenType);
private:
	MachineState mCurrentState;
	MachineState mLegalMoves[LAST_STATE][LAST_CHAR]; // matrix of legal moves
	TokenType mCorrespondingTokenTypes[LAST_STATE]; // lists which end state corresponds wo which token type (none for BAD_TOKEN)
};

#endif