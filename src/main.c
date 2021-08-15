#include <stdio.h>
#include <string.h>
#include "task.h"
#include "timer.h"
#include <unistd.h>
#include <pthread.h>
#include <log.h>

#define MAX_DELAY_SCH 250

FILE *trace = NULL;

void schedule_run(task_t *all_task, int num_of_task)
{
    int task_idx = 0; 
    task_t *current_task = NULL;
    int rc = 0;

    while(1)
    {
        for(task_idx = 0; task_idx < num_of_task; ++task_idx)
        {
            current_task = &all_task[task_idx];

            if(get_task_type(current_task) == TASK_TYPE_IO)
            {
                if(get_task_priority(current_task) == TASK_PRIORITY_LOW)
                {
                    if(is_ready_for_task(current_task, IN_HANDLE))
                    {
                        //execute task
                        if(current_task->in_task.handle != NULL) {
                            rc = execute_task(current_task->in_task);
                            if(rc != 0)
                                log_trace("failed in execution of task_handler");
                            else
                                set_task_state(current_task, TASK_STATE_PENDING);
                        } else {
                            log_trace("No in task handler");
                            set_task_state(current_task, TASK_STATE_PENDING);
                        }
                    }
                }
                if(is_ready_for_task(current_task, OUT_HANDLE))
                {
                    //execute task
                    if(current_task->out_task.handle != NULL) {
                        rc = execute_task(current_task->in_task);
                        if(rc != 0)
                            log_trace("failed in execution of task_handler");
                        else
                            set_task_state(current_task, TASK_STATE_DONE);
                    } else {
                        log_trace("No out task handler");
                        set_task_state(current_task, TASK_STATE_DONE);
                    }
                }
            }
        }
    }
    usleep(1000*MAX_DELAY_SCH);
}


void * action(void * data)
{
    log_trace("Worked and time = %u",get_time());
    log_trace("Name = %s",data);
}

char *str = "Nikhil";

int
init_log(void)
{
    trace = fopen("./trace.log", "w+");
    if(trace == NULL)
    {
        printf("trace file not opened\n");
        return -1;
    }
    log_add_fp(trace, LOG_TRACE);
    log_set_quiet(false);
    return 0;
}

int main()
{
    int rc = 0;
    task_t t1;
    rc = init_log();
    if(rc != 0)
    {
        printf("init trace failed\n");
        return -1;
    }
   memset(&t1, 0, sizeof(t1)); 
    t1.in_time = 2051;
    t1.out_time = 2052;
    t1.priority = TASK_PRIORITY_LOW;
    t1.type = TASK_TYPE_IO;
    t1.state = TASK_STATE_START;
    
    schedule_run(&t1, 1);

    t1.in_task.handle = &action;
    t1.in_task.data = (void *)str;
    
    t1.out_task.handle = &action;
    t1.out_task.data = (void *)str;

    return 0;
}
