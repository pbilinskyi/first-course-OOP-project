#include <iostream>
#include <ostream>
#include "Info.h"
#include "lowLevelFunc.h"

void doNothing() {
	std::cout << "nothing to do" << std::endl;
}

std::ostream& outputInStream(std::ostream& os, Info& inf) {
	return os;
}

std::ostream& statInStream(std::ostream& os, Info& inf) {
	return os;
}