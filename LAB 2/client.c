#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

int main(int argc, char const* argv[]) {
    int status, valread, client_fd;
    char num_str[20];
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    // Create socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);

    printf("Connecting to server ......\n");

    status = connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // Read number as string
    printf("Enter a number: ");
    scanf("%19s", num_str);

    // Send string to server
    send(client_fd, num_str, strlen(num_str), 0);
    printf("Number sent\n");

    valread = recv(client_fd, buffer, 1024, 0);
    printf("%s\n", buffer);

    close(client_fd);
    return 0;
}