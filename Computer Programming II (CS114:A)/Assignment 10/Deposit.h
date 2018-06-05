//
//  Deposit.h
//  Hw10
//  Driver program for the ATM system
//
//  Created by Tomy Hsieh on 2018/5/23.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <chrono>
#include <thread>
#include <vector>
using namespace std;
#include "Account.h"

class Deposit {
public:
  Deposit(int userAccountNumber, vector<Account> &atmAccounts) : accountNumber(userAccountNumber), accounts(atmAccounts) {}
  void execute();

private:
  int accountNumber;
  vector<Account> &accounts;
  double amount;
  Account *getAccount(int accountNumber, vector<Account> &accounts);
  double promptForDepositAmount() const;
};

#endif

void Deposit::execute() {
  Account *current = getAccount(accountNumber, accounts);
  amount = promptForDepositAmount();
  if (amount != 0) {
    cout << "Please insert a deposit envelope containing $" << amount
    << " in the deposit slot.\n\n";
    for (int i = 0; i < 3; i++) {
      this_thread::sleep_for(chrono::milliseconds(1000));
      cout << ".";
    }
    cout << endl;
    cout << "Your envelope has been received.\n"
    << "NOTE: The money deposited will not be available until we\n"
    << "verify the amount of any enclosed cash, and any enclosed "
    "checks clear.\n\n";
    current->credit(amount);
  }
}

Account *Deposit::getAccount(int accountNumber, vector<Account> &accounts) {
  for (vector<Account>::iterator it = accounts.begin(); it != accounts.end(); it++) {
    if (it->getAccountNumber() == accountNumber) {
      return &*it;
    }
  }
  return nullptr;
}

double Deposit::promptForDepositAmount() const {
  int depot;
  cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
  cin >> depot;
  cout << "\n";
  return depot/100;
}
