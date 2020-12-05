#pragma once
#include <string>
#include <iostream>
#include "accounts.h"
#include "timeHandler.h"
using namespace std;

class CD : public accounts
{
private:
    string status;
    double penalty = 5.0;
    double ogAmount;
    int interestRate;
    string withdrawDate;
    string creationDate;
    int numYears = 5;

public:
    //Default constructor
    CD() : accounts(){}

    //setters
    void setOgAmount(double amount)
    {
        ogAmount = amount;
    }

    void setCreationDate(string date)
    {
        creationDate = date;
    }

    //getters
    double getOgAmount()
    {
        return ogAmount;
    }

    string getCreationDate()
    {
        return creationDate;
    }

    double getInterestRate()
    {
        interestRate = 0.05 * accountBalance;
        return interestRate;
    }

    //functions
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
            cout << "A $" << amount << " withdrawal has been made" << endl;
        }
        else
            cout << "Account not open!";
     return accountBalance;
    }

    void cancellation()
    {
        /*
        Depending on num of days remaining, penalty may change i.e penalty shouldnt be fixed.
        */
        ogAmount -= penalty;
        cout << "Due to an early cancellation of your CD account, a penalty has been deducted from your balance, and no interest was added to your initial deposit." << endl;
        withdraw(ogAmount);
        setAccountBalance(0.0);
        closeAcc();
    }

    void addInterest()
    {
        double interest = 0.05 * accountBalance;
        accountBalance += interest;
    }
};
