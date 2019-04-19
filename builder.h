#pragma once
#include "info.h"
#include "Lexer.h"
#include <string>

class Builder {
public:
	void loadData(Info&, const char* filename);
private:
	Lexer::LineType parseLine(std::string & s);
	Lexer lex;
	int notes_number = 0;
	int stateScaleMarks_sum = 0;
	//indicators if header/footer/note row is already red
	bool headerIsFound = false;
	bool footerIsFound = false;
	bool noteIsFound = false;
	
	//parseLine() handles error 301 wrong order of numeration
	//this field represent expected number of next note
	//if the red number isn't equal to expected, error 301 is thrown in parseInt()
	size_t expectedNextNumber = 0;

	//temp data
	std::string studentsName;
	std::string surname;
	std::string gradebookCode;
	std::string groupCode;
	std::string subjectsName;
	int summaryMark;
	int termMark;
	int examMark;
	int stateScaleMark;

	//diagnostical messages
	const std::string message400 = "400 error in working with file";
	const std::string message500 = "500 bad_alloc";

	const std::string message100 = "100 header is upsent";
	const std::string message101 = "101 more than one header";
	const std::string message102 = "102 header isn't concerted with content of file";
	const std::string message103 = "103 header has wrong number of fields";
	const std::string message104 = "104 other error in header";
	
	const std::string message200 = "200 footer is upsent";
	const std::string message201 = "201 more than one footer";
	const std::string message202 = "202 footer isn't concerted with content of file";
	const std::string message203 = "203 footer has wrong number of fields";
	const std::string message204 = "204 other error in footer";
	
	const std::string message300 = "300 the order <header><notes><footer> is violated";
	const std::string message301 = "301 wrong numeration of notes";
	const std::string message302 = "302 wrong number of fields in string";
	const std::string message303 = "303 other error in string";
};