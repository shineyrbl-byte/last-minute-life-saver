#include "PlannerRoutes.h"
#include "../include/json.hpp"
#include "../services/PriorityEngine.h"
#include "../services/RiskAnalyzer.h"
#include "../services/RecommendationEngine.h"
#include "../utils/DateUtils.h"

#include <algorithm>
using json = nlohmann::json;
using namespace std;

void registerPlannerRoutes(
    httplib::Server& server,
    TaskManager& manager
)
{
    server.Get("/generate-day",
    [&](const httplib::Request&, httplib::Response& res)
    {
        auto tasks = manager.getAllTasks();

        sort(tasks.begin(), tasks.end(),
        [](const Task& a, const Task& b)
        {
            return PriorityEngine::calculatePriority(a) >
                   PriorityEngine::calculatePriority(b);
        });

        json plan = json::array();

        int startHour = 9;

        for (auto &task : tasks)
        {
            if (task.status == "Completed") continue;

            int endHour = startHour + min(task.estimatedHours, 2);

            plan.push_back({
                {"task", task.title},
                {"time", to_string(startHour) + ":00 - " + to_string(endHour) + ":00"},
                {"risk", RiskAnalyzer::getRiskLevel(task)},
                {"priorityScore", PriorityEngine::calculatePriority(task)},
                {"recommendation", RecommendationEngine::getRecommendation(task)}
            });

            startHour = endHour + 1;
        }

        json response = {
            {"message", "Your day has been planned based on task priority and deadline risk."},
            {"plan", plan}
        };

        res.set_content(response.dump(4), "application/json");
    });
}