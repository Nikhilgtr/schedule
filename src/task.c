#include "task.h"

task_type_e
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

task_action_state_e
get_task_in_state(const task_t *task)
{
    if(task != NULL)
        return task->in_state;
}

void
set_task_in_state(task_t *task, task_action_state_e state)
{
    if(task != NULL)
    task->in_state = state;
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
