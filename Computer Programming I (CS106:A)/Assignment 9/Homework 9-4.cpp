//
//  main.cpp
//  Hw9-4
//  Find Substring From Dictionary (Class of Dynamic Char)
//
//  Created by Tomy Hsieh on 2017/11/21.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::ios;

class string {
public:
    // prints all English words which are contiguous substrings of inputtedWord into a file
    void embeddedWords(string &inputtedWord);
    
    // returns true if and only if dictionaryWord is a substring of inputtedWord
    bool isSubstring(string &inputtedWord);
    
    size_t size = 0;
    char *charArray = new char[21]();
};

int main()
{
    string inputtedWord;
    cout << "Enter a word: ";
    cin >> inputtedWord.charArray;
    inputtedWord.size = strlen( inputtedWord.charArray );
    
    string dictionaryWord;
    dictionaryWord.embeddedWords( inputtedWord );
}

void string::embeddedWords(string &inputtedWord) {
    
    ifstream inFile("Dictionary.txt", ios::in);
    if (!inFile) {
        cout << "File could not be opened" << endl;
        exit(1);
    }
    
    ofstream outFile("Word.txt", ios::out);
    if (!outFile) {
        cout << "File could not be saved" << endl;
        exit(1);
    }
    
    while (!inFile.eof()) {
        inFile >> charArray;
        size = strlen(charArray);
        if (isSubstring(inputtedWord)) {
            outFile << charArray << endl;
            cout << charArray << endl;
        }
    }
    
    delete[] charArray;
    delete[] inputtedWord.charArray;
    inFile.close();
    outFile.close();
}

bool string::isSubstring(string &inputtedWord) {
    for (int i=0; i<inputtedWord.size; i++) {
        if (charArray[0] == inputtedWord.charArray[i]) {
            if (size == 1) {
                return true;
            }
            else {
                bool Sub = true;
                for (int j=1; j<size; j++) {
                    if (charArray[j] != inputtedWord.charArray[i+j]) {
                        Sub = false;
                        break;
                    }
                }
                if (Sub) {
                    return true;
                }
            }
        }
    }
    return false;
}
