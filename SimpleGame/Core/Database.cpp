#include "stdafx.h"
#include "Database.h"
#include <iostream>

Database::~Database()
{
    Close();
}

void Database::Open(const std::string& path)
{
    if (sqlite3_open(path.c_str(), &m_db) != SQLITE_OK)
    {
        std::cerr << "Database::Open failed: " << sqlite3_errmsg(m_db) << std::endl;
    }
}

// Equivalent to EF Core: context.Database.EnsureCreated()
// Runs the CREATE TABLE IF NOT EXISTS — no separate migration command needed
void Database::EnsureCreated()
{
    const char* sql =
        "CREATE TABLE IF NOT EXISTS PlayerProgress ("
        "  Id       INTEGER PRIMARY KEY AUTOINCREMENT, "
        "  Username TEXT    NOT NULL, "
        "  MaxLevel INTEGER NOT NULL DEFAULT 1, "
        "  Date     TEXT    NOT NULL"
        ");"
        "CREATE TABLE IF NOT EXISTS UserAccount ("
        "  Id       INTEGER PRIMARY KEY AUTOINCREMENT, "
        "  Username TEXT    NOT NULL UNIQUE, "
        "  Password TEXT    NOT NULL, "
        "  Entered  INTEGER NOT NULL DEFAULT 0"
        ");";

    char* errMsg = nullptr;
    if (sqlite3_exec(m_db, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "Database::EnsureCreated failed: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

void Database::Close()
{
    if (m_db)
    {
        sqlite3_close(m_db);
        m_db = nullptr;
    }
}

bool Database::Insert(const PlayerProgress& progress)
{
    const char* sql =
        "INSERT INTO PlayerProgress (Username, MaxLevel, Date) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, progress.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int (stmt, 2, progress.maxLevel);
    sqlite3_bind_text(stmt, 3, progress.date.c_str(),     -1, SQLITE_TRANSIENT);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

bool Database::Update(const PlayerProgress& progress)
{
    const char* sql =
        "UPDATE PlayerProgress SET MaxLevel = ?, Date = ? WHERE Username = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_int (stmt, 1, progress.maxLevel);
    sqlite3_bind_text(stmt, 2, progress.date.c_str(),     -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, progress.username.c_str(), -1, SQLITE_TRANSIENT);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

std::vector<PlayerProgress> Database::GetAll()
{
    std::vector<PlayerProgress> results;
    const char* sql = "SELECT Id, Username, MaxLevel, Date FROM PlayerProgress;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return results;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        PlayerProgress p;
        p.id       = sqlite3_column_int (stmt, 0);
        p.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        p.maxLevel = sqlite3_column_int (stmt, 2);
        p.date     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        results.push_back(p);
    }

    sqlite3_finalize(stmt);
    return results;
}

PlayerProgress Database::GetByUsername(const std::string& username)
{
    PlayerProgress result;
    const char* sql =
        "SELECT Id, Username, MaxLevel, Date FROM PlayerProgress WHERE Username = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return result;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result.id       = sqlite3_column_int (stmt, 0);
        result.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        result.maxLevel = sqlite3_column_int (stmt, 2);
        result.date     = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
    }

    sqlite3_finalize(stmt);
    return result;
}

// ── UserAccount ──────────────────────────────────────────────────────────────

bool Database::UA_Insert(const UserAccount& account)
{
    const char* sql =
        "INSERT INTO UserAccount (Username, Password, Entered) VALUES (?, ?, ?);";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, account.username.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, account.password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int (stmt, 3, account.entered ? 1 : 0);

    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

bool Database::UA_SetEntered(const std::string& username)
{
    // First set all users entered = false
    {
        const char* sql = "UPDATE UserAccount SET Entered = 0;";
        char* errMsg = nullptr;
        sqlite3_exec(m_db, sql, nullptr, nullptr, &errMsg);
        if (errMsg) sqlite3_free(errMsg);
    }
    // Then set the specific user entered = true
    const char* sql = "UPDATE UserAccount SET Entered = 1 WHERE Username = ?;";
    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return false;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);
    bool ok = sqlite3_step(stmt) == SQLITE_DONE;
    sqlite3_finalize(stmt);
    return ok;
}

UserAccount Database::UA_GetByUsername(const std::string& username)
{
    UserAccount result;
    const char* sql =
        "SELECT Id, Username, Password, Entered FROM UserAccount WHERE Username = ?;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return result;

    sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        result.id       = sqlite3_column_int (stmt, 0);
        result.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        result.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        result.entered  = sqlite3_column_int(stmt, 3) != 0;
    }

    sqlite3_finalize(stmt);
    return result;
}

std::string Database::UA_GetLoggedInUsername()
{
    const char* sql =
        "SELECT Username FROM UserAccount WHERE Entered = 1 LIMIT 1;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return "";

    std::string name;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        const char* text = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (text) name = text;
    }

    sqlite3_finalize(stmt);
    return name;
}

std::vector<UserAccount> Database::UA_GetAll()
{
    std::vector<UserAccount> results;
    const char* sql = "SELECT Id, Username, Password, Entered FROM UserAccount;";

    sqlite3_stmt* stmt = nullptr;
    if (sqlite3_prepare_v2(m_db, sql, -1, &stmt, nullptr) != SQLITE_OK)
        return results;

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        UserAccount a;
        a.id       = sqlite3_column_int (stmt, 0);
        a.username = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        a.password = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        a.entered  = sqlite3_column_int(stmt, 3) != 0;
        results.push_back(a);
    }

    sqlite3_finalize(stmt);
    return results;
}
