#include "../include/Library.hpp"

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <thread>
#include <vector>
#include <arpa/inet.h>

namespace Library {

void handleClient(int client_socket, Core& db, const std::string& client_addr) {

    std::cout << "Handling client " << client_addr << " in thread " << std::this_thread::get_id() << std::endl;
    
    while (true) {
        char buffer[2048] = {0};
        ssize_t bytes_read = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
        if (bytes_read < 0) {
            std::cerr << "Failed to read from client " << client_addr << ": " << strerror(errno) << std::endl;
            break;
        }
        if (bytes_read == 0) {
            std::cout << "Client " << client_addr << " disconnected" << std::endl;
            break;
        }
        
        std::string command(buffer, bytes_read);
        std::cout << "Received from " << client_addr << ": " << command << " (thread " << std::this_thread::get_id() << ")" << std::endl;
        
        std::string response;
        try {
            response = db.processCommand(command);
        } catch (const Exception& e) {
            response = "ERROR: Code " + std::to_string(e.getCode()) + ": " + e.getMsg();
        }
        
        std::cout << "Sending to " << client_addr << ": " << response << " (thread " << std::this_thread::get_id() << ")" << std::endl;
        if (send(client_socket, response.c_str(), response.length(), 0) < 0) {
            std::cerr << "Failed to send response to " << client_addr << ": " << strerror(errno) << std::endl;
            break;
        }
        
        if (response == "EXIT") {
            std::cout << "Client " << client_addr << " sent EXIT, closing connection (thread " << std::this_thread::get_id() << ")" << std::endl;
            break;
        }
    }
    
    close(client_socket);
    std::cout << "Client " << client_addr << " disconnected (thread " << std::this_thread::get_id() << ")" << std::endl;
}

void runServer(int port) {
    Core db;
    
    // socket creation
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        throw Exception(15, "Failed to create socket");
    }
    
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        close(server_fd);
        throw Exception(16, "Failed to set socket options");
    }
    
    // adress settings
    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        close(server_fd);
        throw Exception(17, "Failed to bind socket");
    }
    
    if (listen(server_fd, 10) < 0) {
        close(server_fd);
        throw Exception(18, "Failed to listen on socket");
    }
    
    std::cout << "Server started on port " << port << std::endl;
    
    std::vector<std::thread> client_threads;
    
    while (true) {
        sockaddr_in client_addr{};
        socklen_t addrlen = sizeof(client_addr);
        int client_socket = accept(server_fd, (struct sockaddr*)&client_addr, &addrlen);
        if (client_socket < 0) {
            std::cerr << "Failed to accept connection: " << strerror(errno) << std::endl;
            continue;
        }

        // get IP address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
        std::string client_addr_str = std::string(client_ip) + ":" + std::to_string(ntohs(client_addr.sin_port));
        
        std::cout << "New client connected: " << client_addr_str << std::endl;
        
        // new thread
        client_threads.emplace_back(handleClient, client_socket, std::ref(db), client_addr_str);
        client_threads.back().detach();
    }
    
    close(server_fd);
}

} 
