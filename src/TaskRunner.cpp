#include "TaskRunner.h"

#include <Arduino.h>

TaskRunner::TaskRunner() {}

TaskRunner::~TaskRunner() {}

void TaskRunner::add(shared_ptr<Task> task) {
    this->taskMutex.lock();
    this->tasks.push_back(task);
    this->taskMutex.unlock();
}

void TaskRunner::add(std::function<void()> task, uint32_t period, bool oneShot) {
    this->taskMutex.lock();
    this->tasks.push_back(shared_ptr<Task>(new Task(task, period, oneShot)));
    this->taskMutex.unlock();
}

void TaskRunner::add(std::function<void()> task, uint32_t period) {
    this->add(task, period, false);
}

void TaskRunner::execute() {
    this->taskMutex.lock();
    this->currentMillis = millis();
    bool did_execute = false;

    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        did_execute |= (*it)->execute(currentMillis);
    }

    if (did_execute) {
        this->tasks.erase(std::remove_if(this->tasks.begin(),
                                         this->tasks.end(),
                                         [](shared_ptr<Task> x) { return x->isOneShot() && x->hasExecuted(); }),
                          this->tasks.end());
    }
    this->taskMutex.unlock();
}

void TaskRunner::disableAll() {
    this->taskMutex.lock();
    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        (*it)->setEnabled(false);
    }
    this->taskMutex.unlock();
}

void TaskRunner::enableAll() {
    this->taskMutex.lock();
    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        (*it)->setEnabled(true);
    }
    this->taskMutex.unlock();
}