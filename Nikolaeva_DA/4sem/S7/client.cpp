#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

const int PORT = 8080;
const char* SERVER_IP = "127.0.0.1";
const int BUFFER_SIZE = 4096;

// Функция отправки запроса на сервер
void sendRequest(const std::string& request) {
	// Создание сокета
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		std::cerr << "ERROR: Socket creation failed" << std::endl;
		return;
	}

	// Настройка адреса сервера
	sockaddr_in serverAddr;
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);

	// Преобразование IP-адреса
	if (inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr) <= 0) {
		std::cerr << "ERROR: Invalid address" << std::endl;
		close(sock);
		return;
	}

	// Подключение к серверу
	if (connect(sock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
		std::cerr << "ERROR: Connection failed" << std::endl;
		close(sock);
		return;
	}

	// Отправка запроса
	send(sock, request.c_str(), request.size(), 0);

	// Получение ответа
	char buffer[BUFFER_SIZE];
	int bytesRead = recv(sock, buffer, BUFFER_SIZE, 0);
	if (bytesRead > 0) {
		std::cout << "Server response:\n" << std::string(buffer, bytesRead) << std::endl;
	} else {
		std::cerr << "ERROR: No response from server" << std::endl;
	}

	close(sock);
}

int main() {
	std::cout << "Student Database Client\n";
	std::cout << "Available commands:\n"
		<< "  GET_ALL - Get all students\n"
		<< "  SELECT [query] - Run query (e.g. SELECT rating>4.0)\n"
		<< "  ADD|name|group|rating|info - Add new student\n"
		<< "  EXIT - Quit program\n";

	while (true) {
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);

		if (input.empty()) continue;

		if (input == "EXIT") {
			std::cout << "Goodbye!" << std::endl;
			break;
		}

		sendRequest(input);
	}

	return 0;
}
