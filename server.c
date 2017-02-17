#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <arpa/inet.h>
#include <errno.h>

#define MY_PORT 9999
#define MAXBUF  1024

void serverloop(int sockfd)
{
    int addrlen;
    int clientfd;
    struct sockaddr_in client_addr;
    char buffer[MAXBUF];

    addrlen = sizeof(client_addr);

    clientfd = accept(sockfd, (struct sockaddr*)&client_addr, &addrlen);
    printf("%s:%d connected\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    send(clientfd, buffer, recv(clientfd, buffer,MAXBUF, 0), 0);

    close(clientfd);

}

int main(int argc, char const *argv[])
{
    int sockfd;
    struct sockaddr_in self;
    char buffer[MAXBUF];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    self.sin_family = AF_INET;
    self.sin_port = htons(MY_PORT);
    self.sin_addr.s_addr = INADDR_ANY;
    bind(sockfd, (struct sockaddr*)&self, sizeof(self) != 0);
    listen(sockfd, 20);

    while(1)
    {
        serverloop(sockfd);
    }
    close(sockfd);
    return 0;
}
