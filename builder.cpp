#include "builder.h"
#include <iostream>
#include <ifstream>
#include <stdexcept>

void Builder::loadData(Info& i, const char* filename) {
	ifstream is(filename);
	if (!is)  throw std::invalid_argument(message400);
	

}