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
#define GetCurrentDir getcwd
using namespace std;

class directory{

public:

    const string basePath= getCurrentDir();
    const string accountsPath = basePath+"/accounts";

    void changePath(string path){
        string newPath;
        newPath+=basePath+"/"+path;
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
        cout<<newDirPath<<endl;
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
        cout<<"Account number in writeToFile: "<<accountNumber;
        string newPath = accountsPath.data()+slice+accountNumber;
        cout<<newPath<<endl;
        if(chdir(newPath.data())==0){
            cout<<"Was able to switch path"<<endl;
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
                    cout<<"Info: "<<info<<endl;
                    cout<<"Writing transaction successful!"<<endl;
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
};