#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "scheduler.h"

int main() {
    Queue *running = queue_init();
    Queue *waiting = queue_init();


    // Define an array to hold the workload items
    workload_item items[] = {
        {0, -1, 0, 18, 0, "init", 10},
        {1, 0, 1, 16, 0, "bash", 1},
        {2, 0, 3, 16, 0, "bash", 1},
        {3, 1, 4, 6, 0, "find", 2},
        {4, 1, 7, 9, 0, "gcc", 5},
        {5, 4, 8, 9, 0, "ld", 4},
        {6, 2, 10, 13, 0, "ssh", 3},
        {7, 6, 11, 13, 0, "crypt", 5},
        {8, 2, 14, 16, 0, "snake", 4},
        {9, 1, 14, 15, 0, "cat", 5}
    };

    // Calculate the size of the array
    int numItems = sizeof(items) / sizeof(items[0]);

    // Push each item from the array into the waiting queue
    for (int i = 0; i < numItems; i++) {
        enqueue(waiting, items[i]);
    }

    // Display the queue before scheduling
    printf("Queue before scheduling:\n");
    display(waiting);

    // Apply scheduling
    for (int time = 0; time <= 20; time++) {
        schedule(running, waiting, time);
    }

    // Display the queue after scheduling
    printf("\nQueue after scheduling:\n");
    display(waiting);

    return 0;
}
