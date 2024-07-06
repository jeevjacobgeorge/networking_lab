#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>

void main(){

      int serv_sock = socket(AF_INET,SOCK_STREAM,0);
      if (serv_sock == -1){
            perror("Socket Creation unsuccessful");
            exit(1);
      }
      char* ip = "127.0.0.1";
      int port = 6969; 
      struct sockaddr_in addr;
      memset(&addr,'\0',sizeof(addr));
      addr.sin_family = AF_INET;
      addr.sin_port = port; 
      addr.sin_addr.s_addr = inet_addr(ip);
      
      int n = bind(serv_sock,(struct sockaddr *)&addr,sizeof(addr));
      if (n == -1){
            perror("Error while binding.\n");
      }
      listen(serv_sock,3);
      socklen_t size;
      int client_sock = accept(serv_sock,(struct sockaddr*)&addr,&size);
      char buffer[1024];
      strcpy(buffer,"Eda mone");
      send(client_sock,buffer,sizeof(buffer),0);
      close(serv_sock);
}