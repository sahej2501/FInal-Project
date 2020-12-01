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
        file.open("Savings.txt");
        file.close();
        file.open("CD.txt");
        file.close();
        file.open("Info.txt");
        file.close();
        file.open("Transactions.txt");
        file.close();
    }

    
};