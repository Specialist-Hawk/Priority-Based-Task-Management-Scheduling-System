#include <iostream>
#include "TaskManager.h"
using namespace std;
int main() {
    TaskManager tm;
    tm.addTask(101, "Fix Login", "Fix crash on startup", 10, 30, 2);
    tm.addTask(102, "Do laundry", "Finish all the clothes in my room", 5, 60, 5);
    cout<<"Tetsing Priority Queue"<<endl;
    tm.displayAll();
    tm.getNextTask();
    return 0;
}
// TIP See CLion help at <a
// href="https://www.jetbrains.com/help/clion/">jetbrains.com/help/clion/</a>.
//  Also, you can try interactive lessons for CLion by selecting
//  'Help | Learn IDE Features' from the main menu.