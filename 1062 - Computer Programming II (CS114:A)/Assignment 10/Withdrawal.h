//
//  Withdrawal.h
//  Hw10
//  Driver program for the ATM system
//
//  Created by Tomy Hsieh on 2018/5/23.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef WITHDRAWAL_H
#define WITHDRAWAL_H

#include <vector>
using namespace std;
#include "Account.h"

class Withdrawal {
public:
  Withdrawal(int userAccountNumber, vector<Account> &atmAccounts,
             int &atmRemainingBills) : accountNumber(userAccountNumber), accounts(atmAccounts), remainingBills(atmRemainingBills) {}
  void execute();

private:
  int accountNumber;
  vector<Account> &accounts;
  int amount;
  int &remainingBills;
  Account *getAccount(int accountNumber, vector<Account> &accounts);
  int displayMenuOfAmounts() const;
};

#endif

void Withdrawal::execute() {
  Account *current = getAccount(accountNumber, accounts);
  amount = displayMenuOfAmounts();
  if (amount) {
    cout << "Please take your cash from the cash dispenser.\n";
    current->debit(amount);
  }
}

Account *Withdrawal::getAccount(int accountNumber, vector<Account> &accounts) {
  for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); it++) {
    if (it->getAccountNumber() == accountNumber) {
      return &*it;
    }
  }
  return nullptr;
}

int Withdrawal::displayMenuOfAmounts() const {
  int withchoice = 0;
  while (withchoice == 0) {
    cout << "Withdrawal options:\n"
    << "1 - $20\n"
    << "2 - $40\n"
    << "3 - $60\n"
    << "4 - $100\n"
    << "5 - $200\n"
    << "6 - Cancel transaction\n\n"
    << "Choose a withdrawal option (1-6):";
    cin >> withchoice;
    if (!(1 <= withchoice && withchoice <= 6)) {
      cout << "\nInput Error!\n";
      withchoice = 0;
    }
  }
  switch (withchoice) {
    case 1:
      return 20;
      break;
    case 2:
      return 40;
      break;
    case 3:
      return 60;
      break;
    case 4:
      return 100;
      break;
    case 5:
      return 200;
      break;
    default:
      return 0;
      break;
  }
}

