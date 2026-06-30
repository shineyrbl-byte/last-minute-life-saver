#pragma once

#include "../include/httplib.h"
#include "../src/TaskManager.h"

void registerPlannerRoutes(
    httplib::Server& server,
    TaskManager& manager
);