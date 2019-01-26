//
//  MemberDatabase.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "MemberDatabase.h"
#include <fstream>
using std::ifstream;
using std::ios;
using std::ofstream;
#include <iostream>

MemberDatabase::MemberDatabase() { loadMembers(); }
MemberDatabase::~MemberDatabase() { saveMembers(); }
vector<Member>::iterator MemberDatabase::end() { return members.end(); }
void MemberDatabase::addMember(Member newMember) {
  members.push_back(newMember);
}

bool MemberDatabase::existingId(string id) {
  for (vector<Member>::iterator it = members.begin(); it != members.end();
       ++it) {
    if (string(it->getIdNumber()) == id) {
      return true;
    }
  }
  return false;
}

bool MemberDatabase::existingEmail(string email) {
  for (vector<Member>::iterator it = members.begin(); it != members.end();
       ++it) {
    if (string(it->getEmail()) == email) {
      return true;
    }
  }
  return false;
}

vector<Member>::iterator MemberDatabase::getMember(string email,
                                                   string password) {
  for (vector<Member>::iterator it = members.begin(); it != members.end();
       ++it) {
    if (string(it->getEmail()) == email &&
        string(it->getPassword()) == password) {
      return it;
    }
  }
  return members.end();
}

void MemberDatabase::loadMembers() {
  ifstream inFile("Members.dat", ios::in | ios::binary);
  while (inFile.peek() != EOF) {
    members.resize(members.size() + 1);
    inFile.read(reinterpret_cast<char *>(&members[members.size() - 1]),
                sizeof(Member));
  }
  inFile.close();
}

void MemberDatabase::saveMembers() {
  ofstream outFile("Members.dat", ios::out | ios::binary);
  for (int i = 0; i < members.size(); i++) {
    outFile.write(reinterpret_cast<const char *>(&members[i]), sizeof(Member));
  }
  outFile.close();
}
