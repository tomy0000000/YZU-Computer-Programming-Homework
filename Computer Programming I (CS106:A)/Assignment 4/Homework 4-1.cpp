//
//  main.cpp
//  Hw4-1
//  Amicable Pair
//
//  Created by Tomy Hsieh on 2017/10/3.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int summingFactors(int i);
void display(int n, int m);

int main() {
    
    //Initialization
    int Number;
    cout << "Enter a positive integer: ";
    cin >> Number;
    cout << "Amicable pairs between 1 and " << Number << ": " << endl;
    cout << endl;
    
    //Create Array to Store summingFactors-es
    int *Arr = new int[Number];
    fill_n(Arr, Number, 0);
    for (int Counter=1; Counter <= Number; Counter++) {
        Arr[Counter] = summingFactors(Counter);
    }
    
    //Walkthrough Array, Find Amicable Pair and Print
    for (int Steper=1; Steper <= Number; Steper++) {
        if (Arr[Steper] > Number) { //Skip if Summingfactor Exceed Range
            continue;
        }
        else if (Steper == Arr[Arr[Steper]] && Steper < Arr[Steper]) { //Make Sure Pair Print Onlu if Steper is Smaller
            display(Steper, Arr[Steper]);
        }
    }
    
}

//Scan Factors and Return Sum-Up
int summingFactors(int i) {
    
    int Sum=0;
    
    for (int Factor=1; Factor < i; Factor++) {
        if (i%Factor == 0) {
            Sum += Factor;
        }
    }
    
    return Sum;
    
}

//Print Amicable Pair in Format
void display(int n, int m) {
    
    //Initialize Arrays for Each Number
    int nArr[100000], mArr[100000];
    fill_n(nArr, 1000, 0);
    fill_n(nArr, 1000, 0);
    int nCounter=0, mCounter=0;
    
    //Scan Factors
    for (int Factor=1; Factor < n; Factor++) {
        if (n%Factor == 0) {
            nArr[nCounter] = Factor;
            nCounter++;
        }
    }
    for (int Factor=1; Factor < m; Factor++) {
        if (m%Factor == 0) {
            mArr[mCounter] = Factor;
            mCounter++;
        }
    }
    
    //Print First Line
    cout << n << " = ";
    for (int Printer=0; Printer < mCounter; Printer++) {
        if (Printer == mCounter-1) {
            cout << mArr[Printer] << endl;
        }
        else {
            cout << mArr[Printer] << " + ";
        }
    }
    
    //Print Second Line
    cout << m << " = ";
    for (int Printer=0; Printer < nCounter; Printer++) {
        if (Printer == nCounter-1) {
            cout << nArr[Printer] << endl;
        }
        else {
            cout << nArr[Printer] << " + ";
        }
    }
    
    cout << endl;
    
}
