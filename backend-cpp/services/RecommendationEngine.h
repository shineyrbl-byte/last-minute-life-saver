#pragma once

#include "../models/Task.h"
#include <string>

class RecommendationEngine
{
public:
    static std::string getRecommendation(const Task& task);
};