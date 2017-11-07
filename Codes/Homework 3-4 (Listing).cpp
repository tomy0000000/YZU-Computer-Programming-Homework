//
//  main.cpp
//  Hw3-4 (Specialized)
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
    cout << endl;
    cout << "Perfect numbers between 1 and " << Number << ":" << endl;
    
    //Print Results
    if (Number >= 6) {
        cout << "6 = 1 + 2 + 3" << endl;
    }
    if (Number >= 28) {
        cout << "28 = 1 + 2 + 4 + 7 + 14" << endl;
    }
    if (Number >= 496) {
        cout << "496 = 1 + 2 + 4 + 8 + 16 + 31 + 62 + 124 + 248" << endl;
    }
    if (Number >= 8128) {
        cout << "8128 = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 127 + 254 + 508 + 1016 + 2032 + 4064" << endl;
    }
    if (Number >= 33550336) {
        cout << "33550336 = 1 + 2 + 4 + 8 + 16 + 32 + 64 + 128 + 256 + 512 + 1024 + 2048 + 4096 + 8191 + 16382 + 32764 + 65528 + 131056 + 262112 + 524224 + 1048448 + 2096896 + 4193792 + 8387584 + 16775168" << endl;
    }
    
}
