#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>
void main(){

      int client_sock = socket(AF_INET,SOCK_STREAM,0);
      if (client_sock == -1){
            perror("Socket Creation unsuccessful");
            exit(1);
      }
      char* ip = "127.0.0.1";
      int port = 6969; 
      struct sockaddr_in sa;
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port; 
      sa.sin_addr.s_addr = inet_addr(ip);
      
      int n = connect(client_sock,(struct sockaddr *)&sa,sizeof(sa));
      if (n == -1){
            printf("connection error");
            exit(1);
      }
      char buffer[1024];
      memset(buffer,'\0',sizeof(buffer));
      recv(client_sock,buffer,1024,0);
      printf("%s",buffer);
          


}