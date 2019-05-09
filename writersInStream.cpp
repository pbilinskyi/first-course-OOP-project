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
	inf.studs.sort();
//	inf.print();
	auto itr = inf.studs.begin();
	auto end = inf.studs.end();
	while((os) && ((*itr).getRating() >= 75) && (itr != end))
	{
		os << (*itr).getGradebookCode() << ", " <<  (*itr).getSurname() << ", " << (*itr).getName() << ", ";
		os << std::to_string((*itr).getStability()) << ", " << std::to_string((*itr).getExcellentCount()) << std::endl;
		(*itr).subs.sort();
		//(*itr).subs.print();

		auto itr_subs = (*itr).subs.begin();
		auto end_subs = (*itr).subs.end();
		while (itr_subs != end_subs) {
			os << "\t" << (*itr_subs).getStateScaleMarkInLetters() << ", " << (*itr_subs).getName() << std::endl;
			++itr_subs;
		}
		++itr;
	}
	return os;
}