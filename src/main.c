#include <stdio.h>
#include <string.h>
#include "task.h"
#include "timer.h"
#include <unistd.h>
#include <pthread.h>
clock_t end, start;

void callback(int sig)
{
    printf("Hello = ");
    end = clock();
    printf("%f\n",((double) (end - start)) / CLOCKS_PER_SEC);
    start = end;
}

void init_timer(void) 
{
    timer_set_cb(&callback);
    start_timer(1, 1);
}

void schedule_run(task_t *all_task, int num_of_task)
{
    int task_idx = 0; 
    unsigned int current_time = 0;
    task_t *current_task = NULL;
    int rc = 0;
    pthread_t tid;
    
    while(1)
    {
        for(task_idx = 0; task_idx < num_of_task; ++task_idx)
        {
            current_time = get_time();
            current_task = &all_task[task_idx];

            if(get_task_type(current_task) == TASK_TYPE_OPERATION)
            {
                if(get_task_priority(current_task) == TASK_PRIORITY_LOW)
                {
                    if((get_task_in_time(current_task) <= current_time && 
                                get_task_out_time(current_task) >= current_time) &&
                            get_task_in_state(current_task) == TASK_STATE_INIT)
                    {
                        //call in_task
                        if(current_task->in_task != NULL) {
                            printf("Thread create\n");

                            rc = pthread_create(&tid, NULL, current_task->in_task, current_task->data); 
                            if(rc != 0)
                                printf("Thread creation failed & rc = %d\n", rc);
                        }
                        pthread_detach(tid);    //deattaching thre thread

                        if(current_task->out_task != NULL) 
                            set_task_in_state(current_task, TASK_STATE_PENDING);
                        else
                            set_task_in_state(current_task, TASK_STATE_DONE);
                    }
                }
            }
        }
        usleep(1000*250);
    }
}

void * action(void * data)
{
    printf("Worked and time = %u\n",get_time());
    printf("Name = %s\n",data);
}

char *str = "Nikhil";

int main()
{
    task_t t1;
    t1.in_time = 1348;
    t1.out_time = 1350;
    t1.priority = TASK_PRIORITY_LOW;
    t1.type = TASK_TYPE_OPERATION;
    t1.in_state = TASK_STATE_INIT;
    t1.in_task = &action;
    t1.data = (void *)str;

    schedule_run(&t1, 1);
    return 0;
}
