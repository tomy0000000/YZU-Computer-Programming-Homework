//
//  main.cpp
//  Hw3
//
//  Created by Tomy Hsieh on 2017/9/12.
//  Copyright © 2017年 Tomy Creative Studio. All rights reserved.
//
//  聽說，檔，不可以沒有註解(?)

#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
    int number, dig1, dig2, dig3, dig4, dig5; // integer read from user
    
    cout << "Enter a 5-digits integer: "; // prompt
    cin >> number; //read integer from user
    
    //load each digits
    dig5 = number / 10000;
    dig4 = number / 1000 - dig5 * 10;
    dig3 = number / 100 - dig5 * 100 - dig4 * 10;
    dig2 = number / 10 - dig5 * 1000 - dig4 * 100 - dig3 * 10;
    dig1 = number / 1 - dig5 * 10000 - dig4 * 1000 - dig3 * 100 - dig2 * 10;
    
    //print results
    if (dig1 == dig5 && dig2 == dig4)
        cout << number << " is a palindrome!!!" << endl;
    else
        cout << number << " is not a palindrome." << endl;
    
} // end main
