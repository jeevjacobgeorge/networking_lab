#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void main(){
      int port = 6969;
      char *ip = "127.0.0.1";
      struct sockaddr_in sa;

      int sockfd = socket(AF_INET,SOCK_DGRAM,0);
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);
      char buffer[1024];
      strcpy(buffer,"Eda mone");
      sendto(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&sa,sizeof(sa));
      bzero(&buffer,sizeof(buffer));
      socklen_t size = sizeof(sa);
      recvfrom(sockfd,&buffer,sizeof(buffer),0,(struct sockaddr*)&sa,&size);
      printf("%s",buffer);
}