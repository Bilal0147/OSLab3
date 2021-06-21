#include<string.h>
#include<stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

struct node *taskList = NULL;

void add(char *name, int priority, int burst) {
    Task *t = malloc(sizeof(Task)); //memory allocation for structure
    t->name = malloc(sizeof(char) * (strlen(name) + 1)); //memory allocation for pointer
    strcpy(t->name, name); //copying name 
    t->priority = priority; //copying priority value
    t->burst = burst; //copying burst value
    insert(&taskList, t); //inserting all attributes to tasklist structure
}
Task *NextTask() {
    Task *highest_priority = taskList->task;
    struct node *current = taskList;
    while(current){
        if(current->task->priority >= highest_priority->priority){ //checking for higher priority
            highest_priority = current->task; //interchanging tasks
        }
        current = current->next; //moving to next node
    }
    return highest_priority;
}
void schedule() {
    while(taskList) {
        Task *t = NextTask(); //picking the task to run
        run(t, t->burst); //running selected task for its burst time
        delete(&taskList, t); //freeijng the list 
    }
}
