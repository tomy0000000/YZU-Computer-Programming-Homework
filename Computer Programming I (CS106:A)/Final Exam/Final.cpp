//
//  main.cpp
//  Final
//  Hi-Lai Harbour Taoyuan Location Reservation System
//
//  Created by Tomy Hsieh on 2018/1/13.
//  Copyright © 2018年 Tomy Creative Studio. All rights reserved.
//
//  Code remains unchanged comparing to submitted version.

#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

struct Member {
  char mobileNumber[12]; // mobile number
};

struct Reservation {
  char mobileNumber[12]; // mobile phone number
  char name[8];          // name
  char date[12];         // booking date
  int time;              // booking time
  char email[40];        // email address
  int customerNumber;    // customer number
};

char times[6][12] = {"",        "11:30 AM", "12:00 PM",
                     "2:30 PM", "5:30 PM",  "6:00 PM"};

// Load File Functions
void loadMembers(vector<Member> &members);
void loadReservations(vector<Reservation> &reservations);

// Save File Functons
void saveMembers(const vector<Member> &members);
void saveReservations(const vector<Reservation> &reservations);

// Menu Functons
void book(vector<Reservation> &reservations, char mobileNumber[]);
void myBookings(vector<Reservation> &reservations, char mobileNumber[]);

// input an integer in the range [ begin, end ]
int inputAnInteger(int begin, int end);

// return true if and only if reservations contains an element with specified
// mobileNumber and date
bool exist(const vector<Reservation> &reservations, char mobileNumber[],
           char date[]);
int displayBookingInfo(const vector<Reservation> &reservations,
                       char mobileNumber[]);
void modifyBooking(vector<Reservation> &reservations, int recordNo,
                   char mobileNumber[]);

int main() {

  cout << "Welcome to Hi-Lai Harbour Taoyuan Location!\n\n";
  vector<Member> members; // Vector of the informations of all members
  loadMembers(members);

  cout << "Please enter your mobile number: ";
  char mobileNumber[12]; // current user's mobile number
  cin >> mobileNumber;   // input mobile number
  cin.ignore();

  bool exist = false;
  for (unsigned int i = 0; i < members.size(); ++i) {
    if (strcmp(members[i].mobileNumber, mobileNumber) == 0) {
      exist = true;
    }
  }
  if (!exist) {
    Member newMember;
    strcpy_s(newMember.mobileNumber, 12, mobileNumber);
    members.push_back(newMember);
  }

  vector<Reservation> reservations; // vector of all reservations
  loadReservations(reservations);

  // enumeration constants represent main menu options
  enum MenuOption { Book_A_Table = 1, My_Bookings, EXIT };
  bool userExited = false; // user has not chosen to exit

  // loop while user has not chosen option to exit system
  while (!userExited) {

    // show main menu and get user selection
    cout << "1 - Book a Table\n";
    cout << "2 - My Bookings\n";
    cout << "3 - End\n";
    cout << "Enter your choice: (1~3): ";

    int mainMenuSelection = inputAnInteger(1, 3);

    // decide how to proceed based on user's menu selection
    switch (mainMenuSelection) {
    case Book_A_Table:
      book(reservations, mobileNumber);
      break;
    case My_Bookings:
      myBookings(reservations, mobileNumber);
      break;
    case EXIT: // user chose to terminate session
      saveMembers(members);
      saveReservations(reservations);
      userExited = true; // this session should end
      cout << endl;
      break;
    default: // user did not enter an integer from 1-3
      cout << "\nIncorrect choice!" << endl;
    } // end switch
  }   // end while

  system("pause");
}

void loadMembers(vector<Member> &members) {
  ifstream inFile("Members.dat", ios::binary | ios::in);
  while (inFile.peek() != EOF) {
    members.resize(members.size() + 1);
    inFile.read(reinterpret_cast<char *>(&members[members.size() - 1]),
                sizeof(Member));
  }
  inFile.close();
}

void loadReservations(vector<Reservation> &reservations) {
  ifstream inFile("Reservations.dat", ios::binary | ios::in);
  while (inFile.peek() != EOF) {
    reservations.resize(reservations.size() + 1);
    inFile.read(
        reinterpret_cast<char *>(&reservations[reservations.size() - 1]),
        sizeof(Reservation));
  }
  inFile.close();
}

void saveMembers(const vector<Member> &members) {
  ofstream outFile("Members.dat", ios::binary | ios::out);
  for (int i = 0; i < members.size(); i++) {
    outFile.write(reinterpret_cast<const char *>(&members[i]), sizeof(Member));
  }
  outFile.close();
}

void saveReservations(const vector<Reservation> &reservations) {
  ofstream outFile("Reservations.dat", ios::binary | ios::out);
  for (int i = 0; i < reservations.size(); i++) {
    outFile.write(reinterpret_cast<const char *>(&reservations[i]),
                  sizeof(Reservation));
  }
  outFile.close();
}

int inputAnInteger(int begin, int end) {
  int num;
  cin >> num;
  return (num <= end && num >= begin) ? num : -1;
}

void book(vector<Reservation> &reservations, char mobileNumber[]) {

  Reservation newRes;
  strcpy_s(newRes.mobileNumber, mobileNumber);
  cout << endl;

  // Date
  cout << "Enter date (yyyy-mm-dd): ";
  cin >> newRes.date;
  cin.ignore();
  if (exist(reservations, mobileNumber, newRes.date)) {
    cout << "You have already booked a table on " << newRes.date << "!" << endl;
    return;
  }

  // Time
  for (int i = 1; i < 6; i++) {
    cout << i << ". " << times[i] << endl;
  }
  do {
    cout << "Enter your choice: ";
    newRes.time = inputAnInteger(1, 5);
    if (newRes.time == -1) {
      cout << "Input Error!" << endl;
    }
  } while (newRes.time == -1);

  // Name
  cout << "Enter name: ";
  cin >> newRes.name;
  cin.ignore();

  // Email
  cout << "Enter email: ";
  cin >> newRes.email;
  cin.ignore();

  // Number of Customers
  do {
    cout << "Enter the number of customers (1~15): ";
    newRes.customerNumber = inputAnInteger(1, 15);
    if (newRes.customerNumber == -1) {
      cout << "Input Error!" << endl;
    }
  } while (newRes.customerNumber == -1);

  reservations.push_back(newRes);
  cout << "Reservation Completed!" << endl;
}

void myBookings(vector<Reservation> &reservations, char mobileNumber[]) {
  int numBookings = displayBookingInfo(reservations, mobileNumber);
  if (numBookings == 0) {
    cout << "You have no reservations!" << endl;
    return;
  }
  int recordNo;
  do {
    cout << "Choose a reservation (0 to End): ";
    recordNo = inputAnInteger(0, numBookings);
    if (recordNo == -1) {
      cout << "Input Error!" << endl;
    } else if (recordNo == 0) {
      return;
    }
  } while (recordNo == -1);

  // find Exact Index
  int curNum = 1;
  for (int i = 0; i < reservations.size(); i++) {
    if (strcmp(reservations[i].mobileNumber, mobileNumber) == 0) {
      if (curNum == recordNo) {
        recordNo = i;
        break;
      } else {
        curNum++;
      }
    }
  }

  cout << "1 - Modify Booking" << endl;
  cout << "2 - Cancel Booking" << endl;
  cout << "3 - End" << endl;
  int action;
  do {
    cout << "Enter your choice: (1~3): ";
    action = inputAnInteger(1, 3);
    switch (action) {
    case 1:
      modifyBooking(reservations, recordNo, mobileNumber);
      break;
    case 2:
      for (int i = recordNo; i < reservations.size() - 1; i++) {
        reservations[i] = reservations[i + 1];
      }
      reservations.pop_back();
      break;
    case 3:
      cout << endl;
      return;
    default:
      cout << "Input Error!" << endl;
      break;
    }
  } while (action == -1);
}

bool exist(const vector<Reservation> &reservations, char mobileNumber[],
           char date[]) {
  for (int i = 0; i < reservations.size(); i++) {
    if (strcmp(reservations[i].mobileNumber, mobileNumber) == 0 &&
        strcmp(reservations[i].date, date) == 0) {
      return true;
    }
  }
  return false;
}

int displayBookingInfo(const vector<Reservation> &reservations,
                       char mobileNumber[]) {
  int numBookings = 0;
  cout << endl;
  for (int i = 0; i < reservations.size(); i++) {
    if (strcmp(reservations[i].mobileNumber, mobileNumber) == 0) {
      if (numBookings == 0) {
        cout << setw(15) << "Mobile Number";
        cout << setw(8) << "Name";
        cout << setw(13) << "Date";
        cout << setw(10) << "Time";
        cout << setw(30) << "Email";
        cout << setw(18) << "No. of Customers";
        cout << endl;
      }
      numBookings++;
      cout << numBookings;
      cout << setw(14) << reservations[i].mobileNumber;
      cout << setw(8) << reservations[i].name;
      cout << setw(13) << reservations[i].date;
      cout << setw(10) << times[reservations[i].time];
      cout << setw(30) << reservations[i].email;
      cout << setw(18) << reservations[i].customerNumber;
      cout << endl;
    }
  }
  cout << endl;
  return numBookings;
}

void modifyBooking(vector<Reservation> &reservations, int recordNo,
                   char mobileNumber[]) {
  cout << "1. Date"
       << "\t\t\t" << reservations[recordNo].date << endl;
  cout << "2. Time"
       << "\t\t\t" << times[reservations[recordNo].time] << endl;
  cout << "3. No of Customers"
       << "\t" << reservations[recordNo].customerNumber << endl;
  cout << endl;
  int choice;
  cout << "Enter your choice (0 to End): ";
  choice = inputAnInteger(0, 3);
  switch (choice) {
  case 0:
    cout << endl;
    return;
  case 1:
    char newDate[12];
    cout << "Enter date (yyyy-mm-dd): ";
    cin >> newDate;
    cin.ignore();
    if (exist(reservations, mobileNumber, newDate)) {
      cout << "You have already booked a table on " << newDate << "!" << endl;
      return;
    }
    strcpy_s(reservations[recordNo].date, newDate);
    break;
  case 2:
    int newTime;
    for (int i = 1; i < 6; i++) {
      cout << i << ". " << times[i] << endl;
    }
    do {
      cout << "Enter your choice: ";
      newTime = inputAnInteger(1, 5);
      if (newTime == -1) {
        cout << "Input Error!" << endl;
      }
    } while (newTime == -1);
    reservations[recordNo].time = newTime;
    break;
  case 3:
    int newData;
    do {
      cout << "Enter the number of customers (1~15): ";
      newData = inputAnInteger(1, 15);
      if (newData == -1) {
        cout << "Input Error!" << endl;
      }
    } while (newData == -1);
    reservations[recordNo].customerNumber = newData;
    break;
  default:
    cout << "Input Error!" << endl;
    break;
  }
  cout << endl;
}