#pragma once

#include "../include/httplib.h"
#include "../src/TaskManager.h"

void registerTaskRoutes(
    httplib::Server& server,
    TaskManager& manager
);