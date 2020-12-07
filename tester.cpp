

#include <iostream>
#include "timeHandler.h"
#include "AccountNode.h"
#include "Bank.h"
#include <string>
#include <sstream>
#include <fstream>
#include "directoryHandler.h"
#include "timeHandler.h"

#include <ctime>
using namespace std;

int key=3000;
directory d;
timeHandler t;
BankTree tree;

struct User
{
    string username;
    string password;
    string accntNum;
};

vector<User> usersVec;


void saveAccounts(){

    
    //tree.currAccount.get()...
    ofstream outFile;
    chdir(d.basePath.data());
    string newPath = d.accountsPath+"/"+tree.currAccount.getAccountNumber();
    chdir(newPath.data());

    //saving to checkings
    outFile.open("checkings.txt");
    if(outFile){
        cout<<"file opened"<<endl;
    }
    outFile << to_string(tree.currAccount.getCheckingBalance())<<endl;
    outFile.close();
    
    //saving to savings
    outFile.open("savings.txt");
    outFile << to_string(tree.currAccount.getSavingsBalance())<<endl;
    outFile.close();

    //saving to info
    outFile.open("info.txt");
    outFile << tree.currAccount.getFirstName() <<endl;
    outFile << tree.currAccount.getLastName() <<endl;
    outFile << tree.currAccount.getPhone() <<endl;
    outFile <<tree.currAccount.getAddress() <<endl;
    outFile<< t.formatDate(tree.currAccount.getOpenDate())<<endl;
    outFile<<tree.currAccount.getAccountNumber()<<endl;
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

void readAccounts(){
    directory d;
    AllAccounts temp;
    Date tempDate;
    ifstream inFile;
    string line, fname, lname;
    double checkB, saveB, cdB;
    vector <string> lines;
    vector <string> date,sT,cT,cdT,allT;
    char delim = '/';
    for (int i =0; i<usersVec.size();i++){
        string accNum=usersVec[i].accntNum;
        string newPath = d.accountsPath+"/"+accNum;
        chdir(newPath.data());
        inFile.open("info.txt");
        while(getline(inFile,line)){
            lines.push_back(line);
        }
        cout<<lines.size()<<endl;
        fname=lines[0];
        lname=lines[1];
        temp.setFirstLastName(fname, lname);
        temp.setPhone(lines[2]);
        temp.setAddress(lines[3]);
        temp.setAccountNumber(lines[5]);
        temp.setKey(d.getKey(temp.getAccountNumber()));
        cout<<temp.getKey()<<endl;
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
        cdB=stod(lines[2]);
        temp.setBalance(saveB, checkB, cdB);
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
        
        cout<<temp.getName()<<endl;
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


int main(){
    User u1;
    u1.username="mike";
    u1.password="gegg";
    u1.accntNum="000ae87";
    usersVec.push_back(u1);
    cout<<"UsersvecSize: "<<usersVec.size()<<endl;
    timeHandler t;
    directory d;
    Date d1 = t.getCurrentTime();
    Date d2;
    BankTree tree;
    AllAccounts account1;
    account1.setAccountNumber("000ae87");
    string actN=account1.getAccountNumber();
    //cout<<"Account number: "<<actN<<endl;
    //d.createFiles(account1.getAccountNumber());
    vector< vector<string> > transactions;

    account1.savingsDeposit(400.0);
    account1.savingsDeposit(11.0);
    account1.CDDeposit(100.0);
    readAccounts();
    setCurrAccount();
    
    
    return 0;
}



