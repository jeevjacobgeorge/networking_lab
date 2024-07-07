#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
void check(int n){
      if (n < 0){
            printf("error");
            exit(1);
      }
}

void main(){
      char letter;
      printf("Enter letter for server to count:");
      scanf("%c",&letter);
      int port = 3444;
      char* ip = "127.0.0.1";
      struct sockaddr_in sa;
      int sockfd = socket(AF_INET,SOCK_STREAM,0);
      check(sockfd);
      printf("\nSocket created successfully\n");
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = bind(sockfd,(struct sockaddr *)&sa,sizeof(sa));
      check(n);
      listen(sockfd,3);
      printf("Listening....\n");
      int client_sock = accept(sockfd,0,0);
      check(client_sock);

      char buffer[1024];
      recv(client_sock,buffer,sizeof(buffer),0);
      int count = 0;
      for (int i = 0; buffer[i]; i++){
            if (buffer[i] == letter)
                  count++;
      }
      send(client_sock,&count,sizeof(count),0);
           
      sleep(1);
      close(client_sock);
      close(sockfd);
}