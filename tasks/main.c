/*2º Projeto de IAED*/
/*João Lopes - 90732*/

#include "commands.h"
#include "tasks.h"

int main(int argc, char *argv[]){

  Tasks_init();

  while(readCommand()){
  } /*Keep reading input if the user has not entered "exit"*/

  return 0;
}
