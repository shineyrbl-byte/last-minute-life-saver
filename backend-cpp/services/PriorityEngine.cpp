#include "../utils/DateUtils.h"
#include "PriorityEngine.h"
#include <algorithm>
using namespace std;

int PriorityEngine::calculatePriority(const Task& task) {
    int score = 0;

    if (task.importance == "High") score += 30;
    else if (task.importance == "Medium") score += 20;
    else score += 10;

    if (task.estimatedHours >= 4) score += 20;
    else if (task.estimatedHours >= 2) score += 10;
    else score += 5;

    int days = DateUtils::daysUntil(task.deadline);

    if (days <= 1)
        score += 50;
    else if (days <= 3)
        score += 35;
    else if (days <= 7)
        score += 20;
    else
        score += 10;

    if (task.status == "Completed") score = 0;
    if (task.status == "Skipped") score += 10;

    return min(score, 100);
}