// scheduler.c

#include "scheduler.h"
#include <stdio.h>

// Function to perform a scheduling round
void schedule(Queue* running, Queue* waiting, int time) {
    int cpuCapability = 20; // Example CPU capability, you can change this value
    int currentTime = time;

    // Identify all possible processes
    Queue* possibleProcesses = identifyPossibleProcesses(waiting, currentTime);

    // Select current processes
    Queue* currentProcesses = selectCurrentProcesses(possibleProcesses, currentTime);

    // Calculate the sum of priorities of current processes
    int sumPriorities = calculateSumPriorities(currentProcesses);

    // Check if the sum of priorities exceeds CPU capability
    if (sumPriorities <= cpuCapability) {
        // Enqueue all current processes into the running queue
        Node* current = currentProcesses->front;
        while (current != NULL) {
            enqueue(running, current->data);
            current = current->next;
        }
    } else {
        // Enqueue only processes with greater priority into the running queue
        // and the rest into the waiting queue
        separateProcesses(running, waiting, currentProcesses, cpuCapability);
    }

    // Increment idle time and delay termination time for de-scheduled processes
    updateProcesses(waiting, currentTime);
}


// Function to identify all possible processes (tf > t)
Queue* identifyPossibleProcesses(Queue* waiting, int currentTime) {
    Queue* possibleProcesses = queue_init();
    Node* current = waiting->front;
    while (current != NULL) {
        if (current->data.tf > currentTime) {
            enqueue(possibleProcesses, current->data);
        }
        current = current->next;
    }
    return possibleProcesses;
}

// Function to select current processes (ts ≤ t ≤ tf)
Queue* selectCurrentProcesses(Queue* possibleProcesses, int currentTime) {
    Queue* currentProcesses = queue_init();
    Node* current = possibleProcesses->front;
    while (current != NULL) {
        if (current->data.ts <= currentTime && currentTime <= current->data.tf) {
            enqueue(currentProcesses, current->data);
        }
        current = current->next;
    }
    return currentProcesses;
}

// Function to calculate the sum of priorities of current processes
int calculateSumPriorities(Queue* currentProcesses) {
    int sum = 0;
    Node* current = currentProcesses->front;
    while (current != NULL) {
        sum += current->data.prio;
        current = current->next;
    }
    return sum;
}

// Function to separate processes based on CPU capability
void separateProcesses(Queue* running, Queue* waiting, Queue* currentProcesses, int cpuCapability) {
    Node* current = currentProcesses->front;
    while (current != NULL) {
        if (current->data.prio <= cpuCapability) {
            enqueue(running, current->data);
        } else {
            enqueue(waiting, current->data);
        }
        current = current->next;
    }
}

// Function to update processes (increment idle time and delay termination time)
void updateProcesses(Queue* waiting, int currentTime) {
    Node* current = waiting->front;
    while (current != NULL) {
        if (current->data.ts < currentTime && currentTime <= current->data.tf) {
            current->data.idle++;
            current->data.tf++;
        }
        current = current->next;
    }
}
