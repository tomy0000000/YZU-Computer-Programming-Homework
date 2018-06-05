//
//  BuyTickets.cpp
//  Hw 11
//  Object Oriented Vieshow Cinemas Taipei QSquare system
//
//  Created by Tomy Hsieh on 2018/6/3.
//  Copyright © 2018年 Tomy Hsieh. All rights reserved.
//

#include <iomanip>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include "BuyTickets.h"

extern char hours[17][8];
extern char movieNames[30][60];
extern char availableDates[10][12];
extern int numDates;
int inputAnInteger(int begin, int end);

BuyTickets::BuyTickets(MovieDatabase &theMovieDatabase,
                       BookingDatabase &theBookingDatabase, string theEmail)
    : movieDatabase(theMovieDatabase), bookingDatabase(theBookingDatabase) {
  unsigned long length = theEmail.size();
  for (int i = 0; i < length; i++) {
    email[i] = theEmail[i];
  }
  email[length] = '\0';
}

void BuyTickets::execute() {

  // Show Movie Table
  movieDatabase.displaySessionTimes(movieNames, availableDates);

  // Select Movie
  Booking tmpBooking;
  int input;
  do {
    cout << "Enter Movie Code\t\t(0 - 10):\t";
    input = inputAnInteger(0, 10);
    if (input == -1) {
      cout << endl << "Input Error!" << endl;
      cout << "--------------------" << endl;
    }
  } while (input == -1);
  tmpBooking.setMovieCode(input);
  do {
    cout << "Enter Date Code\t\t\t(0 - 3):\t";
    input = inputAnInteger(0, 3);
    if (input == -1) {
      cout << endl << "Input Error!" << endl;
      cout << "--------------------" << endl;
    } else if (!movieDatabase.getMovie(tmpBooking.getMovieCode())
                    .getDate(input)) {
      cout << endl << "Date Not Available!" << endl;
      cout << "--------------------" << endl;
    }
  } while (input == -1 ||
           !movieDatabase.getMovie(tmpBooking.getMovieCode()).getDate(input));
  tmpBooking.setDateCode(input);
  do {
    cout << "Enter Session Time Code\t(0 - 16):\t";
    input = inputAnInteger(0, 16);
    if (input == -1) {
      cout << endl << "Input Error!" << endl;
      cout << "--------------------" << endl;
    } else if (!movieDatabase.getMovie(tmpBooking.getMovieCode())
                    .getSessionTime(input)) {
      cout << endl << "Session Time Not Available!" << endl;
      cout << "--------------------" << endl;
    }
  } while (
      input == -1 ||
      !movieDatabase.getMovie(tmpBooking.getMovieCode()).getSessionTime(input));
  tmpBooking.setSessionTimeCode(input);
  cout << "--------------------" << endl;

  // Display Summary
  cout << "Movie:\t\t" << movieNames[tmpBooking.getMovieCode()] << endl
       << "Date:\t\t" << availableDates[tmpBooking.getDateCode()] << endl
       << "Show Time:\t" << hours[tmpBooking.getSessionTimeCode()] << endl
       << "Price:\t\t"
       << movieDatabase.getMovie(tmpBooking.getMovieCode()).getPrice(0)
       << " (Adult)" << endl
       << "\t\t\t"
       << movieDatabase.getMovie(tmpBooking.getMovieCode()).getPrice(1)
       << " (Concession)" << endl
       << "\t\t\t"
       << movieDatabase.getMovie(tmpBooking.getMovieCode()).getPrice(2)
       << " (Disability)" << endl
       << "\t\t\t"
       << movieDatabase.getMovie(tmpBooking.getMovieCode()).getPrice(3)
       << " (Elderly)" << endl
       << "--------------------" << endl;

  // Select Ticket Amount
  int numTickets[4], totalTicket;
  char ticketType[4][12] = {"Adult\t\t", "Concession\t", "Disability\t",
                            "Elderly\t\t"};
  do {
    totalTicket = 0;
    for (int i = 0; i < 4; i++) {
      do {
        cout << "Enter the Number of " << ticketType[i] << " Tickets (0 - 6): ";
        numTickets[i] = inputAnInteger(0, 6);
        if (numTickets[i] == -1) {
          cout << endl << "Input Error!" << endl;
          cout << "--------------------" << endl;
        }
      } while (numTickets[i] == -1);
      totalTicket += numTickets[i];
    }
    if (totalTicket < 1) {
      cout << endl << "You didn't buy any ticket!" << endl;
      cout << "--------------------" << endl;
    }
  } while (totalTicket < 1);
  tmpBooking.setNumTickets(numTickets);
  cout << "--------------------" << endl;

  // Packup
  tmpBooking.displayBooking(movieDatabase);
  cout << "--------------------" << endl;
  selectSeats(tmpBooking);
  tmpBooking.setEmail(string(email));
  bookingDatabase.addBooking(tmpBooking);
  cout << "Successful!" << endl;
  cout << "--------------------" << endl;
}

void BuyTickets::selectSeats(Booking &newBooking) {

  // Print Seat Map
  cout << "  A B C D E F G H I J K L" << endl;
  for (int i = 0; i < 8; i++) {
    cout << i << " ";
    for (int j = 0; j < 12; j++) {
      cout << movieDatabase.getMovie(newBooking.getMovieCode())
                  .getOccupiedSeat(newBooking.getDateCode(),
                                   newBooking.getSessionTimeCode(), i, j)
           << " ";
    }
    cout << endl;
  }

  // Select Seats
  string tmpSeat[24];
  int totalTicket = 0;
  for (int i = 0; i < 4; i++) {
    totalTicket += newBooking.getNumTickets(i);
  }
  cout << endl << "Select " << totalTicket << " seats (e.g. 0A):" << endl;
  bool validSeat;
  for (int i = 0; i < totalTicket; i++) {
    validSeat = false;
    do {
      cout << "? ";
      cin >> tmpSeat[i];
      tmpSeat[i][1] = toupper(tmpSeat[i][1]);
      if (tmpSeat[i].size() != 2 || !isnumber(tmpSeat[i][0]) ||
          !isalpha(tmpSeat[i][1])) {
        cout << endl << "Input Error!" << endl;
        cout << "--------------------" << endl;
      } else if (!movieDatabase.getMovie(newBooking.getMovieCode())
                      .getOccupiedSeat(newBooking.getDateCode(),
                                       newBooking.getSessionTimeCode(),
                                       int(tmpSeat[i][0]) - '0',
                                       int(tmpSeat[i][1]) - 'A')) {
        validSeat = true;
        movieDatabase.setMovieSeat(
            newBooking.getMovieCode(), newBooking.getDateCode(),
            newBooking.getSessionTimeCode(), int(tmpSeat[i][0]) - '0',
            int(tmpSeat[i][1]) - 'A');
      } else {
        cout << endl
             << "This seat bas been occupied." << endl
             << "Please select another seat." << endl;
        cout << "--------------------" << endl;
      }
    } while (!validSeat);
  }
  newBooking.setSeletedSeats(tmpSeat, totalTicket);
}
