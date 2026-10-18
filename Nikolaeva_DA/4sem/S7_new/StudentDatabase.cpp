#include "StudentDatabase.h"
#include <cmath>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <regex>

using namespace std;

int StudentDatabase::binarySearch(const string& name) const {
	int left = 0;
	int right = students.size() - 1;

	while (left <= right) {
		int mid = left + (right - left) / 2;
		if (students[mid].name == name) return mid;
		students[mid].name < name ? left = mid + 1 : right = mid - 1;
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
	ratingIndex[getRatingRangeKey(student.rating)].insert(index);
}

void StudentDatabase::removeFromIndices(int index) {
	if (index < 0 || index >= static_cast<int>(students.size())) return;

	const auto& student = students[index];
	groupIndex[student.group].erase(index);
	ratingIndex[getRatingRangeKey(student.rating)].erase(index);
}

void StudentDatabase::sortStudentsByName() {
	std::sort(students.begin(), students.end(),
			[](const Student& a, const Student& b) { return a.name < b.name; });
}

bool StudentDatabase::loadFromFile(const string& filename) {
	ifstream file(filename);
	if (!file.is_open()) return false;

	students.clear();
	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		string name, groupStr, ratingStr, info;

		if (getline(iss, name, ',') &&
				getline(iss, groupStr, ',') &&
				getline(iss, ratingStr, ',') &&
				getline(iss, info))
		{
			try {
				students.emplace_back(
						name,
						stoi(groupStr),
						stod(ratingStr),
						info
						);
			} catch (...) {

				std::cerr << "Error parsing line: " << line << std::endl;
			}
		}
	}

	sortStudentsByName();
	rebuildIndices();
	return true;
}

bool StudentDatabase::saveToFile(const string& filename) {
	ofstream file(filename);
	if (!file.is_open()) return false;

	for (const auto& s : students) {
		file << s.name << "," << s.group << ","
			<< fixed << setprecision(2) << s.rating << ","
			<< s.info << "\n";
	}
	return true;
}

bool StudentDatabase::addStudent(const Student& student) {
	if (binarySearch(student.name) != -1) return false;

	students.push_back(student);
	sortStudentsByName();
	rebuildIndices();
	return true;
}

bool StudentDatabase::removeStudent(const string& name) {
	int index = binarySearch(name);
	if (index == -1) return false;

	removeFromIndices(index);
	students.erase(students.begin() + index);
	rebuildIndices();
	return true;
}

bool StudentDatabase::updateStudent(const string& name, const Student& new_student) {
	int index = binarySearch(name);
	if (index == -1) return false;

	removeFromIndices(index);
	students[index] = new_student;
	updateIndices(index, new_student);
	return true;
}


std::vector<StudentDatabase::Student> StudentDatabase::select(const std::string& query) {
	previousResults.clear();

	if (query.empty()) {
		std::cerr << "Error: Empty query" << std::endl;
		return {};
	}

	try {
		auto criteria = parseQuery(query);

		if (criteria.empty()) {
			std::cerr << "Error: Invalid query syntax. Example: SELECT rating>4.0;group=101" << std::endl;
			return {};
		}

		std::vector<Student> result;

		for (const auto& s : students) {
			bool match = true;
			for (const auto& c : criteria) {
				if (c.fieldName == "name") {
					std::string val = std::get<std::string>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && s.name != val) match = false;
					if (c.operation == SelectionCriteria::Operation::CONTAINS && s.name.find(val) == std::string::npos) match = false;
				} 
				else if (c.fieldName == "group") {
					int val = std::get<int>(c.value);
					if (s.group != val) match = false;
				} 
				else if (c.fieldName == "rating") {
					double val = std::get<double>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && fabs(s.rating - val) >= 1e-9) match = false;
					if (c.operation == SelectionCriteria::Operation::GREATER_THAN && s.rating <= val) match = false;
					if (c.operation == SelectionCriteria::Operation::LESS_THAN && s.rating >= val) match = false;
				}
				if (!match) break;
			}
			if (match) result.push_back(s);
		}

		previousResults = result;
		return result;

	} catch (const std::exception& e) {  
		std::cerr << "Query execution error: " << e.what() << std::endl;
		return {}; 
	}
}

std::vector<StudentDatabase::Student> StudentDatabase::reselect(const std::string& query) {
	if (previousResults.empty()) {
		std::cout << "No previous results. Performing regular SELECT." << std::endl;
		return select(query);
	}

	if (query.empty()) {
		std::cerr << "Error: Empty query" << std::endl;
		return {};
	}

	try {
		auto criteria = parseQuery(query);

		if (criteria.empty()) {
			std::cerr << "Error: Invalid query syntax. Example: RESELECT rating>4.0;group=101" << std::endl;
			return {};
		}

		std::vector<Student> result;

		for (const auto& s : previousResults) {
			bool match = true;
			for (const auto& c : criteria) {
				if (c.fieldName == "name") {
					std::string val = std::get<std::string>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && s.name != val) match = false;
					if (c.operation == SelectionCriteria::Operation::CONTAINS && s.name.find(val) == std::string::npos) match = false;
				} 
				else if (c.fieldName == "group") {
					int val = std::get<int>(c.value);
					if (s.group != val) match = false;
				} 
				else if (c.fieldName == "rating") {
					double val = std::get<double>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && fabs(s.rating - val) >= 1e-9) match = false;
					if (c.operation == SelectionCriteria::Operation::GREATER_THAN && s.rating <= val) match = false;
					if (c.operation == SelectionCriteria::Operation::LESS_THAN && s.rating >= val) match = false;
				}
				if (!match) break;
			}
			if (match) result.push_back(s);
		}

		previousResults = result;
		return result;

	} catch (const std::exception& e) {  
		std::cerr << "Query execution error: " << e.what() << std::endl;
		return {}; 
	}
}

string StudentDatabase::serialize(const vector<Student>& students) {
	stringstream ss;
	ss << students.size() << "\n";
	for (const auto& s : students) {
		ss << s.name << "\n" << s.group << "\n"
			<< fixed << setprecision(2) << s.rating << "\n"
			<< s.info << "\n";
	}
	return ss.str();
}

vector<StudentDatabase::Student> StudentDatabase::deserialize(const string& data) {
	vector<Student> result;
	stringstream ss(data);
	size_t count;
	ss >> count;
	ss.ignore();

	for (size_t i = 0; i < count; ++i) {
		string name, groupStr, ratingStr, info;
		getline(ss, name);
		getline(ss, groupStr);
		getline(ss, ratingStr);
		getline(ss, info);

		try {
			result.emplace_back(
					name,
					stoi(groupStr),
					stod(ratingStr),
					info
					);
		} catch (...) {

			std::cerr << "Error deserializing record " << i << std::endl;
		}
	}
	return result;
}

std::vector<StudentDatabase::SelectionCriteria> StudentDatabase::parseQuery(const std::string& query) const {
	std::vector<SelectionCriteria> criteria;
	std::regex pattern(R"((name|group|rating)\s*([><=*]+)\s*([^;]+))");
	std::smatch match;
	std::string remaining = query;

	while (std::regex_search(remaining, match, pattern)) {
		SelectionCriteria c;
		c.fieldName = match[1];
		std::string op = match[2];
		std::string value = match[3];
		value.erase(value.find_last_not_of(" \t") + 1);

		if (op == "=") c.operation = SelectionCriteria::Operation::EQUAL;
		else if (op == ">") c.operation = SelectionCriteria::Operation::GREATER_THAN;
		else if (op == "<") c.operation = SelectionCriteria::Operation::LESS_THAN;
		else if (op == "*=") c.operation = SelectionCriteria::Operation::CONTAINS;
		else {
			std::cerr << "Error: Invalid operator: " << op << std::endl;
			return {};
		}

		try {
			if (c.fieldName == "name") {
				c.value = value;
			} 
			else if (c.fieldName == "group") {
				c.value = std::stoi(value);
			} 
			else if (c.fieldName == "rating") {
				c.value = std::stod(value);
			} 
			else {
				std::cerr << "Error: Unknown field: " << c.fieldName << std::endl;
				return {};
			}
		} 
		catch (const std::exception& e) {
			std::cerr << "Error parsing value '" << value << "' for field '" << c.fieldName << "': " << e.what() << std::endl;
			return {};
		}

		criteria.push_back(c);
		remaining = match.suffix();
	}

	if (criteria.empty()) {
		std::cerr << "Error: No valid criteria found in query" << std::endl;
	}

	return criteria;
}
void StudentDatabase::printAllStudents() const {
	for (const auto& s : students) {
		cout << s << "\n";
	}
}

void StudentDatabase::sortByField(vector<Student>& students, const string& field) {
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
