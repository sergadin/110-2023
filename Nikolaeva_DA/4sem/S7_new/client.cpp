#include "StudentDatabase.h"
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sstream>
#include <fstream>

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
		<< "  RESELECT [QUERY] - Refine previous selection\n"
		<< "  ADD|name|group|rating|info - Add new student\n"
		<< "  DELETE [NAME]    - Delete a student by name\n"
		<< "  FORMAT [html/text] [filename] - Set output format and optional filename\n"
		<< "  EXIT             - Quit\n\n";
}

void printResults(const std::vector<StudentDatabase::Student>& students,
		const std::string& format = "html",
		const std::string& filename = "")
{
	std::stringstream output;

	if(students.empty()){
		std::cout << "No results found." << std::endl;
		return;
	}

	if (format == "html") {
		output << "<table border='1'>\n<tr><th>Name</th><th>Group</th><th>Rating</th><th>Info</th></tr>\n";
		for (const auto& s : students) {
			output << "<tr><td>" << s.name << "</td><td>" << s.group
				<< "</td><td>" << std::fixed << std::setprecision(2) << s.rating
				<< "</td><td>" << s.info << "</td></tr>\n";
		}
		output << "</table>\n";
	}
	else {
		output << "Found " << students.size() << " students:\n";
		for (const auto& s : students) {
			output << s.name << " | Group: " << s.group
				<< " | Rating: " << std::fixed << std::setprecision(2) << s.rating
				<< " | Info: " << s.info << "\n";
		}
	}
	output << std::endl;

	if (!filename.empty()) {
		std::ofstream file(filename);
		if (file.is_open()) {
			file << output.str();
			file.close();
			std::cout << "Results saved to " << filename << std::endl;
		}
		else {
			std::cerr << "Error opening file " << filename << " for writing." << std::endl;
		}
	}
	else {
		std::cout << output.str();
	}
}

int main(int argc, char* argv[]) {
	std::vector<StudentDatabase::Student> previousResults; 
	Client client;
	if (!client.connect()) return 1;

	std::string current_format = "html";
	printHelp();

	std::string scenarioFile;
	if (argc > 1) {
		scenarioFile = argv[1];
		std::cout << "Running scenario from file: " << scenarioFile << std::endl;
	}

	std::istream* inputSource = &std::cin;
	std::ifstream scenarioStream;
	if (!scenarioFile.empty()) {
		scenarioStream.open(scenarioFile);
		if (scenarioStream.is_open()) {
			inputSource = &scenarioStream;
		}
		else {
			std::cerr << "Could not open scenario file: " << scenarioFile << std::endl;
			return 1;
		}
	}

	while (true) {
		std::cout << "[FORMAT: " << current_format << "]> ";
		std::string input;
		std::getline(*inputSource, input);

		if (inputSource == &scenarioStream && scenarioStream.eof()) {
			std::cout << "Scenario complete." << std::endl;
			break;
		}

		if (input.empty()) continue;

		if (input.substr(0, 6) == "FORMAT") {
			std::istringstream iss(input.substr(7));
			std::string format, filename;
			iss >> format >> filename;
			if (format == "text" || format == "html") {
				current_format = format;
			}
			else {
				std::cerr << "Invalid format. Use 'text' or 'html'." << std::endl;
			}
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
			if (response.substr(0, 5) == "ERROR") {
				std::cerr << response << std::endl;
			}
			else if (input.substr(0, 6) == "DELETE" || input.substr(0, 3) == "ADD"){
				std::cout << response << std::endl;
			} else {
				auto students = StudentDatabase::deserialize(response);
				if (input == "GET_ALL") {
					printResults(students, current_format);
				}
				else if (input.substr(0, 6) == "SELECT" || input.substr(0, 8) == "RESELECT") {
					std::string query = input.substr(input.find(' ') + 1);
					printResults(students, current_format);
				}
			}
		} catch (...) {
			std::cerr << "Invalid data received" << std::endl;
		}
	}

	return 0;
}
