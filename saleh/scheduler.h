// scheduler.h

#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "queue.h"

// Function prototypes
void schedule(Queue* running, Queue* waiting, int time);
Queue* identifyPossibleProcesses(Queue* waiting, int currentTime);
Queue* selectCurrentProcesses(Queue* possibleProcesses, int currentTime);
int calculateSumPriorities(Queue* currentProcesses);
void separateProcesses(Queue* running, Queue* waiting, Queue* currentProcesses, int cpuCapability);
void updateProcesses(Queue* waiting, int currentTime);

#endif /* SCHEDULER_H */
