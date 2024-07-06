//selective repeat sender
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define Max_Frames 10000
typedef struct packet{
      int seq_no;
      char type[6];
}packet;
void main(){
      int port = 6000;
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
      int frames[Max_Frames] = {0};//0 for NACK 1 for positve ack
      sleep(1);
      while (1){
            printf(".");
            packet frame;
            strcpy(frame.type,"FRAME");
            for (int i = 0; i < window_size;j++){
                if (frames[j]==0)
                { 
                    frame.seq_no = j;
                    send(cl_sock,&frame,sizeof(frame),0);
                    printf("Frame %d sent\n",frame.seq_no);
                    i++;
                }
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
            for (j = 0; j < Max_Frames;j++){
                  if (frames[j]==0){ //NACK
                        // printf("Going Back to %d\n",j);
                        break; //start transmitting from corrupted frame
                  }
            }
            sleep(2);
      }//while
      close(cl_sock);
      close(sockfd);
}