#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

void check(int n){
      if (n==-1){
            printf("Error\n");
            exit(1);
      }
}
void main(){
      int port = 6969;
      char*ip = "127.0.0.1";
      int sockfd = socket(AF_INET,SOCK_STREAM,0); check(sockfd);
      
      struct sockaddr_in sa;
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);

      int n = connect(sockfd,(struct sockaddr*)&sa,sizeof(sa));
      check(n);

      char buffer[100];
      while(strcmp(buffer,"-1")){ //when user enters -1 breaks
            bzero(buffer,100);
            printf("Enter expression:");
            fgets(buffer,100,stdin);
            char *newline = strchr(buffer,'\n');
            if (newline)
                  *newline = '\0';
            send(sockfd,buffer,100,0);
            int result;
            recv(sockfd,&result,sizeof(result),0);
            printf("The answer is %d\n",result);

      }
      close(sockfd);
     

}