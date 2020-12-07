#include<iostream>
#include<vector>
#include <string>
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

//Added by Sahej
BankTree tree;
int key;

directory d;

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

//Sahej import
void depOrWidth();
void openAccount(AllAccounts &a);
string generateAC(int keyPassed);


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

//Added by Sahej
void depOrWidth()
{
    AllAccounts currAcount;
    string login, password, accountNum;
    bool run = false;

    while(!run)
    {
        cout<<"Please enter Login for User: "<<endl;
        cin>>login;
        cout<<"Please enter user Password: "<<endl;
        cin>>password;
        for(int i = 0; i < usersVec.size(); i++)
        {
            if(login == usersVec[i].username) //&& password == usersVec[i].password)
            {
                if(password == usersVec[i].password)
                {
                    accountNum = usersVec[i].accntNum;
                    run = true;
                }
            }
            else
            {
                run = false;
            }
        }
        if(!run)
        {
            cout<<"No login or password match, try again"<<endl;
        }
    }

    int tempKey = d.getKey(accountNum);
    //cout<<tempKey<<" "<<accountNum<<endl;
    tree.searchAcc(tempKey);
    //cout<<tree.currAccount.acc->getName()<<endl;
    tree.modifi(currAcount);
    cout<<currAcount.getAccountNumber()<<endl;
    

    bool userRun = true;
    while(userRun)
    {
        int choice;
        cout<<"[1] Savings"<<'\n'<<"[2] Checkings"<<'\n'<<"[3] CD"<<'\n'<<"[4] Quit"<<endl;
        cin>>choice;
        switch (choice)
        {
        case 1:
            cin.ignore();
            int depChoice; 
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Back"<<endl;
            cin>>depChoice;
            switch (depChoice)
            {
            case 1:
                cin.ignore();
                int dep;
                cout<<"Enter deposit ammount"<<endl;
                cin>>dep;
                currAcount.savingsDeposit(dep);
                cout<<"Current Balance is: "<<currAcount.getSavingsBalance()<<endl;
                break;
            case 2:
                cin.ignore();
                //int dep;
                cout<<"Enter widthdraw ammount"<<endl;
                cin>>dep;
                currAcount.savingsWithdraw(dep);
                cout<<"Current Balance is: "<<currAcount.getSavingsBalance()<<endl;
                break;
            case 3:
                cin.ignore();
                cout<<"Current Balance is: "<<currAcount.getSavingsBalance()<<endl;
                break;
            case 4:
                break;
            default:
                cout<<"Invalid Input, try again"<<endl;
                break;
            }
            break;
        case 2:
            cin.ignore();
            //int depChoice; 
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Back"<<endl;
            cin>>depChoice;
            switch (depChoice)
            {
            case 1:
                cin.ignore();
                int dep;
                cout<<"Enter deposit ammount"<<endl;
                cin>>dep;
                currAcount.checkingDeposit(dep);
                cout<<"Current Balance is: "<<currAcount.getCheckingBalance()<<endl;
                break;
            case 2:
                cin.ignore();
                //int dep;
                cout<<"Enter widthdraw ammount"<<endl;
                cin>>dep;
                currAcount.checkingWithdraw(dep);
                cout<<"Current Balance is: "<<currAcount.getCheckingBalance()<<endl;
                break;
            case 3:
                cin.ignore();
                cout<<"Current Balance is: "<<currAcount.getCheckingBalance()<<endl;
                break;
            case 4:
                break;
            default:
                cout<<"Invalid Input, try again"<<endl;
                break;
            }
            break;
        case 3:
            cin.ignore();
            //int depChoice; 
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Cancel CD"<<'\n'<<"[5] Back"<<endl;
            cin>>depChoice;
            switch (depChoice)
            {
            case 1:
                cin.ignore();
                int dep;
                cout<<"Enter deposit ammount"<<endl;
                cin>>dep;
                currAcount.CDDeposit(dep);
                cout<<"Current Balance is: "<<currAcount.getCDBalance()<<endl;
                break;
            case 2:
                cin.ignore();
                //int dep;
                cout<<"Enter widthdraw ammount"<<endl;
                cin>>dep;
                currAcount.CDWithdraw(dep);
                cout<<"Current Balance is: "<<currAcount.getCDBalance()<<endl;
                break;
            case 3:
                cin.ignore();
                cout<<"Current Balance is: "<<currAcount.getCDBalance()<<endl;
                break;
            case 4:
                cin.ignore();
                currAcount.cdCancel();
                break;
            case 5:
                break;
            default:
                cout<<"Invalid Input, try again"<<endl;
                break;
            }
            break;
        case 4:
            userRun = false;
            break;
        default:
            cout<<"Invalid Input, try again"<<endl;
            break;
            }

    }
    tree.upadteAcc(currAcount.getKey(), currAcount);
    tree.searchAcc(currAcount.getKey());
}

void openAccount(AllAccounts &a)
{
    string accNum, login, password, name, firstName, lastName, phone, address;

    //New login and password for user
    bool run = true;
    while(run)
    {
        cout<<"Please choose a login Username: "<<endl;
        getline(cin, login);
        cout<<"Please choose a password: "<<endl;
        getline(cin, password);
        run = LoginPasswordMatch(login, password, usersVec);
        if(run)
        {
            cout<<"Login or Password already exsist, try again"<<endl;
        }
    }
    
    //generating a new account num
    accNum = generateAC(key);
    a.setKey(d.getKey(accNum));
    a.setAccountNumber(accNum);

    //Entering Name for new user
    cin.clear();
    cout<<"Please Enter Your Full Name"<<endl;
    getline(cin, name);
    firstName = name.substr(0, name.find(" "));
    lastName = name.substr(name.find(" "), name.length());
    a.setFirstLastName(firstName, lastName);
    //cin.ignore();

    // //Entering Phone number
    cin.clear();
    cout<<"Please Enter a Phone Number for the Account (format: xxx-xxx-xxxx): "<<endl;
    getline(cin, phone);
    a.setPhone(phone);
    //cin.ignore();

    //Entering Address
    cin.clear();
    cout<<"Enter a Address for the account: "<<endl;
    getline(cin, address);
    a.setAddress(address);

    tree.insertAcc(a);
    //tree.searchAcc(a.getKey());
    createUser(login, password, accNum, usersVec);
}

string generateAC(int keyPassed){
    srand(time(0));
    const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = sizeof(alphanum) - 1;
    string actN;
    actN+=to_string(keyPassed);
    for(int i =0; i<=10;i++){
        actN+=alphanum[rand()%len];
    }
    key++;
    return actN;
}
//Added by Sahej