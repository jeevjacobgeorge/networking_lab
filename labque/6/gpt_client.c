#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAX_EXPRESSION_LENGTH 100
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char expression[MAX_EXPRESSION_LENGTH];
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        return -1;
    }


      printf("Enter an arithmetic expression (or -1 to exit): ");
      fgets(expression, MAX_EXPRESSION_LENGTH, stdin);
      expression[strcspn(expression, "\n")] = 0; // Remove newline character


      send(sock, expression, strlen(expression), 0);
      int valread = read(sock, buffer, BUFFER_SIZE);
      if (valread > 0) {
      buffer[valread] = '\0';
      printf("Result: %s\n", buffer);
      }


    close(sock);
    return 0;
}
