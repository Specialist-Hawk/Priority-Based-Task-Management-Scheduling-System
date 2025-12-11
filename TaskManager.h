//
// Created by shayan on 12/11/2025.
//

#ifndef PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKMANAGER_H
#define PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKMANAGER_H

#include<iostream>
#include<unordered_map> //This si for Hash map
#include"Task.h"
using namespace std;

class TaskManager {
  unordered_map<int, Task> tasks;
public:
  void addTask(int id, string name, string desc, int priority, int duration, int deadline) {
      if(tasks.find(id) != tasks.end()) {
          cout<<"Task already exists"<<endl;
          return;
      }
      Task newTask(id, name, desc, priority,duration, deadline);
      tasks.insert({id, newTask});
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
          cout<<"Task with ID"<< id <<"not found"<<endl;
      }
  }
};

#endif //PRIORITY_BASED_TASK_MANAGEMENT___SCHEDULING_SYSTEM_TASKMANAGER_H