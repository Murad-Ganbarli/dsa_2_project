#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "workload.h"

// Function prototypes
void schedule_processes(struct workload_item_t *workload, size_t workload_size);
void print_schedule(struct workload_item_t *workload, size_t workload_size);

#endif /* SCHEDULER_H */
