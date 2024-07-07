#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
void main(){
      int port = 1234;
      char* ip = "127.0.0.1";
      int listenfd = socket(AF_INET,SOCK_STREAM,0);
            
      struct sockaddr_in sa;
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = bind(listenfd,(struct sockaddr*)&sa,sizeof(sa));
      if (n == -1 ){
            printf("Error in Binding..\n");
            close(listenfd);
            exit(1);
      }
      listen(listenfd,5);
      int connfd = accept(listenfd,0,0);

      time_t t = time(NULL);

      send(connfd,&t,sizeof(t),0);
      // sleep(1);
      char buffer[10];
      recv(connfd,&buffer,sizeof(buffer),0);
      printf("%s\n",buffer);
      sleep(1);
      close(connfd);
      close(listenfd);
}