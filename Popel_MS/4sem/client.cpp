#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <typeinfo>
#include "unistd.h"
#include <errno.h>

int main(int argc, char *argv[])
{
    int s;
    struct sockaddr_in server;
    struct hostent *hp;
    char buf[1024];


    if (argc < 4) {
        fprintf(stderr, "Usage: %s <hostname> <port> <message>\n", argv[0]);
        return 1;
    } /* должно быть 3 аргумента: адрес, порт и сообщение */

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 1;
    } /* Создаем сокет для работы по TCP/IP */

    /* Заполняем струтуру с адресом сервера */
    server.sin_family = AF_INET; /* протокол IP */
    hp = gethostbyname(argv[1]); /* Обращаемся к DNS и узнаем адрес по символьному имени*/
    if (hp == NULL) {
        fprintf(stderr, "Unknown host: %s\n", argv[1]);
        return 1;
    }
    bcopy( hp->h_addr, &server.sin_addr, hp->h_length); /* копируем из hp->h_addr в &server.sin_addr hp->h_length байт */
    server.sin_port = htons(atoi(argv[2])); /* номер порта, на котором запущен сервер */



    if (connect(s, reinterpret_cast<struct sockaddr *>(&server), sizeof(server)) == -1) {
        perror("connect");
        return 1;
    }

    int len = strlen(argv[3]);
    if (send(s, &len, sizeof(int), 0) == -1) {
        perror("send");
        close(s);
        return 1;
    }

    if (send(s, argv[3], len, 0) == -1) {
        perror("send");
        close(s);
        return 1;
    }

    bzero(buf, sizeof(buf));
    int bytes_read = recv(s, buf, sizeof(buf), MSG_WAITALL);
    if (bytes_read == -1) {
        perror("recv");
        close(s);
        return 1;
    }

    printf("Server response: %s\n", buf);
    close(s);
    return 0;
}
