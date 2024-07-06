#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BUCKET_SIZE 10
#define OUTPUT_RATE 1

void leaky_bucket(int incoming_packets[], int n) {
    int bucket = 0; // Current amount of data in the bucket
    int i = 0;
    
    while (i < n || bucket > 0) {
        // Process incoming packets if there are any left
        if (i < n) {
            if (incoming_packets[i] + bucket > BUCKET_SIZE) {
                printf("Incoming packet of size %d discarded. Bucket overflow.\n", incoming_packets[i]);
            } else {
                bucket += incoming_packets[i];
                printf("Incoming packet of size %d added to the bucket. Current bucket size: %d\n", incoming_packets[i], bucket);
            }
            i++;
        }
        
        // Send packets out of the bucket
        if (bucket > 0) {
            if (bucket >= OUTPUT_RATE) {
                bucket -= OUTPUT_RATE;
                printf("Sent packet of size %d. Remaining bucket size: %d\n", OUTPUT_RATE, bucket);
            } else {
                printf("Sent packet of size %d. Bucket is now empty.\n", bucket);
                bucket = 0;
            }
        }
        
        // Simulate time passing (1 second per iteration)
        sleep(1);
    }
}

int main() {
    int incoming_packets[] = {4, 2, 6, 1, 8, 3, 5, 7}; // Example packet sizes
    int n = sizeof(incoming_packets) / sizeof(incoming_packets[0]);

    printf("Simulating leaky bucket algorithm...\n");
    leaky_bucket(incoming_packets, n);

    return 0;
}
