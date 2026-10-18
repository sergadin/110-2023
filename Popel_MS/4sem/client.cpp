#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int s;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[BUFFER_SIZE];

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <hostname> <port>\n", argv[0]);
        return 1;
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    }

    server.sin_family = AF_INET;
    hp = gethostbyname(argv[1]);
    if (hp == NULL) {
        fprintf(stderr, "Unknown host: %s\n", argv[1]);
        return 1;
    }
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons(atoi(argv[2]));

        if (connect(s, reinterpret_cast<struct sockaddr *>(&server), sizeof(server)) == -1) {
        perror("connect");
        return 1;
    }

    while (true) {
        std::cout << "Enter query (or 'quit' to exit or 'kill' to kill the program): ";
        std::string query;
        std::getline(std::cin, query);

        int len = query.length();
        if (send(s, &len, sizeof(int), 0) == -1) {
            perror("send length");
            break;
        }
        if (send(s, query.c_str(), len, 0) == -1) {
            perror("send data");
            break;
        }

        memset(buf, 0, sizeof(buf));
        int bytes_read = recv(s, &len, sizeof(int), 0);
        if (bytes_read == -1) {
            perror("recv length");
            break;
        } else if (bytes_read == 0) {
            printf("Server closed connection.\n");
            break;
        }

        bytes_read = recv(s, buf, std::min(len, static_cast<int>(sizeof(buf)) - 1), 0);
        if (bytes_read == -1) {
            perror("recv data");
            break;
        } else if (bytes_read == 0) {
            printf("Server closed connection.\n");
            break;
        }

        buf[bytes_read] = '\0';
        printf("Server response: %s\n", buf);

        int entry_count;
        bytes_read = recv(s, &entry_count, sizeof(int), 0);
        if (bytes_read == -1) {
            perror("recv entry count");
            break;
        } else if (bytes_read == 0) {
            printf("Server closed connection.\n");
            break;
        }

        for (int i = 0; i < entry_count; ++i) {
            int entry_len;
            bytes_read = recv(s, &entry_len, sizeof(int), 0);
            if (bytes_read == -1) {
                perror("recv entry length");
                break;
            } else if (bytes_read == 0) {
                printf("Server closed connection.\n");
                break;
            }

            memset(buf, 0, sizeof(buf));
            bytes_read = recv(s, buf, std::min(entry_len, static_cast<int>(sizeof(buf)) - 1), 0);
            if (bytes_read == -1) {
                perror("recv entry data");
                break;
            } else if (bytes_read == 0) {
                printf("Server closed connection.\n");
                break;
            }

            buf[bytes_read] = '\0';
            printf("Entry: %s\n", buf);
        }
    }

    close(s);
    return 0;
}
