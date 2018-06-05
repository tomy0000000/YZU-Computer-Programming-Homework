//
//  MemberDatabase.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef MemberDatabase_h
#define MemberDatabase_h

#include "Member.h"
#include "Vector.h"

class MemberDatabase {
public:
  MemberDatabase();               // calls loadMembers()
  ~MemberDatabase();              // calls saveMembers()
  vector<Member>::iterator end(); // returns members.end()

  // returns true if there is a member object containing specified id
  bool existingId(string id);

  // returns true if there is a member object containing specified email
  bool existingEmail(string email);

  // adds a member object to the end of the vector members
  void addMember(Member newMember);

  // returns an iterator which points to the member object containing specified
  // email and password
  vector<Member>::iterator getMember(string email, string password);

private:
  vector<Member> members; // vector of the members
  void loadMembers();     // loads members from the file Members.dat
  void saveMembers();     // stores members into the file Members.dat
};

#endif
