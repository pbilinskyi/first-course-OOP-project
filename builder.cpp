#include "builder.h"
#include <iostream>
#include <fstream>
//#include <string>
#include <stdexcept>

//pre: input file must satisfy all of the requirements (those are described in the condition of Labaratory work)
//post: throw invalid_argument iff the ifstream is failed or file is illegal-formed (don't satisfy the requirements)
void Builder::loadData(Info& inf, const char* filename) {
	std::ifstream ifs(filename);
	if (!ifs)  throw std::invalid_argument("400 0 " + message400);

	std::string s;
	int notes_counter = 0;
	int stateScaleMark_sum = 0;
	int expectedNextNumber = 1;
	int physicalNumberOfLine = -1;


	while (getline(ifs, s)) {
		++physicalNumberOfLine;
		std::pair<Lexer::LineType, int> stringData = parseLine(s, physicalNumberOfLine);

		switch (stringData.first)
		{
		case Lexer::LineType::Line: 
			++notes_counter;
			if (footerIsFound) throw std::invalid_argument("300 " + std::to_string(physicalNumberOfLine) + " " + message300);
			if (stringData.second != expectedNextNumber) throw std::invalid_argument("301 " + std::to_string(physicalNumberOfLine) + " " + message301);
			
			try {
				inf.load(groupCode, studentsName, summaryMark, stateScaleMark, examMark, gradebookCode,
					surname, subjectsName, termMark);
			}
			catch (std::invalid_argument &ia) {
				throw std::invalid_argument("303 " + std::to_string(physicalNumberOfLine) + " " + message303);
			}

			stateScaleMarks_sum += stateScaleMark;
			expectedNextNumber++;
			break;
		
		case Lexer::LineType::Header:
			if (headerIsFound) throw std::invalid_argument("101 " + std::to_string(physicalNumberOfLine) + " " + message101);
			if ((notes_counter > 0)||(footerIsFound)) throw std::invalid_argument("300 " + std::to_string(physicalNumberOfLine) + " " + message300);
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

	if (!headerIsFound) throw std::invalid_argument("100 " + std::to_string(physicalNumberOfLine) + " " + message100);
	if (!footerIsFound) throw std::invalid_argument("200 " + std::to_string(physicalNumberOfLine) + " " + message200);
	if (notes_number_header != notes_counter) throw std::invalid_argument("102 -1 " + message102);
	if (state_scale_mark_sum_footer != stateScaleMarks_sum) throw std::invalid_argument("202 -1 " + message202);
	if (!ifs.eof()) throw std::invalid_argument("400 " + std::to_string(physicalNumberOfLine) + " " + message400);

	inf.print();
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
		int numberOfNote;
		numberOfNote = getIntAndConvert(lex, physicalNumberOfLine, field);

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
			//stateScaleMarks_sum += stateScaleMark;
			return { lnType, numberOfNote };
		}
	}
	else if (lnType == Lexer::LineType::Header) {
		notes_number_header = getIntAndConvert(lex, physicalNumberOfLine, field);
		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("103 " + std::to_string(physicalNumberOfLine) + " " + message103);
		return { lnType, -1 };
	}
	else if (lnType == Lexer::LineType::Footer) {
		state_scale_mark_sum_footer = getIntAndConvert(lex, physicalNumberOfLine, field);
		//if there is more fields in note than required
		if (!lex.eof()) throw std::invalid_argument("203 " + std::to_string(physicalNumberOfLine) + " " + message203);
		return { lnType, -1 };
	}
}

int Builder::getIntAndConvert(Lexer & lex, int physicalNumberOfLine, std::string & s){
	if (lex.next(s)) {
		try {
			int field;
			size_t firstUnconverted = 0;
			field = std::stoi(s, &firstUnconverted, 10);
			if (firstUnconverted != s.length()) throw std::invalid_argument("");
			return field;
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
				throw std::invalid_argument("204 " + std::to_string(physicalNumberOfLine) + " " + message204);
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
