#include<iostream>
#include<vector>
#include<fstream>
#include "AccountNode.h"
#include "accounts.h"
#include "timeHandler.h"
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

    /*
    To disable an official's profile, we add an asterisk to their ID name, and
    whenever they try to login, it wont be found.
    */

int main()
{
    
    string Id = "JabezNuetey";
    string pswd = "asdfejh";
    string sus = "Jay";

    readOfficialLogins(officialsVec);
    readAdminLogin(adminsVec);
    readUserLogins(usersVec);
    createOfficial(Id, pswd, officialsVec);
    //disableOfficial(sus, officialsVec);
    //enableOfficial(sus, officialsVec);
    changePassword("John", "asdf56456", usersVec);

    for(int i = 0; i < officialsVec.size(); i++)
    {
        cout << officialsVec[i].username << " " << officialsVec[i].password << endl;
    }
    cout << " " << endl;

    for(int j = 0; j < usersVec.size(); j++)
    {
        cout << usersVec[j].username << " " << usersVec[j].password << " " << usersVec[j].accntNum << endl;
    }
    cout << " " << endl;

    for(int k = 0; k < adminsVec.size(); k++)
    {
        cout << adminsVec[k].username << " " << adminsVec[k].password << endl;
    }

    writeToLogins(adminsVec, officialsVec, usersVec);
    return 0;
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