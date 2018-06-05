//
//  Member.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "Member.h" // Member class definition
#include <iostream>
using std::cout;
using std::endl;

Member::Member(string theEmail, string thePassword, string theIdNumber,
               string theName, string thePhone) {
  setEmail(theEmail);
  setPassword(thePassword);
  setIdNumber(theIdNumber);
  setName(theName);
  setPhone(thePhone);
}

void Member::setEmail(string theEmail) {
  unsigned long length = theEmail.size();
  length = (length < 40 ? length : 39);
  for (int i = 0; i < length; i++)
    email[i] = theEmail[i];
  email[length] = '\0';
}

string Member::getEmail() { return string(email); }

void Member::setPassword(string thePassword) {
  unsigned long length = thePassword.size();
  length = (length < 24 ? length : 23);
  for (int i = 0; i < length; i++)
    password[i] = thePassword[i];
  password[length] = '\0';
}

string Member::getPassword() { return string(password); }

void Member::setIdNumber(string theIdNumber) {
  unsigned long length = theIdNumber.size();
  length = (length < 12 ? length : 11);
  for (int i = 0; i < length; i++)
    idNumber[i] = theIdNumber[i];
  idNumber[length] = '\0';
}

string Member::getIdNumber() { return string(idNumber); }

void Member::setName(string theName) {
  unsigned long length = theName.size();
  length = (length < 12 ? length : 11);
  for (int i = 0; i < length; i++)
    name[i] = theName[i];
  name[length] = '\0';
}

string Member::getName() { return string(name); }

void Member::setPhone(string thePhone) {
  unsigned long length = thePhone.size();
  length = (length < 12 ? length : 11);
  for (int i = 0; i < length; i++)
    phone[i] = thePhone[i];
  phone[length] = '\0';
}

string Member::getPhone() { return string(phone); }

void Member::display() {
  cout << "1. Name:\t\t\t" << name << endl
       << "2. Email Address:\t" << email << endl
       << "3. Phone Number:\t" << phone << endl
       << "4. ID Number:\t\t" << idNumber << endl
       << "5. Password:\t\t" << password << endl;
}
