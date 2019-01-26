//
//  main.cpp
//  Hw2-2 (for)
//  Print Factors
//
//  Created by Tomy Hsieh on 2017/9/20.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    
    int Num; //Initialize ints
    
    //Prompt for Number
    cout << "Enter a positive integer: ";
    cin >> Num;
    cout << endl << "The positive factors of 1000:" << endl;
    
    for (int Counter=1; Counter <= Num; Counter++) {
        if (Num%Counter == 0) { //print out counter if mod result equal zero
            cout << Counter << endl;
        }
    }
    
    cout << endl; //print one more EOF to qualify the format
    
}
