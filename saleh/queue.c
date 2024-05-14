#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node {
    workload_item data;
    struct node* next;
};

typedef struct node Node;

Node* front = NULL;
Node* rear = NULL;

void enqueue(workload_item item) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = item;
    newNode->next = NULL;
    if (front == NULL && rear == NULL) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

void dequeue() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = front;
    if (front == rear) {
        front = rear = NULL;
    } else {
        front = front->next;
    }
    free(temp);
}

void display() {
    if (front == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* temp = front;
    while (temp != NULL) {
        printf("PID: %d, PPID: %d, Start: %zu, Finish: %zu, Idle: %zu, Command: %s, Priority: %d\n",
            temp->data.pid, temp->data.ppid, temp->data.ts, temp->data.tf, temp->data.idle, temp->data.cmd, temp->data.prio);
        temp = temp->next;
    }
}
