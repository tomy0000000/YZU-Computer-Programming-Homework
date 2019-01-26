//
//  MemberDetails.h
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef MemberDetails_h
#define MemberDetails_h

#include "MemberDatabase.h"
#include "Vector.h"

class MemberDetails {
public:
  MemberDetails(MemberDatabase &theMemberDatabase);
  void execute(vector<Member>::iterator it);

private:
  MemberDatabase &memberDatabase;
};

#endif
