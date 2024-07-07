#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h> // for toupper()
void check(int n){
      if (n < 0){
            printf("error");
            exit(1);
      }
}

void main(){
      int port = 3444;
      char* ip = "127.0.0.1";
      int sockfd = socket(AF_INET,SOCK_STREAM,0); 
      check(sockfd);
      struct sockaddr_in sa;
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);
      int n = connect(sockfd,(struct sockaddr *)&sa,sizeof(sa));
      check(n);
      
      char buffer[1024];
      printf("Enter message to send:");
      fgets(buffer,sizeof(buffer),stdin);
      send(sockfd,buffer,sizeof(buffer),0);
      recv(sockfd,buffer,sizeof(buffer),0);
      printf("%s\n",buffer);
      close(sockfd);


}