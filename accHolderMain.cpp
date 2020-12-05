//Sahej 

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Bank.h"
#include "regex"
#include "AccountNode.h"
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

vector<User> usersVec;
int key = 0;
BankTree tree;


string generateAC(int keyPassed);
void openAccount(AllAccounts &);
void createOfficial(string, string, vector<Official> &officialsVec);
void readOfficialLogins(vector<Official> &officialsVec);
int getKey();
void depOrWidth();
void createUser(string, string, string, vector<User> &usersVec);
bool LoginPasswordMatch(string id, string pswd, vector<User> &usersVec);

int main()
{
    
    void createUser(string, string, string, vector<User> &usersVec);

    //test object for search
    // AllAccounts r, c, x;
    // r.setKey(001);
    // c.setKey(002);
    // x.setKey(003);
    // tree.insertAcc(c);
    // tree.insertAcc(x);
    // r.setFirstLastName("Sahej", "Bhatia");
    // r.setPhone("417-425-2478");
    // r.setAddress("1001 E Harrison St Springfield MO 65807");
    // tree.insertAcc(r);
    // tree.searchAcc(001);
    //*************************

    timeHandler t;
    vector<string> closedAccounts;
    
    // for(int i = 0; i < 10; i++)
    // {
    //     AllAccounts tempAcc;
    //     tempAcc.setKey(i);
    //     tree.insertAcc(tempAcc);
    // }

    AllAccounts newAccount;
    bankAcc currAcc;
    // cout<<"[1] Open a account"<<'\n'<<"[2] Close account"<<'\n'<<"[3] Search for a account"<<
    // '\n'<<"[4] Withdraw or Deposit to an account"<<endl;
    bool run = true;
    // cin>>selection;
    while (run)
    {
    int selection;
    cout<<"[1] Open a account"<<'\n'<<"[2] Close account"<<'\n'<<"[3] Search for a account"<<
    '\n'<<"[4] Withdraw or Deposit to an account"<<endl;
    cin>>selection;
    switch (selection)
    {
    case 1:
        cin.ignore();
        openAccount(newAccount);
        newAccount.setKey(001);
        tree.insertAcc(newAccount);
        break;
    case 2:
        cin.ignore();
        tree.removeAcc(002);
        closedAccounts.push_back(tree.closeInfo + t.formatDate(t.getCurrentTime()));
        //Checking to see if close info was updated
        for(int i = 0; i < closedAccounts.size(); i++)
        {
            cout<<closedAccounts[i]<<endl;
        }
        break;
    case 3:
        tree.searchAcc(001);
        break;
    case 4:
        break;
    case 5:
        run = false;
        cout<<"Error, invalid Selection"<<endl;
        break;
    }
    //cin.ignore();
    }
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
    a.setAccountNumber(accNum);

    //Entering Name for new user
    cout<<"Please Enter Your Full Name"<<endl;
    getline(cin, name);
    firstName = name.substr(0, name.find(" "));
    lastName = name.substr(name.find(" "), name.length());
    a.setFirstLastName(firstName, lastName);
    //cin.ignore();

    //Entering Phone number
    cout<<"Please Enter a Phone Number for the Account (format: xxx-xxx-xxxx): "<<endl;
    getline(cin, phone);
    a.setPhone(phone);
    //cin.ignore();

    //Entering Address
    cout<<"Enter a Address for the account: "<<endl;
    getline(cin, address);
    a.setAddress(address);

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
        getline(cin, login);
        cout<<"Please enter user Password: "<<endl;
        getline(cin, password);
        for(int i = 0; i < usersVec.size(); i++)
        {
            if(login == usersVec[i].username && password == usersVec[i].password)
            {
                accountNum = usersVec[i].accntNum;
                run = true;
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

    int tempKey = getKey(accountNum);
    tree.searchAcc(tempKey);
    tree.modifi(currAcount);
    

    bool run2 = true;
    while(run2)
    {
        cout<<"[1] Savings"<<'\n'<<"[2] Checkings"<<'\n'<<"[3] CD"<<'\n'<<"[4] Quit"<<endl;
        int choose;
        cin>>choose;
        switch(choose)
        {
        case 1:
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Back"<<endl;
            int check;
            bool run = true;
            cin>>check;
            while(run)
            {
                 if(check == 1)
                {
                    int dep;
                    cout<<"Enter deposit ammount"<<endl;
                    cin>>dep;
                    currAcount.savingsDeposit(dep);
                    cout<<"Done"<<endl;
                }
                else if(check == 2)
                {
                    int dep;
                    cout<<"Enter withdraw ammount"<<endl;
                    cin>>dep;
                    currAcount.savingsWithdraw(dep);
                    cout<<"Done"<<endl;
                }
                else if (check == 3)
                {
                    currAcount.getSavingsBalance();
                }
                else if(check == 4)
                {
                    run = false;
                    break;
                }
            }
            break;
        case 2:
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Back"<<endl;
            int check;
            bool run = true;
            cin>>check;
            while(run)
            {
                 if(check == 1)
                {
                    int dep;
                    cout<<"Enter deposit ammount"<<endl;
                    cin>>dep;
                    currAcount.checkingDeposit(dep);
                    cout<<"Done"<<endl;
                }
                else if(check == 2)
                {
                    int dep;
                    cout<<"Enter withdraw ammount"<<endl;
                    cin>>dep;
                    currAcount.checkingWithdraw(dep);
                    cout<<"Done"<<endl;
                }
                else if (check == 3)
                {
                    currAcount.getCheckingBalance();
                }
                else if(check == 4)
                {
                    run = false;
                    break;
                }
            }
            break;
        case 3:
            cout<<"[1] Deposit"<<'\n'<<"[2] Withdraw"<<'\n'<<
            "[3] Check Balance"<<'\n'<<"[4] Cancel"<<'\n'<<"[5] Back"<<endl;
            int check;
            bool run = true;
            cin>>check;
            while(run)
            {
                 if(check == 1)
                {
                    int dep;
                    cout<<"Enter deposit ammount"<<endl;
                    cin>>dep;
                    currAcount.CDDeposit(dep);
                    cout<<"Done"<<endl;
                }
                else if(check == 2)
                {
                    int dep;
                    cout<<"Enter withdraw ammount"<<endl;
                    cin>>dep;
                    currAcount.savingsWithdraw(dep);
                    cout<<"Done"<<endl;
                }
                else if (check == 3)
                {
                    currAcount.getSavingsBalance();
                }
                else if(check = 4)
                {
                    currAcount.cdCancel();
                    cout<<"Done"<<endl;
                }
                else if(check == 5)
                {
                    run = false;
                    break;
                }
            }
            break;
        case 4:
            run2 = false;
            break;
        
        default:
            cout<<"Please Enter a Valid choice"<<endl;
            break;
        }
    tree.upadteAcc(currAcount.getKey(), currAcount);
}
   



    





}

void createUser(string id, string pswd, string accntNum, vector<User> &usersVec)
{
    User newUser;
    newUser.username = id;
    newUser.password = pswd;
    newUser.accntNum = accntNum;
    usersVec.push_back(newUser);
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