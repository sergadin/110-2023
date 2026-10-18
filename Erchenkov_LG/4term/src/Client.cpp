#include "../include/Library.hpp"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

namespace Library {

void runClient(const std::string& host, int port) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        throw Exception(18, "Failed to create socket");
    }
    
    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (inet_pton(AF_INET, host.c_str(), &server.sin_addr) <= 0) {
        close(sock);
        throw Exception(19, "Invalid address");
    }
    
    if (connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0) {
        close(sock);
        throw Exception(20, "Connection failed");
    }
    
    std::cout << "Connected to server " << host << ":" << port << std::endl;
    
    while (true) {
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);
        if (command.empty()) {
            continue;
        }
        
        if (command == "exit") {
            command = "EXIT";
        }
        
        std::cout << "Sending command: " << command << std::endl;
        if (send(sock, command.c_str(), command.length(), 0) < 0) {
            std::cerr << "Failed to send command: " << strerror(errno) << std::endl;
            break;
        }
        
        char buffer[2048] = {0};
        ssize_t valread = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (valread < 0) {
            std::cerr << "Failed to read response: " << strerror(errno) << std::endl;
            break;
        }
        if (valread == 0) {
            std::cerr << "Server closed connection" << std::endl;
            break;
        }
        
        std::string response(buffer, valread);
        std::cout << "Server response:\n" << response << std::endl;
        
        if (response == "EXIT") {
            std::cout << "Received EXIT, closing connection" << std::endl;
            break;
        }
    }
    
    close(sock);
    std::cout << "Client disconnected" << std::endl;
}

}
