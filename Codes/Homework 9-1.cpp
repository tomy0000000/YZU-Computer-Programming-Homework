//
//  main.cpp
//  Hw9-1
//  Find Substring From Dictionary (STL String)
//
//  Created by Tomy Hsieh on 2017/11/20.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords (string &dictionaryWord, string &inputtedWord);

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring (string &dictionaryWord, string &inputtedWord);

int main() {
    
    string inputtedWord;
    cout << "Enter a word: ";
    cin >> inputtedWord;
    
    string dictionaryWord;
    embeddedWords(dictionaryWord, inputtedWord);
    
}

void embeddedWords (string &dictionaryWord, string &inputtedWord) {
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
        inFile >> dictionaryWord;
        if (isSubstring(dictionaryWord, inputtedWord)) {
            outFile << dictionaryWord << endl;
            cout << dictionaryWord << endl;
        }
    }
    
    inFile.close();
    outFile.close();
}

bool isSubstring (string &dictionaryWord, string &inputtedWord) {
    return !(inputtedWord.find(dictionaryWord) == string::npos);
}
