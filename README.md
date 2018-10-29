# TaskRunner

TaskRunner is a library for a Arduino Sketches which can will execute tasks in a cooperative environment. This can be useful for `esp8266` and similar platforms.

## Simple Example

The following simple example will execute the `task_to_execute` function every 1000 milliseconds.

```cpp
#include <Arduino.h>
#include <TaskRunner.h>

TaskRunner tasks;

void task_to_execute() {
    Serial.println("A am a task");
}

void setup() {
    Serial.begin(115200);

    tasks.add([]() {task_to_execute; }, 1000);
}

void loop() {
    tasks.execute();
}
```