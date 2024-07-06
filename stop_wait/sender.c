//stop_wait sender
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
typedef struct packet{
      int seq_no;
      char type[6];
}packet;

void main(){
      int port = 6969;
      char* ip = "127.0.0.1";
      int sockfd = socket(AF_INET,SOCK_STREAM,0);
      struct sockaddr_in addr;
      memset(&addr,'\0',sizeof(addr));
      addr.sin_family = AF_INET;
      addr.sin_port = port;
      addr.sin_addr.s_addr = inet_addr(ip);

      int n = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

      listen(sockfd,5);
      printf("Listening.....\n");
      socklen_t size;
      int cl_sock = accept(sockfd,(struct sockaddr *)&addr,&size);
      printf("\nReciever connected");

      //action begins here
      int i = 0;
      while(i < 10){
        packet p1;
        p1.seq_no = i;
        strcpy(p1.type,"FRAME");
        printf("Frame %d sent\n",i);
        send(cl_sock,&p1,sizeof(p1),0);
        packet response;
        recv(cl_sock,&response,sizeof(response),0);
        if (!strcmp(response.type,"ACK")){
          printf("ACK Recived\n");
          i++;
        }
        else{
          printf("NACK Recieved\n");
        }
        sleep(2);
      }
}