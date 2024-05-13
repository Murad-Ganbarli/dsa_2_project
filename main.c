#include <stdio.h>
#include <stdlib.h>
#include "workload.h" // Header file for workload data structures and functions
#include "scheduler.h" // Header file for scheduling functions

int main() {
    // Declare variables to store workload data
    struct workload_item_t workload[MAX_PROCESSES];
    size_t workload_size = 0;

    // Read workload data from input file
    if (!read_workload("data/workload.txt", workload, &workload_size)) {
        fprintf(stderr, "Error reading workload data from file\n");
        return 1;
    }
    printf("Workload data read successfully\n");

    // Schedule processes based on given rules
    schedule_processes(workload, workload_size);
    printf("Processes scheduled successfully\n");

    // Print scheduling results
    print_schedule(workload, workload_size);

    return 0;
}
