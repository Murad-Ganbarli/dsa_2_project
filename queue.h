#ifndef QUEUE_H
#define QUEUE_H

#include "workload.h"

// Define structure for a node in the queue
typedef struct Node {
    struct workload_item_t *item;
    struct Node *next;
} Node;

// Define structure for the queue
typedef struct {
    Node *front;
    Node *rear;
} Queue;

// Function prototypes
Queue* createQueue();
int isEmpty(Queue *queue);
void enqueue(Queue *queue, struct workload_item_t *item);
struct workload_item_t* dequeue(Queue *queue);
void freeQueue(Queue *queue);
// Function to peek at the front element of the queue
struct workload_item_t* peek(Queue *queue);

#endif /* QUEUE_H */
