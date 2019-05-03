//Pavlo Bilinskyi
//Lexer.h contains the definition of class Lexer, according to conditions of Lab3.
//Lexer stands for simple lexical analizator with lazy algorhitm.
#pragma once
#include <string>

class Lexer {
public:	
	Lexer() = default;

	enum class LineType { Empty, Footer, Header, Line };

	//Initialize s with value of argument. Define the type of loaded string according to LineType. 
	//pre: argument must not refer to nullptr.
	//post: s now has the value of argument, typeOfLoadedString now is defined, pos_ is zero.
	LineType load(const std::string&);

	//Assign argument to the value of next field of loaded string from position pos_. Ignore whitespaces.
	//pre: argument must not be nullptr.
	//post: argument now is changed to the value of found field. 
	//return true iff next field is available in string
	bool next(std::string &);

	//Indicate if the end of the string reached.
	bool eof() const noexcept;

	//Indicate if the argument is a delimiter.
	bool isDelimiter(char) const noexcept;

	LineType getLineType() const noexcept;
private:
	std::string s;
	int len;
	LineType typeOfLoadedString;
	const static int START_POSITION = -1;
	int pos_;
};