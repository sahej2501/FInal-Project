#include <iostream>
#include "timeHandler.h"
#include "AccountNode.h"
#include "Bank.h"
#include "directoryHandler.h"
#include <ctime>
using namespace std;

int key=3000;
const int a=17;
const int b=20;

string generateAC(int keyPassed);
string encryptMessage(string m);
string decryptCipher(string c);

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
    vector< vector<string> > transactions;
    // account1.savingsDeposit(100);
    // account1.savingsDeposit(20);
    // account1.checkingDeposit(50);
    // account1.CDDeposit(200);
    // transactions= account1.getTransactionHst();
    // for(int i=0; i<transactions.size();i++){
    //     for(int j=0;j<transactions[i].size();j++){
    //         d.writeToFile(actN,'t',transactions[i][j]);
    //     }
    // }       
    
    // string ac1=generateAC(key);
    // cout<<key<<endl;
    // cout<<d.getKey(ac1)<<endl;

   string msg = "AFFINE CIPHER"; 
      
    //Calling encryption function 
    string cipherText = encryptMessage(msg); 
    cout << "Encrypted Message is : " << cipherText<<endl; 
      
    //Calling Decryption function 
    cout << "Decrypted Message is: " << decryptCipher(encryptMessage(msg))<<endl;
    return 0;
}


string encryptMessage(string msg) 
{ 
    ///Cipher Text initially empty 
    string cipher = "";  
    for (int i = 0; i < msg.length(); i++) 
    { 
        // Avoid space to be encrypted  
        if(msg[i]!=' ')  
            /* applying encryption formula ( a x + b ) mod m 
            {here x is msg[i] and m is 26} and added 'A' to  
            bring it in range of ascii alphabet[ 65-90 | A-Z ] */
            cipher = cipher +  
                        (char) ((((a * (msg[i]-'A') ) + b) % 26) + 'A'); 
        else
            //else simply append space character 
            cipher += msg[i];      
    } 
    return cipher; 
} 
  
string decryptCipher(string cipher) 
{ 
    string msg = ""; 
    int a_inv = 0; 
    int flag = 0; 
      
    //Find a^-1 (the multiplicative inverse of a  
        //in the group of integers modulo m.)  
    for (int i = 0; i < 26; i++) 
    { 
        flag = (a * i) % 26; 
          
        //Check if (a*i)%26 == 1, 
                //then i will be the multiplicative inverse of a 
        if (flag == 1) 
        {  
            a_inv = i; 
        } 
    } 
    for (int i = 0; i < cipher.length(); i++) 
    { 
        if(cipher[i]!=' ') 
            /*Applying decryption formula a^-1 ( x - b ) mod m  
            {here x is cipher[i] and m is 26} and added 'A'  
            to bring it in range of ASCII alphabet[ 65-90 | A-Z ] */
            msg = msg +  (char) (((a_inv * ((cipher[i]+'A' - b)) % 26)) + 'A'); 
        else
            //else simply append space characte 
            msg += cipher[i];  
    } 
  
    return msg; 
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
