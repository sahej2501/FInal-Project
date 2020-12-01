#pragma once
#include <string>
#include <iostream>
#include "accounts.h"
using namespace std;

//paste jay stuff
class Checking : public accounts
{
public:
    //Default constructor
    Checking() : accounts(){}

    //withdraw function
    double withdraw(double amount)
    {
        double fundCharge = -25.0;
        if (open == true)
        {
            if (accountBalance - amount < 0)   //if the withdrawal amount will cause a negative, just deduct the $25 fundCharge from the balance.
            {
                accountBalance = fundCharge;
                cout << "You withdrew more than you had, fund charge has been applied!" << endl;
            }
            else
            {
                accountBalance -= amount;
                cout << "withdraw Successful!" << endl;
            }
        }
        else
        {
            cout << "Account not open!";
        }
        return accountBalance;
    }

    void deposit(double amount)   //a deposit function
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
};