#pragma once

#include "../models/Task.h"
#include <string>
#include <vector>

class GeminiService
{
public:
    static std::string generateDayPlan(const std::vector<Task>& tasks);
};