# TaskRunner

TaskRunner is a library for a Arduino Sketches which can will execute tasks in a cooperative environment. This can be useful for `esp8266` and similar platforms.

## Simple Example

```cpp
#include <Arduino.h>
#include <TaskRunner.h>

TaskRunner tasks;

void task_to_execute() {
    Serial.println("A am a task");
}

void setup() {

}

void loop() {
    tasks.execute();
}
```