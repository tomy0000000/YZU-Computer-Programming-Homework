//
//  main.cpp
//  Hw4
//
//  Created by Tomy Hsieh on 2017/9/12.
//  Copyright © 2017年 Tomy Creative Studio. All rights reserved.
//
//  聽說，檔，不可以沒有註解(?)

#include <iostream> // allows program to perform input and output
using namespace std; // program uses names from the std namespace

int main() {
    
    int s1, s2, s3; // integer read from user
    
    cout << "Enter side 1: "; // prompt
    cin >> s1; //read integer from user
    cout << "Enter side 2: "; // prompt
    cin >> s2; //read integer from user
    cout << "Enter side 3: "; // prompt
    cin >> s3; //read integer from user
    
    //determine output
    if (s1*s1 == s2*s2 + s3*s3 || s2*s2 == s1*s1 + s3*s3 || s3*s3 == s1*s1 + s2*s2)
        cout << "These are the sides of a right triangle." << endl;
    else
        cout << "These do not form a right triangle." << endl;
    
}
