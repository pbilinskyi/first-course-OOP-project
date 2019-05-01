#pragma once
#include <string>

class Info {
private:
	friend class TestStudentResult;
	//=====================
	class Student {
	private:
		//====================
		class SubjectResult {
		private:
			std::string name;
			int summaryMark;
			int termMark;
			int examMark;
			int stateScaleMark;
			//theese methods-checkers need to be rewised 
			bool isMarkOfNotAllowed(int summaryMark) const noexcept;
			bool isMarkOfUpsent(int summaryMark) const noexcept;
			//====================
			bool isValidSubjectName(std::string& name) const noexcept;
			bool isCorrectData(std::string& name, int summaryMark, int termMark, int examMark, int stateScaleMark) const noexcept;
			bool areConcerted(int stateScaleMark, int symmaryMark) const noexcept;
		public:
			SubjectResult(int summaryMark, int stateScaleMark, int examMark, std::string& subjectName, int termMark);
			std::string getName() const noexcept;
			int getSummaryMark() const noexcept;
			int getTermMark() const noexcept;
			int getExamMark() const noexcept;
			int getStateScaleMark() const noexcept;
			bool operator==(SubjectResult&) const;
			bool operator>(SubjectResult&) const;
			bool operator<(SubjectResult&) const;
			bool operator>=(SubjectResult&) const;
			bool operator<=(SubjectResult&) const;
		};
		//====================
		class SubjectResults {
		public: 
			int size();
		};
		//====================
		std::string name;
		std::string surname;
		std::string gradebookCode;
		std::string groupCode;
		//additional feilds that help to change the stability in a correct and clear way
		static const int MAX_RESULT = 100;
		static const int MIN_RESULT = 0;
		static const int UNDEFINED = -1;
		int currentWorth = MAX_RESULT;
		int currentBest = MIN_RESULT;
		int stability = UNDEFINED;
		void modifyStability(int summaryMark) noexcept;
		//------------
		int rating = UNDEFINED;
		void modifyRating(int summaryMark, int old_size_of_container) noexcept;
		//following methods check the corectness of input data
		bool isValidGradeBookCode(std::string& gradebookCode) const noexcept;
		bool isValidGroupCode(std::string& groupCode) const noexcept;
		bool hasValidNameSymbols(std::string&) const noexcept;
		bool isCorrectData(std::string& name, std::string& surname, std::string& groupCode, std::string& gradebookCode) const noexcept;
	public:
		SubjectResults subs;
		Student(std::string& groupCode, std::string& name, std::string& gradebookCode, std::string& surname);
		void load(int summaryMark, int stateScaleMark, int examMark, std::string& subjectName, int termMark);
		std::string getName() const noexcept;
		std::string getSurname() const noexcept;
		std::string getGradebookCode() const noexcept;
		int getStability() const noexcept;
		int getRating() const noexcept;
		bool operator==(Student&) const;
		bool operator>(Student&) const;
		bool operator<(Student&) const;
		bool operator>=(Student&) const;
		bool operator<=(Student&) const;
	};
	class Students {
	public:
		int size();
	};
	int notesNumber;
	int markSum;
public:
	void load(std::string& groupCode, std::string& name, std::string& gradebookCode, std::string& surname);
	void load(std::string& groupCode, std::string& name, int summaryMark, int stateScaleMark, 
		int examMark, std::string& gradebookCode, std::string& surname,  
				std::string& subjectName,  int termMark);
	Students studs;

	int getNotesNumber() const noexcept;
	int getMarkSum() const noexcept;
};

