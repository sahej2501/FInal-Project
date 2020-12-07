// #ifndef ALLACCOUNTS_H
// #define ALLACCOUNTS_H
#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include "timeHandler.h"
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
        string accountNumber;
        string firstName;
        string lastName; 
        string phoneNum;
        string address;
        Date openDate;

    public:
        //constructors
        AllAccounts()
        {
            accountNumber = "";
        }

        //getters
        Date getOpenDate()
        {
            return openDate;
        }

        int getKey()
        {
            return key;
        }

        vector< vector<string> > getTransactionHst()
        {
            vector< vector<string> > trans;
            trans.push_back(save.getTransactionHistory());
            trans.push_back(check.getTransactionHistory());
            trans.push_back(cd.getTransactionHistory());
            return trans;
        }

        string getAddress()
        {
            return address;
        }

        string getPhone()
        {
            return phoneNum;
        }

        string getName()
        {
            string name;
            name = firstName + " " + lastName;
            return name;
        }

        string getFirstName(){
            return firstName;
        }

        string getLastName(){
            return lastName;
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

        Date getCDCreationDate()
        {
            return cd.getCreationDate();
        }

        void cdAddIntrest()
        {
            cd.addInterest();
        }

        double getOGAmount()
        {
            return cd.getOgAmount();
        }


        //setters
        void setOpenDate(Date d)
        {
            openDate = d;
        }

        void setCDCreationDate(Date d)
        {
            cd.setCreationDate(d);
        }

        void setBalance(double s, double c, double f)
        {
            save.setAccountBalance(s);
            check.setAccountBalance(c);
            cd.setAccountBalance(f);
        }

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

        void savingsDeposit(int d, string accNum)
        {
            save.deposit(d);
            save.setAccountNumber(accNum);
        }

        void checkingDeposit(int d)
        {
            check.deposit(d);
        }

        void CDDeposit(int d)
        {
            //cd.setOgAmount = d;
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

        void cdCancel()
        {
            cd.cancellation();
        }

        void setOGAmount(double a)
        {
            cd.setOgAmount(a);
        }
        //og     
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
//#endif