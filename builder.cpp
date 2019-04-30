#include "builder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

//pre: input file must satisfy all of the requirements (those are described in the condition of Labaratory work)
//post: throw invalid_argument iff the ifstream is failed or file is illegal-formed (don't satisfy the requirements)
void Builder::loadData(Info& inf, const char* filename) {
	std::ifstream ifs(filename);
	int physicalNumberOfLine = 0;
	if (!ifs)  throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);

	std::string s;
	while (getline(ifs, s)) {
		parseLine(s, physicalNumberOfLine);


		inf.load(studentsName, surname, groupCode, gradebookCode,
			subjectsName, summaryMark, termMark, examMark, stateScaleMark);

		++physicalNumberOfLine;
	}

	if (!ifs.eof()) throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);
	ifs.close();
	if (!ifs) throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);
}

//pre: the fields of s mush hold the requirements, that is stated is condition of Labaratory work
//post: throw invalid_argument, if s don't satisfy the requirements
//if s is empty line, then returned numberOfString == -1
std::pair<Lexer::LineType, int> Builder::parseLine(std::string& s, int physicalNumberOfLine) {
	Lexer::LineType lnType = lex.load(s);
	//skip empty string
	if (lnType == Lexer::LineType::Empty) return { Lexer::LineType::Empty, -1};

	//read first field: number, header or footer
	std::string field;
	if (lnType == Lexer::LineType::Line) {
		lex.next(field);
		int numberOfNote;

		try {
			numberOfNote = std::stoi(field);
		}
		catch (...) {
			throw std::invalid_argument("303 " + std::to_string(physicalNumberOfLine) + " " + message303);
		}

		getString(lex, physicalNumberOfLine, groupCode);
		getString(lex, physicalNumberOfLine, studentsName);
		summaryMark = getIntAndConvert(lex, physicalNumberOfLine, field);
		stateScaleMark = getIntAndConvert(lex, physicalNumberOfLine, field);
		examMark = getIntAndConvert(lex, physicalNumberOfLine, field);
		gradebookCode = getIntAndConvert(lex, physicalNumberOfLine, field);
		getString(lex, physicalNumberOfLine, surname);
		getString(lex, physicalNumberOfLine, subjectsName);
		termMark = getIntAndConvert(lex, physicalNumberOfLine, field);

		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("302 " + std::to_string(physicalNumberOfLine) + " " + message302);
		//if succesful
		else return { lnType, numberOfNote };
	}
	else if (lnType == Lexer::LineType::Header) {
		notes_number = getIntAndConvert(lex, physicalNumberOfLine, field);
		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("103 " + std::to_string(physicalNumberOfLine) + " " + message103);
	}
	else if (lnType == Lexer::LineType::Footer) {
			stateScaleMarks_sum = getIntAndConvert(lex, physicalNumberOfLine, field);
			//if there is more fields in note than required
			if (!lex.eof()) throw std::invalid_argument("203 " + std::to_string(physicalNumberOfLine) + " " + message203);
	}
}

int Builder::getIntAndConvert(Lexer & lex, int physicalNumberOfLine, std::string & s){
	int field;
	if (lex.next(s)) {
		try {
			field = std::stoi(s);
		}
		catch (...) {
			switch (lex.getLineType())
			{
			case Lexer::LineType::Header:
				throw std::invalid_argument("104 " + std::to_string(physicalNumberOfLine) + " " + message104);
				break;
			case Lexer::LineType::Line:
				throw std::invalid_argument("303 " + std::to_string(physicalNumberOfLine) + " " + message303);
				break;
			case Lexer::LineType::Footer:
				throw std::invalid_argument("204 " + std::to_string(physicalNumberOfLine) + " " + message104);
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
			throw std::invalid_argument("103 " + std::to_string(physicalNumberOfLine) + " " + message103);

			break;
		case Lexer::LineType::Line:
			throw std::invalid_argument("302 " + std::to_string(physicalNumberOfLine) + " " + message302);
			break;
		case Lexer::LineType::Footer:
			throw std::invalid_argument("203 " + std::to_string(physicalNumberOfLine) + " " + message203);
			break;
		default:
			break;
		}
	}
}

void Builder::getString(Lexer & lex, int physicalNumberOfLine, std::string& field)
{
	if (!lex.next(field)) {
		throw std::invalid_argument("302 " + std::to_string(physicalNumberOfLine) + " " + message302);
	}
}
