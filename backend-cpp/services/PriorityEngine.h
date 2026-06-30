#pragma once

#include "../models/Task.h"

class PriorityEngine {
public:
    static int calculatePriority(const Task& task);
};