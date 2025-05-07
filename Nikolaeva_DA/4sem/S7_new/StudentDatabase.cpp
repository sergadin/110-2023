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

vector<StudentDatabase::Student> StudentDatabase::select(const string& query) {
	previousResults.clear();
	try {
		auto criteria = parseQuery(query);

		for (const auto& s : students) {
			bool match = true;
			for (const auto& c : criteria) {
				if (c.fieldName == "name") {
					string val = get<string>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && s.name != val) match = false;
					if (c.operation == SelectionCriteria::Operation::CONTAINS && s.name.find(val) == string::npos) match = false;
				}
				else if (c.fieldName == "group") {
					int val = get<int>(c.value);
					if (s.group != val) match = false;
				}
				else if (c.fieldName == "rating") {
					double val = get<double>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && fabs(s.rating - val) >= 1e-9) match = false;
					if (c.operation == SelectionCriteria::Operation::GREATER_THAN && s.rating <= val) match = false;
					if (c.operation == SelectionCriteria::Operation::LESS_THAN && s.rating >= val) match = false;
				}
				if (!match) break;
			}
			if (match) previousResults.push_back(s);
		}
	} catch (...) {

		std::cerr << "Error in select query: " << query << std::endl;
	}
	return previousResults;
}

vector<StudentDatabase::Student> StudentDatabase::reselect(const string& query) {
	if (previousResults.empty()) {
		return select(query); 
	}

	vector<Student> currentResults = previousResults; 
	previousResults.clear(); 

	try {
		auto criteria = parseQuery(query);

		for (const auto& s : currentResults) {
			bool match = true;
			for (const auto& c : criteria) {
				if (c.fieldName == "name") {
					string val = get<string>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && s.name != val) match = false;
					if (c.operation == SelectionCriteria::Operation::CONTAINS && s.name.find(val) == string::npos) match = false;
				}
				else if (c.fieldName == "group") {
					int val = get<int>(c.value);
					if (s.group != val) match = false;
				}
				else if (c.fieldName == "rating") {
					double val = get<double>(c.value);
					if (c.operation == SelectionCriteria::Operation::EQUAL && fabs(s.rating - val) >= 1e-9) match = false;
					if (c.operation == SelectionCriteria::Operation::GREATER_THAN && s.rating <= val) match = false;
					if (c.operation == SelectionCriteria::Operation::LESS_THAN && s.rating >= val) match = false;
				}
				if (!match) break;
			}
			if (match) previousResults.push_back(s);
		}
	} catch (...) {

		std::cerr << "Error in reselect query: " << query << std::endl;
	}

	return previousResults;
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

vector<StudentDatabase::SelectionCriteria> StudentDatabase::parseQuery(const string& query) const {
	vector<SelectionCriteria> criteria;
	regex pattern(R"((\w+)\s*([><=*]+)\s*([^;]+))");
	smatch match;
	string remaining = query;

	while (regex_search(remaining, match, pattern)) {
		SelectionCriteria c;
		c.fieldName = match[1];
		string op = match[2];
		string value = match[3];

		if (op == "=") c.operation = SelectionCriteria::Operation::EQUAL;
		else if (op == ">") c.operation = SelectionCriteria::Operation::GREATER_THAN;
		else if (op == "<") c.operation = SelectionCriteria::Operation::LESS_THAN;
		else if (op == "*=") c.operation = SelectionCriteria::Operation::CONTAINS;
		else {
			std::cerr << "Invalid operator: " << op << std::endl;
			continue;
		}

		if (c.fieldName == "name") {
			c.valueType = SelectionCriteria::ValueType::STRING;
			c.value = value;
		}
		else if (c.fieldName == "group") {
			c.valueType = SelectionCriteria::ValueType::INTEGER;
			try {
				c.value = stoi(value);
			} catch (const std::invalid_argument& e) {
				std::cerr << "Invalid group value: " << value << std::endl;
				continue;
			}
		}
		else if (c.fieldName == "rating") {
			c.valueType = SelectionCriteria::ValueType::DOUBLE;
			try {
				c.value = stod(value);
			} catch (const std::invalid_argument& e) {
				std::cerr << "Invalid rating value: " << value << std::endl;
				continue;
			}
		}
		else {
			std::cerr << "Invalid field name: " << c.fieldName << std::endl;
			continue;
		}

		criteria.push_back(c);
		remaining = match.suffix();
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
