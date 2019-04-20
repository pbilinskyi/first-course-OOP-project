#pragma once
#include "info.h"
#include "Lexer.h"
#include <string>

class Builder {
public:
	void loadData(Info&, const char* filename);
private:
	std::pair<Lexer::LineType, int> parseLine(std::string & s);
	
	//this method is responsible for 303 erorr, (it handles errors, that can occur during the convertation)
	//if next() returns false, throw i_a with message 302 (because next() returns false iff the end of the string is reached)
	//if the convertation is failed, invalid_argument with diagnostical message is thrown
	int getIntAndConvert(Lexer& lex, int numberOfString, std::string& s);
	void getString(Lexer& lex, int numberOfString, std::string& field);

	Lexer lex;
	//fields from header and footer
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
	const std::string message400 = "error in working with file";
	const std::string message500 = "bad_alloc";

	const std::string message100 = "header is upsent";
	const std::string message101 = "more than one header";
	const std::string message102 = "header isn't concerted with content of file";
	const std::string message103 = "header has wrong number of fields";
	const std::string message104 = "other error in header";
	
	const std::string message200 = "footer is upsent";
	const std::string message201 = "more than one footer";
	const std::string message202 = "footer isn't concerted with content of file";
	const std::string message203 = "footer has wrong number of fields";
	const std::string message204 = "other error in footer";
	
	const std::string message300 = "the order <header><notes><footer> is violated";
	const std::string message301 = "wrong numeration of notes";
	const std::string message302 = "wrong number of fields in string";
	const std::string message303 = "other error in string";
};