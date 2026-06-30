#include "AnalyticsRoutes.h"
#include "../include/json.hpp"

using json = nlohmann::json;

void registerAnalyticsRoutes(
    httplib::Server& server,
    TaskManager& manager
)
{
    server.Get("/analytics",
    [&](const httplib::Request&, httplib::Response& res)
    {
        json response = {
            {"totalTasks", manager.getTotalTasks()},
            {"completed", manager.getCompletedTasks()},
            {"pending", manager.getPendingTasks()},
            {"skipped", manager.getSkippedTasks()},
            {"productivityScore", manager.getProductivityScore()}
        };

        res.set_content(response.dump(4), "application/json");
    });
}