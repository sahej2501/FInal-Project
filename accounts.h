#pragma once
#include <string>
#include <iostream>
using namespace std;

class accounts{
    private:
        string accountNumber;
        double accountBalance;
        bool open; //bool to see if the account is accessible 
        double annualInterestRate;
        double annualService;
        string accountType; //for account type
        string username;
        string password;
        string timeOpened;
        double maturity;
        bool closed;
    public:
        //contructor
        accounts(string aN="0000000000", double aB=0.0, bool o=false, double aI=0.0, double aS=0.0, string aT="0001", string uN = "N/A", string pW = "N/A",double mat=0.0, bool close=false){
            //default Number is 0000000, account Balance is 0, its closed, 0.0 interest rate, 0.0 annual charge
            //it starts at a low risk, it has N for none account type, and 0 annual service charge.
            accountNumber=aN;
            accountBalance=aB;
            open=o;
            annualInterestRate=aI;
            annualService=aS;
            accountType=aT;
            closed = close;
            maturity=mat;
        }

        //getters
        string getAccountNumber(){
            return accountNumber;
        }

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

        void setAccountNumber(string aN){
            accountNumber=aN;
        }

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


        virtual double withdrawl(double amount){
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

        virtual void deposit(double amount){
            if(open){
                accountBalance+=amount;
                cout<<"Deposit successful! Current balance: "<< accountBalance;
            }
            else{
                cout<<"Account not open!";
            }
        }
};

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
    }
};
