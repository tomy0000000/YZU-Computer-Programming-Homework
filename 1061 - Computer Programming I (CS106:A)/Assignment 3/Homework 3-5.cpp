//
//  main.cpp
//  Hw3-5
//  Print Multiplication Table
//
//  Created by Tomy Hsieh on 2017/9/25.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    
    for (int Last=1; Last <= 9; Last++) {
        
        for (int Former=2; Former <= 5; Former++) {
            
            if (Former==5) {
                if (Former*Last < 10) {
                    cout << "\t" << Former << " * " << Last << " = " << " " << Former*Last << endl;
                }
                else {
                    cout << "\t" << Former << " * " << Last << " = " << Former*Last << endl;
                }
            }
            else {
                if (Former*Last < 10) {
                    cout << "\t" << Former << " * " << Last << " = " << " " << Former*Last << "\t";
                }
                else {
                    cout << "\t" << Former << " * " << Last << " = " << Former*Last << "\t";
                }
            }
            
        }

    }
    
    cout << endl;
    
    for (int Last=1; Last <= 9; Last++) {
        
        for (int Former=6; Former <= 9; Former++) {
            
            if (Former==9) {
                if (Former*Last < 10) {
                    cout << "\t" << Former << " * " << Last << " = " << " " << Former*Last << endl;
                }
                else {
                    cout << "\t" << Former << " * " << Last << " = " << Former*Last << endl;
                }
            }
            else {
                if (Former*Last < 10) {
                    cout << "\t" << Former << " * " << Last << " = " << " " << Former*Last << "\t";
                }
                else {
                    cout << "\t" << Former << " * " << Last << " = " << Former*Last << "\t";
                }
            }
            
        }
        
    }
    
}
