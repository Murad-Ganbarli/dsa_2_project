#include "scheduler.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

// Function to schedule processes using a queue
void schedule_processes(struct workload_item_t *workload, size_t workload_size) {
    // Sort workload items by starting time
    qsort(workload, workload_size, sizeof(struct workload_item_t), compare_workload_items);

    // Initialize CPU occupation and queues for pending and running processes
    Queue *pendingQueue = createQueue();
    Queue *runningQueue = createQueue();

    // Enqueue all workload items into the pending queue
    for (size_t i = 0; i < workload_size; i++) {
        enqueue(pendingQueue, &workload[i]);
    }

    // Simulate CPU scheduling
    int time = 0;
    while (!isEmpty(pendingQueue) || !isEmpty(runningQueue)) {
        // Check for pending processes to start
        while (!isEmpty(pendingQueue) && ((struct workload_item_t *)peek(pendingQueue))->ts <= time) {
            struct workload_item_t *process = dequeue(pendingQueue);
            printf("Process %s (PID: %d) started at time %d\n", process->cmd, process->pid, time);
            enqueue(runningQueue, process);
        }

        // Execute the running process
        if (!isEmpty(runningQueue)) {
            struct workload_item_t *currentProcess = peek(runningQueue);
            printf("Executing process %s (PID: %d) at time %d\n", currentProcess->cmd, currentProcess->pid, time);
            currentProcess->tf--; // Decrement finish time
            if (currentProcess->tf == 0) {
                printf("Process %s (PID: %d) completed at time %d\n", currentProcess->cmd, currentProcess->pid, time);
                dequeue(runningQueue);
            }
        } else {
            printf("CPU idle at time %d\n", time);
        }

        time++;
    }

    // Free memory allocated for queues
    freeQueue(pendingQueue);
    freeQueue(runningQueue);
}



// Function to print schedule for current timestep
void print_schedule(struct workload_item_t *workload, size_t workload_size) {
    // Print header for the chronogram
    printf("        ");
    for (size_t t = 0; t < MAX_TIME; t++) {
        if (t % 5 == 0)
            printf("|");
        else
            printf(".");
    }
    printf("\n");

    // Sort workload items by starting time
    qsort(workload, workload_size, sizeof(struct workload_item_t), compare_workload_items);

    // Iterate over each process
    for (size_t i = 0; i < workload_size; i++) {
        // Print process command
        printf("%-8s", workload[i].cmd);

        // Initialize finish time and idle time for the process
        size_t finish_time = 0;
        size_t idle_time = 0;

        // Print X for each time step where process is scheduled
        for (size_t t = 0; t < MAX_TIME; t++) {
            if (workload[i].ts <= t && t <= workload[i].tf) {
                printf("X");
            } else {
                printf(".");
            }

            // Update finish time and idle time
            if (workload[i].ts <= t && t <= workload[i].tf) {
                finish_time = workload[i].tf;
            } else if (t > workload[i].tf) {
                idle_time++;
            }
        }

        // Print process finish time and idle time
        printf("  (tf=%zu,idle=%zu)\n", finish_time, idle_time);
    }
}
