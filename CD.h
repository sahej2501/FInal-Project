#ifndef CD_H
#define CD_H
#include <string>
#include <iostream>
#include "accounts.h"
using namespace std;

class CD : public accounts
{
private:
    string status;
    double penalty;

public:
    //Default constructor
    CD() : accounts()
    {
        annualInterestRate = 0;//whatever fixed amnt we decide
    }

    void deposit(double amount)
    {
        if(open == true)
        {
            accountBalance += amount;
            cout << "A $" << amount << " deposit has been made" << endl;
        }
        else
        {
            cout << "Account not open!";
        }
    }

    double withdraw(double amount)
    {
        if (open == true)
        {
            accountBalance -= amount;
            cout << "withdraw Successful!" << endl;
        }
        else
        {
            cout << "Account not open!";
        }
        return accountBalance;
    }

    void cancellation()
    {
        accountBalance -= penalty;
        withdraw(accountBalance);
        closeAcc();
    }
};
#endif