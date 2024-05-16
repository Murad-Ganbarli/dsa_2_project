#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "workload.h"

#define MAX_TIME 20 // Maximum time steps

// Function prototypes
void schedule_processes(struct workload_item_t *workload, size_t workload_size);
void print_schedule(struct workload_item_t *workload, size_t workload_size);
// Function prototype for comparing workload items by starting time (ts)
int compare_workload_items(const void *a, const void *b);

#endif /* SCHEDULER_H */
