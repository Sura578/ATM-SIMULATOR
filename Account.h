#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <string>
struct account
{
    std::string account;
    std::string password;
    double balance=0;
    double amount=0;
};
#endif