#include "StudentDatabase.h"
#include <thread>
#include <mutex>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <sstream>
#include <fstream>
#include <regex>

const int PORT = 8081;
const int BUFFER_SIZE = 4096;
const int MAX_CLIENTS = 10;

std::mutex db_mutex;

void handle_client(int client_sock, StudentDatabase& db) {
	char buffer[BUFFER_SIZE];

	while (true) {
		memset(buffer, 0, BUFFER_SIZE);
		int bytes_read = recv(client_sock, buffer, BUFFER_SIZE, 0);

		if (bytes_read <= 0) {
			std::cout << "Client disconnected" << std::endl;
			break;
		}

		std::string request(buffer, bytes_read);
		std::string response;

		try {
			std::lock_guard<std::mutex> lock(db_mutex);

			request = std::regex_replace(request, std::regex("^\\s+|\\s+$"), "");

			if (request == "GET_ALL") {
				response = StudentDatabase::serialize(db.getAllStudents());
			}
			else if (request == "get_all") {
				response = "ERROR: Command must be uppercase (use GET_ALL)";
			}
			else if (request.substr(0, 6) == "SELECT") {
				std::string query = request.substr(6);
				query = std::regex_replace(query, std::regex("^\\s+"), "");
				response = StudentDatabase::serialize(db.select(query));
			}
			else if (request.substr(0, 8) == "RESELECT") {

				std::string query = request.substr(8);
				query = std::regex_replace(query, std::regex("^\\s+"), "");
				response = StudentDatabase::serialize(db.select(query));
			}
			else if (request.substr(0, 3) == "ADD") {
				std::istringstream iss(request.substr(4));
				std::vector<std::string> parts;
				std::string part;

				while (std::getline(iss, part, '|')) {
					parts.push_back(part);
				}

				if (parts.size() == 4) {
					StudentDatabase::Student student(
							parts[0],
							std::stoi(parts[1]),
							std::stod(parts[2]),
							parts[3]
							);

					if (db.addStudent(student)) {
						response = "SUCCESS: Student added";
					}
					else {
						response = "ERROR: Student already exists";
					}
				}
				else {
					response = "ERROR: Invalid ADD format";
				}
			}
			else if (request.substr(0, 6) == "DELETE") {
				std::string nameToDelete = request.substr(7);
				if (db.removeStudent(nameToDelete)) {
					response = "SUCCESS: Student deleted";
				}
				else {
					response = "ERROR: Student not found";
				}
			}
			else {
				response = "ERROR: Unknown command";
			}
		}
		catch (const std::exception& e) {
			response = "ERROR: " + std::string(e.what());
		}

		if (send(client_sock, response.c_str(), response.size(), 0) < 0) {
			std::cerr << "Failed to send response" << std::endl;
		}
	}

	close(client_sock);
}

int main() {
	StudentDatabase db;
	if (!db.loadFromFile("students.csv")) {
		std::cerr << "Warning: Failed to load students.csv, initializing with empty database" << std::endl;

		db.addStudent({"Иван Иванов", 101, 4.5, "Пример данных"});
		db.addStudent({"Мария Петрова", 102, 3.8, "Тестовые данные"});
	}

	int server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (server_sock < 0) {
		std::cerr << "Socket creation failed" << std::endl;
		return 1;
	}

	sockaddr_in server_addr{};
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	int opt = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	if (bind(server_sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		std::cerr << "Bind failed" << std::endl;
		close(server_sock);
		return 1;
	}

	if (listen(server_sock, MAX_CLIENTS) < 0) {
		std::cerr << "Listen failed" << std::endl;
		close(server_sock);
		return 1;
	}

	std::cout << "Server started on port " << PORT << std::endl;

	while (true) {
		sockaddr_in client_addr{};
		socklen_t client_len = sizeof(client_addr);

		int client_sock = accept(server_sock,
				(sockaddr*)&client_addr,
				&client_len);

		if (client_sock < 0) {
			std::cerr << "Accept error" << std::endl;
			continue;
		}

		std::cout << "New connection from "
			<< inet_ntoa(client_addr.sin_addr) << ":"
			<< ntohs(client_addr.sin_port) << std::endl;

		std::thread(handle_client, client_sock, std::ref(db)).detach();
	}

	close(server_sock);
	return 0;
}
