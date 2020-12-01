#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "accounts.h"
using namespace std;

void createAccounts();
void loginAccounts();

Checking tempChecking;
//CD tempCD;

int main(){
    bool cont = true;
    int choice;
    int select;
    string login;
    string psswd;
    string tempAN;
    while(cont){
        cout<<"Welcome to Bear Bank Systems, would you like to: \n[1] Open an account\n[2] Login\n[3] exit\nOption:";
        cin >> choice;
        cout << " " << endl;
        
        if(choice == 1 || choice == 2 || choice == 3)
        {
            switch(choice)
            {
                case 1:
                    //create Accounts fxn
                    createAccounts();
                    //cout << "Open-Account in the works..." << endl;
                    //cout << " " << endl;
                    break;
                case 2:
                    cout << "Login as: \n[1] System Administrator\n[2] Bank Official\n[3] Customer\n[4] Back\nOption:";
                    cin >> select;
                    cout << " " << endl;
                    if(select == 1 || select == 2 || select == 3 || select == 4)
                    {
                        switch (select)
                        {
                        case 1:
                            cout << "Enter UserID: ";
                            cin >> login;
                            cout << "Enter Password: ";
                            cin >> psswd;
                            cout << "Welcome Admin, system in progress..." << endl;
                            cout << " " << endl;
                            /*options for admins are; 
                            1. create/disable bank official login profile
                            2. create, delete and modify account types (whatever that means)
                            3. retrieve any user's login id and change their password
                            */
                            break;
                        case 2:
                            cout << "Enter UserID: ";
                            cin >> login;
                            cout << "Enter Password: ";
                            cin >> psswd;
                            cout << "Welcome Official, system in progress..." << endl;
                            cout << " " << endl;
                            /*options for officials are; 
                            1. open or close an account (store closed accnts in a file fro retrieval)
                            2. deposit or withdraw money w/ customer permission (ask for user's login & password to prove permission's granted)
                            3. search accounts by account num, customer name or phone number (dont know if its either one or all methods should be valid)
                            */
                            break;
                        case 3:
                            // cout << "Enter UserID: ";
                            // cin >> login;
                            // cout << "Enter Password: ";
                            // cin >> psswd;
                            // cout << "Welcome Customer, system in progress..." << endl;
                            // cout << "Your last login date and time was: Today" << endl;
                            // cout << " " << endl;
                            loginAccounts();
                            /*options for customer are; 
                            1. create new account
                            2. Login to accnts (we'd still have to use the C/S/CD to begin accnt types to know which accnt they are accessing)
                            3. Change id and password
                            4. Check all account transactions within day/date range (we would provide a given format to follow, we would use date range to save time bullshit) 
                            */
                            break;
                        case 4:
                            cont = true;
                            continue;
                        }
                    }
                    else
                    {
                        cout << "Invalid Input! Please choose valid option" << endl;
                        cout << " " << endl;
                        cont = true;
                        continue;
                    }
                    break;
                case 3:
                    //update stuff before close
                    cout << "Goodbye!" << endl;
                    cont = false;
                    break;
            }
        }
        else
        {
            cout << "Invalid Input! Please choose valid option" << endl;
            cout << " " << endl;
            cont = true;
            continue;
        }
    }

return 0;
};

void createAccounts()
{
    tempChecking.setAccountNumber("C1234");
    //tempCD.setAccountNumber("CD12345");

    cout << "......" << endl;
    bool cont = true;
    int selection;
    while(cont){
    cout << "[1] Deposit" << "\n[2] Withdraw" << "\n[3] Check Balance" << "\n[4] Go Back \n: ";
    cin >> selection;
    if (selection == 1 )
    {
        double depAmount;
        cout << "Enter deposit amount: ";
        cin >> depAmount;
        tempChecking.deposit(depAmount);
        break;
    }
    else if (selection == 2)
    {
        double withAmount;
        cout << "Enter withdraw amount: ";
        cin >> withAmount;
        tempChecking.withdraw(withAmount);
        break;
    }
    else if (selection == 3)
    {
        cout << "Your balance is: " << tempChecking.getAccountBalance() << endl;
        break;
    }
    else if (selection == 4)
    {
        cont = false;
        break;
    }
    else
    {
        cout << "invalid input" << endl;
        break;
    }
    }
};

void loginAccounts()
{
    cout << "......" << endl;
    int selection;
    bool cont = true;
    while(cont){
    cout << "[1] Deposit" << "\n[2] Withdraw" << "\n[3] Check Balance" << "\n[4] Go Back \n: ";
    cin >> selection;
    if (selection == 1 )
    {
        double depAmount;
        cout << "Enter deposit amount: ";
        cin >> depAmount;
        tempChecking.deposit(depAmount);
        break;
    }
    else if (selection == 2)
    {
        double withAmount;
        cout << "Enter withdraw amount: ";
        cin >> withAmount;
        tempChecking.withdraw(withAmount);
        break;
    }
    else if (selection == 3)
    {
        cout << "Your balance is: " << tempChecking.getAccountBalance() << endl;
        break;
    }
    else if (selection == 4)
    {
        break;
    }
    else
    {
        cout << "invalid input" << endl;
        break;
    }
    }
};