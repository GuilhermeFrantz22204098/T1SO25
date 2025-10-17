#include "sjf.h"
#include <stdio.h>
#include <stdlib.h>
#include "msg.h"
#include <unistd.h>
#include <limits.h>

void sjf_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task) {
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
    }
    if (*cpu_task == NULL) {
        uint32_t min_time = UINT_MAX;
        queue_elem_t* min_time_elem = NULL;
        queue_elem_t* current_elem = rq->head;

        // get shortest job
        while (current_elem != NULL) {
            if (current_elem->pcb->time_ms < min_time) {
                min_time = current_elem->pcb->time_ms;
                min_time_elem = current_elem;
            }
            current_elem = current_elem->next;
        }

        // run the process
        if (min_time_elem != NULL) {
            *cpu_task = min_time_elem->pcb;
            printf("T primeira exec: %u, PID: %d\n", current_time_ms, (*cpu_task)->pid);
            remove_queue_elem(rq, min_time_elem);
            free(min_time_elem);
        }
    }
}