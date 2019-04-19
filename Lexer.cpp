//Pavlo Bilinskyi
#include "Lexer.h"
#include <string>
#include <iostream>
#include <regex>

Lexer::LineType Lexer::load(std::string source) {

	if (source.length() > 0) {
		s = source;
		len = s.length();
		pos_ = 0;

		std::string firstLetters = s.substr(0, 6);
		if (firstLetters.compare("header") == 0) {
			typeOfLoadedString = LineType::Header;
			this->next(source);
		}

		else if (firstLetters.compare("footer") == 0) {
			typeOfLoadedString = LineType::Footer;
			this->next(source);
		}
		else typeOfLoadedString = LineType::Line;
		
		size_t i = 0;
		bool isEmpty = true;
		while (i < len) {
			if ((!isWhitespace(s[i])) && (!eof())) isEmpty = false;
			++i;
		}
		if (isEmpty) typeOfLoadedString = LineType::Empty;
	}
	else {
		typeOfLoadedString = LineType::Empty;
	}

	return typeOfLoadedString;
}

bool Lexer::next(std::string &field) {
	bool isSuccesful = false;

//empty string contains 1 empty field []
//this block must match the field [] of empty string only once
	if ((typeOfLoadedString == LineType::Empty)&&(pos_==len)) {
		field = "";
		isSuccesful = true;
		++pos_;
	}
		
//there is one empty field [] between last delimiter and the end of the string
	else if ((pos_ == len) && (isDelimiter(s[pos_ - 1]))) {
		field = "";
		isSuccesful = true;
		++pos_;
	}

	if (!eof()) {
		size_t fieldEnd = pos_;
		size_t whitespaceCount = 0;
		while ((!isDelimiter(s[fieldEnd])) && (fieldEnd < len)) {
			if (isWhitespace(s[fieldEnd])) ++whitespaceCount;
			++fieldEnd;
		}

		field = std::string(fieldEnd - pos_ - whitespaceCount, ' ');
		size_t tempNextPos = 0;
		while (pos_ < fieldEnd) {
			if (!isWhitespace(s[pos_])) {
				field[tempNextPos] = s[pos_];
				++tempNextPos;
			}
			++pos_;
		}
		isSuccesful = true;
		++pos_;
	}
	return isSuccesful;
}

bool Lexer::eof() const noexcept {
	return (pos_ >= len);
}

bool Lexer::isDelimiter(char c) const noexcept{
	bool isDelimiter = false;
	if (delimiters) {
		size_t i = 0;
		while ((!isDelimiter) && (i < nDelim_)) {
			if (delimiters[i] == c) isDelimiter = true;
			++i;
		}
	}
	return isDelimiter;
}

bool Lexer::isWhitespace(char c) const noexcept
{
	return ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r') || (c == '\v'));
}

/*const char* Lexer::getTypeOfLine() const noexcept
{
	switch (typeOfLoadedString)
	{
		case LineType::Line:    return "Line";
		case LineType::Empty:   return "Empty";
		case LineType::Header:  return "Header";
		case LineType::Footer:  return "Footer";
		default:      return "Undefined";
	}
}
*/

Lexer::~Lexer()
{
	delete[] delimiters;
}
