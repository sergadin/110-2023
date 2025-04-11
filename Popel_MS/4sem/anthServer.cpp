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

void set_nonblocking(int sock) {
    int flags = fcntl(sock, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl F_GETFL");
        exit(1);
    }
    if (fcntl(sock, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl F_SETFL");
        exit(1);
    }
}

struct ClientState {
    std::string lastQuery;
    std::string lastResult;
    ClientState() : lastQuery(""), lastResult("") {}
};

std::map<int, ClientState> clientStates;
DataBase db(nullptr);

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    fd_set readfds;
    int max_fd;
    char buf[BUFFER_SIZE];
    registerParsers();

    if ((as = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(as, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&on), sizeof(on)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(as, reinterpret_cast<struct sockaddr *>(&server), sizeof(server)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(as, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    set_nonblocking(as);
    max_fd = as;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(as, &readfds);

        int activity = select(max_fd + 1, &readfds, NULL, NULL, NULL);
        if (activity == -1) {
            perror("select");
            exit(1);
        }

        if (FD_ISSET(as, &readfds)) {
            struct sockaddr_in client;
            socklen_t client_len = sizeof(client);
            if ((ms = accept(as, reinterpret_cast<struct sockaddr *>(&client), &client_len)) == -1) {
                perror("accept");
                continue;
            }

            set_nonblocking(ms);

            while (1) {
                bzero(buf, sizeof(buf));
                int bytes_read = recv(ms, buf, sizeof(buf), MSG_WAITALL);
                if (bytes_read == -1) {
                    perror("recv");
                    close(ms);
                    break;
                }

                std::string query(buf);
                if (query == "quit") {
                    close(ms);
                    break;
                } else if (query == "kill") {
                    close(ms);
                    close(as);
                    return 0;
                }

                result res = db.startQuery(ms, query);

                if (res.error.getCode() != 0) {
                    std::string errorMsg = "Error: " + res.error.getMessage();
                    send(ms, errorMsg.c_str(), errorMsg.size(), 0);
                } else {
                    send(ms, res.message.c_str(), res.message.size(), 0);
                }
            }
        }
    }
    close(as);
    return 0;
}
