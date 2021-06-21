#include<string.h>
#include<stdlib.h>
#include "schedulers.h"
#include "task.h"
#include "cpu.h"
#include "list.h"

struct node *taskList = NULL;
struct node *next_node;

void add(char *name, int priority, int burst) {
    Task *t = malloc(sizeof(Task)); //memory allocation for structure
    t->name = malloc(sizeof(char) * (strlen(name) + 1)); //memory allocation for pointer
    strcpy(t->name, name); //copying name 
    t->priority = priority; //copying priority value
    t->burst = t->remainingburst = burst; //copying burst value
    insert(&taskList, t); //inserting all attributes to tasklist structure
}
Task *NextTask() {
    Task *ret = next_node->task;
    next_node = (next_node -> next) ? next_node->next : taskList; //returns next node if available otherwise tasklist
    return ret;
}
void schedule() {
    next_node = taskList;
    while(taskList) {
        Task *t = NextTask();
        int slice = QUANTUM < t->remaining_burst ? QUANTUM : t->remaining_burst; //if quantum is small then slice will become quantum
        																		 //if quantum is greater than burst time then slice becomes burst time
        run(t, slice); //running for slice time
        t->remaining_burst -= slice; //subtracting slice time from remaining burst
        if(!t->remaining_burst) { //if remaining burst is empty
            delete(&taskList, t); //delete the task from list
        }
    }
}
