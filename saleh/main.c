#include <stdio.h>
#include "queue.h"

int main() {
    workload_item item1 = {1, 0, 100, 200, 50, "cmd1", 1};
    workload_item item2 = {2, 1, 300, 400, 60, "cmd2", 2};
    workload_item item3 = {3, 1, 500, 600, 70, "cmd3", 3};

    enqueue(item1);
    enqueue(item2);
    enqueue(item3);

    printf("Queue after enqueue:\n");
    display();

    dequeue();
    dequeue();

    printf("\nQueue after dequeue:\n");
    display();

    return 0;
}
    