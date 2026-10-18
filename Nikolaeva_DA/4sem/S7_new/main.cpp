#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StudentDatabase.h"
#include <random>

using namespace std;

void demonstrateLocalMode() {
	cout << "=== Local Mode ===" << endl;
	StudentDatabase db;

	if (!db.loadFromFile("students.csv")) {
		cerr << "Failed to load data. Creating new database." << endl;
	}

	db.addStudent({ "Иван Смирнов", 101, 4.5, "Замечательно" });
	db.addStudent({ "Александра Смирнова", 102, 3.8, "Хорошо" });

	cout << "\nAll students:" << endl;
	db.printAllStudents();

	cout << "\nStudents with rating > 4.0:" << endl;
	auto topStudents = db.select("rating>4.0");
	for (const auto& s : topStudents) {
		cout << s.name << " | Group: " << s.group
			<< " | Rating: " << fixed << setprecision(2) << s.rating
			<< " | Info: " << s.info << endl;
	}

	if (db.saveToFile("students_updated.csv")) {
		cout << "\nData saved successfully" << endl;
	}
}

void demonstrateServerMode() {
	cout << "\n=== Server Mode ===" << endl;
	cout << "Start server: ./server" << endl;
	cout << "Start client: ./client [scenario_file]" << endl;
	cout << "Available client commands:" << endl;
	cout << "  GET_ALL, SELECT [field][op][value], RESELECT [query], ADD|...format, DELETE [name]" << endl;
}

void generateTestData(int numRecords) {
	ofstream file("large_dataset.csv");
	if (!file) {
		cerr << "Error creating test file" << endl;
		return;
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> groupDist(100, 200);
	std::uniform_real_distribution<> ratingDist(2.0, 5.0);

	for (int i = 0; i < numRecords; ++i) {
		file << "Student_" << i << ","
			<< groupDist(gen) << ","
			<< fixed << setprecision(2) << ratingDist(gen) << ","
			<< "Record_" << i << "\n";
	}
	cout << "Generated " << numRecords << " test records in large_dataset.csv" << endl;
}

int main() {
	int choice;
	do {
		cout << "\n=== Main Menu ===" << endl
			<< "1. Local Mode Demo" << endl
			<< "2. Server Mode Info" << endl
			<< "3. Generate Test Data" << endl
			<< "0. Exit" << endl
			<< "Enter choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
			case 1: demonstrateLocalMode(); break;
			case 2: demonstrateServerMode(); break;
			case 3:
				{
					int numRecords;
					cout << "Enter the number of test records to generate: ";
					cin >> numRecords;
					cin.ignore();
					generateTestData(numRecords);
					break;
				}
			case 0: cout << "Exiting..." << endl; break;
			default: cout << "Invalid choice!" << endl;
		}
	} while (choice != 0);

	return 0;
}
