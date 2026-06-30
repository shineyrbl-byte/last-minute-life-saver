#include "RiskAnalyzer.h"
#include "../utils/DateUtils.h"

using namespace std;

string RiskAnalyzer::getRiskLevel(const Task& task)
{
    int days = DateUtils::daysUntil(task.deadline);

    if(days <= 1 && task.estimatedHours >= 4)
        return "High";

    if(days <= 3)
        return "Medium";

    return "Low";
}