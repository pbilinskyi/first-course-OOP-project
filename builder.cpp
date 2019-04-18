#include "builder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void Builder::loadData(Info& i, const char* filename) {
	std::ifstream ifs(filename);
	if (!ifs)  throw std::invalid_argument(message400);

	std::string s;
	while (getline(ifs, s)) {

	}

	if (!ifs.eof()) throw std::invalid_argument(message400);
	ifs.close();
	if (!ifs) throw std::invalid_argument(message400);
}