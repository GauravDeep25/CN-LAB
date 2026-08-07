#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc,char const* argv[]){
    int listening_socket, connected_socket;
    ssize_t valread;
    struct sockaddr_in address, cli_address;
    int opt = 1;
    socklen_t addrlen = sizeof(cli_address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";

    //creating socket file descriptor
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    //forcefully attaching socket to the port 8080
    bind(listening_socket, (struct sockaddr*)&address, sizeof(address));
    listen(listening_socket, 3);
    connected_socket = accept(listening_socket, (struct sockaddr*)&cli_address, &addrlen);
    recv(connected_socket, buffer, 1024, 0);
    printf("%s\n", buffer);
    send(connected_socket, hello, strlen(hello), 0);
    printf("message sent\n");

    //closing the connected socket
    close(connected_socket);

    //closing the listening socket
    close(listening_socket);

    return 0;
}