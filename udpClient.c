//Клиентская реализация модели клиент-сервер UDP
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>


#define PORT    6667        //номер порта
#define MAXLINE 1024

int main() {

    int    sockfd;                       //дескриптор сокета
    int    n;                            //
    int    len;                          //
    int    opt = 1;                      //значение флага сокета
    char   buffer[MAXLINE];              //
    char   *hello = "Hello from client"; //
    struct sockaddr_in servaddr;         //структура адреса 


    //Создание дескриптора файла сокета
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    //memset(&servaddr, 0, sizeof(servaddr));

    //Заполнение информации о сервере
    servaddr.sin_family      = AF_INET;
    servaddr.sin_port        = htons(PORT);

    if (0 >= inet_pton(AF_INET, "255.255.255.255", &servaddr.sin_addr) ) {
      perror("Not correct ip adress");
      exit(EXIT_FAILURE);
    }
    
    //Установить широковещательный тип сокета
    setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));

    //Отправка данных в другие подсети того же сегмента сети
    sendto( sockfd, hello, strlen(hello), MSG_CONFIRM, (struct sockaddr *) &servaddr, sizeof(servaddr) );

    //Получить ответ от сервера
    n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *) &servaddr, &len);

    buffer[n] = '\0';

    printf("Server : %s\n", buffer);

    close(sockfd);

    return 0;

}
