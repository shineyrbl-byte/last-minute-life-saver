#pragma once

#include "../include/httplib.h"
#include "../src/TaskManager.h"

void registerPriorityRoutes(
    httplib::Server& server,
    TaskManager& manager
);