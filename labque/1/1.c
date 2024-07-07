//answer of 1st question in labque.word
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void get_formatted_datetime(char*buffer,int size){
      time_t raw_time;
      time(&raw_time);

      struct tm* timeptr;
      timeptr = localtime(&raw_time);

      strftime(buffer,size,"Day:%A Date:%d-%m-%Y Time:%I:%M",timeptr);

}
int main(){
      char buffer[1000];
      

      int pipefd[2];    
      int n = pipe(pipefd);
      if (n==-1){
            perror("Pipe error\n");
            exit(1);
      }

      pid_t f = fork();
      if (f==-1){
            perror("Fork error");
            exit(1);
      }

      if (f){ //Parent procees 😐
            close(pipefd[0]); //close the read end 
            get_formatted_datetime(buffer,sizeof(buffer));
            printf("Parent's time is %s\n",buffer);
            printf("I am the parent my id is %d\n",getpid());
            printf("Parent's Child id is %d\n",f);
            write(pipefd[1],buffer,sizeof(buffer));
            close(pipefd[1]);
            wait(NULL);
      }
      else{ //I am the child 😌
            close(pipefd[1]); //close the write end of pipe 
            printf("--I am the child with id %d\n",getpid());
            printf("--My parent is %d\n--Ok let me read the time sent from parent...😌\n",getppid());
            read(pipefd[0],buffer,sizeof(buffer));
            close(pipefd[0]); // Close the read end of the pipe
            printf("--Server print '%s'\n", buffer);
      }
      return 0;
}