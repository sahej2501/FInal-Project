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
    account1.setAccountNumber("0000000000");
    string actN=account1.getAccountNumber();
    cout<<"Account number: "<<actN<<endl;
    d.createFiles(account1.getAccountNumber());
    account1.savingsDeposit(100);
    account1.savingsDeposit(20);
    vector <string> transactions= account1.getTransactionHst();
    for(int i =0; i <transactions.size();i++){
        d.writeToFile(actN,'t',transactions[i]);
    }
    return 0;
}