//
//  main.cpp
//  Hw6-1
//  Caculate Digit with Recusive
//
//  Created by Tomy Hsieh on 2017/10/16.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int numDigits(int number);

int main() {
    
    int number;
    cout << "Enter a positive integer: ";
    cin >> number;
    
    cout << "\nThe number of digits of " << number << ": ";
    cout << numDigits(number) << endl << endl; //Calling Function First Time
    
}

int numDigits(int number) {
    
    if (number < 10) { //Return 1 if number<10
        return 1;
    }
    else {
        return numDigits(number/10) + 1; //Keep Calling Function until number<10
    }
    
}
