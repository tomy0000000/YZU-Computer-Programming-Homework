//
//  main.cpp
//  Hw5
//
//  Created by Tomy Hsieh on 2017/9/12.
//  Copyright © 2017年 Tomy Creative Studio. All rights reserved.
//
//  聽說，檔，不可以沒有註解(?)

#include <iostream>
using namespace std;

int main() {
    
    int year; // integer read from user
    bool Leap; // Boolean record result
    
    cout << "Enter a year: "; // prompt
    cin >> year; //read integer from user
    
    Leap = false; // set defalut as common
    
    //Determaine 1st type of Leap Year
    if (year%4 == 0 && year%100 != 0)
        Leap = true;

    //Determaine 2nd type of Leap Year (if not the 1st type)
    if (Leap == false && year%400 == 0)
        Leap = true;
    
    //Print results
    if (Leap == true)
        cout << "Year " << year << " is a leap year." << endl;
    else
        cout << "Year " << year << " is a common year." << endl;
}
