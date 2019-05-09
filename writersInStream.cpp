#include <iostream>
#include <ostream>
#include "Info.h"
#include "writersInStream.h"

std::ostream& outputInStream(std::ostream& os, Info& inf) {
	auto i = inf.studs.begin();
	auto end = inf.studs.end();

	while ((os) && (i != end)) {
		os << (*i).getName() << std::endl;
		++i;
	}
	
	return os;
}

std::ostream& statInStream(std::ostream& os, Info& inf) {
	return os;
}

std::string& constructNote();