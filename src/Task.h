#ifndef __TASK_H
#define __TASK_H

#include <Arduino.h>

#include <functional>


class Task {
public:
    Task(std::function<void ()> task, uint32_t taskPeriod);
    Task(std::function<void ()> task, uint32_t taskPeriod, bool oneShot);

    bool execute(uint64_t currentMillis);
    
    void setEnabled(bool enabled);
    bool isEnabled() const;

    bool isOneShot() const;
    bool hasExecuted() const;

private:
    std::function<void ()> task;
    uint64_t previousMillis;
    uint32_t taskPeriod;
    bool oneShot;
    bool executed;
    bool enabled;
};

#endif