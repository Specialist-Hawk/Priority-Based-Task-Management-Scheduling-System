//
// Created by shayan on 12/13/2025.
//

#ifndef PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKHOLDER_H
#define PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKHOLDER_H
#include "Task.h"
struct TaskHolder{
    Task task;
    TaskHolder* next;
    Task Node(Task t) {
        task = t;
        next = NULL;
    }
};
#endif //PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKHOLDER_H