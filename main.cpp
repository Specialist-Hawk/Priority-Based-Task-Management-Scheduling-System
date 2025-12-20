#include <iostream>
#include "TaskManager.h"
using namespace std;

int main() {
    TaskManager tm;
    int choice;

    int id, priority, duration, deadline;
    string name, description;
    cout<<"========================================"<<endl;
    cout<<"  PRIORITY-BASED TASK SCHEDULER SYSTEM"<<endl;
    cout<<"========================================"<<endl;
    while (true) {
        cout<<"\nMain Menu"<<endl;
        cout<<"1. Add Task"<<endl;
        cout<<"2. Completed Task"<<endl;
        cout<<"3. Show All Tasks"<<endl;
        cout<<"4. Recommended Task"<<endl;
        cout<<"5. Undo Last Completion"<<endl;
        cout<<"6. View History"<<endl;
        cout<<"0. Exit"<<endl;
        cout<<"Enter choice: ";
        cin>>choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout<<"Enter ID: ";
                cin>>id;
                cin.ignore();
                cout<<"Enter Name: ";
                getline(cin,name);
                cout<<"Enter Description: ";
                getline(cin,description);
                cout<<"Enter Priority (1-10): ";
                cin>>priority;
                cout<<"Enter Duration (Mins): ";
                cin>>duration;
                cout<<"Enter Deadline (Hours): ";
                cin>>deadline;
                tm.addTask(id, name, description, priority, duration, deadline);
                break;
            case 2:
                cout<<"Enter Task ID to remove (complete): ";
                cin>>id;
                tm.removeTask(id);
                break;
            case 3:
                tm.displayAll();
                break;
            case 4:
                tm.getNextTask();
                break;
            case 5:
                tm.undo();
                break;
            case 6:
                tm.History();
                break;
            case 0:
                cout<<"Exiting..."<<endl;
                return 0;
            default:
                cout<<"Invalid choice"<<endl;
        }
    }
}