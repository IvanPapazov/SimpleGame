#include "stdafx.h"
#include "DatabaseInitializer.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <ctime>

// Inserts a default row only if the table is empty
void DatabaseInitializer::Seed(Database& db)
{
    if (!db.GetAll().empty())
        return; // already has data, nothing to seed

    // Get today's date as YYYY-MM-DD
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
    localtime_s(&tm, &t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d");

    PlayerProgress defaultPlayer;
    defaultPlayer.username = "Player1";
    defaultPlayer.maxLevel = 1;
    defaultPlayer.date     = oss.str();

    db.Insert(defaultPlayer);
}
