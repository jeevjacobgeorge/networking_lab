#include <stdio.h>
#include <unistd.h>

// Define color codes
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define CYAN "\033[1;36m"
#define RESET "\033[0m"

void display_bucket(int bucket, int bucket_size) {
    printf("[");
    for (int i = 0; i < bucket_size; i++) {
        if (i < bucket) {
            printf("#");
        } else {
            printf(" ");
        }
    }
    printf("] %d/%d\n", bucket, bucket_size);
}

int main() {
    int bucket_size;
    printf("Enter Bucket size: ");
    scanf("%d", &bucket_size);
    int rate;
    printf("Enter Output Rate: ");
    scanf("%d", &rate);
    int n;
    printf("Enter number of packets: ");
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        printf("Enter size of packet %d: ", i + 1);
        scanf("%d", &arr[i]);
    }

    int i = 0; // pointer for arr
    int bucket = 0; // current amount of data in the bucket

    printf("\nSimulating leaky bucket algorithm...\n");
    while (i < n || bucket > 0) {
        if (i < n) { // Check if we can accommodate the incoming packet into the bucket
            if (bucket + arr[i] <= bucket_size) { // Check if there is space
                bucket += arr[i];
                printf(GREEN "\n----> Incoming packet of size %d added to the bucket. Current Bucket size: %d\n" RESET, arr[i], bucket);
                display_bucket(bucket, bucket_size);
                i++;
            } else {
                printf(RED "\nXXX Packet of size %d discarded XXX. Bucket Overflow\n" RESET, arr[i]);
                display_bucket(bucket, bucket_size);
                i++;
            }
        }

        sleep(1);
        // Leak some data out of the bucket
        if (bucket > 0) { // First check if bucket is not empty
            if (bucket >= rate) { // Check if bucket has more packets than the output rate
                bucket -= rate;
                printf(CYAN "Sent packet of size %d ----> Remaining bucket size: %d\n" RESET, rate, bucket);
            } else { // If bucket has lesser packets than output rate
                printf(YELLOW "******* Sent last packet of size %d. Bucket Empty *******\n" RESET, bucket);
                bucket = 0;
            }
            display_bucket(bucket, bucket_size);
        }
        sleep(2);
    }

    printf("\nLeaky bucket simulation completed.\n");
    return 0;
}
