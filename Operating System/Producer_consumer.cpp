#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10;
int x = 0;

// Function to produce an item and add it to the buffer
void producer() {
    --mutex;
    ++full;
    --empty;
    ++x;
    printf("\nProducer produces item %d", x);
    ++mutex;
}

// Function to consume an item and remove it from the buffer
void consumer() {
    --mutex;
    --full;
    ++empty;
    printf("\nConsumer consumes item %d", x);
    --x;
    ++mutex;
}

int main() {
    int choice;
    while (1) {
        printf("\n1. Press 1 for Producer\n2. Press 2 for Consumer\n3. Press 3 for Exit");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                if ((mutex == 1) && (empty != 0))
                    producer();
                else
                    printf("\nBuffer is full. Cannot produce.");
                break;
            case 2:
                if ((mutex == 1) && (full != 0))
                    consumer();
                else
                    printf("\nBuffer is empty. Cannot consume.");
                break;
            case 3:
                exit(0);
                break;
        }
    }
    return 0;
}
