#pragma once
#include <string>
#include "StackTemplate.h"

class Info {
private:
	//=====================
	class Student {
	private:
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
			//copying and moving
			//SubjectResult(const SubjectResult&) = default;
			//SubjectResult(SubjectResult&&) = default;
			//SubjectResult& operator=(const SubjectResult&) = default;
			//SubjectResult& operator=(SubjectResult&&) = default;
			//~SubjectResult() = default;
			//
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
		std::string name;
		std::string surname;
		std::string gradebookCode;
		std::string groupCode;
		//additional fields that help to change the stability in a correct and clear way
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
		using SubjectResults = Stack<SubjectResult>;
		SubjectResults subs;

		Student(std::string& groupCode, std::string& name, std::string& gradebookCode, std::string& surname);
		Student() = default;
		/*Student(const Student&);
		Student(Student&&) = default;
		Student& operator=(const Student&) = default;
		Student& operator=(Student&&) = default;
		~Student() = default;
		*/

		void load(int summaryMark, int stateScaleMark, int examMark, std::string& subjectName, int termMark);
		std::string getName() const noexcept;
		std::string getSurname() const noexcept;
		std::string getGradebookCode() const noexcept;
		int getStability() const noexcept;
		int getRating() const noexcept;
		bool operator==(const Student&);
		bool operator!=(const Student&);
		bool operator>(Student&) const;
		bool operator<(Student&) const;
		bool operator>=(Student&) const;
		bool operator<=(Student&) const;
		operator std::string() const;
	};
public:
	void load(std::string& groupCode, std::string& name, std::string& gradebookCode, std::string& surname);
	void load(std::string& groupCode, std::string& name, int summaryMark, int stateScaleMark, 
		int examMark, std::string& gradebookCode, std::string& surname,  
				std::string& subjectName,  int termMark);
	
	using Students = Stack<Student>;
	Students studs;
};

