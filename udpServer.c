// Серверная реализация модели клиент-сервер UDP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/in.h>


#define PORT    8080
#define MAXLINE 1024

int main()
{
    int    sockfd;
    char   buffer[MAXLINE];
    char   *hello = "Hello from server";
    struct sockaddr_in servaddr, cliaddr;

    // Создание дескриптора файла сокета
    if( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    // Заполнение информации о сервере
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Привязываем сокет с адресом сервера
    if( bind(sockfd, (const struct sockaddr *) &servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    int len, n;

    len = sizeof(cliaddr); // len is value / resuslt
    n = recvfrom(sockfd, 
                (char*) buffer, 
                MAXLINE, 
                MSG_WAITALL, 
                (struct sockaddr *) &cliaddr, 
                &len
    );

    buffer[n] = '\0';

    printf("Client: %s\n", buffer);

    sendto( sockfd, 
            (const char *) hello, 
            strlen(hello), 
            MSG_CONFIRM, 
            (const struct sockaddr *) &cliaddr, 
            len
    );

    printf("Server: Hello message sent.\n");
    
    return 0;
}
