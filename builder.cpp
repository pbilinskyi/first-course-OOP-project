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
void Builder::parseLine(std::string& s) {
	
}