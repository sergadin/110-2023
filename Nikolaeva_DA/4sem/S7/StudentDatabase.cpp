#include "StudentDatabase.h"
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iomanip>



int StudentDatabase::binarySearch(const std::string& name) const {
	int left = 0;
	int right = students.size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (students[mid].name == name) {
			return mid;
		} else if (students[mid].name < name) {
			left = mid + 1;
		} else {
			right = mid - 1;
		}
	}
	return -1;
}

double StudentDatabase::getRatingRangeKey(double rating) const {
	return floor(rating * 10) / 10.0;
}

void StudentDatabase::rebuildIndices() {
	groupIndex.clear();
	ratingIndex.clear();

	for (size_t i = 0; i < students.size(); ++i) {
		updateIndices(i, students[i]);
	}
}

void StudentDatabase::updateIndices(int index, const Student& student) {
	groupIndex[student.group].insert(index);
	double ratingKey = getRatingRangeKey(student.rating);
	ratingIndex[ratingKey].insert(index);
}

void StudentDatabase::removeFromIndices(int index) {
	if (index < 0 || static_cast<size_t>(index) >= students.size()) return;

	const Student& student = students[index];
	groupIndex[student.group].erase(index);

	double ratingKey = getRatingRangeKey(student.rating);
	ratingIndex[ratingKey].erase(index);
}

void StudentDatabase::sortStudentsByName() {
	std::sort(students.begin(), students.end(), 
			[](const Student& a, const Student& b) { return a.name < b.name; });
}


bool StudentDatabase::loadFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error opening file: " << filename << std::endl;
		return false;
	}

	students.clear();
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		std::string name, groupStr, ratingStr, info;

		if (std::getline(iss, name, ',') &&
				std::getline(iss, groupStr, ',') &&
				std::getline(iss, ratingStr, ',') &&
				std::getline(iss, info)) {

			try {
				int group = std::stoi(groupStr);
				double rating = std::stod(ratingStr);
				if (binarySearch(name) == -1) {
					students.emplace_back(name, group, rating, info);
				}
			} catch (...) {
				continue;
			}
		}
	}

	sortStudentsByName();
	rebuildIndices();
	return true;
}

bool StudentDatabase::saveToFile(const std::string& filename) {
	std::ofstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error creating file: " << filename << std::endl;
		return false;
	}

	for (const auto& student : students) {
		file << student.name << "," << student.group << ","
			<< std::fixed << std::setprecision(2) << student.rating << ","
			<< student.info << "\n";
	}
	return true;
}

bool StudentDatabase::addStudent(const Student& student) {
	if (binarySearch(student.name) != -1) {
		return false;
	}

	students.push_back(student);
	sortStudentsByName();
	rebuildIndices();
	return true;
}

bool StudentDatabase::removeStudent(const std::string& name) {
	int index = binarySearch(name);
	if (index == -1) {
		return false;
	}

	removeFromIndices(index);
	students.erase(students.begin() + index);
	return true;
}

bool StudentDatabase::updateStudent(const std::string& name, const Student& new_student) {
	int index = binarySearch(name);
	if (index == -1) {
		return false;
	}

	removeFromIndices(index);
	students[index] = new_student;
	updateIndices(index, new_student);
	sortStudentsByName();
	return true;
}


std::vector<StudentDatabase::SelectionCriteria> StudentDatabase::parseQuery(const std::string& query) const {
	std::vector<SelectionCriteria> criteriaList;
	std::regex criteriaRegex(R"((\w+)\s*([=><*]=?)\s*([^;]+))");
	std::smatch match;
	std::string remainingQuery = query;

	while (std::regex_search(remainingQuery, match, criteriaRegex)) {
		SelectionCriteria criteria;
		criteria.fieldName = match[1].str();
		std::string opStr = match[2].str();
		std::string valueStr = match[3].str();

		// Определение операции
		if (opStr == "=") {
			criteria.operation = SelectionCriteria::Operation::EQUAL;
		} else if (opStr == ">") {
			criteria.operation = SelectionCriteria::Operation::GREATER_THAN;
		} else if (opStr == "<") {
			criteria.operation = SelectionCriteria::Operation::LESS_THAN;
		} else if (opStr == "*=") {
			criteria.operation = SelectionCriteria::Operation::CONTAINS;
		}

		// Парсинг значения в зависимости от типа поля
		if (criteria.fieldName == "name") {
			criteria.valueType = SelectionCriteria::ValueType::STRING;
			criteria.value = valueStr;
		} 
		else if (criteria.fieldName == "group") {
			criteria.valueType = SelectionCriteria::ValueType::INTEGER;
			try {
				criteria.value = std::stoi(valueStr);
			} catch (...) {
				throw std::invalid_argument("Invalid group value");
			}
		}
		else if (criteria.fieldName == "rating") {
			criteria.valueType = SelectionCriteria::ValueType::DOUBLE;
			try {
				criteria.value = std::stod(valueStr);
			} catch (...) {
				throw std::invalid_argument("Invalid rating value");
			}
		}
		else {
			throw std::invalid_argument("Unknown field: " + criteria.fieldName);
		}

		criteriaList.push_back(criteria);
		remainingQuery = match.suffix().str();
	}

	return criteriaList;
}

std::vector<StudentDatabase::Student> StudentDatabase::select(const std::string& query) {
	std::vector<Student> results;

	try {
		auto criteriaList = parseQuery(query);

		for (const auto& student : students) {
			bool match = true;
			for (const auto& criteria : criteriaList) {
				bool fieldMatch = false;

				if (criteria.fieldName == "name") {
					const std::string& value = std::get<std::string>(criteria.value);
					if (criteria.operation == SelectionCriteria::Operation::EQUAL) {
						fieldMatch = (student.name == value);
					} else if (criteria.operation == SelectionCriteria::Operation::CONTAINS) {
						fieldMatch = (student.name.find(value) != std::string::npos);
					}
				}
				else if (criteria.fieldName == "group") {
					int value = std::get<int>(criteria.value);
					if (criteria.operation == SelectionCriteria::Operation::EQUAL) {
						fieldMatch = (student.group == value);
					}
				}
				else if (criteria.fieldName == "rating") {
					double value = std::get<double>(criteria.value);
					if (criteria.operation == SelectionCriteria::Operation::EQUAL) {
						fieldMatch = (fabs(student.rating - value) < 1e-9);
					} else if (criteria.operation == SelectionCriteria::Operation::GREATER_THAN) {
						fieldMatch = (student.rating > value);
					} else if (criteria.operation == SelectionCriteria::Operation::LESS_THAN) {
						fieldMatch = (student.rating < value);
					}
				}

				match = match && fieldMatch;
				if (!match) break;
			}

			if (match) {
				results.push_back(student);
			}
		}
	} catch (const std::exception& e) {
		std::cerr << "Query error: " << e.what() << std::endl;
		return {};
	}

	previousResults = results;
	return results;
}

std::vector<StudentDatabase::Student> StudentDatabase::reselect(const std::string& query) {
	std::vector<Student> results;

	try {
		auto criteriaList = parseQuery(query);
		double targetRating = 0.0;
		bool hasRatingCriteria = false;

		// Поиск критерия по рейтингу
		for (const auto& criteria : criteriaList) {
			if (criteria.fieldName == "rating" && 
					criteria.operation == SelectionCriteria::Operation::EQUAL) {
				targetRating = std::get<double>(criteria.value);
				hasRatingCriteria = true;
				break;
			}
		}

		if (!hasRatingCriteria) {
			std::cerr << "Reselect requires rating equality criteria" << std::endl;
			return {};
		}

		// Фильтрация предыдущих результатов
		double minRating = targetRating;
		double maxRating = targetRating + 0.1;

		for (const auto& student : previousResults) {
			if (student.rating >= minRating && student.rating < maxRating) {
				results.push_back(student);
			}
		}
	} catch (const std::exception& e) {
		std::cerr << "Reselect error: " << e.what() << std::endl;
		return {};
	}

	return results;
}


//HTML
std::string StudentDatabase::toHTML(const std::vector<Student>& students) {
	std::stringstream ss;
	ss << "<!DOCTYPE html>\n<html>\n<head>\n<title>Student Database</title>\n"
		<< "<style>\n"
		<< "table { border-collapse: collapse; width: 100%; }\n"
		<< "th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }\n"
		<< "th { background-color: #f2f2f2; }\n"
		<< "</style>\n</head>\n<body>\n"
		<< "<h1>Student Records</h1>\n"
		<< "<table>\n"
		<< "<tr><th>Name</th><th>Group</th><th>Rating</th><th>Info</th></tr>\n";

	for (const auto& student : students) {
		ss << "<tr>"
			<< "<td>" << student.name << "</td>"
			<< "<td>" << student.group << "</td>"
			<< "<td>" << std::fixed << std::setprecision(2) << student.rating << "</td>"
			<< "<td>" << student.info << "</td>"
			<< "</tr>\n";
	}

	ss << "</table>\n</body>\n</html>";
	return ss.str();
}

std::string StudentDatabase::toTeX(const std::vector<Student>& students) {
	std::stringstream ss;
	ss << "\\documentclass{article}\n"
		<< "\\usepackage[utf8]{inputenc}\n"
		<< "\\usepackage[russian]{babel}\n"
		<< "\\begin{document}\n"
		<< "\\section*{Student Records}\n"
		<< "\\begin{tabular}{|l|l|l|l|}\n"
		<< "\\hline\n"
		<< "Name & Group & Rating & Info \\\\ \\hline\n";

	for (const auto& student : students) {
		ss << student.name << " & " << student.group << " & " 
			<< std::fixed << std::setprecision(2) << student.rating << " & " 
			<< student.info << " \\\\ \\hline\n";
	}

	ss << "\\end{tabular}\n\\end{document}";
	return ss.str();
}

void StudentDatabase::printAllStudents() const {
	std::cout << "=== All Students ===\n";
	for (const auto& student : students) {
		std::cout << student << "\n";
	}
	std::cout << "===================\n";
}

void StudentDatabase::sort(std::vector<Student>& students, const std::string& field) {
	if (field == "name") {
		std::sort(students.begin(), students.end(),
				[](const Student& a, const Student& b) { return a.name < b.name; });
	} 
	else if (field == "group") {
		std::sort(students.begin(), students.end(),
				[](const Student& a, const Student& b) { return a.group < b.group; });
	}
	else if (field == "rating") {
		std::sort(students.begin(), students.end(),
				[](const Student& a, const Student& b) { return a.rating < b.rating; });
	}
}
