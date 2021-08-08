#ifndef TASK_H
#define TASK_H

#include <stdio.h>
typedef enum _task_priority_
{
    TASK_PRIORITY_LOW,
    TASK_PRIORITY_HIGH,
    TASK_PRIORITY_MAX
}task_priority_e;

typedef enum _task_action_state_
{
    TASK_STATE_INIT,
    TASK_STATE_PENDING,
    TASK_STATE_DONE,
    TASK_STATE_HALT, //Used for exception case
    TASK_STATE_MAX
}task_action_state_e;

typedef enum _task_type_
{
    TASK_TYPE_STATUS,
    TASK_TYPE_OPERATION,
    TASK_TYPE_MAX
}task_type_e;

typedef enum _task_operation_type_
{
    TASK_OPERATION_TYPE_GPIO,
    TASK_OPERATION_TYPE_UART,
    TASK_OPERATION_TYPE_SOCKET,
    TASK_OPERATION_TYPE_TEST,
    TASK_OPERATION_TYPE_MAX,
}task_operation_type_e;

typedef struct task {
    task_operation_type_e operation_type;
    unsigned short in_time;         //Time to start task and call in_task
    unsigned short out_time;        //Time to stop task and call out_task 
    unsigned char day;              //day of the week
    task_priority_e priority;       //High or Low (High priority will be given preference
    task_type_e type;               //status or operation
    unsigned long period;           //After how many time period status is called 
    task_action_state_e state;
    void * (*in_task)(void *data);     
    void * (*out_task)(void *data);
    void *data; 
} task_t;

task_type_e
get_task_type(const task_t *task);

task_priority_e
get_task_priority(const task_t *task);

task_action_state_e
get_task_in_state(const task_t *task);

void
set_task_in_state(task_t *task, task_action_state_e state);

unsigned short
get_task_in_time(const task_t *task);

unsigned short
get_task_out_time(const task_t *task);
#endif
