#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc, char const* argv[]){
    int status,valread,client_fd;
    struct sockaddr_in serv_addr;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    //creating socket file descriptor
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    send(client_fd, hello, strlen(hello), 0);
    printf("hello message sent\n");

    valread = recv(client_fd, buffer, 1024, 0);
    printf("%s\n", buffer);

    //closing the socket
    close(client_fd);
    return 0;
}