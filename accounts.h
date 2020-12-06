#ifndef ACCOUNTS_H
#define ACCOUNTS_H
#include <string>
#include <iostream>
#include "timeHandler.h"
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

class accounts{
    protected:
        timeHandler t;
        //string accountNumber;
        double accountBalance;
        bool open; //bool to see if the account is accessible 
        double annualInterestRate;
        double annualService;
        string accountType; //for account type
        string username;
        string password;
        string timeOpened;
        int maturity;
        bool closed;
        vector <string> transactionHistory;


        Date openedDate;

    public:
        //contructor
        accounts(string aN="0000000000", double aB=0.0, bool o=true, double aI=0.0, double aS=0.0, string aT="0001", string uN = "N/A", string pW = "N/A",int mat=0.0, bool close=false){
            //default Number is 0000000, account Balance is 0, its closed, 0.0 interest rate, 0.0 annual charge
            //it starts at a low risk, it has N for none account type, and 0 annual service charge.
            //accountNumber=aN;
            accountBalance=aB;
            open=o;
            annualInterestRate=aI;
            annualService=aS;
            accountType=aT;
            closed = close;
            maturity=mat;
            openedDate = t.getCurrentTime();
        }

        //getters
        vector <string> getTransactionHistory(){
            return transactionHistory;
        }
        // string getAccountNumber(){
        //     return accountNumber;
        // }

        double getAccountBalance(){
            return accountBalance;
        }

        bool getOpenStatus(){
            return open;
        }

        double getInterestRate(){
            return annualInterestRate;
        }

        double getService(){
            return annualService;
        }

        string getAccountType(){
            return accountType;
        }

        string getPassword(){
            return password;
        }

        string getUsername(){
            return username;
        }

        //setters
        void setPassword(string pass){
            password=pass;
        }

        void setUsername(string user){
            username=user;
        }

        // void setAccountNumber(string aN){
        //     accountNumber=aN;
        // }

        void setAccountBalance(double aB){
            accountBalance=aB;
        }

        void setOpenStatus(bool o){
            open=o;
        }

        void setInterestRate(double aI){
            annualInterestRate=aI;
        }

        void setService(double aS){
            annualService=aS;
        }

        void setType(char aT){
            accountType=aT;
        }


        double withdrawl(double amount){
            if(open){
                if(amount>accountBalance){
                    cout<<"Withdrawl unsuccessful, insufficient amount!";
                }
                else{
                    accountBalance-=amount;
                    cout<<"Withdrawl successful! Current Balance: "<< accountBalance;
                }
            }
            else{
                cout<<"Account not open!";
            }
            return accountBalance;
        }

        void deposit(double amount){
            if(open){
                accountBalance+=amount;
                cout<<"Deposit successful! Current balance: "<< accountBalance;
            }
            else{
                cout<<"Account not open!";
            }
        }
        virtual void closeAcc()
        {
            open = false;
        }



    void yearsPassed(){ //gets the difference of the two dates and if its greater than 365 it returns the difference of the amount of years to maturity as an int
    // for jay
        int daysDifferent = t.getDifference(openedDate, t.getCurrentTime());
        int yearsPassed = daysDifferent/365;
        if(yearsPassed>0&&yearsPassed>maturity){
            maturity = yearsPassed-maturity;
        }
        
    }

    //this function is strictly for testing for jay so that he can pass in future dates to test his interest
    void yearsPassedTester(Date newDate){ 
        int daysDifferent = t.getDifference(openedDate, newDate);
        int yearsPassed = daysDifferent/365;
        if(yearsPassed>0&&yearsPassed>maturity){
            maturity = yearsPassed-maturity;
        }
        
    }
};
#endif
