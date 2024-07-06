//go back n sender
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

      int n = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));

      listen(sockfd,5);
      printf("Listening.....\n");
      socklen_t size;
      int cl_sock = accept(sockfd,(struct sockaddr *)&addr,&size);
      printf("Reciever connected\n");
      char buffer[1024];
      int window_size = 3;
      int j = 0;
      int frames[1000] = {0};//0 for NACK 1 for positve ack
      sleep(1);
      while (1){
            packet frame;
            strcpy(frame.type,"FRAME");
            for (int i = 0; i < window_size; i++){
                  frame.seq_no = j+i;
                  send(cl_sock,&frame,sizeof(frame),0);
                  printf("Frame %d sent\n",frame.seq_no);
            }
            for (int i = 0; i < window_size; i++){
                  packet response;
                  recv(cl_sock,&response,sizeof(response),0);
                  if (!strcasecmp(response.type,"ACK")){
                        frames[response.seq_no] = 1;
                        printf("Positive ack recieved for frame %d\n",response.seq_no);
                  }
                  else{
                        printf("---Negative ack recieved for frame %d---\n",response.seq_no);
                  }
            }
            for (int i = 0; i < 3; i++){
                  if (frames[j]==0){ //NACK
                        printf("Going Back to %d\n",j);
                        break; //start transmitting from corrupted frame
                  }
                  else{ //ACK
                        j++;
                  }
            }
            sleep(3);
      }//while
      close(cl_sock);
      close(sockfd);
}