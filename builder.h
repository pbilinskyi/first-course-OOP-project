#pragma once
#include "info.h"
#include "Lexer.h"

class Builder {
public:
	bool loadData(Info&, const char* filename);
private:
	Lexer lex; 

};