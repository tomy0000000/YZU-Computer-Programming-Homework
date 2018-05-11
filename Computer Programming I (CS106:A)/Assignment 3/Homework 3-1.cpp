//
//  main.cpp
//  Hw3-1
//  Print Largest & Second Largest
//
//  Created by Tomy Hsieh on 2017/9/24.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    //Initialization
    int First=0, Second=0, Num, items;
    
    //Prompt
    cout << "Enter the number of integers to be processed followed by the integers:" << endl;
    cin >> items;
    
    //Read Numbers
    for (int Counter=1; Counter <= items; Counter++) {
        cin >> Num;
        if (Num > First) {
            Second = First;
            First = Num;
        }
        else if (Num > Second) {
            Second = Num;
        }
    }
    
    //Print Results
    cout << endl;
    cout << "Largest is " << First << endl;
    cout << "Second largest is " << Second << endl;
    
}
