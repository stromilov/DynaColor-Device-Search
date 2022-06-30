#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sock, len;
    struct sockaddr_in addr, cliaddr;
    char buf[1024];
    int bytes_read;


    if( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    memset(&addr, 0, sizeof(addr));
    memset(&cliaddr, 0, sizeof(cliaddr));

    addr.sin_family = AF_INET;
    addr.sin_port = htons(6666);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(sock, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        perror("bind");
        exit(2);
    }

    while(1) {

        len = sizeof(cliaddr);
        bytes_read = recvfrom(sock, buf, 1024, 0, (struct sockaddr *)  &cliaddr, &len);
        buf[bytes_read] = '\0';
        printf("%s", buf);

        printf("IP:%s\n", inet_ntoa(cliaddr.sin_addr) );
        printf("port:%x\n", ntohs(cliaddr.sin_port) );
    }

    return 0;
}
