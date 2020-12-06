#include<iostream>
#include<vector>
#include<fstream>
#include "AccountNode.h"
#include "Bank.h"
#include "timeHandler.h"
#include "directoryHandler.h"
using namespace std;


struct Official
{
    string username;
    string password;
};
struct Admin
{
    string username;
    string password;
};
struct User
{
    string username;
    string password;
    string accntNum;
};

vector<Official> officialsVec;
vector<Admin> adminsVec;
vector<User> usersVec;

void createOfficial(string, string, vector<Official> &officialsVec);
void createUser(string, string, string, vector<User> &usersVec);
bool LoginPasswordMatch(string, string, vector<User> &usersVec);
void enableOfficial(string, vector<Official> &officialsVec);
void disableOfficial(string, vector<Official> &officialsVec);

void readAdminLogin(vector<Admin> &adminsVec);
void readOfficialLogins(vector<Official> &officialsVec);
void readUserLogins(vector<User> &usersVec);
void writeToLogins(vector<Admin> &adminsVec, vector<Official> &officialsVec, vector<User> &usersVec);
void changePassword(string, string, vector<User> &usersVec);


int main()
{
    bool cont = true;
    int choice;
    int select;
    string login;
    string psswd;

    while(cont){
        cout<<"Welcome to Bear Bank Systems, would you like to: \n[1] Open an account\n[2] Login\n[3] exit\nOption:";
        cin >> choice;
        cout << " " << endl;
        
        if(choice == 1 || choice == 2 || choice == 3)
        {
            switch(choice)
            {
                case 1:
                    //createAccount();
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
                            cout << "Enter UserID: ";
                            cin >> login;
                            cout << "Enter Password: ";
                            cin >> psswd;
                            cout << "Welcome Customer, system in progress..." << endl;
                            cout << "Your last login date and time was: Today" << endl;
                            cout << " " << endl;
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
}

bool LoginPasswordMatch(string id, string pswd, vector<User> &usersVec)
{
    for(int i = 0; i < usersVec.size(); i++)
    {
        if(id == usersVec[i].username || pswd == usersVec[i].password)
            return true;
        else
            return false;
    }
}

void createOfficial(string id, string pswd, vector<Official> &officialsVec)
{
    Official newOff;
    newOff.username = id;
    newOff.password = pswd;
    officialsVec.push_back(newOff);
}

void createUser(string id, string pswd, string accntNum, vector<User> &usersVec)
{
    User newUser;
    newUser.username = id;
    newUser.password = pswd;
    newUser.accntNum = accntNum;
    usersVec.push_back(newUser);
}

void enableOfficial(string id, vector<Official> &officialsVec)
{
    bool present = true;

    for (int i = 0; i < officialsVec.size(); i++)
    {
        if (id + "*" == officialsVec[i].username)
        {
            officialsVec[i].username = id;
            present = true;
            break;
        }
        else
        {
            present = false;
            continue;
        }  
    }
    if(present == false)
        cout << "official's profile does not exist" << endl;
}

void disableOfficial(string id, vector<Official> &officialsVec)
{
    bool present = true;

    for (int i = 0; i < officialsVec.size(); i++)
    {
        if (id == officialsVec[i].username)
        {
            officialsVec[i].username = officialsVec[i].username + "*";
            present = true;
            break;
        }
        else
        {
            present = false;
            continue;
        }  
    }
    if(present == false)
        cout << "official's profile does not exist" << endl;
}

void readOfficialLogins(vector<Official> &officialsVec)
{   
    string text;
    ifstream inFile;
    Official off;

    cout << "Reading from officials file...";
    inFile.open("officials.txt");
    if(inFile)
    {
        while (getline(inFile, text))
        {
            off.username = text.substr(0, text.find(" "));
            off.password = text.substr(text.find(" ") + 1, text.length());
            officialsVec.push_back(off);
        }
    }
    else
        cout << "Officials file not found" << endl;

    cout << "complete" << endl;
    inFile.close();    
}

void readUserLogins(vector<User> &usersVec)
{
    string text;
    ifstream inFile;
    User customer;

    cout << "Reading from user file...";
    inFile.open("users.txt");
    if(inFile)
    {
        while (getline(inFile, text))
        {
            customer.username = text.substr(0, text.find(" "));
            text = text.substr(text.find(" ") + 1, text.length());
            customer.password = text.substr(0, text.find(" "));
            customer.accntNum = text.substr(text.find(" ") + 1, text.length());
            usersVec.push_back(customer);
        }
    }
    else
        cout << "Users file not found" << endl;

    cout << "complete" << endl;
    inFile.close();
}

void readAdminLogin(vector<Admin> &adminsVec)
{
    string text;
    ifstream inFile;
    Admin systemAdmin;

    cout << "Reading from admin file...";
    inFile.open("admins.txt");
    if(inFile)
    {
        while (getline(inFile, text))
        {
            systemAdmin.username = text.substr(0, text.find(" "));
            systemAdmin.password = text.substr(text.find(" ") + 1, text.length());
            adminsVec.push_back(systemAdmin);
        }
    }
    else
        cout << "Admins file not found" << endl;

    cout << "complete" << endl;
    inFile.close(); 
}

void writeToLogins(vector<Admin> &adminsVec, vector<Official> &officialsVec, vector<User> &usersVec)
{
    ofstream writeAdmin;
    writeAdmin.open("admins.txt");
    ofstream writeOfficial;
    writeOfficial.open("officials.txt");
    ofstream writeUser;
    writeUser.open("users.txt");

    for (int i = 0; i < adminsVec.size(); i++)
        writeAdmin << adminsVec[i].username << " " << adminsVec[i].password << endl;
    for (int j = 0; j < officialsVec.size(); j++)
        writeOfficial << officialsVec[j].username << " " << officialsVec[j].password << endl;
    for (int k = 0; k < usersVec.size(); k++)
        writeUser << usersVec[k].username << " " << usersVec[k].password << " " << usersVec[k].accntNum <<endl;
}

void changePassword(string id, string newPswd, vector<User> &usersVec)
{
    bool present = true;

    for (int i = 0; i < usersVec.size(); i++)
    {
        if (id == usersVec[i].username)
        {
            usersVec[i].password = newPswd;
            present = true;
            break;
        }
        else
        {
            present = false;
            continue;
        }  
    }
    if(present == false)
        cout << "user's profile does not exist" << endl;
}