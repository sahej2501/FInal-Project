#pragma once
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <mach-o/dyld.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fstream>
#define GetCurrentDir getcwd
using namespace std;

class directory{

public:

    const string basePath= getCurrentDir();

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

    void createFiles(string username){
        mkdir(username.data(), S_IRWXU | S_IRWXG);
        changePath(username);
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

    void writeToFile(string username, char fileType, string info){
        ofstream outFile;
        chdir(basePath.data());
        string newPath = basePath.data()+'/'+username;
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
                    outFile.open("info.txt",ios::app);
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
            cout<<"Could not change directories!"<<endl;
        }
    }
};