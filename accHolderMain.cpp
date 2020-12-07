//Sahej 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Bank.h"
#include "regex"
#include "AccountNode.h"
#include "directoryHandler.h"
#include "timeHandler.h"

using namespace std;

struct Official
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

vector<User> usersVec;
int key = 0;
BankTree tree;
timeHandler t;
directory d;
vector<ClosedAccounts> cAccounts;
vector<AllAccounts> balanced;
vector<AllAccounts> og;


string generateAC(int keyPassed);
void openAccount(AllAccounts &);
void createOfficial(string, string, vector<Official> &officialsVec);
void readOfficialLogins(vector<Official> &officialsVec);
int getKey(string line);
void depOrWidth();
void createUser(string, string, string, vector<User> &usersVec);
bool LoginPasswordMatch(string id, string pswd, vector<User> &usersVec);
void shutAcc();
void balanceTree(vector<AllAccounts> og, vector<AllAccounts> &balanced, int start, int end);


int main()
{

    //AllAccounts newAccount;
    bankAcc currAcc;
    int key = 0;

    bool run = true;

    //test for balance
    AllAccounts a1;
    AllAccounts a2;
    AllAccounts a3;
    AllAccounts a4;
    AllAccounts a5;
    AllAccounts a6;
    AllAccounts a7;

    og.push_back(a1);
    og.push_back(a2);
    og.push_back(a3);
    og.push_back(a4);
    og.push_back(a5);
    og.push_back(a6);
    og.push_back(a7);
    

    for(int i = 0; i < og.size(); i++)
    {
        og[i].setKey(key);
        key++;
    }

    balanceTree(og, balanced, 0, og.size() - 1);

    for(int i = 0; i < og.size(); i++)
    {
        //cout<<og[i].getKey()<<" ";
    }

    for(int i = 0; i < balanced.size(); i++)
    {
        //cout<<'\n'<<balanced[i].getKey()<<" ";
        tree.insertAcc(balanced[i]);
    }

    tree.displayAllAccounts();
    


    
    // while (run)
    // {
    // int selection;
    // string accNumBO;
    // cout<<"[1] Open a account"<<'\n'<<"[2] Close account"<<'\n'<<"[3] Search for a account"<<
    // '\n'<<"[4] Withdraw or Deposit to an account"<<'\n'<<"[5] Exit"<<endl;
    // cin>>selection;
    // switch (selection)
    // {
    // case 1:
    //     cin.ignore();
    //     openAccount(newAccount);
    //     //tree.insertAcc(newAccount);
    //     break;
    // case 2:
    //     cin.ignore();
    //     shutAcc();
    //     break;
    // case 3:
    //     cin.ignore();
    //     bool isThere;
    //     //string accNumBO;
    //     cout<<"Please Enter Bank Account Number: "<<endl;
    //     cin>>accNumBO;
    //     isThere = tree.searchAcc(d.getKey(accNumBO));
    //     if(isThere)
    //     {
    //         cout<<tree.currAccount.getAccountNumber()<<'\n'<<tree.currAccount.getName()<<'\n'<<tree.currAccount.getPhone()<<'\n'
    //         <<tree.currAccount.getAddress()<<endl;
    //     }
    //     break;
    // case 4:
    //     cin.ignore();
    //     depOrWidth();
    //     break;
    // case 5:
    //     run = false;
    //     break;
    // default:
    //     cout<<"Error, invalid Selection"<<endl;
    //     break;
    // }
    // //cin.ignore();
    // }
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
    a.setKey(getKey(accNum));
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

int getKey()
{
    string AccNum;
    int key;
    cout<<"Enter a Account Number: "<<endl;
    cin>>AccNum;
    AccNum = AccNum.substr(0, 2);
    key = stoi(AccNum);

    return key;
}

void createOfficial(string id, string pswd, vector<Official> &officialsVec)
{
    Official newOff;
    newOff.username = id;
    newOff.password = pswd;
    officialsVec.push_back(newOff);
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

void createUser(string id, string pswd, string accntNum, vector<User> &usersVec)
{
    User newUser;
    newUser.username = id;
    newUser.password = pswd;
    newUser.accntNum = accntNum;
    cout<<"Account Number is: "<<accntNum<<endl;
    usersVec.push_back(newUser);
    // for(int i = 0; i < usersVec.size(); i++)
    // {
    //     cout<<usersVec[i].username<<" "<<usersVec[i].password<<endl;
    // }
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

int getKey(string line)
{
    regex keyFinder("^\\d*");
    smatch s;

    regex_search(line, s, keyFinder);
    return stoi(s[0]);
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

void shutAcc()
{
    string accNumBO, currInfo;
    ClosedAccounts c;
    cout<<"Please Enter Bank Account Number: "<<endl;
    cin>>accNumBO;
    tree.removeAcc(d.getKey(accNumBO));
    tree.searchAcc(d.getKey(accNumBO));

    currInfo = tree.currAccount.getName() + " " + tree.currAccount.getPhone() + tree.currAccount.getAddress() + 
    t.formatDate(t.getCurrentTime());

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

void balanceTree(vector<AllAccounts> og, vector<AllAccounts> &balanced, int start, int end)
{
    if(start > end)
        return;

    int mid = (start+end)/2;
    AllAccounts curr = og[mid];
    balanced.push_back(curr);

    balanceTree(og, balanced, start, mid - 1);
    balanceTree(og, balanced, mid + 1, end);
}