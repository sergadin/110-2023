#include "StudentDatabase.h"
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

const int PORT = 8080;
const int BUFFER_SIZE = 4096;
const int MAX_CLIENTS = 10;

// Функция обработки клиентского соединения
void handleClient(int clientSocket, StudentDatabase& db) {
	char buffer[BUFFER_SIZE];

	while (true) {
		memset(buffer, 0, BUFFER_SIZE);
		int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);

		// Проверяем, не отключился ли клиент
		if (bytesRead <= 0) {
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		std::string request(buffer);
		std::string response;

		// Обработка разных типов запросов
		if (request == "GET_ALL") {
			// Получить всех студентов
			response = db.toHTML(db.select(""));
		} 
		else if (request.substr(0, 6) == "SELECT") {
			// Выборка по условию
			std::string query = request.substr(7);
			response = db.toHTML(db.select(query));
		}
		else if (request.substr(0, 3) == "ADD") {
			// Добавление нового студента
			std::istringstream iss(request.substr(4));
			std::string name, groupStr, ratingStr, info;

			if (std::getline(iss, name, '|') &&
					std::getline(iss, groupStr, '|') &&
					std::getline(iss, ratingStr, '|') &&
					std::getline(iss, info)) {

				try {
					StudentDatabase::Student student(
							name, 
							std::stoi(groupStr), 
							std::stod(ratingStr), 
							info
							);

					if (db.addStudent(student)) {
						response = "SUCCESS: Student added";
					} else {
						response = "ERROR: Student already exists";
					}
				} catch (...) {
					response = "ERROR: Invalid data format";
				}
			} else {
				response = "ERROR: Invalid ADD format";
			}
		}
		else {
			response = "ERROR: Unknown command";
		}

		send(clientSocket, response.c_str(), response.size(), 0);
	}

	close(clientSocket);
}

int main() {
	// Инициализация базы данных
	StudentDatabase db;
	if (!db.loadFromFile("students.csv")) {
		std::cerr << "Failed to load database" << std::endl;
		return 1;
	}

	// Создание сокета
	int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serverSocket < 0) {
		std::cerr << "ERROR: Socket creation failed" << std::endl;
		return 1;
	}

	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = INADDR_ANY;

	// Привязка сокета
	if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		std::cerr << "ERROR: Bind failed" << std::endl;
		close(serverSocket);
		return 1;
	}

	// Ожидание подключений
	if (listen(serverSocket, MAX_CLIENTS) < 0) {
		std::cerr << "ERROR: Listen failed" << std::endl;
		close(serverSocket);
		return 1;
	}

	std::cout << "Server started on port " << PORT << std::endl;

	// Основной цикл сервера
	while (true) {
		sockaddr_in clientAddr;
		socklen_t clientLen = sizeof(clientAddr);

		// Принимаем новое подключение
		int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientLen);
		if (clientSocket < 0) {
			std::cerr << "ERROR: Accept failed" << std::endl;
			continue;
		}

		// Запускаем обработчик клиента в отдельном потоке
		std::cout << "New client connected" << std::endl;
		std::thread(handleClient, clientSocket, std::ref(db)).detach();
	}

	close(serverSocket);
	return 0;
}
