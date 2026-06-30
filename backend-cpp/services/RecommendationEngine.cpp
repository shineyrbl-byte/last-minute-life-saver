#include "RecommendationEngine.h"
#include "PriorityEngine.h"
#include "RiskAnalyzer.h"
#include "../utils/DateUtils.h"

using namespace std;

string RecommendationEngine::getRecommendation(const Task& task)
{
    int priority = PriorityEngine::calculatePriority(task);

    string risk = RiskAnalyzer::getRiskLevel(task);

    int days = DateUtils::daysUntil(task.deadline);

    if (task.status == "Completed")
        return "Task completed. Great job!";

    if (risk == "High")
        return "Start immediately. This task is at high risk of missing its deadline.";

    if (priority >= 80)
        return "Complete at least half of this task today.";

    if (days > 7)
        return "You can safely postpone this task for now.";

    return "Try to make some progress today.";
}