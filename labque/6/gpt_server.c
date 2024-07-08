#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>

#define PORT 8080
#define MAX_EXPRESSION_LENGTH 100
#define BUFFER_SIZE 1024

int evaluate_expression(char *expr) {
    int result = 0;
    int current_value = 0;
    char operator = '+';
    int i = 0;
    int len = strlen(expr);

    while (i < len) {
        if (isdigit(expr[i])) {
            current_value = current_value * 10 + (expr[i] - '0');
        }

        if (!isdigit(expr[i]) && !isspace(expr[i]) || i == len - 1) {
            switch (operator) {
                case '+': result += current_value; break;
                case '-': result -= current_value; break;
                case '*': result *= current_value; break;
                case '/': result /= current_value; break;
            }
            operator = expr[i];
            current_value = 0;
        }
        i++;
    }
    return result;
}

int main() {
      close(PORT);
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server is listening on port %d\n", PORT);

    
      if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
      perror("accept");
      close(server_fd);
      exit(EXIT_FAILURE);
      }

      int valread = read(new_socket, buffer, BUFFER_SIZE);
      if (valread > 0) {
      buffer[valread] = '\0';
      int result = evaluate_expression(buffer);
      sprintf(buffer, "%d\n", result);
      send(new_socket, buffer, strlen(buffer), 0);
      }
      sleep(1);
      close(new_socket);
    
    return 0;
}
