//
//  BalanceInquiry.h
//  Hw10
//  Driver program for the ATM system
//
//  Created by Tomy Hsieh on 2018/5/23.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef BALANCE_INQUIRY_H
#define BALANCE_INQUIRY_H

#include <vector>
using namespace std;
#include "Account.h"

class BalanceInquiry {
public:
  BalanceInquiry(int userAccountNumber, vector<Account> &atmAccounts) : accountNumber(userAccountNumber), accounts(atmAccounts) {}
  void execute();

private:
  int accountNumber;
  vector<Account> &accounts;
  Account *getAccount(int accountNumber, vector<Account> &accounts);
};

#endif

void BalanceInquiry::execute() {
  Account *current = getAccount(accountNumber, accounts);
  cout << "Balance Information:\n"
  << " - Available balance: $" << current->getAvailableBalance()
  << "\n - Total balance:     $" << current->getTotalBalance() << "\n";
}

Account *BalanceInquiry::getAccount(int accountNumber, vector<Account> &accounts) {
  for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); it++) {
    if (it->getAccountNumber() == accountNumber) {
      return &*it;
    }
  }
  return nullptr;
}
