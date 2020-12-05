#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#include "accounts.h"
#include "AccountNode.h"
#include "regex"
#define GetCurrentDir getcwd
using namespace std;

class directory{

public:

    const string basePath= getCurrentDir();
    const string accountsPath = basePath+"/accounts";
    int accountCount=0;

    void changePath(string actN){
        string newPath;
        newPath+=basePath+"/"+accountsPath+"/"+actN;
        const char* changedPath=newPath.data();
        chdir(changedPath);
    }

    string getCurrentDir(){
        char buff[FILENAME_MAX]; //create string buffer to hold path
        GetCurrentDir( buff, FILENAME_MAX );
        string current_working_dir(buff);
        return current_working_dir;
    }

    void createFiles(string actN){
        chdir(basePath.data());
        chdir(accountsPath.data());
        mkdir(actN.data(), S_IRWXU | S_IRWXG);
        string newDirPath= accountsPath+"/"+actN;
        chdir(newDirPath.data());
        ofstream file;
        file.open("checkings.txt");
        file.close();
        file.open("savings.txt");
        file.close();
        file.open("cd.txt");
        file.close();
        file.open("info.txt");
        file.close();
        file.open("transactions.txt");
        file.close();
    }

    void writeToFile(string accountNumber, char fileType, string info){
        ofstream outFile;
        chdir(basePath.data());
        chdir(accountsPath.data());
        string slice = "/";
        string newPath = accountsPath.data()+slice+accountNumber;
        if(chdir(newPath.data())==0){
            switch(fileType){
                case 's':
                    outFile.open("savings.txt",ios::app);
                    outFile << info << endl;
                    break;
                case 'i':
                    outFile.open("info.txt",ios::app);
                    outFile << info << endl;
                    break;
                case 'c':
                    outFile.open("checking.txt",ios::app);
                    outFile << info << endl;
                    break;
                case 't':
                    outFile.open("transactions.txt",ios::app);
                    outFile << info << endl;
                    break;
                case 'd':
                    outFile.open("cd.txt",ios::app);
                    outFile << info << endl;
                    break;
                default:
                    cout<<"File not found error!"<<endl;
            }
        }
        else{
            cout<<"writing to file failed"<<endl;
        }
    }

    //gets a line passed in and returns the key aka the first n digits
    int getKey(string line){
        regex keyFinder("^\\d*");
        smatch s;

        regex_search(line, s, keyFinder);
        return stoi(s[0]);
    }


    string encryptMessage(string msg) { 
        ///Cipher Text initially empty 
        string cipher = "";  
        for (int i = 0; i < msg.length(); i++) { 
            // Avoid space to be encrypted  
            if(msg[i]!=' ')  
                /* applying encryption formula ( a x + b ) mod m 
                {here x is msg[i] and m is 26} and added 'A' to  
                bring it in range of ascii alphabet[ 65-90 | A-Z ] */
                cipher = cipher +  (char) ((((a * (msg[i]-'A') ) + b) % 26) + 'A'); 
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


};