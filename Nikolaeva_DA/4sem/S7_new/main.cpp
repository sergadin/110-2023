#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "StudentDatabase.h"

using namespace std;

void demonstrateLocalMode() {
	cout << "=== Local Mode ===" << endl;
	StudentDatabase db;

	if (!db.loadFromFile("students.csv")) {
		cerr << "Failed to load data. Creating new database." << endl;
	}

	
	db.addStudent({"John Doe", 101, 4.5, "Excellent"});
	db.addStudent({"Jane Smith", 102, 3.8, "Good"});

	
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
	cout << "Start client: ./client" << endl;
	cout << "Available client commands:" << endl;
	cout << "  GET_ALL, SELECT [field][op][value], ADD|...format" << endl;
}

void generateTestData() {
	ofstream file("large_dataset.csv");
	if (!file) {
		cerr << "Error creating test file" << endl;
		return;
	}

	for (int i = 0; i < 1000; ++i) {
		file << "Student_" << i << ","
			<< (100 + i % 10) << ","
			<< fixed << setprecision(2) << (3.0 + (i % 40) * 0.05) << ","
			<< "Record_" << i << "\n";
	}
	cout << "Generated 1000 test records in large_dataset.csv" << endl;
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
			case 3: generateTestData(); break;
			case 0: cout << "Exiting..." << endl; break;
			default: cout << "Invalid choice!" << endl;
		}
	} while (choice != 0);

	return 0;
}
