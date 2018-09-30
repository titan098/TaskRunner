#include "Task.h"

Task::Task(std::function<void ()> task, uint32_t taskPeriod) : Task(task, taskPeriod, false) {
}

Task::Task(std::function<void ()> task, uint32_t taskPeriod, bool oneShot) {
    this->task = task;
    this->taskPeriod = taskPeriod;
    this->oneShot = oneShot;
    this->executed = false;
    this->enabled = true;

    this->previousMillis = millis();
}

bool Task::execute(uint64_t currentMillis) {
    if (!this->enabled) {
        return false;
    }

    if (this->oneShot && this->executed) {
        return false;
    }

    if (currentMillis - this->previousMillis >= this->taskPeriod) {
        this->previousMillis = currentMillis;
        (this->task)();
        this->executed = true;
        return true;
    }
    return false;
}

bool Task::isOneShot() const {
    return this->oneShot;
}

bool Task::hasExecuted() const {
    return this->executed;
}

void Task::setEnabled(bool enabled) {
    this->enabled = enabled;
}

bool Task::isEnabled() const {
    return this->enabled;
}

