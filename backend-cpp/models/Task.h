#pragma once

#include <string>

using namespace std;

class Task
{
public:

    int id;

    string title;

    string deadline;      // YYYY-MM-DD

    int estimatedHours;   // e.g. 4

    string category;

    string importance;    // High / Medium / Low

    string status;

    Task(
        int id,
        string title,
        string deadline,
        int estimatedHours,
        string category,
        string importance,
        string status
    );
};