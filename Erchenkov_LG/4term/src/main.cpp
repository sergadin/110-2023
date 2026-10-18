#include "../include/Library.hpp"
#include <iostream>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [server|client] [options]" << std::endl;
        return 1;
    }
    
    try {
        if (std::string(argv[1]) == "server") {
            int port = (argc > 2) ? std::stoi(argv[2]) : 8080;
            Library::runServer(port);
        }
        else if (std::string(argv[1]) == "client") {
            std::string host = (argc > 2) ? argv[2] : "127.0.0.1";
            int port = (argc > 3) ? std::stoi(argv[3]) : 8080;
            Library::runClient(host, port);
        }
        else {
            std::cerr << "Invalid mode. Use 'server' or 'client'" << std::endl;
            return 1;
        }
    } catch (const Library::Exception& e) {
        std::cerr << "Error: Code " << e.getCode() << ": " << e.getMsg() << std::endl;
        return 1;
    }
    
    return 0;
}
