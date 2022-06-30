#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


char message[] = "Hello there!\n";

int main()
{
    int sock;
    struct sockaddr_in addr;

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    if(sock < 0) {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(6666);
    inet_pton(AF_INET, "192.168.0.212", &addr.sin_addr);

    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
        perror("connect");
        exit(2);
    }

    sendto(sock, message, sizeof(message), 0, (struct sockaddr *) &addr, sizeof(addr));
    
    
    close(sock);

    return 0;
}
