//
//  main.cpp
//  Hw3-2
//  Determin Palindrome
//
//  Created by Tomy Hsieh on 2017/9/25.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    //Initialization
    int Len=0, HalfPt;
    char number[8];
    bool Res=true;
    
    //Prompt
    cout << "Enter a positive integer of at most 8 digits: ";
    cin >> number;
    
    //Analyze Number Length
    for (int Steper=0; number[Steper] != '\0'; Steper++) {
        Len = Steper+1;
    }
    
    //Calculate Halfpoint
    if (Len%2 == 1) {
        HalfPt = (Len-1)/2 - 1;
    }
    else {
        HalfPt = Len/2 - 1;
    }
    
    //Check Every Digit
    for (int Counter=0; Counter <= HalfPt; Counter++) {
        if (number[Counter] != number[Len-Counter-1]) {
            Res = false;
        }
    }
    
    //Print Result
    if (Res == true) {
        cout << number << " is a palindrome." << endl;
    }
    else {
        cout << number << " is not a palindrome." << endl;
    }
    
}
