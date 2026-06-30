#include "TaskRoutes.h"
#include "../include/json.hpp"

using json = nlohmann::json;

void registerTaskRoutes(
    httplib::Server& server,
    TaskManager& manager
)
{
    server.Get("/tasks",
    [&](const httplib::Request&, httplib::Response& res)
    {
        json taskList = json::array();

        auto tasks = manager.getAllTasks();

        for(auto &task : tasks)
        {
            taskList.push_back({
                {"id", task.id},
                {"title", task.title},
                {"deadline", task.deadline},
                {"estimatedHours", task.estimatedHours},
                {"category", task.category},
                {"importance", task.importance},
                {"status", task.status}
            });
        }

        res.set_content(taskList.dump(4), "application/json");
    });

    server.Post("/tasks",
    [&](const httplib::Request& req, httplib::Response& res)
    {
        json body = json::parse(req.body);

        Task task = manager.addTask(
            body["title"],
            body["deadline"],
            body["estimatedHours"],
            body["category"],
            body["importance"]
        );

        json response = {
            {"message","Task added successfully"},
            {"task",
            {
                {"id",task.id},
                {"title",task.title},
                {"deadline",task.deadline},
                {"estimatedHours",task.estimatedHours},
                {"category",task.category},
                {"importance",task.importance},
                {"status",task.status}
            }}
        };

        res.set_content(response.dump(4),"application/json");
    });
}