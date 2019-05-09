#include <iostream>
#include <ostream>
#include "Info.h"
#include "writersInStream.h"

std::ostream& outputInStream(std::ostream& os, Info& inf) {
	auto i = inf.studs.begin();
	auto end = inf.studs.end();

	//calculate header and footer fields 
	int noteCounter = 0;
	int stateScaleMarkSum = 0;
	while ((i != end)) {
		noteCounter += (*i).subs.size();
		auto i_subs = (*i).subs.begin();
		auto end_subs = (*i).subs.end();
		while (i_subs != end_subs) {
			stateScaleMarkSum += (*i_subs).getStateScaleMark();
			++i_subs;
		}
		++i;
	}
	//

	i = inf.studs.begin();
	int ind = 1;
	if (os) os << "header: " << noteCounter << std::endl;
	while ((os) && (i != end)) {

		auto i_subs = (*i).subs.begin();
		auto end_subs = (*i).subs.end();
		while (i_subs != end_subs) {
			os << ind << ":\t" << (*i).getGroupCode() << ":\t" << (*i).getName() << ":\t" << (*i_subs).getSummaryMark() << ":\t";
			os << (*i_subs).getStateScaleMark() << ":\t" << (*i_subs).getExamMark() << ":\t" << (*i).getGradebookCode() << ":\t";
			os << (*i).getSurname() << ":\t" << (*i_subs).getName() << ":\t" << (*i_subs).getTermMark() << std::endl;
			++ind;
			++i_subs;
		}
		
		++i;
	}
	if (os) os << "footer: " << stateScaleMarkSum;

	return os;
}

std::ostream& statInStream(std::ostream& os, Info& inf) {
	return os;
}

std::string& constructNote();