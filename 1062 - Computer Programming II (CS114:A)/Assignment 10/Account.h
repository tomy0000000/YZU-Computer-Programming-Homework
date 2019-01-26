//
//  Account.h
//  Hw10
//  Driver program for the ATM system
//
//  Created by Tomy Hsieh on 2018/5/23.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account {
public:
  Account(int theAccountNumber, int thePIN, double theAvailableBalance,
          double theTotalBalance) : accountNumber(theAccountNumber), pin(thePIN), availableBalance(theAvailableBalance), totalBalance(theTotalBalance) {}
  bool validatePIN(int userPIN) const { return userPIN == pin; }
  double getAvailableBalance() const { return availableBalance; }
  double getTotalBalance() const { return totalBalance; }
  int getAccountNumber() const { return accountNumber; }
  void credit(double amount) { availableBalance += amount; }
  void debit(double amount) {
    totalBalance -= amount;
    availableBalance -= amount;
  }
private:
  int accountNumber;
  int pin;
  double availableBalance;
  double totalBalance;
};

#endif
