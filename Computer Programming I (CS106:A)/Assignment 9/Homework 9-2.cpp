//
//  main.cpp
//  Hw9-2
//  Find Substring From Dictionary (Vector of Char)
//
//  Created by Tomy Hsieh on 2017/11/21.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// prints all English words which are contiguous substrings of inputtedWord into a file
void embeddedWords(vector<char> &dictionaryWord, vector<char> &inputtedWord);

// returns true if and only if dictionaryWord is a substring of inputtedWord
bool isSubstring(vector<char> &dictionaryWord, vector<char> &inputtedWord);

int main() {
    vector<char> inputtedWord;
    
    cout << "Enter a word: ";
    char ch = cin.get();
    while (ch != '\n') {
        inputtedWord.push_back(ch);
        ch = cin.get();
    }
    
    vector<char> dictionaryWord;
    embeddedWords(dictionaryWord, inputtedWord);
}

void embeddedWords(vector<char> &dictionaryWord, vector<char> &inputtedWord) {
    
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
    
    while (inFile.peek() != EOF) {
        char ch;
        while (inFile.get(ch) && ch != '\n') {
            dictionaryWord.push_back(ch);
        }
        //dictionaryWord.pop_back();
        if (isSubstring(dictionaryWord, inputtedWord)) {
            for (int i = 0; i<dictionaryWord.size(); i++) {
                outFile << dictionaryWord[i];
                cout << dictionaryWord[i];
            }
            outFile << endl;
            cout << endl;
        }
        
        dictionaryWord.clear();
    }
    
    inFile.close();
    outFile.close();
}

bool isSubstring(vector<char> &dictionaryWord, vector<char> &inputtedWord) {
    for (int i = 0; i<inputtedWord.size(); i++) {
        if (dictionaryWord[0] == inputtedWord[i]) {
            if (dictionaryWord.size() == 1) {
                return true;
            }
            else {
                bool Sub = true;
                for (int j = 1; j<dictionaryWord.size(); j++) {
                    if (i+j >= inputtedWord.size() || dictionaryWord[j] != inputtedWord[i+j]) {
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
