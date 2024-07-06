#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

void main(){
      int port = 6969;
      char * ip = "127.0.0.1";
      struct sockaddr_in sa;

      int sockfd = socket(AF_INET,SOCK_STREAM,0);

      // memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = connect(sockfd,(struct sockaddr*)&sa,sizeof(sa));
      if (n == -1){
            perror("connection error");
            exit(1);
      }

      char buffer[1024];
      
      while(1){
            printf("\nType 'exit' to leave\nEnter message:");
            scanf("%s",buffer);
            send(sockfd,buffer,sizeof(buffer),0);
      }

}