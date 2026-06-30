#include "UpdateTaskRoutes.h"
#include "../include/json.hpp"

using json = nlohmann::json;

void registerUpdateTaskRoutes(
    httplib::Server& server,
    TaskManager& manager
)
{
    server.Put("/tasks/status",
    [&](const httplib::Request& req,
        httplib::Response& res)
    {
        json body = json::parse(req.body);

        bool success =
            manager.updateTaskStatus(
                body["id"],
                body["status"]
            );

        json response;

        if(success)
        {
            response["message"] =
                "Task updated successfully";
        }
        else
        {
            response["message"] =
                "Task not found";
        }

        res.set_content(
            response.dump(4),
            "application/json"
        );
    });
}