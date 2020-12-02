#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include "timeHandler.h"
#include "directoryHandler.h"
using namespace std;

int main(){
    timeHandler t1;
    directory dir;

    cout<<"Date 1:"<<t1.formatDate(t1.getCurrentTime())<<endl;
    chdir(dir.basePath.data());
    dir.createFiles("ae87");
    dir.writeToFile("ae87",'t',"+$1000 d/1/12/2020");
    timeHandler::Date d1;
    timeHandler::Date d2;
    d1=t1.getCurrentTime();
    d2.d=2;
    d2.m=12;
    d2.y=2020;
    cout<<"Date 2: "<<t1.formatDate(d2)<<endl;
    cout<<"Difference between date 1 and date 2: "<<t1.getDifference(d1,d2)<<endl;
    return 0;
}