//stop_wait reciever
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
      char buffer[1024];
      int n = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
      if (n == -1){
            printf("connection error");
            exit(1);
      }
      int i =0;
      while(i < 10){
            packet p1;
            recv(sockfd,&p1,sizeof(p1),0);
            printf("Frame %d recieved\n",i);
            packet response;
            response.seq_no = p1.seq_no;
            if (rand()%2){//positive ack
                  strcpy(response.type,"ACK");
                  printf("ACK is being sent\n");
                  i++;
            }
            else{//negative ack
                  strcpy(response.type,"NACK");
                  printf("NACK is being sent\n");
            }
            send(sockfd,&response,sizeof(response),0);
      }
   


}