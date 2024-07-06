#include <stdio.h>
#include <unistd.h>

void display(int bucket , int bucket_size){
      printf("[");
      for (int i = 0; i < bucket_size;i++){
            if (i < bucket){
                  printf("#");
            }
            else{
                  printf(" ");
            }
      }
      printf("] %d/%d\n",bucket,bucket_size);
}
void main(){
      int bucket_size;
      printf("Enter Bucket size:");
      scanf("%d",&bucket_size);
      int rate;
      printf("Enter Output Rate:");
      scanf("%d",&rate);
      int n;
      printf("Enter no of packets:");
      scanf("%d",&n);
      int arr[n];
      for (int i = 0; i < n; i++){
            printf("Enter %d packet:",i);
            scanf("%d",&arr[i]);
      }
      int i = 0;//pointer for arr
      int bucket = 0; // Current amount of data in the bucket
      while(i<n || bucket > 0){
            if (i<n){ //lets check if we can accomadate the incoming packet into the bucket
                  if( bucket + arr[i]  <= bucket_size){//check if there is space
                        bucket+=arr[i];
                        printf("Incoming packet------> %d added to the bucket. Current Bucket size:%d\n",arr[i],bucket);
                  } 
                  else{
                        printf("Incoming packet------> %d discarded.Bucket Overflow\n",arr[i]);
                  } 
                  display(bucket,bucket_size);
                  i++;
                  
            }
            //ok now lets leak some data out of the bucket
            if (bucket > 0){//first check if bucket is not empty
                  if (bucket >= rate){ //check bucket has more packets than the output rate
                        bucket -= rate;
                        printf("Sent packet of size -->%d------>.\n",rate);
                  }
                  else{ //if bucket has lesser packets than output rate
                        printf("*******Sent last packeet of size %d.***********\nBucket Empty\n",bucket);
                        bucket = 0;
                  }
                  display(bucket,bucket_size);
            }
            sleep(2);
      }

}
//SAMPLE INPUT 10 2 5 6 9 5 3 2