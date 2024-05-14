#ifndef WORKLOAD_ITEM_H
#define WORKLOAD_ITEM_H

struct workload_item_t {
    int pid;         //< the event id
    int ppid;        //< the event parent id
    size_t ts;       //< start date
    size_t tf;       //< finish date
    size_t idle;     //< total time the process has been idle;
    char *cmd;       //< the binary name
    int prio;        //< process priority
};

typedef struct workload_item_t workload_item;

#endif /* WORKLOAD_ITEM_H */
