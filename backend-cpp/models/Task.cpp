#include "Task.h"

Task::Task(
    int id,
    string title,
    string deadline,
    int estimatedHours,
    string category,
    string importance,
    string status
)
{
    this->id = id;
    this->title = title;
    this->deadline = deadline;
    this->estimatedHours = estimatedHours;
    this->category = category;
    this->importance = importance;
    this->status = status;
}