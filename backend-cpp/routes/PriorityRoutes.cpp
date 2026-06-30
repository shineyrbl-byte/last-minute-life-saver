#include "PriorityRoutes.h"
#include "../include/json.hpp"
#include "../services/PriorityEngine.h"
#include "../services/RiskAnalyzer.h"
#include "../utils/DateUtils.h"
#include "../services/RecommendationEngine.h"

#include <algorithm>
#include <string>

using json = nlohmann::json;
using namespace std;

void registerPriorityRoutes(
    httplib::Server& server,
    TaskManager& manager
)
{
    server.Get("/priority",
    [&](const httplib::Request&, httplib::Response& res)
    {
        auto tasks = manager.getAllTasks();

        json result = json::array();

        for (auto &task : tasks)
        {
            int priority = PriorityEngine::calculatePriority(task);
            string risk = RiskAnalyzer::getRiskLevel(task);
            string recommendation = RecommendationEngine::getRecommendation(task);
            int daysRemaining = DateUtils::daysUntil(task.deadline);
            
            result.push_back({
                {"id", task.id},
                {"title", task.title},
                {"deadline", task.deadline},
                {"estimatedHours", task.estimatedHours},
                {"importance", task.importance},
                {"status", task.status},
                {"priorityScore", priority},
                {"risk", risk},
                {"daysRemaining", daysRemaining},
                {"recommendation", recommendation}
            });
        }

        sort(result.begin(), result.end(),
        [](const json& a, const json& b)
        {
            return a["priorityScore"] > b["priorityScore"];
        });

        res.set_content(result.dump(4), "application/json");
    });
}