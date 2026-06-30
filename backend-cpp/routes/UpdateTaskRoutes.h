#pragma once

#include "../include/httplib.h"
#include "../src/TaskManager.h"

void registerUpdateTaskRoutes(
    httplib::Server& server,
    TaskManager& manager
);