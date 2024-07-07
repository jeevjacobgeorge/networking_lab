#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(){

      int port = 6969;
      char*ip = "127.0.0.1";
      struct sockaddr_in sa;

      int sockfd = socket(AF_INET,SOCK_STREAM,0);
      if (sockfd == -1){
            printf("socket creation error");
            exit(1);
      }

      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);
      int n = bind(sockfd,(struct sockaddr*)&sa,sizeof(sa));
      if (n == -1){
            printf("Binding error");
            exit(1);
      }

      listen(sockfd,5);
      printf("\nListening...\n");

      while(1){
            socklen_t size;
            struct sockaddr_in ca; //not used for function sake 
            int cl_sockfd = accept(sockfd,(struct sockaddr*)&ca,&size);
            if (cl_sockfd == -1){
                  printf("accept error");
                  close(sockfd);
                  exit(1);
            }
            int f = fork();
            if (f == 0){ //child
                  close(sockfd);
                  while(1){
                        char buffer[1024];
                        int bytes_recieved = recv(cl_sockfd,buffer,sizeof(buffer),0);
                        if (bytes_recieved <= 0){
                              close(cl_sockfd);
                              break;
                        }
                        if (strcasecmp(buffer,"stop") == 0){
                              printf("\nclient dead");
                              break;
                        }
                        else{
                             printf("Message revieved:%s\n",buffer);
                        }
                       
                  }
                  printf("\nclient disconnected");
                  exit(0);
            }
            else
            { //parent 
                  close(cl_sockfd)
            }
           ; 
      }
} 