/*2º Projeto de IAED*/
/*João Lopes - 90732*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"
#include "tasks.h"

int readCommand(){
  char command[10], temp; /*Stores the first word from input, the command*/
  int i = 0;

  while((command[i] = getchar()) != ' ' && command[i] != '\n' /*&& argument[i] != '\0'*/){
    i++;
    /*printf("debug : %c\n", command[i - 1]);*/
  }temp = command[i]; command[i] = '\0';

  if(strcmp(command, "add") == 0){
    /*printf("debug : add command called\n");*/
    command_add();
  }
  else if(strcmp(command, "depend") == 0){
    /*printf("depend activated\n");*/
  }
  else if(strcmp(command, "duration") == 0){
    /*printf("duration activated\n");*/
    command_duration(temp);
  }
  else if(strcmp(command, "remove") == 0){
    /*printf("remove activated\n");*/
    /*command_remove();*/
  }
  else if(strcmp(command, "path") == 0){
    /*printf("path activated\n");*/
  }
  else if(strcmp(command, "exit") == 0){
    /*printf("exit activated\n");*/
    return 0;
  }
  else if(strcmp(command, "first") == 0){
    /*printf("first activated\n");*/
    first();
  }
  else{
    printf("illegal arguments\n");
  }

  return 1; /*Exit with success. A command different than 'exit' was read.*/
}

void command_add(){
  unsigned long id, duration, tmpId, ids[1000];
  int i, noSuchTask = 0, tmp2 = 0;
  char caption[caption_maxSize], tmp;
  struct task *temp;

  struct task *ptr;
  ptr = (struct task*) malloc(sizeof(struct task));

  scanf("%lu \"%[^\"]\" %lu", &id, caption, &duration); /*reads id to id, and anything between "" to caption*/
  if(id <= 0){
    while((tmp = getchar()) != '\n'){}
    printf("illegal arguments\n");
    return;
  }
  if(duration <= 0){
    while((tmp = getchar()) != '\n'){}
    printf("illegal arguments\n");
    return;
  }
  /*printf("debug : inserted task id: %lu, caption: \"%s\" and duration: %lu\n", id, caption, duration);*/
  if((tmp = getchar()) != '\n' && tmp == ' '){
      /*printf("debug : add has more arguments\n");*/
      i = 0;
      while(scanf("%lu", &tmpId) == 1){
        ids[i] = tmpId;
        i++;
        if(tmpId <= 0){
          while((tmp = getchar()) != '\n'){}
          printf("illegal arguments\n");
          return;
        }
        noSuchTask = 1;
        temp = getTasks_h();
        while(temp != NULL){
          if(temp -> id == tmpId){
            noSuchTask = 0;
          }
          temp = temp -> next;
        }
        if(noSuchTask == 1){
          tmp2 = 1;
        }
        if((tmp = getchar()) == '\n'){
          ids[i] = -1;
          break;
        }
      }

      if(tmp2 == 1){
        printf("no such task\n");
        return;
      }

      temp = getTasks_h();
      while(temp != NULL){
        if(temp -> id == id){
          printf("id already exists\n");
          return;
        }
        temp = temp -> next;
      }
      if(Tasks_isEmpty()){
        newTasks_h(ptr);
        newTasks_t(ptr);

        ptr -> prev = NULL;
        ptr -> next = NULL;
        ptr -> id = id;
        ptr -> duration = duration;
        ptr -> caption = (char*) malloc(sizeof(char) * (strlen(caption) + 1));
  	    strcpy(ptr -> caption, caption);

        i = 0;
        while(ids[i] != -1){
          ptr -> ids[i] = ids[i];
          i++;
        }ptr -> ids[i] = -1;

      }
      else{
        ptr -> prev = getTasks_t();
        getTasks_t() -> next = ptr;
        newTasks_t(ptr);
        ptr -> next = NULL;
        ptr -> id = id;
        ptr -> duration = duration;
        ptr -> caption = (char*) malloc(sizeof(char) * (strlen(caption) + 1));
  	    strcpy(ptr -> caption, caption);

        i = 0;
        while(ids[i] != -1){
          ptr -> ids[i] = ids[i];
          i++;
        }ptr -> ids[i] = -1;

      }
      /*printf("debug : added %d more arguments\n", i);*/
  }
  else{
    /*add without any dependencies*/
    temp = getTasks_h();
    while(temp != NULL){
      if(temp -> id == id){
        printf("id already exists\n");
        return;
      }
      temp = temp -> next;
    }
    if(Tasks_isEmpty()){
      newTasks_h(ptr);
      newTasks_t(ptr);

      ptr -> prev = NULL;
      ptr -> next = NULL;
      ptr -> id = id;
      ptr -> duration = duration;
      ptr -> caption = (char*) malloc(sizeof(char) * (strlen(caption) + 1));
	    strcpy(ptr -> caption, caption);
      ptr -> ids[0] = -1;
    }
    else{
      ptr -> prev = getTasks_t();
      getTasks_t() -> next = ptr;
      newTasks_t(ptr);
      ptr -> next = NULL;
      ptr -> id = id;
      ptr -> duration = duration;
      ptr -> caption = (char*) malloc(sizeof(char) * (strlen(caption) + 1));
	    strcpy(ptr -> caption, caption);
      ptr -> ids[0] = -1;
    }
  }
  return;
}

void command_duration(char temp){
  int i;
  unsigned long duration;
  struct task *ptr;
  ptr = getTasks_h();

  if(temp == '\n'){
    while(ptr != NULL){
      printf("%lu \"%s\" %lu", ptr -> id, ptr -> caption, ptr -> duration);
      i = 0;
      while(ptr -> ids[i] != -1){
        if(ptr -> ids[i + 1] == -1){
          if(i == 0){
            printf(" %lu", ptr -> ids[i]);
          }
          else{
            printf("%lu", ptr -> ids[i]);
          }
        }
        else{
          if(i == 0){
            printf(" %lu ", ptr -> ids[i]);
          }
          else{
            printf("%lu ", ptr -> ids[i]);
          }
        }
        i++;
      }
      printf("\n");
      ptr = ptr -> next;
    }
  }
  else if(temp == ' '){
    scanf("%lu", &duration);
    getchar();

    while(ptr != NULL){
      if(ptr -> duration >= duration){
        printf("%lu \"%s\" %lu", ptr -> id, ptr -> caption, ptr -> duration);
        i = 0;
        while(ptr -> ids[i] != -1){
          if(ptr -> ids[i + 1] == -1){
            if(i == 0){
              printf(" %lu", ptr -> ids[i]);
            }
            else{
              printf("%lu", ptr -> ids[i]);
            }
          }
          else{
            if(i == 0){
              printf(" %lu ", ptr -> ids[i]);
            }
            else{
              printf("%lu ", ptr -> ids[i]);
            }
          }
          i++;
        }
        printf("\n");
      }
      ptr = ptr -> next;
    }
  }
}

void command_remove(){
  int id;
  struct task *ptr, *tmp1, *tmp2;
  ptr = getTasks_h();

  scanf("%d", &id);
  getchar();

  if(id <= 0){
    printf("illegal arguments\n");
    return;
  }

  while(ptr != NULL){
    if(ptr -> id == id){
      tmp1 = ptr -> prev;
      tmp2 = ptr -> next;
      tmp1 -> next = tmp2;
      tmp2 -> prev = tmp1;
      free(ptr -> caption);
      free(ptr -> ids);
      free(ptr);

      return;
    }
    ptr = ptr -> next;
  }
}

int idExists(long unsigned id){
  struct task *ptr;
  ptr = getTasks_h();

  while(ptr != NULL){
    if(ptr -> id == id){
      return 1;
    }
    ptr = ptr -> next;
  }

  return 0;
}

void first(){
  long unsigned id, idExists = 0;
  char newCaption[caption_maxSize];
  struct task *ptr;
  ptr = getTasks_h();

  scanf("%lu \"%[^\"]\"", &id, newCaption);
  getchar();

  while(ptr != NULL){
    if(ptr -> id == id){
      idExists = 1;
      break;
    }
    ptr = ptr -> next;
  }

  if(idExists){
    free(ptr -> caption);
    ptr -> caption = (char*)  malloc(sizeof(char) * strlen(newCaption) +1);
    strcpy(ptr -> caption, newCaption);
  }
  else{
    printf("no such task\n");
    return;
  }
}
