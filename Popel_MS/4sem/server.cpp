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
#include "Schedule.h"

#define PORT 1234
#define BACKLOG 5
#define BUFFER_SIZE 1024

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

int main(int argc, char *argv[])
{
    int as, ms;
    struct sockaddr_in server;
    fd_set readfds;
    int max_fd;
    char buf[BUFFER_SIZE];
    DataBase db(nullptr); /* буфер для приема сообщений от клиентов */

    
    if ((as = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    int on = 1;
    if (setsockopt(as, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<char *>(&on), sizeof(on)) == -1) {
        perror("setsockopt");
        exit(1);
    }
    /* Заполняем структуру адреса, на котором будет работать сервер */
    server.sin_family = AF_INET; /* IP */
    server.sin_addr.s_addr = INADDR_ANY; /* любой сетевой интерфейс */
    server.sin_port = htons(1234); /* порт */

    /* сопоставляем адрес с сокетом */
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

    /* цикл обработки клиентов */
    while( 1 ) {
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

            bzero(buf, sizeof(buf));
            int bytes_read = recv(ms, buf, sizeof(buf), MSG_WAITALL);
            if (bytes_read == -1) {
                perror("recv");
                close(ms);
                continue;
            }

            std::string query(buf);
            result res = db.startQuery(ms, query);

            if (res.error.getCode() != 0) {
                std::string errorMsg = "Error: " + res.error.getMessage();
                send(ms, errorMsg.c_str(), errorMsg.size(), 0);
            } else {
                send(ms, res.message.c_str(), res.message.size(), 0);
            }

            close(ms);
        }
    
    }
    close( as ); /* закрываем порт 1234; клиенты больше не могут подключаться */
    return 0;
}
