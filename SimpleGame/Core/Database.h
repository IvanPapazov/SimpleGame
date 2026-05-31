#pragma once
#include <string>
#include <vector>
#include "PlayerProgress.h"
#include "UserAccount.h"
#include "../../externals/sqlite3/sqlite3.h"

// Equivalent to Data/ApplicationDbContext.cs in FireAndIce
// Owns the database connection and exposes operations on the PlayerProgress table
class Database
{
private:
    sqlite3* m_db = nullptr;

public:
    Database() = default;
    ~Database();

    // Opens (or creates) the .db file at the given path
    void Open(const std::string& path);

    // Creates tables if they don't exist
    void EnsureCreated();

    void Close();

    // PlayerProgress table
    bool                        Insert(const PlayerProgress& progress);
    bool                        Update(const PlayerProgress& progress);
    std::vector<PlayerProgress> GetAll();
    PlayerProgress              GetByUsername(const std::string& username);

    // UserAccount table
    bool                       UA_Insert(const UserAccount& account);
    bool                       UA_SetEntered(const std::string& username);   // sets this user entered=true, all others false
    UserAccount                UA_GetByUsername(const std::string& username);
    std::string                UA_GetLoggedInUsername();                      // returns username where entered=true, or ""
    std::vector<UserAccount>   UA_GetAll();
};
