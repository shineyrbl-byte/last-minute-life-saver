#pragma once

#include "../include/httplib.h"
#include "../src/TaskManager.h"

void registerAnalyticsRoutes(
    httplib::Server& server,
    TaskManager& manager
);