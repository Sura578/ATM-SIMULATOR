#include "UI.h"
#include "Logic.cpp"
#include <iostream>
using namespace std;
bool UI::loginScreen()
{
    string account;
    string password;
    cout<<"Account number: ";
    cin>>account;
    cout<<"Password: ";
    cin>>password; 
    if(!atm.login(account,password) || !atm.validateAccount())
    {
        cout<<"Login failed\n";
        return false;
    }
    return true;
}
void UI::menu()
{
    int option;
    do
    {
        cout<<"\n====== ATM ======\n";
        cout<<"1. Withdraw\n";
        cout<<"2. Add money\n";
        cout<<"3. Balance\n";
        cout<<"0. Exit\n";
        cin>>option;
        
        switch(option)
        {
            case 1:
            {
                if(loginScreen())
                {
                    double amount;
                    cout<<"Amount: ";
                    cin>>amount;
                    if(atm.withdraw(amount))
                        cout<<"New balance: "
                        <<atm.getBalance()<<endl;
                    else
                        cout<<"Invalid amount\n";
                }
                break;
            }
            case 2:
            {
                if(loginScreen())
                {
                    double amount;
                    cout<<"Amount: ";
                    cin>>amount;
                    if(atm.addMoney(amount))
                        cout<<"New balance: "
                        <<atm.getBalance()<<endl;

                    else
                        cout<<"Invalid amount\n";
                }

                break;
            }
            case 3:
            {
                if(loginScreen())
                {
                    cout<<"Balance: "
                    <<atm.getBalance()<<endl;
                }

                break;
            }
            case 0:
                cout<<"Goodbye\n";
                break;
            default:
                cout<<"Invalid option\n";
        }
    }while(option!=0);
}   