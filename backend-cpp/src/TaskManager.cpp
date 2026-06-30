#include "TaskManager.h"

TaskManager::TaskManager() {
    nextId = 1;
}

Task TaskManager::addTask(
    string title,
    string deadline,
    int estimatedHours,
    string category,
    string importance
) {
    Task task(
        nextId,
        title,
        deadline,
        estimatedHours,
        category,
        importance,
        "Pending"
    );

    tasks.push_back(task);
    nextId++;

    return task;
}

vector<Task> TaskManager::getAllTasks() {
    return tasks;
}

bool TaskManager::updateTaskStatus(int id, string status) {
    for (auto &task : tasks) {
        if (task.id == id) {
            task.status = status;
            return true;
        }
    }
    return false;
}

int TaskManager::getTotalTasks() {
    return tasks.size();
}

int TaskManager::getCompletedTasks() {
    int count = 0;
    for (auto &task : tasks) {
        if (task.status == "Completed") count++;
    }
    return count;
}

int TaskManager::getPendingTasks() {
    int count = 0;
    for (auto &task : tasks) {
        if (task.status == "Pending") count++;
    }
    return count;
}

int TaskManager::getSkippedTasks() {
    int count = 0;
    for (auto &task : tasks) {
        if (task.status == "Skipped") count++;
    }
    return count;
}

double TaskManager::getProductivityScore() {
    int total = getTotalTasks();

    if (total == 0) return 0;

    return (getCompletedTasks() * 100.0) / total;
}