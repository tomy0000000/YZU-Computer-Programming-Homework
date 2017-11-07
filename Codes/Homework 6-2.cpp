//
//  main.cpp
//  Hw6-2
//  Print Number Respectivly with 2 Recursive Funtion
//
//  Created by Tomy Hsieh on 2017/10/16.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

// Returns a Power of 10 which has the Same Length as Number
int powerTen(int number);

// Prints The Digits of Number
void digits(int number, int power);

int main()
{
    
    int number;
    cout << "Enter a positive integer: ";
    cin >> number;
    
    int power = powerTen(number);
    
    cout << endl << powerTen(number) << endl << endl;
    
    cout << "The digits: ";
    digits(number, power);
    cout << endl;
    
}

int powerTen(int number) {
    
    if (number<10) {
        return 1;
    }
    else {
        return powerTen(number/10)*10;
    }
    
}

void digits(int number, int power) {
    
    if (power == 1) {
        cout << number << endl;
    }
    else {
        cout << (number/power) << " ";
        digits(number%power, power/10);
    }
    
}
