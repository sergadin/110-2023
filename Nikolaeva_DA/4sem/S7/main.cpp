#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
#include "StudentDatabase.h"

using namespace std;

void demonstrateLocalMode() {
	cout << "=== Локальный режим работы ===" << endl;
	StudentDatabase db;

	//  Загрузка данных из файла
	if (!db.loadFromFile("students.csv")) {
		cerr << "Не удалось загрузить данные. Создаем новую БД." << endl;
	}

	// Добавление студентов
	db.addStudent({"Иван Петров", 101, 4.5, "Отличник"});
	db.addStudent({"Мария Сидорова", 102, 3.8, "Хорошистка"});

	// Вывод всех студентов
	cout << "\nВсе студенты:" << endl;
	db.printAllStudents();

	// Выборка данных
	cout << "\nСтуденты с рейтингом > 4.0:" << endl;
	auto topStudents = db.select("rating>4.0");
	cout << db.toHTML(topStudents) << endl;  

	// Сохранение в файл
	if (db.saveToFile("students_updated.csv")) {
		cout << "Данные сохранены в файл." << endl;
	}
}

void demonstrateServerMode() {
	cout << "\n=== Серверный режим ===" << endl;
	cout << "Для запуска сервера используйте: ./server" << endl;
	cout << "Для запуска клиента используйте: ./client" << endl;
}

void generateTestData() {
	ofstream file("large_dataset.csv");
	if (!file.is_open()) { 
		cerr << "Ошибка создания файла" << endl;
		return;
	}

	for (int i = 0; i < 1000; ++i) {  
		file << "Студент_" << i << "," 
			<< (100 + i % 10) << ","
			<< fixed << setprecision(2) << (3.0 + (i % 40) * 0.05) << ","
			<< "Запись №" << i << "\n";
	}
	cout << "Сгенерировано тестовых записей в large_dataset.csv" << endl;
}

int main() {
	int choice;
	do {
		cout << "\n=== Главное меню ===" << endl;
		cout << "1. Локальный режим" << endl;
		cout << "2. О серверном режиме" << endl;
		cout << "3. Генерация тестовых данных" << endl;
		cout << "0. Выход" << endl;
		cout << "Выберите действие: ";
		cin >> choice;
		cin.ignore();

		switch (choice) {
			case 1: demonstrateLocalMode(); break;
			case 2: demonstrateServerMode(); break;
			case 3: generateTestData(); break;
			case 0: cout << "Выход..." << endl; break;
			default: cout << "Неверный выбор!" << endl;
		}
	} while (choice != 0);

	return 0;
}
