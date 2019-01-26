//
//  User.h
//  Hw9
//  Automated Teller Machine
//
//  Created by Tomy Hsieh on 2018/5/15.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef User_h
#define User_h

#include <string>
using namespace std;

class User {
public:
  User(string const ac, string const p, int av, int t) : account(ac), password(p), available(av*100), total(t*100) {}
  bool check_account (string input) { return (input.compare(account) == 0); }
  bool check_password (string input) { return (input.compare(password) == 0); }
  int get_available () { return available/100; }
  int get_total () { return total/100; }
  void Withdrawal (int balance);
  void Deposit (int balance);
private:
  string account;
  string password;
  int available;
  int total;
};

#endif

void User::Withdrawal (int balance) {
  available -= balance*100;
  total -= balance*100;
}

void User::Deposit (int balance) {
  total += balance*100;
}
