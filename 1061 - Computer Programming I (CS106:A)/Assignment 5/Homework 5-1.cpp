//
//  main.cpp
//  Hw5-1
//  Armstrong Number
//
//  Created by Tomy Hsieh on 2017/10/11.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <math.h>
using namespace std;

int main() {
    
    int Num, Len, Power, Digit, End = 0, Sum;
    cout << "Enter an integer between and including 10 and 10000000: ";
    cin >> Num;
    cout << endl << "Armstrong numbers between and including 10 and " << Num << ":" << endl << endl;
    
    for (int Counter = 10; Counter <= Num; Counter++) {
        
        Sum = 0;
        End = 0;
        Len = int(log10(Counter)) + 1;
        
        for (int DigitInd = 1; DigitInd <= log10(Counter) + 1; DigitInd++) {
            Power = int(pow(10, DigitInd)); //Define Divider
            Digit = (Counter%Power - End) / (Power / 10); //Use Mod to Get the Digit
            End += Digit * (Power / 10); //Record Processed Digits
            Sum += int(pow(Digit, Len)); //Add up to Sum
        }
        
        //Verification
        if (Sum == Counter) {
            for (int Space = 0; Space < 8 - Len; Space++) {
                cout << " ";
            }
            cout << Counter << endl;
        }
        
    }
    
}

