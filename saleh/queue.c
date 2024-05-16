#include <stdio.h>
#include <stdlib.h>
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

Queue* queue_init() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}
void enqueue(Queue* queue, workload_item item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    if (queue->front == NULL && queue->rear == NULL) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}

void dequeue(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = queue->front;
    if (queue->front == queue->rear) {
        queue->front = queue->rear = NULL;
    } else {
        queue->front = queue->front->next;
    }
    free(temp);
}

void display(Queue* queue) {
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = queue->front;
    while (temp != NULL) {
        printf("PID: %d, PPID: %d, Start: %zu, Finish: %zu, Idle: %zu, Command: %s, Priority: %d\n",
            temp->data.pid, temp->data.ppid, temp->data.ts, temp->data.tf, temp->data.idle, temp->data.cmd, temp->data.prio);
        temp = temp->next;
    }
}