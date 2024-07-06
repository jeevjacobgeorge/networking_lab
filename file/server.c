#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdlib.h>

void main(){
      int port = 6969;
      char* ip = "127.0.0.1";
      struct sockaddr_in sa,ca;
      printf("\nhello");
      int sockfd = socket(AF_INET,SOCK_STREAM,0);
      if (sockfd == -1 ){
            printf("Socket creation failed");
      }
      printf("\nSocket created successfully");
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = bind(sockfd,(struct sockaddr *)&sa,sizeof(sa));
      if (n == -1){
            printf("\nBinding error");
      }
      listen(sockfd,3);
      printf("\nListening....");
      socklen_t size;
      int client_sock = accept(sockfd,(struct sockaddr*)&ca,&size);
      printf("\nConnected");
      char buffer[2048];
      bzero(buffer,sizeof(buffer));
      //recieve file name
      recv(client_sock,buffer,sizeof(buffer),0);
      
      FILE* fd = fopen(buffer,"r");
      if (!fd){
            perror("Error opening file");
            send(client_sock,"File not found\n",15,0);      
            exit(1);     
      }
      while((fgets(buffer,sizeof(buffer),fd))){
            send(client_sock,buffer,sizeof(buffer),0);
            printf("File sending...\n");
      }
      buffer[0] = '\0';
      send(client_sock,buffer,1,0);
      fclose(fd);
      printf("File transfer completed\n");
      

}