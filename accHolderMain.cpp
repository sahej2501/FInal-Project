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

void openAccount(AllAccounts &);
int getKey();

int main()
{
    BankTree tree;

    //test object for search
    AllAccounts r, c, x;
    r.setKey(001);
    c.setKey(002);
    x.setKey(003);
    tree.insertAcc(c);
    tree.insertAcc(x);
    r.setFirstLastName("Sahej", "Bhatia");
    r.setPhone("417-425-2478");
    r.setAddress("1001 E Harrison St Springfield MO 65807");
    tree.insertAcc(r);
    tree.searchAcc(001);
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
    int selection;
    // cin>>selection;
    while (selection != 5)
    {
    cout<<"[1] Open a account"<<'\n'<<"[2] Close account"<<'\n'<<"[3] Search for a account"<<
    '\n'<<"[4] Withdraw or Deposit to an account"<<endl;
    cin>>selection;
    switch (selection)
    {
    case 1:
        cin.ignore();
        openAccount(newAccount);
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
        tree.searchAcc(002);
        break;
    case 4:
        break;
    default:
        cout<<"Error, invalid Selection"<<endl;
        break;
    }
    cin.ignore();
    }
}

void openAccount(AllAccounts &a)
{
    string name, firstName, lastName, phone, address;

    //Entering Name for new user
    cout<<"Please Enter Your Full Name"<<endl;
    getline(cin, name);
    firstName = name.substr(0, name.find(" "));
    lastName = name.substr(name.find(" "), name.length());
    a.setFirstLastName(firstName, lastName);
    cin.ignore();

    //Entering Phone number
    cout<<"Please Enter a Phone Number for the Account (format: xxx-xxx-xxxx): "<<endl;
    getline(cin, phone);
    a.setPhone(phone);
    cin.ignore();

    //Entering Address
    cout<<"Enter a Address for the account: "<<endl;
    getline(cin, address);
    a.setAddress(address);
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
