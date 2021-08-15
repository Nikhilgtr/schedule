#include "task.h"
#include <timer.h>

#define MAX_DELAY_MINUTE 2

task_oper_type_e
get_task_type(const task_t *task)
{
    if(task != NULL)
    return task->type;
}

task_priority_e
get_task_priority(const task_t *task)
{
    if(task != NULL)
    return task->priority;
}

task_state_e
get_task_state(const task_t *task)
{
    if(task != NULL)
        return task->state;
}

void
set_task_state(task_t *task, task_state_e state)
{
    if(task != NULL)
    task->state = state;
}

unsigned short
get_task_in_time(const task_t *task)
{
    if(task != NULL)
        return task->in_time;
}

unsigned short
get_task_out_time(const task_t *task)
{
    if(task != NULL)
        return task->out_time;
}

int 
execute_task(task_handler_t task)
{
    int rc = 0;
    pthread_t tid;

    rc = pthread_create(&tid, NULL, task.handle, task.data);
    if(rc != 0) 
    {
        log_trace("Thread creation failed & rc = %d\n", rc);
        return rc;
    }
    pthread_detach(tid);    //deattaching the thread
    
    return rc;
}

int
is_ready_for_task(const task_t *task, handle_type_e handle)
{
    unsigned int current_time = 0;
    unsigned short in_time = 0;
    unsigned short out_time = 0;
    
    in_time = get_task_in_time(task);
    out_time = get_task_out_time(task);
    current_time = get_time();

    switch(handle)
    {
    case IN_HANDLE:
        {
            if((current_time >= in_time) && current_time <= (in_time + MAX_DELAY_MINUTE)
                    && (get_task_state(task) == TASK_STATE_START))
                return 1;
        }
        break;
    case OUT_HANDLE:
        {
            if((current_time >= out_time) && current_time <= (out_time + MAX_DELAY_MINUTE)
                    && (get_task_state(task) == TASK_STATE_PENDING))
                return 1;
        }
        break;

    default:
        log_trace("Not proper handle set");
    }
    return 0;
}
