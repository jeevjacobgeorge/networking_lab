#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(){

      char* ip = "127.0.0.1";
      int port = 6969;
      struct sockaddr_in sa,ca;
      int sockfd = socket(AF_INET,SOCK_DGRAM,0);
      if (sockfd == -1){
            perror("Socket creation error");
            exit(1);
      }
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = bind(sockfd,(struct sockaddr*)&sa,sizeof(sa));
      if (n == 1){
            perror("Binding error");
            exit(1);
      }

      char buffer[1024];
      bzero(&buffer,sizeof(buffer));
      socklen_t size = sizeof(ca);
      recvfrom(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&ca,&size);
      printf("%s",buffer);      
      bzero(&buffer,sizeof(buffer));
      strcpy(buffer,"Happy alle");
      sendto(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&ca,sizeof(ca));

}