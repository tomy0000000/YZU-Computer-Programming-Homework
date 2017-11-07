//
//  main.cpp
//  Hw2-1 (for)
//  Convert Binary to Decimal
//
//  Created by Tomy Hsieh on 2017/9/20.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <math.h> //Import to use functions: pow() & log10()
using namespace std;

int main() {
    
    double Num, Power, Digit, End=0, Sum=0; //Initialize ints
    
    //Prompt for binary
    cout << "Enter a positive binary integer: ";
    cin >> Num;
    
    //Loop from 1 to the length of the number
    for (int DigitInd=1; DigitInd <= log10(Num)+1; DigitInd++) {
        Power = pow(10, DigitInd); //define divider
        Digit = (int(Num)%int(Power) - End) / (Power/10); //Use mod to get the digit
        End += Digit * (Power/10); //Record processed digits
        Sum += Digit * pow(2, DigitInd-1); //Sum up the converted numbers
    }
    
    //Print result
    cout << "The decimal equivalent of " << setprecision(0) << fixed << Num << " is " << Sum << endl;
    
}
