
#include "Symbol.h"
#include <vector>
#include <iostream>

// returns true if <s> is already in the symbol table
bool SymbolTableClass::Exists(const std::string& s) {
	for (int i = 0; i < VariableTypes.size(); i++) {
		if (VariableTypes[i].mLabel == s) {
			return true;
		}
		else {
			return false;
		}
	}
}

// Adds an entry to VariableTypes if it doesn't already exist.
void SymbolTableClass::AddEntry(const std::string& s) {
	if (Exists(s)) {
		std::cout << s << " already exists" << std::endl;
		exit(1); // 'quit'?
	}
	else {
		Variable newVar;
		newVar.mLabel = s;
		newVar.mValue = 0;
		VariableTypes.push_back(newVar);
	}
}

// returns variable value of 's' or quits if 's' isn't found.
int SymbolTableClass::GetValue(const std::string& s) {
	for (int i = 0; i < VariableTypes.size(); i++) {
		if (VariableTypes[i].mLabel == s) {
			return VariableTypes[i].mValue;
		}
	}

	std::cout << "Could not find: " << s << std::endl;
	exit(1);
}

void SymbolTableClass::SetValue(const std::string& s, int v) {
	int i = GetIndex(s);
	VariableTypes[i].mValue = v;
}

// returns location of 's', returns -1 if 's' is not found.
int SymbolTableClass::GetIndex(const std::string& s) {
	for (int i = 0; i < VariableTypes.size(); i++) {
		if (VariableTypes[i].mLabel == s)
			return i;
	}
	
	return -1;
}

int SymbolTableClass::GetCount() {
	return VariableTypes.size();
}