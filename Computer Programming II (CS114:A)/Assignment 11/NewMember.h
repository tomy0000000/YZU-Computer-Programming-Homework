//
//  NewMember.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef NewMember_h
#define NewMember_h

#include "MemberDatabase.h"

class NewMember {
public:
  NewMember(MemberDatabase &theMemberDatabase);
  void execute();

private:
  MemberDatabase &memberDatabase;
};

#endif
