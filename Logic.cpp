#include "Logic.h"
#include <fstream>
#include <iostream>
#include <cctype>
void ATM::saveBalance()
{
    std::ifstream archivo("accountinfo.txt");
    std::ofstream temp("temp.txt");
    if(!archivo.is_open() || !temp.is_open())
    {
        return;
    }
    bool found = false;
    std::string acc, key, money;
    while (getline(archivo, acc, ',') &&
       getline(archivo, key, ',') &&
       getline(archivo, money))
    {
        if(acc == user.account)
        {
            temp <<acc<< ","
                 <<key<< ","
                 <<user.balance
                 <<std::endl;
                 found=true;
        }
        else
        {
            temp <<acc<< ","
                 <<key<< ","
                 <<money
                 <<std::endl;
        }
    }
    archivo.close();
    temp.close();
    if(!found)
    {
        remove("temp.txt");
        return;
    }
    remove("accountinfo.txt");
    rename("temp.txt", "accountinfo.txt");
}
bool ATM::validateAccount()
{
    if(user.account.length()!=6)
        return false;
    for(char c:user.account)
        if(!isdigit(c))
            return false;
    if(user.password.length()!=3)
        return false;
    for(char c:user.password)
        if(!isdigit(c))
            return false;
    return true;
}
bool ATM::login(
    const std::string& account,
    const std::string& password)
{
    std::ifstream file("accountinfo.txt");
    std::string acc,key,money;
    while(getline(file,acc,',') &&
        getline(file,key,',') &&
        getline(file,money))
    {
        if(acc==account && key==password)
        {
            user.account=acc;
            user.password=key;
            user.balance=stod(money);
            return true;
        }
    }
    return false;
}
bool ATM::addMoney(double amount)
{
    if(amount<=0)
        return false;
    user.balance+=amount;
    saveBalance();
    return true;
}
bool ATM::withdraw(double amount)
{
    if(amount<=0 || amount>user.balance)
        return false;
    user.balance-=amount;
    saveBalance();
    return true;
}
double ATM::getBalance()
{
    return user.balance;
}
std::string ATM::getAccount()
{
    return user.account;
}