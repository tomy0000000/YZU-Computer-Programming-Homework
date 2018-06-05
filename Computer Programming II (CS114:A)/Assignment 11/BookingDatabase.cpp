//
//  BookingDatabase.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include "BookingDatabase.h"
#include <fstream>
using std::ifstream;
using std::ios;
using std::ofstream;
#include <iostream>
using std::cout;
using std::endl;

extern char hours[17][8];
extern char movieNames[30][60];
extern char availableDates[10][12];

BookingDatabase::BookingDatabase() { loadBookings(); }

BookingDatabase::~BookingDatabase() { saveBookings(); }

void BookingDatabase::addBooking(Booking newBooking) {
  bookings.push_back(newBooking);
}

bool BookingDatabase::existingBooking(string email) {
  for (vector<Booking>::iterator it = bookings.begin(); it != bookings.end();
       ++it) {
    if (string(it->getEmail()) == email) {
      return true;
    }
  }
  return false;
}

void BookingDatabase::displayBookings(string email,
                                      MovieDatabase &movieDatabase) {
  bool found = false;
  for (vector<Booking>::iterator it = bookings.begin(); it != bookings.end();
       ++it) {
    if (it->getEmail() == email) {
      if (!found) {
        cout << "Booking Histories: " << endl << endl;
        found = true;
      } else {
        cout << endl;
      }
      cout << "Movie:\t\t\t" << movieNames[it->getMovieCode()] << endl
           << "Date:\t\t\t" << availableDates[it->getDateCode()] << endl
           << "Show Time:\t\t" << hours[it->getSessionTimeCode()] << endl
           << "Seats:\t\t\t";
      int numTickets = 0;
      for (int i = 0; i < 4; i++) {
        numTickets += it->getNumTickets(i);
      }
      for (int i = 0; i < numTickets; i++) {
        cout << it->getSeletedSeat(i) << ((i == numTickets - 1) ? "" : " ");
      }
      cout << endl << endl;
      it->displayBooking(movieDatabase);
      cout << "--------------------";
    }
  }
  if (!found) {
    cout << endl << "No Booking History Found!" << endl << endl;
    cout << "--------------------" << endl;
  } else {
    cout << "-------------------------------------------------------------"
         << endl;
  }
}

void BookingDatabase::loadBookings() {
  ifstream inFile("Bookings.dat", ios::in | ios::binary);
  while (inFile.peek() != EOF) {
    bookings.resize(bookings.size() + 1);
    inFile.read(reinterpret_cast<char *>(&bookings[bookings.size() - 1]),
                sizeof(Booking));
  }
  inFile.close();
}

void BookingDatabase::saveBookings() {
  ofstream outFile("Bookings.dat", ios::out | ios::binary);
  for (int i = 0; i < bookings.size(); i++) {
    outFile.write(reinterpret_cast<const char *>(&bookings[i]),
                  sizeof(Booking));
  }
  outFile.close();
}
