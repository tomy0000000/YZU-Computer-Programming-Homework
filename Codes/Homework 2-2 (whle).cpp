//
//  main.cpp
//  Hw2-2 (while)
//  Print Factors
//
//  Created by Tomy Hsieh on 2017/9/20.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    
    int Num, Counter=1; //Initialize ints
    
    //Prompt for Number
    cout << "Enter a positive integer: ";
    cin >> Num;
    cout << endl << "The positive factors of 1000:" << endl;
    
    //Loop from 1 to $Num
    while (Counter <= Num) {
        if (Num%Counter == 0) { //print out counter if mod result equal zero
            cout << Counter << endl;
        }
        Counter++; //$Counter+1
    }
    
    cout << endl; //print one more EOF to qualify the format
    
}
