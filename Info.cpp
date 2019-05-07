#include "Info.h"
#include <iostream>
#include <stdexcept>
#include "ctype.h"

void Info::load(std::string& groupCode, std::string& name, std::string& gradebookCode, std::string& surname)
{
	//Student st(groupCode, name, gradebookCode, surname);
	studs.push(Student(groupCode, name, gradebookCode, surname));
}

void Info::load(std::string& groupCode, std::string& name, int summaryMark, int stateScaleMark,
	int examMark, std::string& gradebookCode, std::string& surname,
	std::string& subjectName, int termMark)
{
	//studs.push(Student(groupCode, name, gradebookCode, surname));
	//studs.top().load(summaryMark, stateScaleMark, examMark, subjectName, termMark);
	Student st(groupCode, name, gradebookCode, surname);
	try {
		studs.find(st).load(summaryMark, stateScaleMark, examMark, subjectName, termMark);
	}
	catch (std::out_of_range) {
		load(groupCode, name, gradebookCode, surname);
		studs.find(st).load(summaryMark, stateScaleMark, examMark, subjectName, termMark);
		studs.print();
	}
}

bool Info::Student::SubjectResult::isMarkOfNotAllowed(int summaryMark) const noexcept
{
	//we consider that if student is not allowed to take an exam, his mark is 0
	return (summaryMark >= 0)&&(summaryMark < 36);
}

bool Info::Student::SubjectResult::isMarkOfUpsent(int summaryMark) const noexcept
{
 	//we consider that if student was upsent, his mark is 0
	return (summaryMark >= 0)&&(summaryMark <= 60);
}

bool Info::Student::SubjectResult::isValidSubjectName(std::string & name) const noexcept
{
	bool flag = true;
	size_t n = name.size();
	for (int i = 0; i < n; i++)	{
		if ((!isalpha(name[i])) && (name[i] != '\"') && (name[i] != ' ') && (name[i] != '-')) flag = false;
	}
	if (n > 62) flag = false;
	return flag;
}	

bool Info::Student::SubjectResult::isCorrectData(std::string& name, int summaryMark, int termMark, int examMark, int stateScaleMark) const noexcept
{
	bool flag = true;
	if (!((stateScaleMark >= -1) && (stateScaleMark <= 5) && (stateScaleMark != 1))) flag = false;
	if (!areConcerted(stateScaleMark, summaryMark)) flag = false;
	if (!((termMark <= 60) && (termMark >= 0))) flag = false;
	if (!(((examMark <= 40) && (examMark >= 24)) || (examMark == 0))) flag = false;
	if (summaryMark != (termMark + examMark)) flag = false;
	if (!isValidSubjectName(name)) flag = false;

	return flag;
}

bool Info::Student::SubjectResult::areConcerted(int stateScaleMark, int summaryMark) const noexcept
{
	bool flag = false;
	switch (stateScaleMark)
	{
	case -1: flag = isMarkOfNotAllowed(summaryMark); break;
	case 0: flag = isMarkOfUpsent(summaryMark); break;
	case 2: flag = (summaryMark < 60) && (summaryMark >= 0); break;
	case 3: flag = (summaryMark >= 60) && (summaryMark < 75); break;
	case 4: flag = (summaryMark >= 75) && (summaryMark < 90); break;
	case 5: flag = (summaryMark >= 90) && (summaryMark <= 100); break;
	default: 
		std::cout << "default block is reached\n";
		break;
	}
	return flag;
}

Info::Student::SubjectResult::SubjectResult(int summaryMark, int stateScaleMark, int examMark, std::string& name, int termMark)
{
	if (!isCorrectData(name, summaryMark, termMark, examMark, stateScaleMark))
			throw std::invalid_argument("Error while loading subjects result: input data doesn't satisfy the restrictions.");
	this->name = name;
	this->summaryMark = summaryMark;
	this->termMark = termMark;
	this->examMark = examMark;
	this->stateScaleMark = stateScaleMark;
	
	//std::cout << "SubjectResult " + this->name + " is created."<< std::endl;
}

std::string Info::Student::SubjectResult::getName() const noexcept
{
	return name;
}

int Info::Student::SubjectResult::getSummaryMark() const noexcept
{
	return summaryMark;
}

int Info::Student::SubjectResult::getTermMark() const noexcept
{
	return termMark;
}

int Info::Student::SubjectResult::getExamMark() const noexcept
{
	return examMark;
}

int Info::Student::SubjectResult::getStateScaleMark() const noexcept
{
	return stateScaleMark;
}


bool Info::Student::SubjectResult::operator==(SubjectResult &other) const
{	
	return (!this->summaryMark == other.summaryMark)&&(this->name.compare(other.name) == 0);
}

bool Info::Student::SubjectResult::operator>(SubjectResult &other) const
{
	return ((this->summaryMark > other.summaryMark) || ((this->summaryMark == other.summaryMark) && (this->name.compare(other.name) > 0)));
}

bool Info::Student::SubjectResult::operator<(SubjectResult &other) const
{
	return ((this->summaryMark < other.summaryMark) || ((this->summaryMark == other.summaryMark) && (this->name.compare(other.name) < 0)));
	;
}

bool Info::Student::SubjectResult::operator>=(SubjectResult &other) const
{
	return ((this->summaryMark > other.summaryMark) || ((this->summaryMark == other.summaryMark) && (this->name.compare(other.name) == 0)));
}

bool Info::Student::SubjectResult::operator<=(SubjectResult &other) const
{
	return ((this->summaryMark < other.summaryMark) || ((this->summaryMark == other.summaryMark) && (this->name.compare(other.name) == 0)));
}

void Info::Student::modifyRating(int summaryMark, int old_size_of_container) noexcept
{
	if (rating == UNDEFINED) rating = summaryMark;
	else rating = (rating*old_size_of_container + summaryMark) / (old_size_of_container + 1);
}

bool Info::Student::isValidGradeBookCode(std::string & gradeBookCode) const noexcept
{
	bool flag = true;
	size_t n = gradeBookCode.size();
	for (int i = 0; i < n; i++) {
		if (!isdigit(gradeBookCode[i])) flag = false;
	}
	if (n > 8) flag = false;
	return flag;
}

bool Info::Student::isValidGroupCode(std::string & groupCode) const noexcept
{
	bool flag = true;
	size_t n = groupCode.size();
	for (int i = 0; i < n; ++i) {
		if ((!isalpha(groupCode[i]))&&(!isdigit(groupCode[i]))&&(groupCode[i] != '-')) flag = false;
	}
	if (n > 4) flag = false;
	return flag;
}

bool Info::Student::hasValidNameSymbols(std::string &s) const noexcept
{
	bool flag = true;
	size_t n = s.size();
	for (int i = 0; i < n; ++i) {
		if (!(isalpha(s[i])||((s[i] == '\'')||(s[i] == '-')))) flag = false;
	}
	return flag;
}

bool Info::Student::isCorrectData(std::string& name, std::string& surname, std::string& groupCode, std::string& gradebookCode) const noexcept
{
	bool flag = true;
	if (surname.size() > 24) flag = false;
	if (name.size() > 22) flag = false;
	if ((!hasValidNameSymbols(name)) || (!hasValidNameSymbols(surname))) flag = false;
	if (!isValidGroupCode(groupCode)) flag = false;
	if (!isValidGradeBookCode(gradebookCode)) flag = false;
	return flag;
}

void Info::Student::modifyStability(int summaryMark) noexcept
{
	if (summaryMark < currentWorth) currentWorth = summaryMark;
	if (summaryMark > currentBest) currentBest = summaryMark;
	stability = currentBest - currentWorth;
}

//if input data is incorrect, throw invalid_argument
Info::Student::Student(std::string& groupCode, std::string& name, std::string& gradebookCode, std::string& surname)
{
	if (!(isCorrectData(name, surname, groupCode, gradebookCode))) throw std::invalid_argument("Error while loading student: input data doesn't satisfy the restrictions");
	this->name = name;
	this->surname = surname;
	this->groupCode = groupCode;
	this->gradebookCode = gradebookCode;
}

void Info::Student::load(int summaryMark, int stateScaleMark, int examMark, std::string& subjectName, int termMark)
{
	int old_size = subs.size();
	SubjectResult sr(summaryMark,  stateScaleMark, examMark,  subjectName, termMark);
	/*
		...object is loading into container SubjectResults...
	*/
	modifyStability(summaryMark);
	modifyRating(summaryMark, old_size);
	//std::cout << "Agregated field \"stability\" was modified. Now: " << stability << std::endl;
	//std::cout << "New object was succesfully loaded into StudentResults container" << std::endl;
}

std::string Info::Student::getName() const noexcept
{
	return name;
}

std::string Info::Student::getSurname() const noexcept
{
	return surname;
}

std::string Info::Student::getGradebookCode() const noexcept
{
	return gradebookCode;
}

//pre: if student has no results, return -1
int Info::Student::getStability() const noexcept
{
	return stability;
}

//pre: if student has no results, return -1
int Info::Student::getRating() const noexcept
{
	return rating;
}

bool Info::Student::operator==(const Student &other) 
{
	return (this->getRating() == other.getRating())&&(this->getGradebookCode().compare(other.getGradebookCode()) == 0);
}

bool Info::Student::operator!=(const Student &other) 
{
	return !(*this == other);
}

bool Info::Student::operator>(Student &other) const
{
	return ((this->getRating() > other.getRating())||
		((this->getRating() == other.getRating())&&(this->getGradebookCode().compare(other.getGradebookCode()) > 0)));
}

bool Info::Student::operator<(Student &other) const
{
	return ((this->getRating() < other.getRating()) ||
		((this->getRating() == other.getRating()) && (this->getGradebookCode().compare(other.getGradebookCode()) < 0)));

}

bool Info::Student::operator>=(Student &other) const
{
	return ((this->getRating() > other.getRating()) ||
		((this->getRating() == other.getRating()) && (this->getGradebookCode().compare(other.getGradebookCode()) >= 0)));

}

bool Info::Student::operator<=(Student &other) const
{
	return ((this->getRating() < other.getRating()) ||
		((this->getRating() == other.getRating()) && (this->getGradebookCode().compare(other.getGradebookCode()) <= 0)));

}

Info::Student::operator std::string() const
{
	return name;
}
