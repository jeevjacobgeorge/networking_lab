//go back N reciever
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
      close(6969);
      int port = 6969;
      char* ip = "127.0.0.1";
      int sockfd = socket(AF_INET,SOCK_STREAM,0);
      struct sockaddr_in addr;
      memset(&addr,'\0',sizeof(addr));
      addr.sin_family = AF_INET;
      addr.sin_port = port;
      addr.sin_addr.s_addr = inet_addr(ip);
      char buffer[1024];
      bzero(buffer,sizeof(buffer));
      int n = connect(sockfd,(struct sockaddr*)&addr,sizeof(addr));
      if (n == -1){
            printf("connection error");
            exit(1);
      }
      int window_size = 3;
      int seq_numbers [window_size];
      while (1){
            packet frame;
            for (int i = 0; i < window_size; i++){
                  recv(sockfd,&frame,sizeof(frame),0);
                  //printf("%s %d recieved\n",frame.type,frame.seq_no);
                  seq_numbers[i] = frame.seq_no;
                  
            }

            for (int i = 0; i < window_size; i++){
                  sleep(1);
                  packet response;
                  if (rand()%3){
                        strcpy(response.type,"ACK");
                        printf("Sending Postive ACK for frame %d\n", seq_numbers[i]);
                  }
                  else{
                        strcpy(response.type,"NACK");
                        printf("---Sending Negative ACK for frame %d ----\n", seq_numbers[i]);
                  }
                  response.seq_no = seq_numbers[i];
                  send(sockfd,&response,sizeof(response),0);
            }
      }//while
    close(sockfd);
}