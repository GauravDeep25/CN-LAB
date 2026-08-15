#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>

#define PORT 8080

int palin(int num) {
    int original = num;
    int reverse = 0;
    int remainder;

    while (num != 0) {
        remainder = num % 10;
        reverse = reverse * 10 + remainder;
        num /= 10;
    }

    return original == reverse;
}

int main(int argc, char const* argv[]) {
    int listening_socket, connected_socket;
    ssize_t valread;
    struct sockaddr_in address, cli_address;
    socklen_t addrlen = sizeof(cli_address);
    char buffer[1024] = {0};

    // Create socket
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    printf("Connecting to client ......\n");

    bind(listening_socket, (struct sockaddr*)&address, sizeof(address));
    listen(listening_socket, 3);

    connected_socket = accept(
        listening_socket,
        (struct sockaddr*)&cli_address,
        &addrlen
    );

    // Receive number as string
    valread = recv(connected_socket, buffer, 1023, 0);
    buffer[valread] = '\0';

    printf("Received: %s\n", buffer);

    // Convert string to integer
    int num = atoi(buffer);

    // Check palindrome
    if (palin(num))
        printf("%d is a palindrome\n", num);
    else
        printf("%d is not a palindrome\n", num);

    close(connected_socket);
    close(listening_socket);

    return 0;
}