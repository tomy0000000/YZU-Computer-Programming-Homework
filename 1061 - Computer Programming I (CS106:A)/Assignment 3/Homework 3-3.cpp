//
//  main.cpp
//  Hw3-3
//  Print Prime Factors
//
//  Created by Tomy Hsieh on 2017/9/25.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    //Initialization
    int Number, Target;
    cout << "Enter a positive integer of at most 8 digits: ";
    cin >> Target;
    Number = Target; //Saved Original Number into another Variable
    cout << endl;
    bool *PrimesFact = new bool[Target+1];
    fill_n(PrimesFact, Target+1, false);
    
    //Loop for Prime Factors
    for (int Counter=2; Target != 1; Counter++) {
        while (Target%Counter == 0) {
            Target = Target/Counter;
            PrimesFact[Counter] = true;
        }
    }
    
    //Print Results
    cout << Number << " has the following prime factors: ";
    
    for (int Counter=2; Counter <= Number; Counter++) {
        if (PrimesFact[Counter]) {
            cout << Counter << " ";
        }
    }
    
    cout << endl << endl;
    
}
