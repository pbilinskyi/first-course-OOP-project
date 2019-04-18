//Pavlo Bilinskyi
//Lexer.h contains the definition of class Lexer, according to conditions of Lab3.
//Lexer stands for simple lexical analizator with lazy algorhitm.
#pragma once
#include <string>

class Lexer {
public:	
	Lexer() = default;
	~Lexer();

	enum class LineType { Empty, Footer, Header, Line };

	//Initialize s with value of argument. Define the type of loaded string according to LineType. 
	//pre: argument must not refer to nullptr.
	//post: s now has the value of argument, typeOfLoadedString now is defined, pos_ is zero.
	LineType load(std::string);

	//Assign argument to the value of next field of loaded string from position pos_. Ignore whitespaces.
	//pre: argument must not be nullptr.
	//post: argument now is changed to the value of found field. 
	bool next(std::string &);

	//Indicate if the end of the string reached.
	bool eof() const noexcept;

	//Indicate if the argument is a delimiter.
	bool isDelimiter(char) const noexcept;

	//indicate if the argument is a whitespace.
	bool isWhitespace(char) const noexcept;
private:
	std::string s;
	size_t len;
	LineType typeOfLoadedString;
	size_t pos_;
	const size_t nDelim_ = 2;
	const char* delimiters = new char[nDelim_] {':', '/'};
};