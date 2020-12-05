#include <iostream>
#include "timeHandler.h"
#include "AccountNode.h"
#include "Bank.h"
#include "directoryHandler.h"
using namespace std;

int main(){
    timeHandler t;
    directory d;
    Date d1 = t.getCurrentTime();
    Date d2;
    BankTree tree;
    AllAccounts account1;
    account1.setAccountNumber("ae87");
    string actN=account1.getAccountNumber();
    //cout<<"Account number: "<<actN<<endl;
    d.createFiles(account1.getAccountNumber());
    vector <string> transactions;
    account1.savingsDeposit(100);
    account1.savingsDeposit(20);
    account1.checkingDeposit(50);
    transactions= account1.getTransactionHst();
    cout<<"\nTransactions size: "<<transactions.size()<<endl;
    for(int i =0; i <transactions.size();i++){
        d.writeToFile(actN,'t',transactions[i]);
    }
    return 0;
}