#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

void main(){
      int port = 1234;
      
      char* ip = "127.0.0.1";
      int sockfd = socket(AF_INET,SOCK_STREAM,0);

      struct sockaddr_in sa;
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = connect(sockfd,(struct sockaddr*)&sa,sizeof(sa));
      if (n == -1){
            printf("CONNECTION error\n");
            exit(1);
      }
      time_t t;
      recv(sockfd,&t,sizeof(t),0);
      printf("Time recieved from server is %s",ctime(&t));
      send(sockfd,"Ok",sizeof("OK"),0);
      close(sockfd);
      
}