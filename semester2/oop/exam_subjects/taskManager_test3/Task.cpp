#include "Task.h"

Task::Task(const string& desc, int duration, int priority)
    : description(desc), duration(duration), priority(priority) {}

string Task::getDescription() const {
    return description;
}

int Task::getDuration() const {
    return duration;
}

int Task::getPriority() const {
    return priority;
}