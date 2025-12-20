// Created by shayan on 12/11/2025.
#ifndef PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASK_H
#define PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASK_H

#include <iostream>
#include <string>
using namespace std;

struct Task {
    int id;
    string name;
    string description;
    int priority;
    int duration;
    int deadline;

    Task() = default;
    Task(int i, const string &n, const string &desc, int p, int dur, int d)
        : id(i), name(n), description(desc), priority(p), duration(dur), deadline(d) {}

    void display() const {
        cout<<"\n[ID: "<<id<<"] Task: "<<name;
        cout<<"\n Description: "<<description;
        cout<<"\n Priority: "<<priority;
        cout<<"\n Duration: "<<duration;
        cout<<"\n Deadline: "<<deadline<<endl;
    }

    // For priority_queue: higher priority value => higher precedence (top)
    bool operator<(const Task &b) const {
        return priority < b.priority;
    }
};

#endif // PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASK_H
