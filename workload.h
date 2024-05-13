#ifndef WORKLOAD_H
#define WORKLOAD_H

#include <stdio.h>

// Define constants for maximum number of processes and other parameters
#define MAX_PROCESSES 100

// Define structure for workload item
struct workload_item_t {
    int pid;        //< the event id
    int ppid;       //< the event parent id
    size_t ts;      //< start date
    size_t tf;      //< finish date
    size_t idle;    //< total time the process has been idle;
    char *cmd;      //< the binary name
    int prio;       //< process priority
};

// Function prototypes
int read_workload(const char *filename, struct workload_item_t *workload, size_t *workload_size);

#endif /* WORKLOAD_H */
