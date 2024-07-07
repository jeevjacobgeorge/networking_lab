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
      
      char name[20];
      printf("Enter file name:");
      scanf("%s",name);
      send(sockfd,name,sizeof(name),0);


      char buffer[1024];
      printf("------------%s-------------\n",name);
      do {
            bzero(buffer,sizeof(buffer));
            recv(sockfd,buffer,sizeof(buffer),0);
            printf("%s\n",buffer);
      }while(buffer[0]);
            size_t size;
      recv(sockfd,&size,sizeof(size),0);
      printf("------------%s-------------\n",name);
      printf("File Size is %ld\n",size);
      close(sockfd);


}