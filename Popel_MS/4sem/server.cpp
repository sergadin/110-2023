#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "string.h"
#include <typeinfo>
#include "unistd.h"
#include <fcntl.h>
#include <sys/select.h>
#include <map>
#include "Schedule.h"

#define PORT 1234
#define BACKLOG 5
#define BUFFER_SIZE 1024

static Query* parseSelectingQuery(const std::string& query);
static Query* parseAssigningQuery(const std::string& query);
static Query* parseUpdateQuery(const std::string& query);
static Query* parseInsertQuery(const std::string& query);
static Query* parsePrintQuery(const std::string& query);
static Query* parseDeleteQuery(const std::string& query);

static Query* parseSelectingQuery(const std::string& query) {
    SelectingQuery* q = new SelectingQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseAssigningQuery(const std::string& query) {
    AssigningQuery* q = new AssigningQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseUpdateQuery(const std::string& query) {
    UpdateQuery* q = new UpdateQuery(query);
    try {
        q->UpdateQuery::parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseInsertQuery(const std::string& query) {
    InsertQuery* q = new InsertQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parsePrintQuery(const std::string& query) {
    PrintQuery* q = new PrintQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

static Query* parseDeleteQuery(const std::string& query) {
    DeleteQuery* q = new DeleteQuery(query);
    try {
        q->parse();
        return q;
    } catch (Exception &err) {
        delete q;
        return nullptr;
    }
}

void registerParsers() {
    Query::register_parser(parseSelectingQuery);
    Query::register_parser(parseUpdateQuery);
    Query::register_parser(parseInsertQuery);
    Query::register_parser(parsePrintQuery);
    Query::register_parser(parseDeleteQuery);
    Query::register_parser(parseAssigningQuery);
}

struct ClientState
{
    std::string lastQuery;
    std::string lastResult;
    std::vector<Entry *> previousSelection; // Store previous selection

    ClientState() : lastQuery(""), lastResult(""), previousSelection() {}

    ~ClientState()
    {
        for (Entry *entry : previousSelection)
        {
            delete entry; // Prevent memory leaks
        }
        previousSelection.clear();
    }
};

std::map<int, ClientState> clientStates;
DataBase db(nullptr); // Initialize the database

void registerParsers();          // Forward declaration
void set_nonblocking(int sock); // Forward declaration

void set_nonblocking(int sock)
{
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags == -1)
    {
        perror("fcntl F_GETFL");
        exit(1);
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1)
    {
        perror("fcntl F_SETFL");
        exit(1);
    }
}

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    fd_set readfds;
    int max_fd;

    registerParsers(); // Initialize parsers

    if ((as = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(as, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&on), sizeof(on)) == -1)
    {
        perror("setsockopt");
        exit(1);
    }
    server.sin_family = AF_INET; 
    server.sin_addr.s_addr = INADDR_ANY; 
    server.sin_port = htons(PORT);      
    if (bind(as, reinterpret_cast<struct sockaddr *>(&server), sizeof(server)) == -1)
    {
        perror("bind");
        exit(1);
    }

    if (listen(as, BACKLOG) == -1)
    {
        perror("listen");
        exit(1);
    }

    set_nonblocking(as); // Set non-blocking
    max_fd = as;

    /* цикл обработки клиентов */
    while (1)
    {
        FD_ZERO(&readfds);
        FD_SET(as, &readfds);

        for (const auto &client : clientStates)
        {
            FD_SET(client.first, &readfds);
            if (client.first > max_fd)
            {
                max_fd = client.first;
            }
        }

        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity == -1)
        {
            perror("select");
            exit(1);
        }

        if (FD_ISSET(as, &readfds))
        {
            struct sockaddr_in client;
            socklen_t client_len = sizeof(client);
            if ((ms = accept(as, reinterpret_cast<struct sockaddr *>(&client), &client_len)) == -1)
            {
                perror("accept");
                continue;
            }

            set_nonblocking(ms);
            clientStates[ms] = ClientState();
        }

        for (auto it = clientStates.begin(); it != clientStates.end();)
        {
            int client_fd = it->first;
            if (FD_ISSET(client_fd, &readfds))
            {
                std::cout << "Processing client with fd: " << client_fd << std::endl;
                int len;

                // Try to receive the length
                ssize_t bytes_received = recv(client_fd, &len, sizeof(int), MSG_WAITALL);

                if (bytes_received == -1)
                {
                    if (errno == EAGAIN)
                    {
                        // No data available yet, try again later
                        ++it;
                        continue;
                    }
                    else
                    {
                        perror("recv length");
                        close(client_fd);
                        it = clientStates.erase(it++); // Post-increment to safely erase
                        continue;
                    }
                }
                else if (bytes_received == 0)
                {
                    // Connection closed by client
                    printf("Client closed connection.\n");
                    close(client_fd);
                    it = clientStates.erase(it++); // Post-increment to safely erase
                    continue;
                }

                // Receive the query
                char buf[BUFFER_SIZE];
                bzero(buf, sizeof(buf));

                // Use the length to read the exact number of bytes
                bytes_received = recv(client_fd, buf, std::min(len, static_cast<int>(sizeof(buf)) - 1), 0);

                if (bytes_received == -1)
                {
                    if (errno == EAGAIN)
                    {
                        // No data available yet, try again later
                        ++it;
                        continue;
                    }
                    else
                    {
                        perror("recv data");
                        close(client_fd);
                        it = clientStates.erase(it++); // Post-increment to safely erase
                        continue;
                    }
                }
                else if (bytes_received == 0)
                {
                    // Connection closed by client
                    printf("Client closed connection.\n");
                    close(client_fd);
                    it = clientStates.erase(it++); // Post-increment to safely erase
                    continue;
                }

                buf[bytes_received] = '\0'; // Null-terminate the buffer
                std::string query(buf);
                std::cout << "Query: " << buf << std::endl;

                // Check for quit command
                if (query == "quit")
                {
                    printf("Client requested quit.\n");
                    close(client_fd);
                    it = clientStates.erase(it++); // Post-increment to safely erase
                    continue;
                }

                result res = db.startQuery(client_fd, query);

                if (res.error.getCode() != 0)
                {
                    std::string errorMsg = "Error: " + res.error.getMessage();
                    int error_len = errorMsg.length();
                    send(client_fd, &error_len, sizeof(int), 0);
                    send(client_fd, errorMsg.c_str(), error_len, 0);
                }
                else
                {
                    int message_len = res.message.length();
                    send(client_fd, &message_len, sizeof(int), 0);
                    send(client_fd, res.message.c_str(), message_len, 0);
                }

                ++it;
            }
            else
            {
                ++it;
            }
        }
    }
    close(as); /* закрываем порт 1234; клиенты больше не могут подключаться */
    return 0;
}
