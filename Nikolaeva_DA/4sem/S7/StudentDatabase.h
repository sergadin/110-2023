#ifndef STUDENT_DB_H
#define STUDENT_DB_H

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <iomanip>
#include <algorithm>
#include <regex>

class StudentDatabase {
	public:
		struct Student {
			std::string name;
			int group;
			double rating;
			std::string info;

			Student() : group(0), rating(0.0) {}
			Student(const std::string& name, int group, double rating, const std::string& info)
				: name(name), group(group), rating(rating), info(info) {}

			friend std::ostream& operator<<(std::ostream& os, const Student& student) {
				os << "Name: " << student.name << ", Group: " << student.group
					<< ", Rating: " << std::fixed << std::setprecision(2) << student.rating 
					<< ", Info: " << student.info;
				return os;
			}
		};

		// Основные методы
		bool loadFromFile(const std::string& filename);
		bool saveToFile(const std::string& filename);
		bool addStudent(const Student& student);
		bool removeStudent(const std::string& name);
		bool updateStudent(const std::string& name, const Student& new_student);

		// SQL запросы
		std::vector<Student> select(const std::string& query);
		std::vector<Student> reselect(const std::string& query);

		// Экспорт
		std::string toHTML(const std::vector<Student>& students);
		std::string toTeX(const std::vector<Student>& students);
		void printAllStudents() const;

		// Сортировка
		void sort(std::vector<Student>& students, const std::string& field);

	private:
		std::vector<Student> students;
		std::unordered_map<int, std::unordered_set<int>> groupIndex;
		std::unordered_map<double, std::unordered_set<int>> ratingIndex;
		std::vector<Student> previousResults;

		// Вспомогательные методы
		int binarySearch(const std::string& name) const;
		double getRatingRangeKey(double rating) const;
		void rebuildIndices();
		void updateIndices(int index, const Student& student);
		void removeFromIndices(int index);
		void sortStudentsByName();

		// Парсинг SQL запросов
		struct SelectionCriteria {
			std::string fieldName;
			enum class ValueType { STRING, INTEGER, DOUBLE } valueType;
			std::variant<std::string, int, double> value;
			enum class Operation { EQUAL, GREATER_THAN, LESS_THAN, CONTAINS } operation;
		};
		std::vector<SelectionCriteria> parseQuery(const std::string& query) const;
};

#endif
