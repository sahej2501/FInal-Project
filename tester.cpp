#include <iostream>
#include <string>
#include <vector>
#include "timeHandler.h"
#include "directoryHandler.h"
using namespace std;


int main(){
    timeHandler t;
    directory d;

    cout<<d.getCurrentDir()<<endl;
    d.createFiles("mike1");
    d.writeToFile("mike1",'t',"scb");
}