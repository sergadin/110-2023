#include "StudentDatabase.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>

const int PORT = 8081;
const char* SERVER_IP = "127.0.0.1";
const int BUFFER_SIZE = 4096;

class Client {
	int sock = -1;

	public:
	bool connect() {
		sock = socket(AF_INET, SOCK_STREAM, 0);
		if (sock < 0) {
			std::cerr << "Socket creation error" << std::endl;
			return false;
		}

		sockaddr_in server_addr{};
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(PORT);

		if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
			std::cerr << "Invalid server address" << std::endl;
			close(sock);
			return false;
		}

		if (::connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) != 0) {
			std::cerr << "Connection failed" << std::endl;
			close(sock);
			return false;
		}
		return true;
	}

	std::string sendRequest(const std::string& request) {
		if (send(sock, request.c_str(), request.size(), 0) < 0) {
			std::cerr << "Send error" << std::endl;
			return "";
		}

		char buffer[BUFFER_SIZE];
		std::string response;
		int bytes_read = recv(sock, buffer, BUFFER_SIZE, 0);
		if (bytes_read > 0) {
			response.assign(buffer, bytes_read);
		}
		return response;
	}

	~Client() { 
		if (sock != -1) {
			close(sock);
		}
	}
};

void printHelp() {
	std::cout << "\nAvailable commands:\n"
		<< "  GET_ALL          - Get all students\n"
		<< "  SELECT [QUERY]   - Filter students (e.g: SELECT rating>4.0;group=101)\n"
		<< "  ADD|name|group|rating|info - Add new student\n"
		<< "  FORMAT [html/text] - Set output format\n"
		<< "  EXIT             - Quit\n\n";
}

void printResults(const std::vector<StudentDatabase::Student>& students, 
		const std::string& format = "html") 
{
	if (format == "html") {
		std::cout << "<table border='1'>\n<tr><th>Name</th><th>Group</th><th>Rating</th><th>Info</th></tr>\n";
		for (const auto& s : students) {
			std::cout << "<tr><td>" << s.name << "</td><td>" << s.group 
				<< "</td><td>" << std::fixed << std::setprecision(2) << s.rating 
				<< "</td><td>" << s.info << "</td></tr>\n";
		}
		std::cout << "</table>\n";
	} else {
		std::cout << "Found " << students.size() << " students:\n";
		for (const auto& s : students) {
			std::cout << s.name << " | Group: " << s.group 
				<< " | Rating: " << std::fixed << std::setprecision(2) << s.rating 
				<< " | Info: " << s.info << "\n";
		}
	}
	std::cout << std::endl;
}

int main() {
	Client client;
	if (!client.connect()) return 1;

	std::string current_format = "html";
	printHelp();

	while (true) {
		std::cout << "[FORMAT: " << current_format << "]> ";
		std::string input;
		std::getline(std::cin, input);

		if (input.empty()) continue;

		if (input.substr(0, 6) == "FORMAT") {
			current_format = (input.find("text") != std::string::npos) ? "text" : "html";
			continue;
		}

		if (input == "EXIT") break;
		if (input == "HELP") {
			printHelp();
			continue;
		}

		std::string response = client.sendRequest(input);
		if (response.empty()) {
			std::cerr << "Empty server response" << std::endl;
			continue;
		}

		try {
			auto students = StudentDatabase::deserialize(response);
			printResults(students, current_format);
		} catch (...) {
			std::cerr << "Invalid data received" << std::endl;
		}
	}

	return 0;
}
