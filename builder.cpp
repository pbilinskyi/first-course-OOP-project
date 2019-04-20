#include "builder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

//pre: input file must satisfy all of the requirements (those are described in the condition of Labaratory work)
//post: throw invalid_argument iff the ifstream is failed or file is illegal-formed (don't satisfy the requirements)
void Builder::loadData(Info& inf, const char* filename) {
	std::ifstream ifs(filename);
	if (!ifs)  throw std::invalid_argument(message400);



	std::string s;
	while (getline(ifs, s)) {
		parseLine(s);
		inf.load(studentsName, surname, groupCode, gradebookCode,
			subjectsName, summaryMark, termMark, examMark, stateScaleMark);
	}

	if (!ifs.eof()) throw std::invalid_argument(message400);
	ifs.close();
	if (!ifs) throw std::invalid_argument(message400);
}

//pre: the fields of s mush hold the requirements, that is stated is condition of Labaratory work
//post: throw invalid_argument, if s don't satisfy the requirements
std::pair<Lexer::LineType, int> Builder::parseLine(std::string& s) {
	Lexer::LineType lnType = lex.load(s);
	int numberOfString = -1;
	//skip empty string
	if (lnType == Lexer::LineType::Empty) return { Lexer::LineType::Empty, numberOfString };

	//read first field: number, header or footer
	std::string field;
	if (lnType == Lexer::LineType::Line) {
		lex.next(field);
		try {
			numberOfString = std::stoi(field);
		}
		catch (...) {
			//now we denote dummy number -1, that means, that number of string is now ambigous 
			// is it a physical number of string(ignoring empty strings) in file or what?
			throw std::invalid_argument("303 -1 " + message303);
		}

		getString(lex, numberOfString, groupCode);
		getString(lex, numberOfString, studentsName);
		summaryMark = getIntAndConvert(lex, numberOfString, field);
		stateScaleMark = getIntAndConvert(lex, numberOfString, field);
		examMark = getIntAndConvert(lex, numberOfString, field);
		gradebookCode = getIntAndConvert(lex, numberOfString, field);
		getString(lex, numberOfString, surname);
		getString(lex, numberOfString, subjectsName);
		termMark = getIntAndConvert(lex, numberOfString, field);

		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("302 " + std::to_string(numberOfString) + " " + message302);
		else {
			if (lnType == Lexer::LineType::Header) {
				numberOfString = 0;
				notes_number = getIntAndConvert(lex, numberOfString, field);

				//if there is more fields in note than required
				if (!lex.eof()) throw std::invalid_argument("103 " + std::to_string(numberOfString) + " " + message103);
			}
			else if (lnType == Lexer::LineType::Footer) {
				numberOfString = expectedNextNumber;

				//if there is more fields in note than required
				if (!lex.eof()) throw std::invalid_argument("203 " + std::to_string(numberOfString) + " " + message203);
			}
		}
	}
}

int Builder::getIntAndConvert(Lexer & lex, int numberOfString, std::string & s){
	int field;
	if (lex.next(s)) {
		try {
			field = std::stoi(s);
		}
		catch (...) {
			switch (lex.getLineType())
			{
			case Lexer::LineType::Header:
				throw std::invalid_argument("104 " + std::to_string(numberOfString) + " " + message104);
				break;
			case Lexer::LineType::Line:
				throw std::invalid_argument("303 " + std::to_string(numberOfString) + " " + message303);
				break;
			case Lexer::LineType::Footer:
				throw std::invalid_argument("204 " + std::to_string(numberOfString) + " " + message104);
				break;
			default:
				break;
			}
		}
	}
	else {
		switch (lex.getLineType())
		{
		case Lexer::LineType::Header:
			throw std::invalid_argument("103 " + std::to_string(numberOfString) + " " + message103);

			break;
		case Lexer::LineType::Line:
			throw std::invalid_argument("302 " + std::to_string(numberOfString) + " " + message302);
			break;
		case Lexer::LineType::Footer:
			throw std::invalid_argument("203 " + std::to_string(numberOfString) + " " + message203);
			break;
		default:
			break;
		}
	}
}

void Builder::getString(Lexer & lex, int numberOfString, std::string& field)
{
	if (!lex.next(field)) {
		throw std::invalid_argument("302 " + std::to_string(numberOfString) + " " + message302);
	}
}
