#include "builder.h"
#include <iostream>
#include <fstream>
//#include <string>
#include <stdexcept>

//pre: input file must satisfy all of the requirements (those are described in the condition of Labaratory work)
//post: throw invalid_argument iff the ifstream is failed or file is illegal-formed (don't satisfy the requirements)
void Builder::loadData(Info& inf, const char* filename) {
	std::ifstream ifs(filename);
	int physicalNumberOfLine = 0;
	if (!ifs)  throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);

	std::string s;
	int notes_counter = 0;
	int expectedNextNumber = 1;
	notes_number_header = 1;
	int headerNumberLine = 0;
	while (getline(ifs, s)) {
		++physicalNumberOfLine;
		std::pair<Lexer::LineType, int> stringData = parseLine(s, physicalNumberOfLine);

		switch (stringData.first)
		{
		case Lexer::LineType::Line: 
			++notes_counter;
			if ((!headerIsFound) || (footerIsFound)) throw std::invalid_argument("300 " + std::to_string(physicalNumberOfLine) + " " + message300);
			if (stringData.second != expectedNextNumber) throw std::invalid_argument("301 " + std::to_string(physicalNumberOfLine) + " " + message301);
			expectedNextNumber++;
			inf.load(groupCode, studentsName, summaryMark, stateScaleMark, examMark, gradebookCode,
				 surname, subjectsName, termMark);
			break;
		
		case Lexer::LineType::Header:
			headerNumberLine = physicalNumberOfLine;
			if (headerIsFound) throw std::invalid_argument("101 " + std::to_string(headerNumberLine) + " " + message101);
			else headerIsFound = true;
			break;
		case Lexer::LineType::Footer:
			if (footerIsFound) throw std::invalid_argument("201 " + std::to_string(physicalNumberOfLine) + " " + message201);
			else footerIsFound = true; 
			break;
		default:
			break;
		}
	}

	if (notes_number_header != notes_counter) throw std::invalid_argument("102 -1 " + message102);

	if (!headerIsFound) throw std::invalid_argument("100 " + std::to_string(physicalNumberOfLine) + " " + message100);
	if (!footerIsFound) throw std::invalid_argument("300 " + std::to_string(physicalNumberOfLine) + " " + message300);
	
	if (!ifs.eof()) throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);
	//ifs.close();
	//if (!ifs) throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);
}

//pre: the fields of s mush hold the requirements, that is stated is condition of Labaratory work
//post: throw invalid_argument, if s don't satisfy the requirements
//in our notations, numberOfLine equals -1 means that the string doesn't have a number (string is empty, or header, or footer).
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
		getString(lex, physicalNumberOfLine, gradebookCode);
		getString(lex, physicalNumberOfLine, surname);
		getString(lex, physicalNumberOfLine, subjectsName);
		termMark = getIntAndConvert(lex, physicalNumberOfLine, field);

		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("302 " + std::to_string(physicalNumberOfLine) + " " + message302);
		//if succesful
		else {
			stateScaleMarks_sum += stateScaleMark;
			return { lnType, numberOfNote };
		}
	}
	else if (lnType == Lexer::LineType::Header) {
		int notes_number_header = getIntAndConvert(lex, physicalNumberOfLine, field);
		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("103 " + std::to_string(physicalNumberOfLine) + " " + message103);
		return { lnType, -1 };
	}
	else if (lnType == Lexer::LineType::Footer) {
			int stateScaleMarks_sum_footer = getIntAndConvert(lex, physicalNumberOfLine, field);
			
			if (!stateScaleMarks_sum_footer == stateScaleMarks_sum) throw std::invalid_argument("202 -1 " + message202);
			//if there is more fields in note than required
			if (!lex.eof()) throw std::invalid_argument("203 " + std::to_string(physicalNumberOfLine) + " " + message203);
			return { lnType, -1 };
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
