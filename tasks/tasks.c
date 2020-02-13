/*2º Projeto de IAED*/
/*João Lopes - 90732*/

#include "tasks.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

struct task *Tasks_h, *Tasks_t;

void Tasks_init(){
  Tasks_h = NULL;
  Tasks_t = NULL;
}

int Tasks_isEmpty(){
  if(Tasks_h == NULL)
    return 1;

  return 0;
}

void newTasks_h(struct task *tasks_h){
  Tasks_h = tasks_h;
}

void newTasks_t(struct task *tasks_t){
  Tasks_t = tasks_t;
}

struct task *getTasks_h(){
  return Tasks_h;
}

struct task *getTasks_t(){
  return Tasks_t;
}
