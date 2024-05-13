#include "scheduler.h"
#include <stdio.h>

#define MAX_PROCESSES 100 // Maximum number of processes
#define MAX_TIME 20 // Maximum time steps

void schedule_processes(struct workload_item_t *workload, size_t workload_size) {
    // Initialize variables to track CPU occupation and process status
    int cpu[MAX_TIME] = {0}; // Initialize CPU occupation for each time step

    // Iterate over each process
    for (size_t i = 0; i < workload_size; i++) {
        // Find the earliest available time slot for the current process
        size_t start_time = workload[i].ts;
        while (start_time < MAX_TIME && cpu[start_time] != 0) {
            start_time++;
        }

        // Check if a valid time slot was found
        if (start_time < MAX_TIME) {
            // Assign the process to the CPU for the required duration
            for (size_t t = start_time; t <= workload[i].tf && t < MAX_TIME; t++) {
                cpu[t] = 1; // Mark CPU as occupied
            }
        } else {
            printf("Error: Unable to schedule process %s\n", workload[i].cmd);
            // You can choose to handle this error condition differently, such as skipping the process
        }
    }
}


void print_schedule(struct workload_item_t *workload, size_t workload_size) {
    // Print header for the chronogram
    printf("        ");
    for (size_t t = 0; t < MAX_TIME; t++) {
        if(t % 5 == 0)
            printf("|");
        else
            printf(".");
    }
    printf("\n");

    // Iterate over each process
    for (size_t i = 0; i < workload_size; i++) {
        // Print process command
        printf("%-8s", workload[i].cmd);

        // Initialize finish time and idle time for the process
        size_t finish_time = 0;
        size_t idle_time = 0;

        // Print X for each time step where process is scheduled
        for (size_t t = 0; t < MAX_TIME; t++) {
            if (workload[i].ts <= t && t <= finish_time) {
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
