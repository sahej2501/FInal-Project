#ifndef SAVINGS_H
#define SAVINGS_H
#include <string>
#include <iostream>
#include "accounts.h"

using namespace std;

class Savings : public accounts{
    private:
        string status;                      //a way to see if the account is active or inactive 
        double serviceCharge;           //if the account is inactive(balance is below 50) a service charge of 5 dollars is applied
        double dailyInterest;
    public:
        Savings() : accounts()
        {
            if(accountBalance >= 50)
                status = "Active";
            else if(accountBalance < 50)
                status = "Inactive";
        }
        //returns the status
        string getStatus()
        {
            return status;
        }

        //sets the Status and checks that the annual intrest rate is not more than 10% or less than .1%
        void setStatus(string s)
        {
            status = s;
        }

        void setInterestRate(double dI) 
        {

            dailyInterest = dI;
        }

        double withdraw(double amount)
        {
            if(open == true)
            {
                if(status == "Active")  //override part to check the status 
                {
                    if(amount>accountBalance)
                    {
                        cout<<"withdraw unsuccessful, insufficient amount!";
                    }
                    else
                    {
                        accountBalance-=amount;
                        cout<<"withdraw successful! Current Balance: "<< accountBalance<<'\n';
                        if(accountBalance < 50)
                        {
                            status = "Inactive";
                            serviceCharge = 5;
                            accountBalance = accountBalance - serviceCharge;
                            //cout<<accountBalance<<endl; //adds a service charge with
                        }
                        if(accountBalance < 1)
                        {
                            closeAcc();
                        }
                    }
                    
                }
                else
                {
                   cout<<"Account Balance less than $50, cannot withdraw from Savings Account"<<endl;
                }
            }
            else
            {
                cout<<"Account not open, cannot withdraw at this time"<<endl;
            }

            return accountBalance;
        }

        double deposit(double amount){
            if(open == true)
            {
                accountBalance = accountBalance + amount;
                cout<<"Deposit successful! Current balance: "<< accountBalance<<'\n';
                if(accountBalance >= 50)
                {
                    status = "Active";
                }
            }
            else{
                cout<<"Account not open!";
            }
            return accountBalance;
        }

        void addInterest(Date dt1, Date dt2)
        {
            double dailyInterestRate;
            for(int i = 0; i < getDifference(dt1, dt2); i++)
            {
                dailyInterestRate = accountBalance * dailyInterestRate;
                accountBalance += dailyInterestRate;
            }
            
        }

};
#endif