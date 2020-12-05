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
string encryptMessage(string m);
string decryptCipher(string c);
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
    saveTransactions(transactions,actN)      ;
    
    // string ac1=generateAC(key);
    // cout<<key<<endl;
    // cout<<d.getKey(ac1)<<endl;

    // string msg = "mike"; 
      
    // //Calling encryption function 
    // string cipherText = encryptMessage(msg.toupp; 
    // cout << "Encrypted Message is : " << cipherText<<endl; 
      
    // //Calling Decryption function 
    // cout << "Decrypted Message is: " << decryptCipher(encryptMessage(msg))<<endl;
    return 0;
}





void saveTransactions(vector< vector<string> > transactions,string actN){
    for(int i=0; i<transactions.size();i++){
        for(int j=0;j<transactions[i].size();j++){
            d.writeToFile(actN,'t',transactions[i][j]);
        }
    }
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
