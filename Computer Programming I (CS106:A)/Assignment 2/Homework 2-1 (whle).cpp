//
//  main.cpp
//  Hw2-1 (while)
//  Convert Binary to Decimal
//
//  Created by Tomy Hsieh on 2017/9/19.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h> //Import to use functions: pow()
using namespace std;

int main() {
    
    double Num, DigitInd=1, Power, Digit, End=0, Sum=0; //Initialize ints
    
    //Prompt for binary
    cout << "Enter a positive binary integer: ";
    cin >> Num;
    
    //Loop until $End (Processed digits) Equal the whole number
    do {
        Power = pow(10, DigitInd); //define divider
        Digit = (int(Num)%int(Power) - End) / (Power/10); //Use mod to get the digit
        End += Digit * (Power/10); //Use mod to get the digit
        Sum += Digit * pow(2, DigitInd-1); //Sum up the converted numbers
        DigitInd++;
    } while (End != Num);
    
    //Print result
    cout << "The decimal equivalent of " << setprecision(0) << fixed << Num << " is " << Sum << endl;
    
}
