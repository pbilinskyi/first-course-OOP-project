//Pavlo Bilinskyi
#include "Lexer.h"
#include <string>
#include <cctype>
#include <iostream>

Lexer::LineType Lexer::load(const std::string& source) {
	s = source;
	pos_ = START_POSITION;
	len = s.length();
	std::string first;

	next(first);
	if (first.compare("header") == 0) {
		typeOfLoadedString = Lexer::LineType::Header;
		return Lexer::LineType::Header;
	}
	if (first.compare("footer") == 0) {
		typeOfLoadedString = Lexer::LineType::Footer;
		return Lexer::LineType::Footer;
	}

	pos_ = START_POSITION;
	if (first.empty() && (!eof())) {
		typeOfLoadedString = Lexer::LineType::Empty;
		return Lexer::LineType::Empty;
	}
	else {
		typeOfLoadedString = Lexer::LineType::Line;
		return Lexer::LineType::Line;
	}
}

bool Lexer::next(std::string &field) {
	bool flag = true;
	field.clear();

	if (!eof()) {
		pos_++;
		while ((!isDelimiter(s[pos_])) && (!eof())) {
			if (!std::isspace(s[pos_]))	field += s[pos_];
			pos_++;
		}
	}
	else if (s.empty() && (pos_ == START_POSITION)) { pos_++; }
	else flag = false;
	
	return flag;
}

bool Lexer::eof() const noexcept {
	return (pos_ >= len);
}

bool Lexer::isDelimiter(char c) const noexcept{
	
	return ((c == ':')||(c == '/'));
}

Lexer::LineType Lexer::getLineType() const noexcept
{
	return typeOfLoadedString;
}