#include <iostream>
#include <fstream>
#include <cstdio>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <string>
#include <cctype>
#include<vector>
using namespace std;
void cleaner(void)
{
    cout<<"Goodbye User\n";
    this_thread::sleep_for(chrono::seconds(2));
    cout << "\033[2J\033[1;1H";
}
struct iniaccount
{
    string account="", password="";
    double balance=0, amount=0;  
};
class atm
{
    private:
    iniaccount iniaccount;
    public:
    atm(string account,string password, double balance)
    {
    iniaccount.account = account;
    iniaccount.password = password;
    iniaccount.balance = balance;
    }
bool validator(int &opc)
{
    cin>>opc;
    if(cin.fail())
    {
        cin.clear();
        cin.ignore(1000,'\n');
        opc=9999; //THIS IS TO AVOID TO CLOSE THE ATM IN CASE OF AN DIGIT DURING THE MAIN MENU
        return false;
    }
    return true;
}
void uivalidateaccount()
{
    cout<<"Enter account number"<<endl;
    cin>>iniaccount.account;
    cout<<"Enter security number"<<endl;
    cin>>iniaccount.password;
    if(!validateaccount())
    {
        cout<<"Account number or password in incorrect format \nFormart account 6 numbers\nFomar password 3 digits \n";
    }
    else 
    uilogin();
}
bool validateaccount()
{
    if(iniaccount.account.length()!=6)
    {
        return false;
    }
    for(char c:iniaccount.account)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }
    if(iniaccount.password.length()!=3)
    {
        return false;
    }
    for(char c:iniaccount.password)
    {
        if(!isdigit(c))
        {
            return false;
        }
    }
    return true;
}
void uilogin()
{
    if(!login()) cout<<"Sign in Failed\nUsername or password incorrect\n";
    return;
}
void uigetdatabase()
{
    if(!validateaccount())
    cout<<"Error while trying to get database \n";
}
bool login()
{
    ifstream archivo("accountinfo.txt");
    string acc, key, money;
    while(getline(archivo, acc, ',') &&
          getline(archivo, key, ',') &&
          getline(archivo, money))
    {
        if(iniaccount.account == acc &&
           iniaccount.password == key)
        {
            iniaccount.balance = stod(money);
            return true;
        }
    }
    return false;
}
void lookmoney()
{
    if(login())
    {
        cout<<"Account number "<<iniaccount.account<<" \nCurrent balance "<<iniaccount.balance<<endl;
    }
    else cout<<"not working"<<endl;
}
void savebalance()
{
    ifstream archivo("accountinfo.txt");
    ofstream temp("temp.txt");
    if(!archivo.is_open() || !temp.is_open())
    {
        return;
    }
    string acc, key, money;
    bool found = false;
    while(getline(archivo, acc, ',') &&
          getline(archivo, key, ',') &&
          getline(archivo, money))
    {
        if(acc == iniaccount.account && key == iniaccount.password)
        {
            temp << acc << ","
                 << key << ","
                 << iniaccount.balance
                 << endl;

            found = true;
        }
        else
        {
            temp << acc << ","
                 << key << ","
                 << money
                 << endl;
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
void uiadd()
{
    if(!login())return;
    cout<<"Type amount to add\n";
    cin>>iniaccount.amount;
    if(!addlogic())
    {
        cout<<"Invalid amount \n";
        return;
    }
    else
    {
    savebalance();
    cout<<"New balance "<<iniaccount.balance<<endl;
    return;
    }
}
bool addlogic()
{
    if(!(iniaccount.amount) || iniaccount.amount<=0)
    {
    return false;
    }
    iniaccount.balance=iniaccount.balance+iniaccount.amount;
    return true;
}
void uiwithdrawal()
{
    if(!login())return;
    cout<<"Type withdrawal amount \n";
    cin>>iniaccount.amount;
    if(!wihdrawallogic())
    {
        cout<<"Invalid amount \n";
        return;
    }
    else
    {
    savebalance();
    cout<<"New balance "<<iniaccount.balance<<endl;
    return;
    }
}
bool wihdrawallogic()
{
    if(!iniaccount.amount || iniaccount.amount<=0)
    {
    return false;
    }
    if(iniaccount.amount>iniaccount.balance || iniaccount.amount<=0)
    {
        return false;
    }
    iniaccount.balance=iniaccount.balance-iniaccount.amount;
    return true;
}
};
int main()
{
    atm interacion("", "", 0);
    int opc=1;
    while(opc!=0)
    {
        cout<<"====================ATM===========================\n"<<"Hello User"<<endl;
        cout<<"Select your option: \n 1: For withdrawal \n 2: For paymoney \n 3: Look balance \n 0: Exit \n====================ATM===========================\n";
        interacion.validator(opc);
        switch (opc)
        {
        case 1:
        interacion.uivalidateaccount();
        interacion.uiwithdrawal();
        cleaner();
        break;
        case 2:
        interacion.uivalidateaccount();
        interacion.uiadd();
        cleaner();
        break;
        case 3:
        interacion.uivalidateaccount();
        interacion.lookmoney();
        cleaner();
        break;
        case 0:
        cout<<"Bye\n"; break;
        default:
        cout<<"Invalid option"<<endl;
        cleaner();
        break;
        }
    }
    return 0;
}