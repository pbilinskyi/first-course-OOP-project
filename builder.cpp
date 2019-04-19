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
Lexer::LineType Builder::parseLine(std::string& s) {
	Lexer::LineType lnType = lex.load(s);
	//skip empty string
	if (lnType == Lexer::LineType::Empty) return Lexer::LineType::Empty;

	//read first field: number, header or footer
	std::string field;
	//lex.next(field);
	if (lnType == Lexer::LineType::Line) {
		lex.next(field);
		int number;

		try {
			number = std::stoi(field);
			if (number != expectedNextNumber) throw std::invalid_argument(message301);
		
			lex.next(groupCode);
			lex.next(field);
			summaryMark = std::stoi(field);
			lex.next(studentsName);
			lex.next(field);
			stateScaleMark = std::stoi(field);
			lex.next(field);
			examMark = std::stoi(field);
			lex.next(gradebookCode);
			lex.next(surname);
			lex.next(subjectsName);
			lex.next(field);
			termMark = std::stoi(field);
		}
		catch (std::invalid_argument &ia) {
		
		}
		catch (...) {
			throw std::invalid_argument(message104);
		}
	}
	else {
		if (lnType == Lexer::LineType::Header) {
			lex.next(field);
			try {
				students_amount = std::stoi(field);
			}
			catch (...) {
				throw std::invalid_argument(message104);
			}
			
		}
		else if (lnType == Lexer::LineType::Footer) {

		}
	}
}