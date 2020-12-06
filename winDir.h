
#include <stdio.h>  /* defines FILENAME_MAX */
#define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <iostream>
#include <filesystem>
#include <vector>
#include <windows.h> 
#include <stdio.h>
#include <tchar.h>
#include <cstring>
#include <string>
#include <fstream>
#include <regex>


using namespace std;

class directory {

public:
	TCHAR szDir[MAX_PATH];
    const string dir = getCurrentDir();
    const string accountsDir = getCurrentDir() + "\\accounts";
    int accountCount = 0;


    string getCurrentDir() {
        char buff[FILENAME_MAX];
        GetCurrentDir(buff, FILENAME_MAX);
        string current_working_dir(buff);
        return current_working_dir;
    }

    void gotoBaseDir() {
        TCHAR baseDir[MAX_PATH];
        for (int i = 0; i < dir.length(); i++) {
            baseDir[i] = dir[i];
        }
        SetCurrentDirectory(baseDir);
    }


    void createFiles(string accountNumber) {
        gotoBaseDir();
        _mkdir(accountNumber.data());
        TCHAR newDir[MAX_PATH];
        string newPath = dir + "\\accounts\\"+accountNumber;
        for (int i = 0; i < newPath.length(); i++) {
            newDir[i] = newPath[i];
        }
        SetCurrentDirectory(newDir);
        ofstream savings{ "savings.txt" };
        ofstream checkings{ "checkings.txt" };
        ofstream info{ "info.txt" };
        ofstream transactions{ "transactions.txt" };
        ofstream cd{ "cd.txt" };

    }

    void writeToFile(string accountNumber, char fileType, string info) {
        ofstream outFile;
        TCHAR newDir[MAX_PATH];
        gotoBaseDir();
        string newPath = dir + "\\accounts\\" + accountNumber;
        for (int i = 0; i < newPath.length(); i++) {
            newDir[i] = newPath[i];
        }
        if (SetCurrentDirectory(newDir) != 0) {
            switch (fileType) {
            case 's':
                outFile.open("savings.txt", ios::app);
                outFile << info << endl;
                break;
            case 'i':
                outFile.open("info.txt", ios::app);
                outFile << info << endl;
                break;
            case 'c':
                outFile.open("checking.txt", ios::app);
                outFile << info << endl;
                break;
            case 't':
                outFile.open("transactions.txt", ios::app);
                outFile << info << endl;
                break;
            case 'd':
                outFile.open("cd.txt", ios::app);
                outFile << info << endl;
                break;
            default:
                cout << "File not found error!" << endl;
            }
        }
    }


    int getKey(string line) {
        regex keyFinder("^\\d*");
        smatch s;

        regex_search(line, s, keyFinder);
        return stoi(s[0]);
    }


    void saveTransactions(vector< vector<string> > transactions, string actN) {
        for (int i = 0; i < transactions.size(); i++) {
            for (int j = 0; j < transactions[i].size(); j++) {
                writeToFile(actN, 't', transactions[i][j]);
            }
        }
    }


    string encrypt(string msg, int shift) {
        shift = ((shift % 26) + 26) % 26;

        string final;

        for (int i = 0; i < msg.length(); i++) {
            if (msg[i] >= 'a' && msg[i] <= 'z')
                final += ((msg[i] - 'a' + shift) % 26 + 'a');
            else if (msg[i] >= 'A' && msg[i] <= 'Z')
                final += ((msg[i] - 'A' + shift) % 26 + 'A');
            else
                final += msg[i];
        }
        return final;
    }

    string decrypt(string msg, int shift) {
        return encrypt(msg, 26 - shift % 26);
    }


};