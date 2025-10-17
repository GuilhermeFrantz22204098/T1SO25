#include "rr.h"
#include <stdio.h>
#include <stdlib.h>
#include "msg.h"
#include <unistd.h>

#define TIME_SLICE_MS 500

void rr_scheduler(uint32_t current_time_ms, queue_t *rq, pcb_t **cpu_task) {

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
            free((*cpu_task));
            (*cpu_task) = NULL;
        }
        else if ((current_time_ms - (*cpu_task)->slice_start_ms) >= TIME_SLICE_MS) {
            // Reached the time-slice and is sent back to the rq
            enqueue_pcb(rq, *cpu_task);
            (*cpu_task) = NULL;
        }
    }
    if (*cpu_task == NULL) {
        *cpu_task = dequeue_pcb(rq);
        if (*cpu_task != NULL) {
            // Start time slice for this pcb
            (*cpu_task)->slice_start_ms = current_time_ms;
        }
    }
}