//
//  main.cpp
//  Hw2-3 (for)
//  Print in Reverse-Order
//
//  Created by Tomy Hsieh on 2017/9/20.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h> //Import to use functions: pow() & log10()
using namespace std;

int main() {
    
    double Num, Len, Power, Digit, End=0; //Initialize ints
    //string str;
    
    //Prompt for Number
    cout << "Enter a positive integer: ";
    cin >> Num;
    cout << endl << "The reverse of " << setprecision(0) << fixed << Num << ": ";
    
    //Calculate the length of the Number and Initialize Array
    Len = int(log10(Num)+1);
    double Splited[int(Len)];
    
    //Loop Digits and place into Array
    for (int DigitInd=1; DigitInd <= Len; DigitInd++) {
        Power = pow(10, DigitInd);
        Digit = (int(Num)%int(Power) - End) / (Power/10);
        End += Digit * (Power/10);
        Splited[DigitInd-1] = Digit;
    }
    
    //Print Digits from Array Respectively
    for (int Counter=0; Counter < Len; Counter++) {
        cout << Splited[Counter];
    }
    
    /*
     str = to_string(Num);
     
     for (auto rit=str.crbegin(); rit!=str.crend(); ++rit)
     cout << *rit;
     */
    
    //Final Typeset
    cout << endl << endl;
    
}
