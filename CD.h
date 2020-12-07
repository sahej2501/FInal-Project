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
    double penalty;
    double ogAmount = 0.0;
    Date creationDate;

public:
    //Default constructor
    CD() : accounts(){
        creationDate = t.getCurrentTime();
    }

    //setters
    void setOgAmount(double amount)
    {
        ogAmount = amount;
    }

    void setCreationDate(Date date)
    {
        creationDate = date;
    }

    //getters
    double getOgAmount()
    {
        return ogAmount;
    }

    Date getCreationDate()
    {
        return creationDate;
    }

    //functions
    void deposit(double amount)
    {
        if(open == true)
        {
            accountBalance += amount;
            setCreationDate(t.getCurrentTime());
        }
        else
            cout << "Account not open!";
        string info ="+" + to_string(amount) +" "+ t.formatDate(t.getCurrentTime())+" CD";
        transactionHistory.push_back(info);
    }
    
    double withdraw(double amount)
    {
        //check maturity in main, if it is not 5, cout timelength not met, continue
        if (open == true)
        {
            accountBalance -= amount;
            cout << "$" << accountBalance << " has been withdrawn" << endl;
        }
        else
            cout << "Account not open!";
        string info ="-" + to_string(amount) +" " +t.formatDate(t.getCurrentTime())+" CD";
        transactionHistory.push_back(info);
     return accountBalance;
    }

    void cancellation(double penalty)
    {
        /*
        Depending on num of days remaining, penalty may change i.e penalty shouldnt be fixed.
        */
       penalty = penalty * accountBalance;
        ogAmount -= penalty;
        cout << "Due to an early cancellation of your CD account, a penalty has been deducted from your balance, and no interest was added to your initial deposit." << endl;
        withdraw(ogAmount);
        //setAccountBalance(0.0);
        closeAcc();
    }

    void addInterest()
    {
        double interest = 0.05 * accountBalance;
        accountBalance += interest;
    }
};
