#include <iostream>
#include "timeHandler.h"
#include "AccountNode.h"
#include "Bank.h"
#include "directoryHandler.h"
#include <ctime>
#include <string>
using namespace std;

int key=3000;
const int a=17;
const int b=20;

string generateAC(int keyPassed);
string encrypt(string msg, int shift);
string decrypt(string msg, int shift);
void saveTransactions(vector< vector<string> > transactions,string actN);
timeHandler t;
directory d;
int main(){

    Date d1 = t.getCurrentTime();
    Date d2;
    BankTree tree;
    AllAccounts account1;
    account1.setAccountNumber("ae87");
    string actN=account1.getAccountNumber();
    cout<<"Account number: "<<actN<<endl;
    d.createFiles(account1.getAccountNumber());
    vector< vector<string> > transactions;
    account1.savingsDeposit(100);
    account1.savingsDeposit(20);
    account1.checkingDeposit(50);
    account1.CDDeposit(200);
    transactions= account1.getTransactionHst();
    d.saveTransactions(transactions,actN);
    
    string test="Mike Gegg";
    int shift=1;
    string encrypted= encrypt(test,shift);
    string decrypted = decrypt(encrypted,shift);

    cout<<"Encrypted: "<<encrypted<<endl;
    cout<<"Decrypted: "<<decrypted<<endl;


    return 0;
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
