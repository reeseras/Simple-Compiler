#ifndef SCANNER
#define SCANNER

#include "Token.h"
#include "StateMachine.h"
#include "Debug.h"
#include <fstream>
#include <string>

class Scanner {
private:
	std::ifstream mFin;
	int mLineNumber;
public:
	Scanner(std::string filename);
	~Scanner();
	int GetLineNumber() { return mLineNumber; };
	TokenClass GetNextToken();
};


#endif
