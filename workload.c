#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "workload.h"

#define MAX_CMD_LENGTH 100 // Maximum length for command name

int read_workload(const char *filename, struct workload_item_t *workload, size_t *workload_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        return 0;
    }

    // Read workload data from file line by line
    char line[MAX_CMD_LENGTH];
    while ((*workload_size) < MAX_PROCESSES && fgets(line, sizeof(line), file) != NULL) {
        // Tokenize the line to extract fields
        char *token = strtok(line, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }

        // Assign values to workload item fields
        workload[*workload_size].pid = atoi(token);

        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }
        workload[*workload_size].ppid = atoi(token);

        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }
        workload[*workload_size].ts = (size_t)atoi(token);
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }
        workload[*workload_size].tf = (size_t)atoi(token);
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }
        workload[*workload_size].idle = (size_t)atoi(token);
        
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }
        // Allocate memory for command name and copy it
        workload[*workload_size].cmd = strdup(token);
        if (workload[*workload_size].cmd == NULL) {
            fprintf(stderr, "Memory allocation error\n");
            fclose(file);
            return 0;
        }

        // assign to .prio (int )
        token = strtok(NULL, " ");
        if (token == NULL) {
            fprintf(stderr, "Error parsing line: %s\n", line);
            fclose(file);
            return 0;
        }
        workload[*workload_size].prio = atoi(token);

        
        (*workload_size)++;
    }

    fclose(file);

    for (size_t i = 0; i < *workload_size; i++) {
        printf("%d %-5d %-3zu %-3zu %-3zu %-6s %d\n",
               workload[i].pid, workload[i].ppid, workload[i].ts, workload[i].tf,
               workload[i].idle, workload[i].cmd, workload[i].prio);
    }

    return 1;
}

// compare workload items
int compare_workload_items(const void *a, const void *b) {
    struct workload_item_t *item1 = (struct workload_item_t *)a;
    struct workload_item_t *item2 = (struct workload_item_t *)b;

    if (item1->ts < item2->ts) {
        return -1;
    } else if (item1->ts > item2->ts) {
        return 1;
    } else {
        return 0;
    }
}