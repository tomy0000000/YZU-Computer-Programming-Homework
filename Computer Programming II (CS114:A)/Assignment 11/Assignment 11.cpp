//
//  Assignment 11.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <fstream>
using std::ifstream;
using std::ios;
#include "Vector.h"
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "BuyTickets.h"
#include "MemberDetails.h"
#include "NewMember.h"

#if defined(__clang__)
const char EOL_CHAR = '\r';
const bool BITER = true;
#endif
#if defined(_MSC_VER)
const char EOL_CHAR = '\n';
const bool BITER = false;
#endif

char hours[17][8] = {"09:00", "10:00", "11:00", "12:00", "13:00", "14:00",
                     "15:00", "16:00", "17:00", "18:00", "19:00", "20:00",
                     "21:00", "22:00", "23:00", "00:00", "01:00"};
char movieNames[30][60];
char availableDates[10][12];
int numDates;

int inputAnInteger(int begin, int end);
void signIn(MemberDatabase &memberDatabase);
void loadMovieNames();
void loadAvailableDates();

int main() {
  MemberDatabase memberDatabase;
  NewMember newMember(memberDatabase);

  cout << "Welcome to Vieshow Cinemas Taipei QSquare system\n\n";

  int choice;

  while (true) {
    cout << "Enter your choice:" << endl
         << "1. Sign In" << endl
         << "2. New Member" << endl
         << "3. End" << endl
         << "? ";

    choice = inputAnInteger(1, 3);

    switch (choice) {
    case 1:
      cout << "--------------------" << endl;
      signIn(memberDatabase);
      break;
    case 2:
      cout << "--------------------" << endl;
      newMember.execute();
      break;
    case 3:
      cout << endl << "Thank you..." << endl;
      cout << "--------------------" << endl;
      return 0;
    default:
      cout << endl << "Input Error!" << endl;
      cout << "--------------------" << endl;
      break;
    }
  }
}

int inputAnInteger(int begin, int end) {
  char string[80];

  //  cin.getline(string, 80, '\n');
  cin >> string;

  if (strlen(string) == 0 || strlen(string) >= 3) {
    return -1;
  }

  for (unsigned int i = 0; i < strlen(string); i++) {
    if (string[i] < '0' || string[i] > '9') {
      return -1;
    }
  }

  int number = atoi(string);
  if (number >= begin && number <= end) {
    return number;
  } else {
    return -1;
  }
}

void signIn(MemberDatabase &memberDatabase) {
  char email[40] = "";
  char password[24] = "";

  vector<Member>::iterator it;

  cout << "Enter email address:\t";
  cin >> email;
  cout << "Enter password:\t\t\t";
  cin >> password;
  cin.ignore();

  it = memberDatabase.getMember(email, password);
  if (it == memberDatabase.end()) {
    cout << endl << "Invalid Member Info!" << endl;
    cout << "--------------------" << endl;
    return;
  }
  cout << endl << "Welcome! " << it->getName() << endl;
  cout << "--------------------" << endl;

  loadMovieNames();
  loadAvailableDates();

  MemberDetails memberDetails(memberDatabase);
  MovieDatabase movieDatabase;
  BookingDatabase bookingDatabase;
  BuyTickets buyTickets(movieDatabase, bookingDatabase, email);
  int choice;

  while (true) {
    cout << "Enter your choice:" << endl
         << "1. Account Information" << endl
         << "2. Buy Tickets" << endl
         << "3. My Bookings" << endl
         << "4. Sign Out" << endl
         << "? ";

    choice = inputAnInteger(1, 4);

    switch (choice) {
    case 1:
      cout << "--------------------" << endl;
      memberDetails.execute(it);
      break;
    case 2:
      cout << "--------------------" << endl;
      buyTickets.execute();
      break;
    case 3:
      cout << "----------------------------------------------------------------"
              "-----------------"
           << endl;
      bookingDatabase.displayBookings(email, movieDatabase);
      break;
    case 4:
      cout << "--------------------" << endl;
      return;
    default:
      cout << endl << "Input Error!" << endl;
      cout << "--------------------" << endl;
      break;
    }
  }
}

void loadMovieNames() {
  ifstream inFile("Movie Names.txt", ios::in);
  if (!inFile) {
    cout << "File \"Movie Names.txt\" could not be opened" << endl;
    exit(1);
  }

  int i = 0;
  while (inFile.getline(movieNames[i], 60, EOL_CHAR)) {
    if (BITER) {
      inFile.get();
    }
    i++;
  }
}

void loadAvailableDates() {
  ifstream inFile("Available Dates.txt", ios::in);
  if (!inFile) {
    cout << "File \"Available Dates.txt\" could not be opened" << endl;
    exit(1);
  }

  int i = 0;
  while (inFile.getline(availableDates[i], 12, EOL_CHAR)) {
    if (BITER) {
      inFile.get();
    }
    i++;
  }
  numDates = i;
}
