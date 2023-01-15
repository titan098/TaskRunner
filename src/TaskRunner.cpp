#include "TaskRunner.h"

#include <Arduino.h>

TaskRunner::TaskRunner() {}

TaskRunner::~TaskRunner() {}

void TaskRunner::add(shared_ptr<Task> task) {
    this->tasks.push_back(task);
}

void TaskRunner::add(std::function<void()> task, uint32_t period, bool oneShot) {
    this->tasks.push_back(shared_ptr<Task>(new Task(task, period, oneShot)));
}

void TaskRunner::add(std::function<void()> task, uint32_t period) {
    this->add(task, period, false);
}

void TaskRunner::execute() {
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
}

void TaskRunner::disableAll() {
    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        (*it)->setEnabled(false);
    }
}

void TaskRunner::enableAll() {
    for (auto it = this->tasks.begin(); it != this->tasks.end(); ++it) {
        (*it)->setEnabled(true);
    }
}