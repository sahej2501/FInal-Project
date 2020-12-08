#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "AccountNode.h"
#include "Bank.h"
#include "timeHandler.h"
#include "directoryHandler.h"
#include <sstream>
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
struct ClosedAccounts
{
    string AccNum;
    string info;
};

vector<Official> officialsVec;
vector<Admin> adminsVec;
vector<User> usersVec;
vector<AllAccounts> ogAccounts;
vector<AllAccounts> balancedAccounts;
vector<ClosedAccounts> cAccounts;

int key = 0;
BankTree tree;
timeHandler t;
directory d;

string generateAC(int keyPassed);
void createOfficial(string, string, vector<Official> &officialsVec);
void createUser(string, string, string, vector<User> &usersVec);
bool LoginPasswordMatch(string, string, vector<User> &usersVec);
bool OfficialPasswordMatch(string, string, vector<Official> &officialsVec);
void enableOfficial(string, vector<Official> &officialsVec);
void disableOfficial(string, vector<Official> &officialsVec);

void readAdminLogin(vector<Admin> &adminsVec);
void adminOptions();
void officialsOptions(string);
void usersOptions(string);
void readOfficialLogins(vector<Official> &officialsVec);
void readUserLogins(vector<User> &usersVec);
void writeToLogins(vector<Admin> &adminsVec, vector<Official> &officialsVec, vector<User> &usersVec);
void changePassword(string, string, vector<User> &usersVec);

//Sahej added
void depOrWidth();
void openAccount();
void shutAcc(string);

//mikie g
void setCurrAccount();
void readAccounts();
void saveAccounts();

int main()
{
    bool cont = true;
    int choice;
    int select;
    string login;
    string psswd;
    AllAccounts newAccount;
    bankAcc currAcc;
    //read txt files into vecs
    
    readUserLogins(usersVec);
    readAdminLogin(adminsVec);
    readOfficialLogins(officialsVec);
    readAccounts();

    while(cont){
        cout<<"Welcome to Bear Bank Systems, would you like to: \n[1] Open an account\n[2] Login\n[3] exit\nOption:";
        cin >> choice;
        cout << " " << endl;
        
        if(choice == 1 || choice == 2 || choice == 3)
        {
            switch(choice)
            {
                case 1:
                    openAccount();
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
                            bool run;
                            run = false;
                            while(!run)
                            {
                                cout << "Enter Admin ID: ";
                                cin >> login;
                                cout << "Enter Password: ";
                                cin >> psswd;
                                for (int i = 0; i < adminsVec.size(); i++)
                                {
                                    if(login == adminsVec[i].username)
                                    {
                                        if(psswd == adminsVec[i].password)
                                        {
                                            adminOptions();
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
                            break;
                        case 2:
                            bool keepUp;
                            keepUp = false;
                            while(keepUp == false)
                            {
                                cout << "Enter Official ID: ";
                                cin >> login;
                                cout << "Enter Password: ";
                                cin >> psswd;
                                for (int k = 0; k < officialsVec.size(); k++)
                                {
                                    if(login == officialsVec[k].username)
                                    {
                                        cout << "sia" << endl;
                                        if(psswd == officialsVec[k].password)
                                        {
                                            cout << "sia2" << endl;
                                            officialsOptions(officialsVec[k].username);
                                            keepUp = true;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        cout << "fail" << endl;
                                        keepUp = false;
                                    }
                                }
                                if(keepUp == false)
                                {
                                    cout<<"No login or password match, try again"<<endl;
                                }
                            }
                            /*options for officials are; 
                            1. open or close an account (store closed accnts in a file fro retrieval)
                            2. deposit or withdraw money w/ customer permission (ask for user's login & password to prove permission's granted)
                            3. search accounts by account num, customer name or phone number (dont know if its either one or all methods should be valid)
                            */
                            break;
                        case 3:
                            bool running;
                            running = false;
                            while(running == false)
                            {
                                cout<<"Please enter customer ID: ";
                                cin>>login;
                                cout<<"Please enter customer Password: ";
                                cin>>psswd;
                                for(int i = 0; i < usersVec.size(); i++)
                                {
                                    if(login == usersVec[i].username)
                                    {
                                        if(psswd == usersVec[i].password)
                                        {
                                            usersOptions(usersVec[i].accntNum);
                                            running = true;
                                            break;
                                        }
                                    }
                                    else
                                    {
                                        running = false;
                                    }
                                }
                                if(running == false)
                                {
                                    cout<<"No login or password match, try again"<<endl;
                                }
                            }
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
                    chdir(d.basePath.data());
                    writeToLogins(adminsVec, officialsVec, usersVec);
                    setCurrAccount();
                    saveAccounts();
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
    bool present = true;
    for(int i = 0; i < usersVec.size(); i++)
    {
        if(id == usersVec[i].username || pswd == usersVec[i].password)
            return present;
        else
            present = false;
    }
    return present;
}

bool OfficialPasswordMatch(string id, string pswd, vector<Official> &officialsVec)
{
    bool present = true;
    for(int i = 0; i < officialsVec.size(); i++)
    {
        if(id == officialsVec[i].username || pswd == officialsVec[i].password)
            return present;
        else
            present = false;
    }
    return present;
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
        cout << "Official's profile does not exist or is already enabled" << endl;
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
        cout << "Official's profile does not exist or is already disabled" << endl;
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
    directory d1;
    string text;
    ifstream inFile;
    Admin systemAdmin;

    cout << "Reading from admin file...";
    inFile.open("admins.txt");
    if(inFile)
    {
        while (getline(inFile, text))
        {
            systemAdmin.username = d1.decrypt(text.substr(0, text.find(" ")), 4);
            systemAdmin.password = d1.decrypt(text.substr(text.find(" ") + 1, text.length()), 4);
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
    directory d1;
    ofstream writeAdmin;
    writeAdmin.open("admins.txt");
    ofstream writeOfficial;
    writeOfficial.open("officials.txt");
    ofstream writeUser;
    writeUser.open("users.txt");

    for (int i = 0; i < adminsVec.size(); i++)
        writeAdmin << d1.encrypt(adminsVec[i].username, 4) << " " << d1.encrypt(adminsVec[i].password, 4) << endl;
    for (int j = 0; j < officialsVec.size(); j++)
        writeOfficial << d1.encrypt(officialsVec[j].username, 4) << " " << d1.encrypt(officialsVec[j].password, 4) << endl;
    for (int k = 0; k < usersVec.size(); k++)
        writeUser << d1.encrypt(usersVec[k].username, 4) << " " << d1.encrypt(usersVec[k].password, 4) << " " << d1.encrypt(usersVec[k].accntNum, 4) <<endl;
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
            cout << "Password change successful" << endl;
            break;
        }
        else
        {
            present = false;
            continue;
        }  
    }
    if(present == false)
        cout << "Customer ID was not found" << endl;
}

string generateAC(int keyPassed){
    srand(time(0));
    const char alphanum[] = "0123456789" "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int len = sizeof(alphanum) - 1;
    string actN;
    actN+=to_string(keyPassed);
    actN+="N";
    for(int i =0; i<=9;i++){
        actN+=alphanum[rand()%len];
    }
    return actN;
}

void openAccount()
{
    key++;
    AllAccounts a;
    string accNum, login, password, name, firstName, lastName, phone, address;

    //New login and password for user
    bool run = true;
    while(run)
    {
        cout<<"Please choose a login Username: ";
        cin >> login;
        cout<<"Please choose a password: ";
        cin >> password;
        run = LoginPasswordMatch(login, password, usersVec);
        if(run)
        {
            cout<<"Login or Password already exist, try again"<<endl;
        }
    }
    
    //generating a new account num
    //cout<<key<<endl;
    accNum = generateAC(key);
    a.setKey(key);
    //cout<<key<<endl;
    a.setAccountNumber(accNum);

    //Entering Name for new user
    cin.ignore();
    cout<<"Please Enter Your Full Name: ";
    getline(cin, name);
    firstName = name.substr(0, name.find(" "));
    lastName = name.substr(name.find(" "), name.length());
    a.setFirstLastName(firstName, lastName);

    //Entering Phone number
    cout<<"Please Enter a Phone Number for the Account (format: xxx-xxx-xxxx): ";
    getline(cin, phone);
    a.setPhone(phone);

    //Entering Address
    cout<<"Enter an Address for the account: ";
    getline(cin, address);
    a.setAddress(address);

    tree.insertAcc(a);
    d.createFiles(accNum);
    cout << " " << endl;
    cout << "Congratulations! Your account was sucessfully created.\nYou now have a Checking, Savings and CD account with us!" << endl;
    cout << " " << endl;
    createUser(login, password, accNum, usersVec);
    
}

void adminOptions()
{
    int choice;
    bool cont;
    cont = true;
    string ID;
    string password;
    string newPsswd;
    while(cont)
    {
        cout << "What would you like to do today? \n[1] Create bank official login profile\n[2] Disable bank official login profile\n[3] Enable bank official login profile\n[4] Retrieve customer login ID\n[5] Change customer password\n[6] Back\nOption:";
        cin >> choice;
        switch(choice)
        {
            case 1:
                bool run;
                run = true;
                while(run)
                {
                    cout << "Enter ID: ";
                    cin >> ID;
                    cout << "Enter password: ";
                    cin >> password;
                    run = OfficialPasswordMatch(ID, password, officialsVec);
                    if(run)
                    {
                        cout<<"Login or Password already exist, try again"<<endl;
                    }
                }
                createOfficial(ID, password, officialsVec);
                break;
            case 2:
                cout << "Enter bank official's ID: ";
                cin >> ID;
                disableOfficial(ID, officialsVec);
                break;
            case 3:
                cout << "Enter bank official's ID: ";
                cin >> ID;
                enableOfficial(ID, officialsVec);
                break;
            case 4:
                bool present;
                present = true;
                cout << "Enter customer ID you want to retrieve: ";
                cin >> ID;
                for(int i = 0; i < usersVec.size(); i++)
                {
                    if(ID == usersVec[i].username)
                    {
                        cout << "The customer ID is " << usersVec[i].username << endl;
                        present = true;
                        break;
                    }
                    else
                    {
                        present = false;
                        continue;
                    }
                }
                if (present == false)
                    cout << "The customer ID was not found." << endl;
                break;
            case 5:
                cout << "Enter customer ID: ";
                cin >> ID;
                cout << "Enter new password: ";
                cin >> newPsswd;
                changePassword(ID, newPsswd, usersVec);
                break;
            case 6:
                cont = false;
                break;
            default:
                cout << "Invalid option choice" << endl;
        }
    }  
}

void officialsOptions(string officialID)
{
    bool run;
    run = true;
    int choice;
    string accNumBO;
    while(run)
    {
        cout << "What would you like to do today? \n[1] Create an account for customer\n[2] Close an account\n[3] Act on a customer's account\n[4] Search for account using Account number\n[5] Back\nOption:";
        cin >> choice;
        switch(choice)
        {
            case 1:
                openAccount();
                break;
            case 2:
                shutAcc(officialID);
                break;
            case 3:
                depOrWidth();
                break;
            case 4:
                bool isThere;
                
                cout<<"Please Enter Bank Account Number: "<<endl;
                cin>>accNumBO;
                isThere = tree.searchAcc(d.getKey(accNumBO));
                if(isThere)
                {
                    cout<<tree.currAccount.getAccountNumber()<<'\n'<<tree.currAccount.getName()<<'\n'<<tree.currAccount.getPhone()<<'\n'
                    <<tree.currAccount.getAddress()<<endl;
                }
                break;
            case 5:
                run = false;
                break;
            default:
                cout<<"Invalid Input, try again"<<endl;
                break;
        }
    }
}

void usersOptions(string accountNum)
{
    AllAccounts currAcount;
    int choice;
    string ID;
    string newPsswd;
    bool cont;
    cont = true;

    int tempKey = d.getKey(accountNum);
    cout<<tempKey<<" "<<accountNum<<endl;
    tree.searchAcc(tempKey);
    cout<<tree.currAccount.getName()<<endl;
    tree.modifi(currAcount);
    cout<<currAcount.getAccountNumber()<<endl;
    cout<<currAcount.getSavingsBalance()<<endl;

    while(cont)
    {
        cout << "What would you like to do today? \n[1] Login to accounts\n[2] Change password\n[3] Check Transactions\n[4] Back\nOption:";
        cin >> choice;
        switch(choice)
        {
            case 1:
                bool userRun;
                userRun = true;
                while(userRun)
                {
                    int selection;
                    cout<<"[1] Login to Savings"<<'\n'<<"[2] Login to Checkings"<<'\n'<<"[3] Login to CD (This is a 5 year certificate deposit account)"<<'\n'<<"[4] Back to Homescreen\nOption:";
                    cin>>selection;
                    switch (selection)
                    {
                    case 1:
                        cin.ignore();
                        int depChoice; 
                        cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
                        "[3] Check Balance"<<'\n'<<"[4] Back\nOption:";
                        cin>>depChoice;
                        switch (depChoice)
                        {
                        case 1:
                            cin.ignore();
                            int dep;
                            cout<<"Enter deposit amount: ";
                            cin>>dep;
                            currAcount.savingsDeposit(dep);
                            cout<<"A $"<<dep<<" deposit has been made, "<<"current Balance is: $"<<currAcount.getSavingsBalance()<<endl;
                            break;
                        case 2:
                            cin.ignore();
                            //int dep;
                            cout<<"Enter widthdraw amount: ";
                            cin>>dep;
                            currAcount.savingsWithdraw(dep);
                            cout<<"A $"<<dep<< " withdrawal has been made, "<<"current Balance is: $"<<currAcount.getSavingsBalance()<<endl;
                            break;
                        case 3:
                            cin.ignore();
                            cout<<"Current Balance is: $"<<currAcount.getSavingsBalance()<<endl;
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
                        "[3] Check Balance"<<'\n'<<"[4] Back\nOption:";
                        cin>>depChoice;
                        switch (depChoice)
                        {
                        case 1:
                            cin.ignore();
                            int dep;
                            cout<<"Enter deposit amount: ";
                            cin>>dep;
                            currAcount.checkingDeposit(dep);
                            cout<<"A $"<<dep<< " deposit has been made, "<<"current Balance is: $"<<currAcount.getCheckingBalance()<<endl;
                            break;
                        case 2:
                            cin.ignore();
                            //int dep;
                            cout<<"Enter widthdraw amount: ";
                            cin>>dep;
                            currAcount.checkingWithdraw(dep);
                            cout<<"A $"<<dep<< " withdrawal has been made, "<<"current Balance is: $"<<currAcount.getCheckingBalance()<<endl;
                            break;
                        case 3:
                            cin.ignore();
                            cout<<"Current Balance is: $"<<currAcount.getCheckingBalance()<<endl;
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
                        "[3] Check Balance"<<'\n'<<"[4] Cancel CD"<<'\n'<<"[5] Back\nOption:";
                        cin>>depChoice;
                        switch (depChoice)
                        {
                        case 1:
                            cin.ignore();
                            int dep;
                            cout<<"Enter deposit amount: ";
                            cin>>dep;
                            if(currAcount.getCDBalance() > 0)
                            {
                                cout << "Unfortunately you can only deposit once into a CD account" << endl;
                            }
                            else
                            {
                                currAcount.CDDeposit(dep);
                                currAcount.setCDCreationDate(t.getCurrentTime());
                                cout<<"A $"<<dep<< " deposit has been made, "<<"current Balance is: $"<<currAcount.getCDBalance()<<endl;
                                cout << t.formatDate(currAcount.getCDCreationDate()) << endl;
                            }
                            break;
                        case 2:
                            cin.ignore();
                            //int dep;
                            cout<<"Enter widthdraw amount: ";
                            cin>>dep;
                            currAcount.CDWithdraw(dep);
                            cout<<"A $"<<dep<< " withdrawal has been made, "<<"current Balance is: $"<<currAcount.getCDBalance()<<endl;
                            break;
                        case 3:
                            cin.ignore();
                            cout<<"Current Balance is: $"<<currAcount.getCDBalance()<<endl;
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
                break;
            case 2:
                cout << "Enter ID: ";
                cin >> ID;
                cout << "Enter new password: ";
                cin >> newPsswd;
                changePassword(ID, newPsswd, usersVec);
                break;
            case 3:
                cout << "Transactions under construction" << endl;
                break;
            case 4:
                cont = false;
                break;
            default:
                cout << "Invalid option choice" << endl;
                break;
        }
    }           
}

void depOrWidth()
{
    AllAccounts currAcount;
    string login, password, accountNum;
    bool run = false;

    while(!run)
    {
        cout<<"Please enter Login for Customer: ";
        cin>>login;
        cout<<"Please enter customer Password: ";
        cin>>password;
        for(int i = 0; i < usersVec.size(); i++)
        {
            if(login == usersVec[i].username) //&& password == usersVec[i].password)
            {
                if(password == usersVec[i].password)
                {
                    accountNum = usersVec[i].accntNum;
                    cout << usersVec[i].accntNum << endl;
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
    cout<<tempKey<<" "<<accountNum<<endl;
    tree.searchAcc(tempKey);
    cout<<tree.currAccount.getName()<<endl;
    tree.modifi(currAcount);
    cout<<currAcount.getAccountNumber()<<endl;
    

    bool userRun = true;
    while(userRun)
    {
        int choice;
        cout<<"[1] Login to Savings"<<'\n'<<"[2] Login to Checkings"<<'\n'<<"[3] Login to CD (This is a 5 year certificate deposit account)"<<'\n'<<"[4] Back to Homescreen\nOption:";
        cin>>choice;
        switch (choice)
        {
        case 1:
            cin.ignore();
            int depChoice; 
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Back\nOption:";
            cin>>depChoice;
            switch (depChoice)
            {
            case 1:
                cin.ignore();
                int dep;
                cout<<"Enter deposit amount: ";
                cin>>dep;
                currAcount.savingsDeposit(dep);
                cout<<"A $"<<dep<<" deposit has been made, "<<"current Balance is: $"<<currAcount.getSavingsBalance()<<endl;
                break;
            case 2:
                cin.ignore();
                //int dep;
                cout<<"Enter widthdraw amount: ";
                cin>>dep;
                currAcount.savingsWithdraw(dep);
                cout<<"A $"<<dep<< " withdrawal has been made, "<<"current Balance is: $"<<currAcount.getSavingsBalance()<<endl;
                break;
            case 3:
                cin.ignore();
                cout<<"Current Balance is: $"<<currAcount.getSavingsBalance()<<endl;
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
            "[3] Check Balance"<<'\n'<<"[4] Back\nOption:";
            cin>>depChoice;
            switch (depChoice)
            {
            case 1:
                cin.ignore();
                int dep;
                cout<<"Enter deposit amount: ";
                cin>>dep;
                currAcount.checkingDeposit(dep);
                cout<<"A $"<<dep<< " deposit has been made, "<<"current Balance is: $"<<currAcount.getCheckingBalance()<<endl;
                break;
            case 2:
                cin.ignore();
                //int dep;
                cout<<"Enter widthdraw amount: ";
                cin>>dep;
                currAcount.checkingWithdraw(dep);
                cout<<"A $"<<dep<< " withdrawal has been made, "<<"current Balance is: $"<<currAcount.getCheckingBalance()<<endl;
                break;
            case 3:
                cin.ignore();
                cout<<"Current Balance is: $"<<currAcount.getCheckingBalance()<<endl;
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
            "[3] Check Balance"<<'\n'<<"[4] Cancel CD"<<'\n'<<"[5] Back\nOption:";
            cin>>depChoice;
            switch (depChoice)
            {
            case 1:
                cin.ignore();
                int dep;
                cout<<"Enter deposit amount: ";
                cin>>dep;
                if(currAcount.getCDBalance() > 0)
                {
                    cout << "Unfortunately you can only deposit once into a CD account" << endl;
                }
                else
                {
                    currAcount.CDDeposit(dep);
                    currAcount.setCDCreationDate(t.getCurrentTime());
                    cout<<"A $"<<dep<< " deposit has been made, "<<"current Balance is: $"<<currAcount.getCDBalance()<<endl;
                    cout << t.formatDate(currAcount.getCDCreationDate()) << endl;
                }
                break;
            case 2:
                cin.ignore();
                //int dep;
                cout<<"Enter widthdraw amount: ";
                cin>>dep;
                currAcount.CDWithdraw(dep);
                cout<<"A $"<<dep<< " withdrawal has been made, "<<"current Balance is: $"<<currAcount.getCDBalance()<<endl;
                break;
            case 3:
                cin.ignore();
                cout<<"Current Balance is: $"<<currAcount.getCDBalance()<<endl;
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

void shutAcc(string offID)
{
    string accNumBO, currInfo;
    ClosedAccounts c;
    cout<<"Please Enter Bank Account Number: "<<endl;
    cin>>accNumBO;
    tree.removeAcc(d.getKey(accNumBO));
    tree.searchAcc(d.getKey(accNumBO));

    currInfo = tree.currAccount.getName() + " " + tree.currAccount.getPhone() + tree.currAccount.getAddress() + 
    t.formatDate(t.getCurrentTime()) + " " + offID;

    c.AccNum = accNumBO;
    c.info = currInfo;
    cAccounts.push_back(c);

    //closedAccounts.push_back(tree.closeInfo + t.formatDate(t.getCurrentTime()));
    int erasePos;
    for(int i = 0; i < usersVec.size(); i++)
    { 
        if(usersVec[i].accntNum == accNumBO)
        {
            usersVec[i].accntNum = "";
            usersVec[i].username = "";
            usersVec[i].password = "";
        }
    }
    //Checking to see if close info was updated
    for(int i = 0; i < cAccounts.size(); i++)
    {
        cout<<cAccounts[i].info<<endl;
    }
}

void saveAccounts(){

    AllAccounts tempAcc;
    //tree.currAccount.get()...
    ofstream outFile;
    chdir(d.basePath.data());
    chdir(d.accountsPath.data());
    for(int i=0;i<usersVec.size();i++){
        tree.searchAcc(d.getKey(usersVec[i].accntNum));
        //tree.modifi(tempAcc);
        cout<<usersVec[i].accntNum<<endl;
        cout<<tree.currAccount.getAccountNumber()<<endl;
        string newPath = d.accountsPath+"/"+usersVec[i].accntNum;
        cout<<"new path in saveAccounts: "<<newPath<<endl;
        chdir(newPath.data());

        //saving to checkings
        outFile.open("checkings.txt");
        if(outFile){
            cout<<"file opened"<<endl;
        }
        outFile << to_string(tree.currAccount.getCheckingBalance())<<endl;
        outFile.close();
    
        //saving to savings
        outFile.open("savings.txt",ios::out);
        outFile << to_string(tree.currAccount.getSavingsBalance())<<endl;
        outFile.close();

            //saving to info
        outFile.open("info.txt");
        outFile << tree.currAccount.getFirstName() <<endl;
        outFile << tree.currAccount.getLastName() <<endl;
        outFile << tree.currAccount.getPhone() <<endl;
        outFile <<tree.currAccount.getAddress() <<endl;
        outFile<< t.formatDate(tree.currAccount.getOpenDate())<<endl;
        outFile <<tree.currAccount.getAccountNumber()<<endl;
        outFile.close();
        
        //saving to cd
        outFile.open("cd.txt");
        outFile<<to_string(tree.currAccount.getOGAmount())<<endl;
        outFile<<t.formatDate(tree.currAccount.getOpenDate())<<endl;
        outFile<<to_string(tree.currAccount.getCDBalance())<<endl;
        outFile.close();

        //saving transaction history
        d.saveTransactions(tree.currAccount.getTransactionHst(),tree.currAccount.getAccountNumber());

    }
    

}

void readAccounts(){
    cout<<"Reading the fucking file line 1098"<<endl;
    string keyGetter;
    cout<<"userVec size: "<<usersVec.size()<<endl;
    keyGetter = usersVec[usersVec.size() - 1].accntNum;
    cout<<"Key getter: "<<keyGetter<<endl;
    key = d.getKey(keyGetter);
    //directory d;
    AllAccounts temp;
    Date tempDate;
    ifstream inFile;
    string line, fname, lname;
    double checkB, saveB, cdB;
    vector <string> lines;
    vector <string> date;
    char delim = '/';
    // for(int i =0;i<usersVec.size();i++){
    //     cout<<usersVec[i].accntNum<<endl;
    // }
    for (int i =0; i<usersVec.size();i++){
        string accNum=usersVec[i].accntNum;
        string newPath = d.accountsPath+"/"+accNum;
        cout<<"new path: "<<newPath<<endl;
        if(chdir(newPath.data())==-1){
            cout<<"Couldnt change path!"<<endl;
        }
        inFile.open("info.txt");
        if(!inFile){
            cout<<"file didnt open"<<endl;
        }
        while(getline(inFile,line)){
            lines.push_back(line);
        }
        cout<<lines.size()<<endl;
        fname=lines[0];
        lname=lines[1];
        temp.setFirstLastName(fname, lname);
        cout<<temp.getName()<<endl;
        temp.setPhone(lines[2]);
        cout<<temp.getPhone()<<endl;
        temp.setAddress(lines[3]);
        cout<<temp.getAddress()<<endl;
        temp.setAccountNumber(lines[5]);
        temp.getAccountNumber();
        temp.setKey(d.getKey(temp.getAccountNumber()));
        cout<<temp.getKey()<<endl;
        cout<<"lines[4]"<<lines[4]<<endl;
        string stringDate=lines[4];
        stringstream ss(stringDate);
        string s;
        while(getline(ss,s,delim)){
            date.push_back(s);
        }
        tempDate.d=stoi(date[1]);
        tempDate.m=stoi(date[2]);
        tempDate.y=stoi(date[3]);
        temp.setOpenDate(tempDate);
        cout<<"Open date: "<<t.formatDate(temp.getOpenDate())<<endl;
        inFile.close();
        lines.clear();

        inFile.open("checkings.txt");
        while(getline(inFile,line)){
            lines.push_back(line);
        }
        checkB=stod(lines[0]);
        lines.clear();
        inFile.close();

        inFile.open("savings.txt");
        while(getline(inFile,line)){
            lines.push_back(line);
        }
        cout<<"Savings balance: "<<lines[0]<<endl;
        saveB=stod(lines[0]);
        lines.clear();
        inFile.close();

        inFile.open("cd.txt");
        while(getline(inFile,line)){
            lines.push_back(line);
        }
        inFile.close();
        temp.setOGAmount(stod(lines[0]));
        cout<<"OG amount: "<<temp.getOGAmount()<<endl;
        stringDate = lines[1];
        stringstream sb(stringDate);
        string b;
        date.clear();
        while(getline(sb,b,delim)){
            date.push_back(b);
        }
        tempDate.d=stoi(date[1]);
        tempDate.m=stoi(date[2]);
        tempDate.y=stoi(date[3]);
        temp.setCDCreationDate(tempDate);
        cout<<"CD creation date: "<<t.formatDate(temp.getCDCreationDate())<<endl;
        cdB=stod(lines[2]);
        temp.setBalance(saveB, checkB, cdB);
        cout<<"saveB "<<temp.getSavingsBalance()<<endl;
        cout<<"Savings balance: "<<temp.getSavingsBalance()<<endl;
        cout<<"Checkings balance: "<<temp.getCheckingBalance()<<endl;
        cout<<"CD balance: "<<temp.getCDBalance()<<endl;
        inFile.close();
        
        inFile.open("transactions.txt");
        int indexOfSpace;
        while(getline(inFile,line)){
            for(int i=line.length()-1;i>=0;i--){
                if(line[i]==' '){
                    indexOfSpace=i;
                    break;
                }   
            }
            if(line.substr(indexOfSpace,line.length()).compare("Checkings")){
                
            }

        }

        cout<<temp.getKey()<<" "<<temp.getAccountNumber()<<endl;
        tree.insertAcc(temp);
    }
}

void setCurrAccount(){
    for(int i =0; i < usersVec.size();i++){
        if(usersVec[i].accntNum!=""){
            tree.searchAcc(d.getKey(usersVec[i].accntNum));
            saveAccounts();
        }
    }

}
