//
//  main.cpp
//  Hw1
//
//  Created by Tomy Hsieh on 2017/9/12.
//  Copyright © 2017年 Tomy Creative Studio. All rights reserved.
//
//  聽說，檔，不可以沒有註解(?)

#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main()
{
    int number; // integer read from user
    
    cout << "Enter an integer: "; // prompt
    cin >> number; // read integer from user
    
    //determine output
    if (number % 2 == 1)
        cout << "The integer " << number << " is odd.\n";
    else
        cout << "The integer " << number << " is even.\n";
} // end main
