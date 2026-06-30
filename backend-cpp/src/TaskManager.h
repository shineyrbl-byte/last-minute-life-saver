#pragma once
#include "../models/Task.h"
#include <vector>
#include <string>
using namespace std;

class TaskManager {
private:
    vector<Task> tasks;
    int nextId;

public:
    TaskManager();

    Task addTask(
        string title,
        string deadline,
        int estimatedHours,
        string category,
        string importance
    );

    vector<Task> getAllTasks();

    bool updateTaskStatus(int id, string status);

    int getTotalTasks();
    int getCompletedTasks();
    int getPendingTasks();
    int getSkippedTasks();
    double getProductivityScore();
};