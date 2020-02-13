/*2º Projeto de IAED*/
/*João Lopes - 90732*/

struct task{
  unsigned long id, duration;
  char *caption;
  unsigned long ids[1000];

  struct task *prev, *next;
};

void Tasks_init();
int Tasks_isEmpty();
void newTasks_h(struct task *tasks_h);
void newTasks_t(struct task *tasks_t);
struct task *getTasks_h();
struct task *getTasks_t();
