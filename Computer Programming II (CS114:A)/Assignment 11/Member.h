//
//  Member.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef Member_h
#define Member_h

#include <string>
using std::string;

class Member {
public:
  Member(string theEmail = "", string thePassword = "", string theIdNumber = "",
         string theName = "", string thePhone = "");
  string getEmail();
  string getPassword();
  string getIdNumber();
  string getName();
  string getPhone();
  void setEmail(string theEmail);
  void setPassword(string thePassword);
  void setIdNumber(string theIdNumber);
  void setName(string theName);
  void setPhone(string thePhone);
  // Display details of the member
  void display();

private:
  char email[40];
  char password[24];
  char idNumber[12];
  char name[12];
  char phone[12];
};

#endif
