#pragma once
#include <string>

struct PlayerProgress
{
    int         id       = 0;
    std::string username;
    int         maxLevel = 1;
    std::string date;       // stored as ISO string: YYYY-MM-DD
};
