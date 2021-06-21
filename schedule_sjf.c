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
    Task *shortest_burst = taskList->task;
    struct node *current = taskList;
    while(current){
        if(current->task->burst <= shortest_burst->burst){ //checking for shorter burst
            shortest_burst = current->task; //interchanging tasks
        }
        current = current->next; //moving to next node
    }
    return shortest_burst;
}
void schedule() {
    while(taskList) {
        Task *t = NextTask(); //picking the task to run
        run(t, t->burst); //running selected task for its burst time
        delete(&taskList, t); //freeijng the list 
    }
}
