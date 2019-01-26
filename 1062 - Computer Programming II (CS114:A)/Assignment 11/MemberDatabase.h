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
  MemberDatabase();
  ~MemberDatabase();
  // Get iterator pointing to end
  vector<Member>::iterator end();
  // Add newMember to member database
  void addMember(Member newMember);
  // Check if given ID is already exists
  bool existingId(string id);
  // Check if given email is already exists
  bool existingEmail(string email);
  // Get iterator pointing to specific Member object
  vector<Member>::iterator getMember(string email, string password);

private:
  vector<Member> members;
  void loadMembers();
  void saveMembers();
};

#endif
