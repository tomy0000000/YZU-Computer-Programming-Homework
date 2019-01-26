//
//  main.cpp
//  Hw10
//  Driver program for the ATM system
//
//  Created by Tomy Hsieh on 2018/5/23.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iomanip>
#include <iostream>
using namespace std;
#include "Account.h"
#include "BalanceInquiry.h"
#include "Deposit.h"
#include "Withdrawal.h"

// attempts to authenticate user
void authenticateUser(bool &userAuthenticated, int &currentAccountNumber,
                      vector<Account> &accounts);

// retrieve Account object containing specified account number
Account *getAccount(int accountNumber, vector<Account> &accounts);

// display the main menu and perform transactions
void performTransactions(int &currentAccountNumber, vector<Account> &accounts);

// display the main menu and return an input selection
int displayMainMenu();

int main() {
  bool userAuthenticated = false;
  int currentAccountNumber = 0;

  // create two Account objects for testing
  Account account1(12345, 54321, 1000.0, 1200.0);
  Account account2(98765, 56789, 200.0, 200.0);

  vector<Account> accounts;
  accounts.push_back(account1);
  accounts.push_back(account2);
  while (true) {
    while (!userAuthenticated) {
      cout << "\nWelcome!" << endl;
      authenticateUser(userAuthenticated, currentAccountNumber,
                       accounts);
    }
    performTransactions(currentAccountNumber, accounts);
    userAuthenticated = false;
    currentAccountNumber = 0;
    cout << "\nThank you! Goodbye!" << endl;
  }
}

// attempt to authenticate user against database
void authenticateUser(bool &userAuthenticated, int &currentAccountNumber,
                      vector<Account> &accounts) {
  cout << "\nPlease enter your account number: ";
  int accountNumber;
  cin >> accountNumber;
  cout << "\nEnter your PIN: ";
  int pin;
  cin >> pin;

  Account *const userAccountPtr = getAccount(accountNumber, accounts);

  // if account exists, return result of Account function validatePIN
  if (userAccountPtr != NULL) {
    userAuthenticated = userAccountPtr->validatePIN(pin);
  } else {
    userAuthenticated = false;
  }
  if (userAuthenticated) {
    currentAccountNumber = accountNumber;
  } else {
    cout << "Invalid account number or PIN. Please try again.\n";
  }
}

// retrieve Account object containing specified account number
Account *getAccount(int accountNumber, vector<Account> &accounts) {
  for (size_t i = 0; i < accounts.size(); i++) {
    if (accounts[i].getAccountNumber() == accountNumber) {
      return &accounts[i];
    }
  }
  return NULL;
}

// display the main menu and perform transactions
void performTransactions(int &currentAccountNumber, vector<Account> &accounts) {
  
  enum MenuOption { BALANCE_INQUIRY = 1, WITHDRAWAL, DEPOSIT, EXIT };
  BalanceInquiry *balanceInquiryPtr;
  Withdrawal *withdrawalPtr;
  Deposit *depositPtr;
  static const int INITIAL_REMAINING_BILLS = 500;
  int remainingBills = INITIAL_REMAINING_BILLS;

  bool userExited = false;
  while (!userExited) {
    int mainMenuSelection = displayMainMenu();
    switch (mainMenuSelection) {
    case BALANCE_INQUIRY:
      balanceInquiryPtr = new BalanceInquiry(currentAccountNumber, accounts);
      balanceInquiryPtr->execute();
      delete balanceInquiryPtr;
      break;
    case WITHDRAWAL:
      withdrawalPtr =
          new Withdrawal(currentAccountNumber, accounts, remainingBills);
      withdrawalPtr->execute();
      delete withdrawalPtr;
      break;
    case DEPOSIT:
      depositPtr = new Deposit(currentAccountNumber, accounts);
      depositPtr->execute();
      delete depositPtr;
      break;
    case EXIT:
      cout << "\nExiting the system..." << endl;
      userExited = true;
      break;
    default:
      cout << "\nYou did not enter a valid selection. Try again." << endl;
      break;
    }
  }
}

// display the main menu and return an input selection
int displayMainMenu() {
  cout << "\nMain menu:" << endl;
  cout << "1 - View my balance" << endl;
  cout << "2 - Withdraw cash" << endl;
  cout << "3 - Deposit funds" << endl;
  cout << "4 - Exit\n" << endl;
  cout << "Enter a choice: ";
  int choice;
  cin >> choice;
  return choice;
}
