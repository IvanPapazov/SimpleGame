#pragma once
#include <string>

struct UserAccount
{
    int         id       = 0;
    std::string username;
    std::string password;
    bool        entered  = false;
};
