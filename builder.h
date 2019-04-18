#pragma once
#include "info.h"
#include "Lexer.h"
#include <string>

class Builder {
public:
	bool loadData(Info&, const char* filename);
private:
	Lexer lex;
	size_t students_amount = 0;
	int stateScaleMarks_sum = 0;


	const std::string message400 = "400 error in working with file";
	const std::string message500 = "500 bad_alloc"

	const std::string message100 = "100 title is upsent";
	const std::string message101 = "101 more than one title";
	const std::string message102 = "102 title isn't concerted with content of file";
	const std::string message103 = "103 title has wrong number of fields";
	const std::string message104 = "104 other error in title";
	
	const std::string message200 = "200 bottom colontitul is upsent";
	const std::string message201 = "201 more than one bottom colontitul";
	const std::string message202 = "202 bottom colontitul isn't concerted with content of file";
	const std::string message203 = "203 bottom colontitul has wrong number of fields";
	const std::string message204 = "204 other error in bottom colontitul";
	
	const std::string message300 = "300 the order <title><notes><bottom colontitul> is violated";
	const std::string message301 = "301 wrong numeration of notes";
	const std::string message302 = "302 wrong number of fields in string";
	const std::string message303 = "303 other error in string";
	const std::string message304 = "";
};