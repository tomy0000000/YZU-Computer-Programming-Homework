//
//  main.cpp
//  Hw3-4
//  Perfect Numbers
//
//  Created by Tomy Hsieh on 2017/9/25.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    //Initialization
    int Number;
    cout << "Enter a positive integer of at most 8 digits: ";
    cin >> Number;
    
    //Print Header
    cout << "Perfect numbers between 1 and " << Number << ":" << endl;
    
    //Loop Numbers
    for (int Counter=2; Counter <= Number; Counter++) {
        
        //Initialization for Examine
        int *Arr = new int [Number];
        int Ind=0, Sum=0;
        
        //Record Factors
        for (int Steper=1; Steper < Counter; Steper++) {
            if (Counter%Steper == 0) {
                Arr[Ind] = Steper;
                Sum += Steper;
                Ind++;
            }
        }
        
        //Print if Perfect
        if (Sum == Counter) {
            cout << Counter << " = ";
            for (int Printer=0; Printer <= Ind-1; Printer++) {
                if (Printer != Ind-1) {
                    cout << Arr[Printer] << " + ";
                }
                else {
                    cout << Arr[Printer] << endl;
                }
            }
        }
        
        //Reset Array
        delete [] Arr;
        
    }
    
}
