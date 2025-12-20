//
// Created by shayan on 12/13/2025.
//

#ifndef PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASKHOLDER_H
#define PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASKHOLDER_H

#include "Task.h"

// Simple singly-linked node to store completed tasks (history)
struct TaskHolder {
    Task task;
    TaskHolder* next;

    // Constructor
    TaskHolder(const Task &t) : task(t), next(nullptr) {}
};

#endif // PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASKHOLDER_H