#include "mlfq.h"
#include <stdio.h>
#include <stdlib.h>
#include "msg.h"
#include <unistd.h>

#define NUM_LEVELS 3
static queue_t levels[NUM_LEVELS];
static int current_process_level = -1;

void mlfq_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task) {

    // Gets all new processes into the first level queue
    pcb_t* new_pcb;
    while ((new_pcb = dequeue_pcb(rq)) != NULL) {
        printf("T início: %u, PID: %d\n", current_time_ms, new_pcb->pid);
        enqueue_pcb(&levels[0], new_pcb);
    }

    if (*cpu_task) {
        (*cpu_task)->ellapsed_time_ms += TICKS_MS; // Add to the running time of the application/task
        if ((*cpu_task)->ellapsed_time_ms >= (*cpu_task)->time_ms) {
            // Task finished
            // Send msg to application
            msg_t msg = {
                .pid = (*cpu_task)->pid,
                .request = PROCESS_REQUEST_DONE,
                .time_ms = current_time_ms
            };
            if (write((*cpu_task)->sockfd, &msg, sizeof(msg_t)) != sizeof(msg_t)) {
                perror("write");
            }
            // Application finished and can be removed
            printf("T terminação: %u, PID: %d\n", current_time_ms, (*cpu_task)->pid);
            free((*cpu_task));
            (*cpu_task) = NULL;
        }
        else if ((current_time_ms - (*cpu_task)->slice_start_ms) >= 500) {
            // Reached the time-slice and is sent back to the lower-priority level rq
            int next_level = (current_process_level + 1 < NUM_LEVELS) ? (current_process_level + 1) : (NUM_LEVELS - 1);
            enqueue_pcb(&levels[next_level], *cpu_task);
            printf("Added PID %d to lvl %d\n", (*cpu_task)->pid, next_level);
            *cpu_task = NULL;
        }
    }
    if (*cpu_task == NULL) {
        // Gets the next pcb with the highest priority level
        for (int i = 0; i < NUM_LEVELS; i++) {
            if (levels[i].head != NULL) {
                *cpu_task = dequeue_pcb(&levels[i]);
                if (*cpu_task != NULL) {
                    if ((*cpu_task)->ellapsed_time_ms == 0) {
                        printf("T primeira exec: %u, PID: %d\n", current_time_ms, (*cpu_task)->pid);
                    }
                    // Start time slice for this pcb
                    (*cpu_task)->slice_start_ms = current_time_ms;
                    current_process_level = i;
                }
                break;
            }
        }
    }
}