//
//  main.cpp
//  Hw9-3
//  Find Substring From Dictionary (Struct of Dynamic Char)
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

struct string {
    size_t size = 0;
    char *charArray = new char[21]();
};

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords( string &dictionaryWord, string &inputtedWord );

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring( string &dictionaryWord, string &inputtedWord );

int main() {
    string inputtedWord;
    cout << "Enter a word: ";
    cin >> inputtedWord.charArray;
    inputtedWord.size = strlen(inputtedWord.charArray);
    
    string dictionaryWord;
    embeddedWords(dictionaryWord, inputtedWord);
}

void embeddedWords(string &dictionaryWord, string &inputtedWord) {
    
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
        inFile >> dictionaryWord.charArray;
        dictionaryWord.size = strlen(dictionaryWord.charArray);
        if (isSubstring(dictionaryWord, inputtedWord)) {
            outFile << dictionaryWord.charArray << endl;
            cout << dictionaryWord.charArray << endl;
        }
    }
    
    delete[] dictionaryWord.charArray;
    delete[] inputtedWord.charArray;
    inFile.close();
    outFile.close();
}

bool isSubstring(string &dictionaryWord, string &inputtedWord) {
    for (int i=0; i<inputtedWord.size; i++) {
        if (dictionaryWord.charArray[0] == inputtedWord.charArray[i]) {
            if (dictionaryWord.size == 1) {
                return true;
            }
            else {
                bool Sub = true;
                for (int j=1; j<dictionaryWord.size; j++) {
                    if (dictionaryWord.charArray[j] != inputtedWord.charArray[i+j]) {
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
