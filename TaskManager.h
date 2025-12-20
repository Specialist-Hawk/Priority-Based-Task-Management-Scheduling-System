//
// Created by shayan on 12/11/2025.
//

// TaskManager.h
#ifndef PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASKMANAGER_H
#define PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASKMANAGER_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

#include "Task.h"
#include "TaskHolder.h"

using namespace std;

class TaskManager {
    unordered_map<int, Task> tasks;      // incomplete/current tasks
    priority_queue<Task> taskQueue;      // for recommendation (highest priority first)
    TaskHolder* historyHead = nullptr;   // completed tasks (linked list, newest at head)

    // files
    const string incompleteFile = "incomplete_tasks.txt";
    const string completedFile = "completed_tasks.txt";

public:
    TaskManager() {
        loadIncompleteTasks();
        loadCompletedTasks();
    }

    ~TaskManager() {
        // ensure current state is persisted
        saveIncompleteTasks();
        saveCompletedTasks();
        // free history nodes
        while (historyHead) {
            TaskHolder* tmp = historyHead;
            historyHead = historyHead->next;
            delete tmp;
        }
    }

    void addTask(int id, const string &name, const string &desc, int priority, int duration, int deadline) {
        if(tasks.find(id) != tasks.end()) {
            cout<<"Task already exists"<<endl;
            return;
        }
        Task newTask(id, name, desc, priority, duration, deadline);
        tasks.insert({id, newTask});
        taskQueue.push(newTask); // adds to the priority queue
        cout<<"Task added"<<endl;
        saveIncompleteTasks();
    }

    void displayAll() {
        if (tasks.empty()) {
            cout<<"No tasks found"<<endl;
            return;
        }
        cout<<"\nAll Tasks"<<endl;
        for (const auto& entry : tasks) {
            entry.second.display();
            cout<<"\n";
        }
    }

    void findTask(int id) {
        if(tasks.find(id) != tasks.end()) {
            cout<<"Task Found:";
            tasks.at(id).display();
        } else {
            cout<<"Task with ID "<<id<<" not found"<<endl;
        }
    }

    void getNextTask() {
        while (!taskQueue.empty()) {
            Task topTask = taskQueue.top();
            // Verify it still exists in tasks (not completed)
            if (tasks.find(topTask.id) != tasks.end()) {
                cout<<"\nRecommended Task";
                topTask.display();
                return;
            }
            taskQueue.pop();
        }
        cout<<"\nNo tasks found"<<endl;
    }

    void removeTask(int id) {
        if (tasks.find(id) == tasks.end()) {
            cout<<"Task with ID "<<id<<" not found"<<endl;
            return;
        }
        Task completed = tasks.at(id);
        // push to history (at head)
        TaskHolder *newNode = new TaskHolder(completed);
        newNode->next = historyHead;
        historyHead = newNode;

        // remove from current tasks
        tasks.erase(id);
        cout<<"\nTask completed"<<endl;

        saveIncompleteTasks();
        saveCompletedTasks();
    }

    void History() {
        if (historyHead == nullptr) {
            cout<<"No tasks found in History"<<endl;
            return;
        }
        cout<<"\nTask History (most recent first)"<<endl;
        TaskHolder* current = historyHead;
        while (current != nullptr) {
            cout << "[ID: " << current->task.id << "] " << current->task.name << " (Priority: " << current->task.priority << ")" << endl;
            current = current->next;
        }
    }

    void undo() {
        if (historyHead == nullptr) {
            cout<<"No tasks found in History"<<endl;
            return;
        }
        TaskHolder* nodeDelete = historyHead;
        Task restore = nodeDelete->task;
        // restore to tasks and queue
        tasks.insert({restore.id, restore});
        taskQueue.push(restore);

        // pop from history
        historyHead = historyHead->next;
        delete nodeDelete;

        cout<<"Undo successful. Task restored: "<<restore.name<<endl;
        saveIncompleteTasks();
        saveCompletedTasks();
    }

private:
    // ---------- File handling helpers ----------
    void saveIncompleteTasks() {
        ofstream out(incompleteFile, ios::trunc);
        if (!out.is_open()) {
            cerr << "Error: couldn't open " << incompleteFile << " for writing." << endl;
            return;
        }
        // Write each task as: id|name|description|priority|duration|deadline
        for (const auto &entry : tasks) {
            const Task &t = entry.second;
            // replace any '|' in strings if necessary (simple escape) - here we just assume user won't use '|'
            out << t.id << "|" << t.name << "|" << t.description << "|" << t.priority << "|" << t.duration << "|" << t.deadline << "\n";
        }
        out.close();
    }

    void saveCompletedTasks() {
        ofstream out(completedFile, ios::trunc);
        if (!out.is_open()) {
            cerr << "Error: couldn't open " << completedFile << " for writing." << endl;
            return;
        }
        // walk history and save nodes. newest first (head -> ...)
        TaskHolder* curr = historyHead;
        while (curr != nullptr) {
            const Task &t = curr->task;
            out << t.id << "|" << t.name << "|" << t.description << "|" << t.priority << "|" << t.duration << "|" << t.deadline << "\n";
            curr = curr->next;
        }
        out.close();
    }

    void loadIncompleteTasks() {
        ifstream in(incompleteFile);
        if (!in.is_open()) {
            // file may not exist yet - no problem
            return;
        }
        string line;
        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string part;
            int id, priority, duration, deadline;
            string name, desc;

            if (!getline(ss, part, '|')) continue;
            id = stoi(part);
            if (!getline(ss, name, '|')) name = "";
            if (!getline(ss, desc, '|')) desc = "";
            if (!getline(ss, part, '|')) part = "0"; priority = stoi(part);
            if (!getline(ss, part, '|')) part = "0"; duration = stoi(part);
            if (!getline(ss, part)) part = "0"; deadline = stoi(part);

            Task t(id, name, desc, priority, duration, deadline);
            tasks[id] = t;
            taskQueue.push(t);
        }
        in.close();
    }

    void loadCompletedTasks() {
        ifstream in(completedFile);
        if (!in.is_open()) {
            return;
        }
        string line;
        // We'll push each loaded task onto the history list so order matches file (first line becomes newest head)
        // If you want file order to be oldest->newest, change insertion logic accordingly.
        while (getline(in, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string part;
            int id, priority, duration, deadline;
            string name, desc;

            if (!getline(ss, part, '|')) continue;
            id = stoi(part);
            if (!getline(ss, name, '|')) name = "";
            if (!getline(ss, desc, '|')) desc = "";
            if (!getline(ss, part, '|')) part = "0"; priority = stoi(part);
            if (!getline(ss, part, '|')) part = "0"; duration = stoi(part);
            if (!getline(ss, part)) part = "0"; deadline = stoi(part);

            Task t(id, name, desc, priority, duration, deadline);
            TaskHolder* node = new TaskHolder(t);
            node->next = historyHead;
            historyHead = node;
        }
        in.close();
    }
};

#endif // PRIORITY_BASED_TASK_MANAGEMENT_SCHEDULER_TASKMANAGER_H