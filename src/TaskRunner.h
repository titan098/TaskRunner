#ifndef __TASKRUNNER_H
#define __TASKRUNNER_H

#include <algorithm>
#include <memory>
#include <vector>
#include <mutex>

#include <Arduino.h>

#include "Task.h"

using namespace std;

class TaskRunner {
   public:
    TaskRunner();
    virtual ~TaskRunner();

    void add(shared_ptr<Task> task);
    void add(function<void ()> task, uint32_t period);
    void add(function<void ()> task, uint32_t period, bool oneShot);

    void execute();

    void disableAll();
    void enableAll();

   private:
    unsigned int taskCounter = 0;
    unsigned long currentMillis;

    vector<shared_ptr<Task>> tasks;
    mutex taskMutex;
};

#endif