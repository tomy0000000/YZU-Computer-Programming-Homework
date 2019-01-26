//
//  NewMember.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "NewMember.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

NewMember::NewMember(MemberDatabase &theMemberDatabase)
    : memberDatabase(theMemberDatabase) {}

void NewMember::execute() {
  // Create TempMember
  Member tmpMember;
  string query;
  cout << "Enter ID Number:\t\t";
  cin >> query;
  if (memberDatabase.existingId(query)) {
    cout << endl << "An account already exists with the ID number!" << endl;
    cout << "--------------------" << endl;
    return;
  }
  tmpMember.setIdNumber(query);
  cout << "Enter Name:\t\t\t\t";
  cin >> query;
  tmpMember.setName(query);
  cout << "Enter Email Address:\t";
  cin >> query;
  if (memberDatabase.existingEmail(query)) {
    cout << endl << "An account already exists with the Email!" << endl;
    cout << "--------------------" << endl;
    return;
  }
  tmpMember.setEmail(query);
  cout << "Enter Password:\t\t\t";
  cin >> query;
  tmpMember.setPassword(query);
  cout << "Enter Phone Number:\t\t";
  cin >> query;
  tmpMember.setPhone(query);

  // Save Member Data
  memberDatabase.addMember(tmpMember);

  // Return Success
  cout << endl << "Successful!" << endl;
  cout << "--------------------" << endl;
}
