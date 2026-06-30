#include "DateUtils.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>

using namespace std;

int DateUtils::daysUntil(const string& deadline)
{
    tm target = {};

    istringstream ss(deadline);

    ss >> get_time(&target, "%Y-%m-%d");

    auto now = chrono::system_clock::now();

    time_t nowTime = chrono::system_clock::to_time_t(now);

    tm today = *localtime(&nowTime);

    time_t targetTime = mktime(&target);

    time_t todayTime = mktime(&today);

    double diff =
        difftime(targetTime, todayTime);

    return static_cast<int>(diff / (60 * 60 * 24));
}