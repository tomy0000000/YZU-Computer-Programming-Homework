//
//  main.cpp
//  Hw1
//  Vector Test Program
//
//  Created by Tomy Hsieh on 2018/2/27.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "Vector.h"

void testVector1();
void testVector2();
void printVectorSizeCapacity(vector, std::vector<int> &);

int main() {
    srand( 2 );
    testVector1();
    for (unsigned int seed=0; seed<20; seed++) {
        srand(seed);
        testVector2();
    }
}

void testVector1() {
    
    vector v1;
    std::vector<int> v2;
//    printVectorSizeCapacity(v1, v2);
    unsigned int numErrors = 11;
    unsigned int number;
    for ( unsigned int i = 0; i < 11; i++ ) {
        number = 1 + rand() % 99;
        v1.push_back( number );
        v2.push_back( number );
//        cout << setw( 4 ) << number << endl;
//        printVectorSizeCapacity(v1, v2);
        if ( v1.equal( v2 ) ) {
            numErrors--;
        }
    }
    
    if ( numErrors == 0 ) {
        cout << "push_back is correct.\n";
    } else {
        cout << "push_back is incorrect.\n";
    }
    
    numErrors = 16;
//    printVectorSizeCapacity(v1, v2);
    for ( unsigned int length = 0; length < 16; length++ ) {
        v1.resize( length );
        v2.resize( length );
//        cout << setw( 4 ) << length << endl;
//        printVectorSizeCapacity(v1, v2);
        if (v1.equal(v2)){
            numErrors--;
        }
    }
    
    if ( numErrors == 0 )
    { cout << "resize is correct.\n\n"; }
    else
    { cout << "resize is incorrect.\n\n"; }
}

void testVector2() {
    vector v1;
    std::vector< int > v2;
    unsigned int numErrors = 1000;
    unsigned int number;
    unsigned int length;
    unsigned int choice;
//    printVectorSizeCapacity(v1, v2);
    
    for (unsigned int i = 0; i < 1000; i++) {
        choice = rand() % 3;
        switch (choice) {
            case 0:
                number = 1 + rand() % 99;
//                cout << "PushBack: " << number << endl;
                v1.push_back(number);
                v2.push_back(number);
                break;
            case 1:
//                cout << "PopBack" << endl;
                if (!v2.empty()) {
                    v1.pop_back();
                    v2.pop_back();
                }
                break;
            case 2:
                length = rand() % 200;
//                cout << "ReSize: " << length << endl;
                v1.resize(length);
                v2.resize(length);
                break;
            default:
                break;
        }
//        printVectorSizeCapacity(v1, v2);
        if (v1.equal(v2)) {
//            cout << "\t\t\t\t\tSuccess" << endl;
            numErrors--;
        }
        else {
//            cout << "\t\t\t\t\tFailed" << endl;
        }
    }
    cout << "There are " << numErrors << " errors.\n";
}

void printVectorSizeCapacity(vector v1, std::vector<int> &v2) {
        cout << setw( 4 ) << v1.size() << setw( 4 ) << v1.capacity() << endl;
        cout << setw( 4 ) << v2.size() << setw( 4 ) << v2.capacity() << endl << endl;
}
