#ifndef TASK_H
#define TASK_H

#include <stdio.h>
#include <pthread.h>
#include <log.h>
typedef enum _task_priority_
{
    TASK_PRIORITY_LOW,
    TASK_PRIORITY_HIGH,
    TASK_PRIORITY_MAX
}task_priority_e;

typedef enum _task_state_
{
    TASK_STATE_START,
    TASK_STATE_PENDING,
    TASK_STATE_HALT, //Used for exception case
    TASK_STATE_DONE,
    TASK_STATE_MAX
}task_state_e;

typedef enum _task_oper_type_
{
    TASK_TYPE_STATUS,
    TASK_TYPE_IO,
    TASK_TYPE_MAX
}task_oper_type_e;

typedef enum _handle_type_
{
    IN_HANDLE,
    OUT_HANDLE,
    MAX_HANDLE
}handle_type_e;

typedef enum _task_oper_periperal_
{
    TASK_PERIPHERAL_TYPE_GPIO,
    TASK_PERIPHERAL_TYPE_UART,
    TASK_PERIPHERAL_TYPE_SOCKET,
    TASK_PERIPHERAL_TYPE_TEST,
    TASK_PERIPHERAL_TYPE_MAX
}task_peripheral_e;

typedef void * (*task_fptr)(void *data);

typedef struct _task_handler_
{
    task_fptr handle;
    void *data;
}task_handler_t;

typedef struct task {
    task_peripheral_e peripheral;
    task_priority_e priority;       //High or Low (High priority will be given preference
    task_oper_type_e type;               //status or operation
    task_state_e state;
    
    unsigned short in_time;         //Time to start task and call in_task
    unsigned short out_time;        //Time to stop task and call out_task 
    unsigned char day;              //day of the week
    unsigned long period;           //After how many time period status is called 

    task_handler_t in_task;    
    task_handler_t out_task;    
} task_t;

task_oper_type_e
get_task_type(const task_t *task);

task_priority_e
get_task_priority(const task_t *task);

task_state_e
get_task_state(const task_t *task);

void
set_task_state(task_t *task, task_state_e state);

unsigned short
get_task_in_time(const task_t *task);

unsigned short
get_task_out_time(const task_t *task);

int 
execute_task(task_handler_t task);

int
is_ready_for_task(const task_t *task, handle_type_e handle);
#endif
