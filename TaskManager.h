//
// Created by shayan on 12/11/2025.
//

#ifndef PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKMANAGER_H
#define PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKMANAGER_H

#include<iostream>
#include <queue>
#include<unordered_map> //This si for Hash map
#include <vector>
#include"Task.h"
#include"TaskHolder.h"
using namespace std;

class TaskManager {
    unordered_map<int, Task> tasks;
    priority_queue<Task> taskQueue;
    TaskHolder* historyHead=nullptr;
public:
  void addTask(int id, string name, string desc, int priority, int duration, int deadline) {
      if(tasks.find(id) != tasks.end()) {
          cout<<"Task already exists"<<endl;
          return;
      }
      Task newTask(id, name, desc, priority,duration, deadline);
      tasks.insert({id, newTask});
      taskQueue.push(newTask); //adds to the queue
      cout<<"Task added"<<endl;
  }

  void displayAll() {
      if (tasks.empty()) {
          cout<<"No tasks found"<<endl;
          return;
      }
      cout<<"\nAll Tasks"<<endl;
      for (auto& entry : tasks) {
          entry.second.display();
          cout<<"\n";
      }
  }

  void findTask(int id) {
      if(tasks.find(id) != tasks.end()) {
          cout<<"Task Found:";
          tasks.at(id).display();
      } else {
          cout<<"Task with ID"<<id<<"not found"<<endl;
      }
  }

   void getNextTask() {
      while (!taskQueue.empty()) {
          Task topTask = taskQueue.top();

          if (tasks.find(topTask.id) != tasks.end()) {
              cout<<"\n Recommened Task";
              topTask.display();
              return;
          }
          taskQueue.pop();
      }
      cout<<"\nNo tasks found"<<endl;
  }
   void removeTask(int id) {
      if (tasks.find(id) == tasks.end()) {
          cout<<"Task with ID"<<id<<"not found"<<endl;
          return;
      }
      Task completed = tasks.at(id);
      TaskHolder *newNode = new TaskHolder(completed);
      newNode->next = historyHead;
      historyHead = newNode;
      tasks.erase(id);
      cout<<"\nTask completed"<<endl;
  }
   void History() {
      if (historyHead == nullptr) {
          cout<<"No tasks found in History"<<endl;
          return;
      }
      cout<<"\nTask History"<<endl;
      TaskHolder* current = historyHead;
      while (current != nullptr) {
          cout<<current->task.name <<endl;
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
      tasks.insert({restore.id, restore});
      taskQueue.push(restore);
      historyHead = historyHead->next;
      delete nodeDelete;
  }
};

#endif //PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKMANAGER_H