#include "include/httplib.h"
#include "src/TaskManager.h"
#include "routes/TaskRoutes.h"
#include "routes/AnalyticsRoutes.h"
#include "routes/UpdateTaskRoutes.h"
#include "routes/PriorityRoutes.h"
#include "routes/PlannerRoutes.h"

#include <iostream>
using namespace std;

int main()
{
    httplib::Server server;
    TaskManager manager;

    server.set_post_routing_handler([](const httplib::Request&, httplib::Response& res) {
        res.set_header("Access-Control-Allow-Origin", "*");
        res.set_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.set_header("Access-Control-Allow-Headers", "Content-Type");
    });
    
    server.Options(".*", [](const httplib::Request&, httplib::Response& res) {
        res.status = 204;
    });

    server.Get("/", [](const httplib::Request&, httplib::Response& res)
    {
        res.set_content("Last-Minute Life Saver Backend Running", "text/plain");
    });

    registerTaskRoutes(server, manager);
    registerAnalyticsRoutes(server, manager);
    registerUpdateTaskRoutes(server, manager);
    registerPriorityRoutes(server, manager);
    registerPlannerRoutes(server, manager);

    cout << "Server running on http://localhost:8080\n";

    server.listen("0.0.0.0", 8080);

    return 0;
}