//
//  Assignment 5-2.cpp
//  Hw5-2
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/3/27.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <fstream>
using std::ofstream;
using std::ifstream;

#include <iostream>
using std::ostream;
using std::istream;
using std::cin;
using std::cout;
using std::endl;
using std::ios;

#include "HugeInteger - 1061519 - hw5-2.h"

int enterChoice();
template <typename T> void testHugeIntegers(HugeInteger<T> n1[], HugeInteger<T> n2[]);
template <typename T> void input(HugeInteger<T> n1[], HugeInteger<T> n2[]);
template <typename T> void print(ostream &outFile, HugeInteger<T> n1, HugeInteger<T> n2);

const int numTestCases = 22;

int main() {

  HugeInteger<vector<int>> n1[numTestCases];
  HugeInteger<vector<int>> n2[numTestCases];
  HugeInteger<vector<unsigned int>> n3[numTestCases];
  HugeInteger<vector<unsigned int>> n4[numTestCases];
  HugeInteger<vector<short int>> n5[numTestCases];
  HugeInteger<vector<short int>> n6[numTestCases];
  HugeInteger<vector<unsigned short int>> n7[numTestCases];
  HugeInteger<vector<unsigned short int>> n8[numTestCases];

  int choice = enterChoice();

  switch (choice) {
  case 1:
    testHugeIntegers(n1, n2);
    break;
  case 2:
    testHugeIntegers(n3, n4);
    break;
  case 3:
    testHugeIntegers(n5, n6);
    break;
  case 4:
    testHugeIntegers(n7, n8);
    break;
  default:
    cout << "Program should never get here!";
  }

  system("pause");
}

int enterChoice() {
  cout << "Enter your choice\n"
       << " 1 - test HugeInteger< vector< int > >\n"
       << " 2 - test HugeInteger< vector< unsigned int > >\n"
       << " 3 - test HugeInteger< vector< short int > >\n"
       << " 4 - test HugeInteger< vector< unsigned short int > >\n";

  int menuChoice;
  do {
    cout << "? ";
    cin >> menuChoice;
  } while ((menuChoice < 1) || (menuChoice > 4));
  cout << endl;

  return menuChoice;
}

template <typename T> void testHugeIntegers(HugeInteger<T> n1[], HugeInteger<T> n2[]) {
  input(n1, n2);

  for (int i = 0; i < numTestCases; i++) {
    print(cout, n1[i], n2[i]);
  }

  ofstream outFile("Result.txt", ios::out);

  if (!outFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  for (int i = 0; i < numTestCases; i++) {
    print(outFile, n1[i], n2[i]);
  }

  outFile.close();
}

template <typename T> void input(HugeInteger<T> n1[], HugeInteger<T> n2[]) {
  ifstream inFile("Test cases.txt", ios::in);

  if (!inFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  char digit;
  for (int i = 0; i < numTestCases; i++) {
    T vector1, vector2;
    
    #if defined(__clang__)
    const char EOL_CHAR = '\r';
    const bool BITER = true;
    #endif
    #if defined(_MSC_VER)
    const char EOL_CHAR = '\n';
    const bool BITER = false;
    #endif

    while ((digit = inFile.get()) != EOL_CHAR) {
      vector1.push_back(digit - '0');
    }
    if (BITER) {
      inFile.get();
    }

    while ((digit = inFile.get()) != EOL_CHAR) {
      vector2.push_back(digit - '0');
    }
    if (BITER) {
      inFile.get();
    }
    
    inFile.get();
    if (BITER) {
      inFile.get();
    }

    n1[i].convert(vector1);
    n2[i].convert(vector2);
  }

  inFile.close();
}

template <typename T>
void print(ostream &outFile, HugeInteger<T> n1, HugeInteger<T> n2) {
  if (n1.isZero())
    outFile << n1 << endl;
  else {
    --n1;
    outFile << ++n1 << endl;
  }

  outFile << n2++ << endl;
  n2--;

  outFile << n1 + n2 << endl;

  if (n1 < n2)
    outFile << '-' << n2 - n1 << endl;
  else
    outFile << n1 - n2 << endl;

  outFile << n1 * n2 << endl;

  if (n2.isZero())
    outFile << "DivideByZero!\n";
  else
    outFile << n1 / n2 << endl;

  if (n2.isZero())
    outFile << "DivideByZero!\n";
  else
    outFile << n1 % n2 << endl;

  outFile << endl;
}

/*
void testPreincrement( HugeInteger n1 )
{
   cout << "  n1: " << n1 << endl;
   cout << "++n1: " << ++n1 << endl;
   cout << "  n1: " << n1;
}

void testPostincrement( HugeInteger n1 )
{
   cout << "  n1: " << n1 << endl;
   cout << "n1++: " << n1++ << endl;
   cout << "  n1: " << n1;
}
*/
