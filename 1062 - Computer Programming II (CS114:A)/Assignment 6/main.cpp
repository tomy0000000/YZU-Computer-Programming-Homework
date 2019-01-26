//
//  main.cpp
//  Hw6
//  List Test Program
//
//  Created by Tomy Hsieh on 2018/4/9.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include "List - 1061519 - hw6.h"
const bool DEBUG_MODE = true;

void testList1();
void testList2();
template <typename T>
void printList(list<T> &theList, std::list<T> &theSTLList);

int main() {
  srand(1);
  testList1();
  testList2();
}

template <typename T>
void printList(list<T> &theList, std::list<T> &theSTLList) {

  // Custom List
  cout << "list1: " << theList.size() << endl;
  ListNode<T> *ptr = theList.myHead->next;
  for (; ptr != theList.myHead; ptr = ptr->next) {
    cout << ptr->myVal << " ";
  }
  cout << endl;

  // STD List
  cout << "list2: " << theSTLList.size() << endl;
  typename std::list<T>::iterator it = theSTLList.begin();
  for (; it != theSTLList.end(); it++) {
    cout << *it << " ";
  }
  cout << endl;

  cout << "\t\t\t\t\t" << ((theList.equal(theSTLList)) ? "Success!" : "Failed")
       << endl;
  cout << "------------------------------" << endl;
}

void testList1() {

  list<int> list1;
  std::list<int> list2;
  if (DEBUG_MODE) {
    printList(list1, list2);
  }

  unsigned int numErrors = 11;
  unsigned int number;
  for (unsigned int i = 0; i < 11; i++) {
    number = 1 + rand() % 99;
    if (DEBUG_MODE) {
      cout << number << endl;
    }
    list1.push_front(number);
    list2.push_front(number);
    if (DEBUG_MODE) {
      printList(list1, list2);
    }
    if (list1.equal(list2)) {
      numErrors--;
    }
  }
  if (numErrors == 0) {
    cout << "push_front is correct" << endl;
  } else {
    cout << "push_front is incorrect" << endl;
  }

  numErrors = 11;
  for (unsigned int i = 0; i < 11; i++) {
    number = 1 + rand() % 99;
    if (DEBUG_MODE) {
      cout << number << endl;
    }
    list1.push_back(number);
    list2.push_back(number);
    if (DEBUG_MODE) {
      printList(list1, list2);
    }
    if (list1.equal(list2)) {
      numErrors--;
    }
  }
  if (numErrors == 0) {
    cout << "push_back is correct" << endl;
  } else {
    cout << "push_back is incorrect" << endl;
  }

  numErrors = 30;
  for (unsigned int length = 0; length < 30; length++) {
    if (DEBUG_MODE) {
      cout << length << endl;
    }
    list1.resize(length);
    list2.resize(length);
    if (DEBUG_MODE) {
      printList(list1, list2);
    }
    if (list1.equal(list2)) {
      numErrors--;
    }
  }
  if (numErrors == 0) {
    cout << "resize is correct" << endl;
  } else {
    cout << "resize is incorrect" << endl;
  }
}

void testList2() {
  unsigned int numErrors = 1001;
  unsigned int number = 1 + rand() % 9;

  list<int> list1(number);
  std::list<int> list2(number);
  if (list1.equal(list2)) {
    numErrors--;
  }
  if (DEBUG_MODE) {
    printList(list1, list2);
  }

  unsigned int length;
  unsigned int choice;
  for (unsigned int i = 0; i < 1000; i++) {
    choice = rand() % 4;
    switch (choice) {
    case 0:
      number = 1 + rand() % 99;
      list1.push_front(number);
      list2.push_front(number);
      if (DEBUG_MODE) {
        cout << "push_front: " << number << endl;
        printList(list1, list2);
      }
      break;
    case 1:
      number = 1 + rand() % 99;
      list1.push_back(number);
      list2.push_back(number);
      if (DEBUG_MODE) {
        cout << "push_back: " << number << endl;
        printList(list1, list2);
      }
      break;
    case 2:
      if (!list2.empty()) {
        list1.pop_back();
        list2.pop_back();
        if (DEBUG_MODE) {
          cout << "pop_back" << endl;
          printList(list1, list2);
        }
      }
      break;
    case 3:
      length = rand() % 200;
      list1.resize(length);
      list2.resize(length);
      if (DEBUG_MODE) {
        cout << "resize: " << length << endl;
        printList(list1, list2);
      }
      break;
    default:
      break;
    }

    if (list1.equal(list2)) {
      numErrors--;
    }
  }

  cout << "There are " << numErrors << " errors" << endl;
}
