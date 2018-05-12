//
//  main.cpp
//  Hw2
//  String Test Program
//
//  Created by Tomy Hsieh on 2018/2/28.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "String.h"
#include <string>

void testString();
void printStringSizeCapacity(string, std::string &);

int main() {
    for (unsigned int seed = 0; seed < 40; seed++) {
//        seed += 17;
//        seed += 20;
        srand(seed);
        if (string::printStr) {
            cout << "------------------------------------CALLING TESTER WITH SEED: " << seed << endl;
        }
        testString();
//        break;
    }
    system("pause");
}

void testString() {
    unsigned int n = 20;
    
//    n = 10;
    
    char s[100];
    for (unsigned int i = 0; i < n; i++) {
        s[i] = static_cast< char >(97 + rand() % 26);
    }
    s[n] = '\0';
    
    string str1(s, n);
    std::string str2(s, n);
    
    if (string::printStr) {
        cout << "CONSTRUCTED" << endl;
        printStringSizeCapacity(str1, str2);
    }

    unsigned int numErrors = 2000;
    unsigned int pos;
    unsigned int length;
    char c;
    unsigned int choice;
    for (unsigned int i = 0; i < 2000; i++) {
        choice = rand() % 6;
        
//        ------------------------------------------------------------------
        choice = 4;
//        0 = resize
//        1 = pushback
//        2 = popback
//        3 = assign
//        4 = erase
//        5 = substr
//        ------------------------------------------------------------------
        
        switch (choice) {
            case 0: {
                n = rand() % 200;
                str1.resize(n);
                str2.resize(n);
                
                if (string::printStr) { printStringSizeCapacity(str1, str2); }
                
                if (str1.equal(str2)) { numErrors--; }
                break;
            }
            case 1: {
                c = static_cast< char >(97 + rand() % 26);
                str1.push_back(c);
                str2.push_back(c);
                
                if (string::printStr) { printStringSizeCapacity(str1, str2); }
                
                if (str1.equal(str2)) { numErrors--; }
                break;
            }
            case 2: {
                if (str2.empty()) {
                    numErrors--;
                } else {
                    str1.pop_back();
                    str2.pop_back();
                    if (str1.equal(str2)) { numErrors--; }
                }
                break;
            }
            case 3: {
                length = 1 + rand() % 50;
                for (unsigned int i = 0; i < length; i++) {
                    s[i] = static_cast< char >(97 + rand() % 26);
                }
                s[length] = '\0';
                n = rand() % length;
                str1.assign(s, n);
                str2.assign(s, n);
                
                if (string::printStr) { printStringSizeCapacity(str1, str2); }
                
                if (str1.equal(str2)) { numErrors--; }
                break;
            }
            case 4: {
                if (str2.empty()) {
                    numErrors--;
                } else {
                    pos = rand() % str2.size();
                    n = rand() % str2.size();
                    str1.erase(pos, n);
                    str2.erase(pos, n);
                    
                    if (string::printStr) { printStringSizeCapacity(str1, str2); }
                    
                    if (str1.equal(str2)) { numErrors--; }
                }
                break;
            }
            case 5: {
                if (str2.empty()) {
                    numErrors--;
                } else {
                    pos = rand() % str2.size();
                    n = rand() % str2.size();
                    
                    if (string::printStr) { cout << "-------------------------------\nGET SUBSTR FROM POS " << pos << " WITH LEN " << n << endl; }
                    if (string::printStr) { printStringSizeCapacity(str1, str2); }
                    
                    string v1t(str1.substr(pos, n));
                    std::string v2t(str2.substr(pos, n));
                    
                    if (string::printStr) { printStringSizeCapacity(v1t, v2t); }
                    
                    if (v1t.equal(v2t)) { numErrors--; }
                }
                break;
            }
            default: { break; }
        }
    }
    cout << "There are " << ((numErrors == 0) ? "" : "\t\t\t") << numErrors << " errors.\n";
}

void printStringSizeCapacity(string str1, std::string &str2) {
    cout << setw(4) << str1.size() << setw(4) << str1.capacity() << endl;
    for (int i = 0; i < str1.size(); i++) {
        cout << ((str1.getItem(i) == '\0') ? '0' : str1.getItem(i)) << " ";
    }
    cout << endl;
    cout << setw(4) << str2.size() << setw(4) << str2.capacity() << endl;
    for (int i = 0; i < str2.size(); i++) {
        cout << ((str2[i] == '\0') ? '0' : str2[i]) << " ";
    }
    cout << endl;
    cout << "\t\t\t\t\t" << ((str1.equal(str2)) ? "Success" : "Error") << endl;
}
