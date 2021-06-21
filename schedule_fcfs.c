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
    struct node *currentNode = taskList;
    while(1) { //loop will continue untill last node
        if(!currentNode->next){ //checking for last node
            break; //breaking loop for last node
        }
        currentNode = currentNode->next; //moving to next node
    }
    return currentNode->task; 
}
void schedule() {
    while(taskList) {
        Task *t = NextTask(); //picking the task to run
        run(t, t->burst); //running selected task for its burst time
        delete(&taskList, t); //freeijng the list 
    }
}
