//
//  MemberDetails.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "MemberDetails.h"

int inputAnInteger(int begin, int end);

MemberDetails::MemberDetails(MemberDatabase &theMemberDatabase)
    : memberDatabase(theMemberDatabase) {}

void MemberDetails::execute(vector<Member>::iterator it) {

  // Display Details
  it->display();
  cout << endl;

  // Menu for Adjusting
  int choice = -1;
  do {
    cout << "Which one do you want to modify (0 – not modify)" << endl << "? ";
    choice = inputAnInteger(0, 5);
    if (choice == -1) {
      cout << endl << "Input Error!" << endl;
      cout << "--------------------" << endl;
    }
  } while (choice == -1);
  cout << "--------------------" << endl;

  // Editing Menu
  string query;
  if (choice) {
    cout << "Enter correct data: ";
    cin >> query;
  }
  switch (choice) {
  case 0:
    return;
  case 1:
    it->setName(query);
    break;
  case 2:
    if (memberDatabase.existingEmail(query)) {
      cout << endl << "An account already exists with the Email!" << endl;
      cout << "--------------------" << endl;
      return;
    }
    it->setEmail(query);
    break;
  case 3:
    it->setPhone(query);
    break;
  case 4:
    if (memberDatabase.existingId(query)) {
      cout << endl << "An account already exists with the ID number!" << endl;
      cout << "--------------------" << endl;
      return;
    }
    it->setIdNumber(query);
    break;
  case 5:
    it->setPassword(query);
    break;
  }
  cout << endl << "Successful!" << endl;
  cout << "--------------------" << endl;
}
