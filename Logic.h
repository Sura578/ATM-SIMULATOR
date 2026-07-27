#ifndef ATM_H
#define ATM_H
#include "Account.h"
#include <string>
class ATM
{
private:
    account user;
public:
    bool validateAccount();
    bool login(
        const std::string& account,
        const std::string& password
    );
    bool addMoney(double amount);
    bool withdraw(double amount);
    double getBalance();
    std::string getAccount();
private:
    void saveBalance();
};
#endif