//
//  main.cpp
//  Hw9
//  Automated Teller Machine
//
//  Created by Tomy Hsieh on 2018/5/15.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <list>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
#include "User.h"

int main() {
  
  User acc1("12345", "54321", 1000, 1200);
  User acc2("56789", "98765", 200, 200);
  list<User> users;
  users.push_back(acc1);
  users.push_back(acc2);
  string account, password;
  
  while (true) {
    cout << "Welcome!\n\n"
    << "Please enter your account number: ";
    cin >> account;
    cout << "\nEnter your PIN: ";
    cin >> password;
    cout << "\n";
  
    User *current = nullptr;
    for (list<User>::iterator it = users.begin(); it != users.end(); it++) {
      if (it->check_account(account) && it->check_password(password)) {
        current = &*it;
        break;
      }
    }
    if (current == nullptr) {
      cout << "Account Invalid!\n";
    }
    cout << "\n";
    
    bool operating = true;
    while (operating) {
      int choice = 0;
      while (choice == 0) {
        cout << "Main menu:\n"
        << "1 - View my balance\n"
        << "2 - Withdraw cash\n"
        << "3 - Deposit funds\n"
        << "4 - Exit\n\n"
        << "Enter a choice: ";
        cin >> choice;
        if (!(1 <= choice && choice <= 4)) {
          cout << "\nInput Error!\n";
          choice = 0;
        }
        cout << "\n";
      }
      switch (choice) {
        case 1: {
          cout << "Balance Information:\n"
          << " - Available balance: $"
          << current->get_available()
          << "\n - Total balance:     $"
          << current->get_total()
          << "\n\n";
        }
          break;
        case 2: {
          int withchoice = 0, withamount;
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
            cout << "\n";
          }
          switch (withchoice) {
            case 1:
              withamount = 20;
              break;
            case 2:
              withamount = 40;
              break;
            case 3:
              withamount = 60;
              break;
            case 4:
              withamount = 100;
              break;
            case 5:
              withamount = 200;
              break;
            default:
              break;
          }
          if (withchoice != 6) {
            cout << "Please take your cash from the cash dispenser.\n";
            current->Withdrawal(withamount);
          }
        }
          break;
        case 3:
          int depot;
          cout << "Please enter a deposit amount in CENTS (or 0 to cancel): ";
          cin >> depot;
          cout << "\n";
          if (depot != 0) {
            cout << "Please insert a deposit envelope containing $" << depot/100 << " in the deposit slot.\n\n";
            for (int i=0; i<3; i++) {
              this_thread::sleep_for(chrono::milliseconds(1000));
              cout << ".";
            }
            cout << endl;
            cout << "Your envelope has been received.\n"
            << "NOTE: The money deposited will not be available until we\n"
            << "verify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
            current->Deposit(depot/100);
          }
          break;
        case 4:
          cout << "Exiting the system...\n\n"
          << "Thank you! Goodbye!\n\n";
          operating = false;
          break;
        default:
          break;
      }
    }
  }
  
}
