#ifndef QUEUE_H
#define QUEUE_H

#include "workload_item.h"

struct node {
    workload_item data;
    struct node* next;
};

typedef struct node Node;

typedef struct {
    Node* front;
    Node* rear;
} Queue;

void enqueue(Queue* queue, workload_item item);
void dequeue(Queue* queue);
void display(Queue* queue);
Queue* queue_init();

#endif /* QUEUE_H */
