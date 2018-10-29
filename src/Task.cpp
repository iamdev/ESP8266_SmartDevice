#include "Task.h"
#include <Arduino.h>

void createTask(void (*callback)(void),int interval){
     struct task_t ts = {callback,interval,0}; 
     tasks[taskCount++] = ts;
}

void runTasks(){
    unsigned long t = millis();
    {
        for(int i=0;i<taskCount;i++){
            if(t>(tasks[i].tPrev + tasks[i].loopInterval)){
                tasks[i].tPrev = t;
                tasks[i].callback();
            }
        }   
    }
}