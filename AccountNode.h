#ifndef ALLACCOUNTS_H
#define ALLACCOUNTS_H

#include <string>
#include <iostream>
#include <vector>
#include <string>
#include "accounts.h"
#include "savings.h"
#include "checking.h"
#include "CD.h"


using namespace std;

class AllAccounts
{
    protected: 
        int key;
        Savings save;
        Checking check;
        CD cd;
        string accountNumber, firstName, lastName, phoneNum, address;

    public:
        //constructors
        AllAccounts()
        {
            key = 000;
            accountNumber = "0000000000";
        }

        //getters
        int getKey()
        {
            return key;
        }

        vector<string> getTransactionHst()
        {
            return save.getTransactionHistory();
        }

        void printName()
        {
            cout<<firstName<<" "<<lastName<<endl;
        }

        string getAccountNumber()
        {
            return accountNumber;
        }

        int getSavingsBalance()
        {
            return save.getAccountBalance();
        }

        int getCheckingBalance()
        {
            return check.getAccountBalance();
        }

        int getCDBalance()
        {
            return cd.getAccountBalance();
        }

        //setters
        void setKey(int k)
        {
            key = k;
        }

        void setFirstLastName(string f, string l)
        {
            firstName = f;
            lastName = l;
        }

        void setAddress(string a)
        {
            address = a;
        }

        void setPhone(string p)
        {
            phoneNum = p;
        }

        void setAccountNumber(string s)
        {
            accountNumber = s;
        }

        void savingsDeposit(int d)
        {
            save.deposit(d);
        }

        void checkingDeposit(int d)
        {
            check.deposit(d);
        }

        void CDDeposit(int d)
        {
            cd.deposit(d);
        }

        void savingsWithdraw(int w)
        {
            save.withdraw(w);
        }

        void checkingWithdraw(int w)
        {
            check.withdraw(w);
        }

        void CDWithdraw(int w)
        {
            cd.withdraw(w);
        }

        //functions for bank officials
        void openOrCloseSavings(bool n)
        {
            save.setOpenStatus(n);
        }

        void openOrCloseChecking(bool n)
        {
            check.setOpenStatus(n);
        }

        void openOrCloseCD(bool n)
        {
            cd.setOpenStatus(n);
        }



};
#endif