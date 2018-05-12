//
//  Assignment 7.cpp
//  Hw7
//  HugeInteger test program.
//
//  Created by Tomy Hsieh on 2018/4/17.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ios;
using std::ofstream;

#include "HugeInteger - 1061519 - hw7.h"

int enterChoice();

template <typename T>
void testHugeIntegers(HugeInteger<T> n1[], HugeInteger<T> n2[]);

template <typename T>
void input(HugeInteger<T> n1[], HugeInteger<T> n2[]);

template <typename T>
void print(ostream &outFile, HugeInteger<T> &n1, HugeInteger<T> &n2);

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

  HugeInteger<list<int>> n9[numTestCases];
  HugeInteger<list<int>> n10[numTestCases];
  HugeInteger<list<unsigned int>> n11[numTestCases];
  HugeInteger<list<unsigned int>> n12[numTestCases];
  HugeInteger<list<short int>> n13[numTestCases];
  HugeInteger<list<short int>> n14[numTestCases];
  HugeInteger<list<unsigned short int>> n15[numTestCases];
  HugeInteger<list<unsigned short int>> n16[numTestCases];

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
  case 5:
    testHugeIntegers(n9, n10);
    break;
  case 6:
    testHugeIntegers(n11, n12);
    break;
  case 7:
    testHugeIntegers(n13, n14);
    break;
  case 8:
    testHugeIntegers(n15, n16);
    break;
  default:
    cout << "Program should never get here!";
  }

  system("pause");
}

int enterChoice() {
  cout << "Enter your choice\n"
       << " 1 - test vector< int >\n"
       << " 2 - test vector< unsigned int >\n"
       << " 3 - test vector< short int >\n"
       << " 4 - test vector< unsigned short int >\n"
       << " 5 - test list< int >\n"
       << " 6 - test list< unsigned int >\n"
       << " 7 - test list< short int >\n"
       << " 8 - test list< unsigned short int >\n";

  int menuChoice;
  do {
    cout << "? ";
    cin >> menuChoice;
  } while ((menuChoice < 1) || (menuChoice > 8));
  cout << endl;

  return menuChoice;
}

template <typename T>
void testHugeIntegers(HugeInteger<T> n1[], HugeInteger<T> n2[]) {
  input(n1, n2);

  for (int i = 0; i < numTestCases; i++)
    print(cout, n1[i], n2[i]);

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

template <typename T>
void input(HugeInteger<T> n1[], HugeInteger<T> n2[]) {

  ifstream inFile("Test cases.txt", ios::in);
  if (!inFile) {
    cout << "File could not be opened" << endl;
    system("pause");
    exit(1);
  }

  char digit;
  for (int i = 0; i < numTestCases; i++) {
    T buffer1, buffer2;

#if defined(__clang__)
    const char EOL_CHAR = '\r';
    const bool BITER = true;
#endif
#if defined(_MSC_VER)
    const char EOL_CHAR = '\n';
    const bool BITER = false;
#endif

    while ((digit = inFile.get()) != EOL_CHAR) {
      buffer1.push_back(digit - '0');
    }
    if (BITER) {
      inFile.get();
    }

    while ((digit = inFile.get()) != EOL_CHAR) {
      buffer2.push_back(digit - '0');
    }
    if (BITER) {
      inFile.get();
    }

    inFile.get();
    if (BITER) {
      inFile.get();
    }

    n1[i].convert(buffer1);
    n2[i].convert(buffer2);
  }

  inFile.close();
}

template <typename T>
void print(ostream &outFile, HugeInteger<T> &n1, HugeInteger<T> &n2) {
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
