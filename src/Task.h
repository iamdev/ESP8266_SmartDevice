#ifndef _TASK_H
#define _TASK_H
#define MAX_TASK 5
struct task_t{
    void (*callback)(void);
    int loopInterval;
    unsigned long tPrev;
};

static task_t tasks[MAX_TASK];
static int taskCount = 0;

void createTask(void (*callback)(void),int interval);
void runTasks();
#endif