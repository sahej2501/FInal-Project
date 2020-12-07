
#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
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



    string encrypt(string msg, int shift){
        shift = ((shift%26)+26)%26;

        string final;

        for(int i =0;i<msg.length();i++){
            if(msg[i]>='a' && msg[i]<='z')
                final+=((msg[i]-'a'+shift)%26+'a');
            else if(msg[i]>='A' && msg[i]<='Z')
                final+=((msg[i]-'A'+shift)%26+'A');
            else
                final+=msg[i];
        }
        return final;
    }

    string decrypt(string msg, int shift){
        return encrypt(msg,26-shift%26);
    }

    void clearFile(string accountNumber,string file){
        string folder = accountsPath+"/"+accountNumber;
        chdir(folder.data());
        ofstream outFile2;
        outFile2.open(file);
        file.clear();

        
    }

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
        fstream outFile;
        ifstream inFile;
        chdir(basePath.data());
        chdir(accountsPath.data());
        string slice = "/";
        string newPath = accountsPath.data()+slice+accountNumber;
        if(chdir(newPath.data())==0){
            switch(fileType){
                case 's':
                    outFile.open("savings.txt",fstream::out|fstream::app);
                    outFile << info << endl;
                    outFile.close();
                    break;
                case 'i':
                    outFile.open("info.txt",fstream::app|fstream::out);
                    outFile << info << endl;
                    outFile.close();
                    break;
                case 'c':
                    outFile.open("checking.txt",fstream::app|fstream::out);
                    outFile << info << endl;
                    outFile.close();
                    break;
                case 't':
                    outFile.open("transactions.txt",fstream::app|fstream::out);
                    outFile << info << endl;
                    outFile.close();
                    break;
                case 'd':
                    outFile.open("cd.txt",fstream::app|fstream::out);
                    outFile << info << endl;
                    outFile.close();
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


    void saveTransactions(vector< vector<string> > transactions,string actN){
        for(int i=0; i<transactions.size();i++){
            for(int j=0;j<transactions[i].size();j++){
                writeToFile(actN,'t',transactions[i][j]);
            }
        }
        chdir(basePath.data());   
    }

    

    

};