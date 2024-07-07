#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <ctype.h>// for toupper()

void main(){
      int port = 6969;
      char* ip = "127.0.0.1";
      struct sockaddr_in sa,ca;

      int sockfd = socket(AF_INET,SOCK_STREAM,0);
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = connect(sockfd,(struct sockaddr *)&sa,sizeof(sa));
      printf("Server Connected");
      char file_name[1024];
      strcpy(file_name,"hello.txt");
      send(sockfd,file_name,sizeof(file_name),0);
      char buffer[2048];
      do{
            recv(sockfd,buffer,sizeof(buffer),0);
            for (int i = 0; buffer[i]; i++) {
                  buffer[i] = toupper(buffer[i]);
            }
            printf("\n%s",buffer);
      }while(buffer[0]);
      printf("File transfer complete");

}