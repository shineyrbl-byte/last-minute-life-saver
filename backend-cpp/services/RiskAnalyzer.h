#pragma once

#include "../models/Task.h"
#include <string>

class RiskAnalyzer
{
public:
    static std::string getRiskLevel(const Task& task);
};