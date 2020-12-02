#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
using namespace std;

struct Date{
        int d,m,y;
    };

class timeHandler{

protected:
    
    const int monthDays[12]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

public:
    
    Date getCurrentTime(){
            time_t now = time(0);
            Date tempDate;
            vector <Date> storedDates;
            tm *ltm = localtime(&now);
            int year= 1900 + ltm->tm_year;
            int month= 1 + ltm->tm_mon;
            int day= ltm->tm_mday;
            tempDate.y=year;
            tempDate.m=month;
            tempDate.d=day;

            return tempDate;
        }

        int countLeapYears(Date d) { 
            int years = d.y; 
  
            // Check if the current year needs to be considered 
            // for the count of leap years or not 
            if (d.m <= 2) 
                years--; 
  
            // An year is a leap year if it is a multiple of 4, 
            // multiple of 400 and not a multiple of 100. 
            return years / 4 - years / 100 + years / 400; 
        } 

        int getDifference(Date dt1, Date dt2) { 
        // COUNT TOTAL NUMBER OF DAYS BEFORE FIRST DATE 'dt1' 
  
        // initialize count using years and day 
            long int n1 = dt1.y*365 + dt1.d; 
  
        // Add days for months in given date 
            for (int i=0; i<dt1.m - 1; i++) 
                n1 += monthDays[i]; 
  
        // Since every leap year is of 366 days, 
        // Add a day for every leap year 
            n1 += countLeapYears(dt1); 
  
        // SIMILARLY, COUNT TOTAL NUMBER OF DAYS BEFORE 'dt2' 
  
            long int n2 = dt2.y*365 + dt2.d; 
            for (int i=0; i<dt2.m - 1; i++) 
                n2 += monthDays[i]; 
            n2 += countLeapYears(dt2); 
  
        // return difference between two counts 
            return (n2 - n1); 
        } 

        string formatDate(Date date){
            string formattedDate= "d/"+to_string(date.d)+"/"+to_string(date.m)+"/"+to_string(date.y);
            return formattedDate;
        }



};