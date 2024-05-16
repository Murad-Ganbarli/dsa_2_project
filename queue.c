#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

// Function to create an empty queue
Queue* createQueue() {
    Queue *queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(Queue *queue) {
    return (queue->front == NULL);
}

// Function to enqueue a workload item
void enqueue(Queue *queue, struct workload_item_t *item) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        exit(EXIT_FAILURE);
    }
    newNode->item = item;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

// Function to dequeue a workload item
struct workload_item_t* dequeue(Queue *queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Error: Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = queue->front;
    struct workload_item_t *item = temp->item;
    queue->front = queue->front->next;
    free(temp);
    return item;
}

// Function to peek at the front element of the queue
struct workload_item_t* peek(Queue *queue) {
    if (isEmpty(queue)) {
        fprintf(stderr, "Error: Queue is empty\n");
        exit(EXIT_FAILURE);
    }
    return queue->front->item;
}


// Function to free memory allocated for the queue
void freeQueue(Queue *queue) {
    while (!isEmpty(queue)) {
        dequeue(queue);
    }
    free(queue);
}
