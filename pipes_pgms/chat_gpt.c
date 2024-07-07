#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <string.h>

// Function to format the date and time
void get_formatted_datetime(char *buffer, size_t buffer_size) {
    time_t raw_time;
    struct tm *time_info;

    // Get the current time
    time(&raw_time);
    // Convert the time to local time
    time_info = localtime(&raw_time);

    // Format the time as required
    strftime(buffer, buffer_size, "%A %d-%B-%Y %I.%M %p", time_info);
}

int main() {
    int pipefd[2];
    pid_t cpid;
    char buffer[100];
    
    // Create a pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // Fork a child process
    cpid = fork();      
    
    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (cpid == 0) { // Child process
        close(pipefd[1]); // Close the write end of the pipe

        printf("Child PID is %d\n", getpid());
        printf("Parent PID is %d\n", getppid());
        printf("Child sending request for date and time\n");

        // Read the formatted date and time from the pipe
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]); // Close the read end of the pipe

        // Print the received date and time
        printf("Server print '%s'\n", buffer);
    } else { // Parent process
        close(pipefd[0]); // Close the read end of the pipe

        printf("Parent PID is %d\n", getpid());
        printf("Child PID is %d\n", cpid);

        // Get the formatted date and time
        get_formatted_datetime(buffer, sizeof(buffer));

        // Write the formatted date and time to the pipe
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]); // Close the write end of the pipe

        // Wait for the child process to finish
        wait(NULL);
    }

    return 0;
}
