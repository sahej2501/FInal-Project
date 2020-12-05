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
    d2.d=8;
    d2.m=12;
    d2.y=2020;
    cout<<t.getDifference(d1,d2)<<endl;
    BankTree tree;
    AllAccounts account1;
    account1.setAccountNumber("ae87");
    cout<<account1.getAccountNumber()<<endl;
    d.createFiles(account1.getAccountNumber());
    account1.savingsDeposit(100000);
    tree.insertAcc(account1);
    tree.searchAcc(0);
    return 0;
}