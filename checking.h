#ifndef CHECKING_H
#define CHECKING_H
#include <string>
#include <iostream>
#include "accounts.h"

#include "timeHandler.h"
using namespace std;

//paste jay stuff
class Checking : public accounts
{
public:
    //Default constructor
    Checking() : accounts(){}

    //directory handler object, and time handler object for transaction history handling
    timeHandler t;

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
        //
        string info ="-" + to_string(amount) + t.formatDate(t.getCurrentTime())+" Checking";
        transactionHistory.push_back(info);
        
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
        string info ="+" + to_string(amount) + t.formatDate(t.getCurrentTime())+" Checking";
        transactionHistory.push_back(info);
    }
};
#endif