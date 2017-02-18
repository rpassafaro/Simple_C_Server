#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

int main()
{
    int sockfd;
    char recvline[100];
    struct sockaddr_in servaddr;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(22000);
    inet_pton(AF_INET,"127.0.0.1",&(servaddr.sin_addr));
    connect(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
    write(sockfd,"ping",5);
    read(sockfd,recvline,100);
    write(1,recvline,11);
}
