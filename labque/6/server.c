#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
void check(int n){
      if (n==-1){
            printf("Error\n");
            exit(1);
      }
}
int evaluate(char* buffer){
      int result = 0;
      char operator = '+';
      int curr = 0;
      int l = strlen(buffer);
      for (int i = 0; i < l;i++){
            if(isdigit(buffer[i])){
                  curr = curr * 10 + (buffer[i] - '0');
            }
            if (!isdigit(buffer[i]) && !isspace(buffer[i]) || i == l-1){
                  switch (operator) {
                        case '+': result += curr; break;
                        case '-': result -= curr; break;
                        case '*': result *= curr; break;
                        case '/': result /= curr; break;
                  }
                  operator = buffer[i];
                  curr = 0;
            }
      }
      return result;
}

void main(){
      int port = 6969;
      char*ip = "127.0.0.1";
      int listenfd = socket(AF_INET,SOCK_STREAM,0); check(listenfd);
      
      struct sockaddr_in sa;
      memset(&sa,'\0',sizeof(sa));
      sa.sin_family = AF_INET;
      sa.sin_port = port;
      sa.sin_addr.s_addr = inet_addr(ip);
      int n = bind(listenfd,(struct sockaddr*)&sa,sizeof(sa)); check(n);

      listen(listenfd,5);
      printf("Listening...\n");

      int cl_sock = accept(listenfd,0,0);
      char buffer[100];
      recv(cl_sock,buffer,100,0);
      int result = evaluate(buffer);
      send(cl_sock,&result,sizeof(result),0);
      while(strcmp(buffer,"-1")){
            recv(cl_sock,buffer,100,0);
            int result = evaluate(buffer);
            send(cl_sock,&result,sizeof(result),0);
      }
     
      sleep(1);
      close(cl_sock);
      close(listenfd);



}