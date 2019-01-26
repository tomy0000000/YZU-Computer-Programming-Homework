//
//  main.cpp
//  Hw12
//  Complete Vieshow Cinemas Taipei QSquare Member & Ticket Booking System
//
//  Created by Tomy Hsieh on 2017/12/12.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

struct MemberRecord {
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

struct Movie {
    int movieCode;
    int prices[4];
    // prices[0]:adult
    // prices[1]:concession
    // prices[2]:disability
    // prices[3]:elderly
    bool dates[9];
    bool sessionTimes[17];
    bool occupiedSeats[9][17][8][12]; // occupiedSeats[i][j] is the occupied Seats for all accounts
};                                           // at j-th session time on i-th date

struct BookingInfo {
    char email[40];
    int movieCode;
    int dateCode;
    int sessionTimeCode;
    int numTickets[4];
    // numTickets[0]: the number of adult tickets,
    // numTickets[1]: the number of concession tickets,
    // numTickets[2]: the number of disability tickets,
    // numTickets[3]: the number of elderly tickets
    char seletedSeats[24][4]; // seleted seats for the user with the specified email
};

char hours[17][8] = { "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00",
    "18:00", "19:00", "20:00", "21:00", "22:00", "23:00", "00:00", "01:00" };

//Data Loading Functions
void loadMemberInfo(MemberRecord memberDetails[], int &numMembers);                                                     //Ok
void loadBookingHistories(BookingInfo bookingHistories[], int &numBookings);                                            //Ok
void loadAvailableDates(char availableDates[][12], int &numDates);                                                      //Ok
void loadMovies(Movie movies[], int &numMovies);                                                                        //Beta
void loadMovieNames(char movieNames[][60], int numMovies);                                                              //Ok

//Data Saving Functions
void saveMemberInfo(MemberRecord memberDetails[], int numMembers);                                                      //Ok
void saveMovies(Movie movies[], int numMovies);                                                                         //Beta
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings);                                             //Ok

//Menu Functions
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
            BookingInfo bookingHistories[], int &numBookings, char availableDates[][12], int numDates);                 //Beta
void newMember(MemberRecord memberDetails[], int &numMembers);                                                          //Ok
void buyTickets(BookingInfo bookingHistories[], int &numBookings, Movie movies[], char movieNames[][60],
                int numMovies, char availableDates[][12], int numDates, char email[]);                                  //Beta

//Info Showing Functions
void display(Movie movies[], BookingInfo bookingHistory);                                                               //Beta
void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
                         char availableDates[][12], int numDates);                                                      //Ok
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
                           char movieNames[][60], char availableDates[][12], char email[]);                             //Ok

//Universal Functions
int inputAnInteger(int begin, int end);                                                                                 //Ok

//Tool Functions
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int &recordNumber);           //Ok
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber);                                      //Ok
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int &numMembers);                                     //Ok
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int &numMembers);                                     //Ok
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[]);                                      //Beta

void printMap(Movie movies[], int movieCode, int date, int sessionTime) {
    cout << "  A B C D E F G H I J K L" << endl;
    for (int i=0; i<8; i++) {
        cout << i << " ";
        for (int j=0; j<12; j++) {
            cout << movies[movieCode].occupiedSeats[date][sessionTime][i][j] << " ";
        }
        cout << endl;
    }
}

int main() {

    // Load Datas
    MemberRecord memberDetails[100] = {};
    BookingInfo bookingHistories[1000] = {};
    Movie movies[30] = {};
    char movieNames[30][60] = {};
    char availableDates[10][12];
    int numMembers = 0;
    int numBookings = 0;
    int numMovies = 0;
    int numDates = 0;
    
    loadMemberInfo(memberDetails, numMembers);
    loadBookingHistories(bookingHistories, numBookings);
    loadMovies(movies, numMovies);
    loadMovieNames(movieNames, numMovies);
    loadAvailableDates(availableDates, numDates);
    
    //System Starts
    cout << "Welcome to Vieshow Cinemas Taipei QSquare system" << endl << endl;
    int choice;
    
    while(true) {
        cout << "Enter your choice:" << endl;
        cout << "1. Sign In" << endl;
        cout << "2. New Member" << endl;
        cout << "3. End" << endl;
        cout << "? ";
        choice = inputAnInteger(1, 3);
        cout << endl;
        switch (choice) {
            case 1:
                signIn(memberDetails, numMembers, movies, movieNames, numMovies, bookingHistories, numBookings, availableDates, numDates);
                break;
            case 2:
                newMember(memberDetails, numMembers);
                break;
            case 3:
                saveMemberInfo(memberDetails, numMembers);
                saveBookingHistories(bookingHistories, numBookings);
                saveMovies(movies, numMovies);
                cout << "Thank you..." << endl << endl;
                return 0;
            default:
                cout << "Input Error!" << endl << endl;
                break;
        }
    }
}

void loadMemberInfo(MemberRecord memberDetails[], int &numMembers) {
    ifstream inMemberFile("Member Info.dat", ios::in | ios::binary);
    while (inMemberFile.peek() != EOF) {
        inMemberFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(MemberRecord));
        numMembers++;
    }
    inMemberFile.close();
}

void loadBookingHistories(BookingInfo bookingHistories[], int &numBookings) {
    ifstream inBookingFile("Booking Histories.dat", ios::in | ios::binary);
    while (inBookingFile.peek() != EOF) {
        inBookingFile.read(reinterpret_cast<char*>(&bookingHistories[numBookings]), sizeof(BookingInfo));
        numBookings++;
    }
    inBookingFile.close();
}

void loadAvailableDates(char availableDates[][12], int &numDates) {
    ifstream inDatesFile("Available Dates.txt", ios::in);
    while (inDatesFile.peek() != EOF) {
        inDatesFile.getline(availableDates[numDates], 12);
        
        //Following Are Required in Mac
        string tmp = string(availableDates[numDates]);
        tmp.pop_back();
        strcpy(availableDates[numDates], tmp.c_str());
        //Above Are Required in Mac
        
        numDates++;
    }
    inDatesFile.close();
}

void loadMovies(Movie movies[], int &numMovies) {
    ifstream inMoviesFile("Movies.dat", ios::in | ios::binary);
    while (inMoviesFile.peek() != EOF) {
        inMoviesFile.read(reinterpret_cast<char*>(&movies[numMovies]), sizeof(Movie));
        numMovies++;
    }
    inMoviesFile.close();
}

void loadMovieNames(char movieNames[][60], int numMovies) {
    ifstream inNameFile("Movie Names.txt", ios::in);
    int i=0;
    while (inNameFile.peek() != EOF) {
        inNameFile.getline(movieNames[i], 60);
        i++;
    }
    inNameFile.close();
}

void saveMemberInfo(MemberRecord memberDetails[], int numMembers) {
    ofstream outMemberFile("Member Info.dat", ios::out | ios::binary);
    if (!outMemberFile) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    for (int i=0; i<numMembers; i++) {
        outMemberFile.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(MemberRecord));
    }
    outMemberFile.close();
}

void saveMovies(Movie movies[], int numMovies) {
    ofstream outMovieFile("Movies.dat", ios::out | ios::binary);
    if (!outMovieFile) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    for (int i=0; i<numMovies; i++) {
        outMovieFile.write(reinterpret_cast<const char*>(&movies[i]), sizeof(Movie));
    }
    outMovieFile.close();
}

void saveBookingHistories(BookingInfo bookingHistories[], int numBookings) {
    ofstream outBookingFile("Booking Histories.dat", ios::out | ios::binary);
    if (!outBookingFile) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    for (int i=0; i<numBookings; i++) {
        outBookingFile.write(reinterpret_cast<const char*>(&bookingHistories[i]), sizeof(BookingInfo));
    }
    outBookingFile.close();
}

void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
            BookingInfo bookingHistories[], int &numBookings, char availableDates[][12], int numDates) {
    
    //Create Login Informations
    MemberRecord loginToken;
    int recordNumber = -1;
    bool loggedInFail = true;
    do {
        
        //Prompt
        cout << "Enter email address: ";
        cin >> loginToken.email;
        cout << "Enter password: ";
        cin >> loginToken.password;
        
        //Check Account
        for (int i=0; i<numMembers; i++) {
            if (strcmp(loginToken.email, memberDetails[i].email) == 0) {
                recordNumber = i;
            }
        }
        loggedInFail = illegal(loginToken.email, loginToken.password, memberDetails, numMembers, recordNumber);
        
        //Sent Message if Error
        if (loggedInFail) {
            cout << "Sorry, unrecognized email or password." << endl << endl;
        }
    } while (loggedInFail);
    
    //Logged In Success Menu
    while (true) {
        cout << endl;
        cout << "Enter your choice:" << endl;
        cout << "1. Account Information" << endl;
        cout << "2. Buy Tickets" << endl;
        cout << "3. My Bookings" << endl;
        cout << "4. Sign Out" << endl;
        cout << "? ";
        int choice = inputAnInteger(1, 4);
        cout << endl;
        
        switch (choice) {
            case 1:
                accountInfor(memberDetails, numMembers, recordNumber);
                break;
            case 2:
                displaySessionTimes(movies, movieNames, numMovies, availableDates, numDates);
                buyTickets(bookingHistories, numBookings, movies, movieNames, numMovies, availableDates, numDates, memberDetails[recordNumber].email);
                cout << "Successful!" << endl;
                break;
            case 3:
                displayBookingHistory(bookingHistories, numBookings, movies, movieNames, availableDates, memberDetails[recordNumber].email);
                break;
            case 4:
                return;
            default:
                cout << "Input Error!" << endl << endl;
                break;
        }
    }
    
}

void newMember(MemberRecord memberDetails[], int &numMembers) {
    
    //Create TempMember
    MemberRecord tmpMember;
    cout << "Enter your ID number: ";
    cin >> tmpMember.IDNumber;
    if (existingID(tmpMember.IDNumber, memberDetails, numMembers)) {
        cout << "An account already exists with the ID number!" << endl << endl;
        return;
    }
    cout << "Enter your name: ";
    cin >> tmpMember.name;
    cout << "Enter an email address: ";
    cin >> tmpMember.email;
    if (existingEmail(tmpMember.email, memberDetails, numMembers)) {
        cout << "An account already exists with the Email!" << endl << endl;
        return;
    }
    cout << "Enter a password: ";
    cin >> tmpMember.password;
    cout << "Enter your phone number: ";
    cin >> tmpMember.phone;
    
    //Save Verified TempMember to Database
    strcpy(memberDetails[numMembers].IDNumber, tmpMember.IDNumber);
    strcpy(memberDetails[numMembers].name, tmpMember.name);
    strcpy(memberDetails[numMembers].email, tmpMember.email);
    strcpy(memberDetails[numMembers].password, tmpMember.password);
    strcpy(memberDetails[numMembers].phone, tmpMember.phone);
    numMembers++;
    
    //Return Success
    cout << "Successful!" << endl;
    cout << endl;
    
}

void buyTickets(BookingInfo bookingHistories[], int &numBookings, Movie movies[], char movieNames[][60],
                int numMovies, char availableDates[][12], int numDates, char email[]) {
    BookingInfo tmpBooking;
    do {
        cout << "Enter Movie Code: (0 - 11): ";
        tmpBooking.movieCode = inputAnInteger(0, 11);
        if (tmpBooking.movieCode == -1) {
            cout << "Input Error!" << endl << endl;
        }
    } while (tmpBooking.movieCode == -1);
    do {
        cout << "Enter date code (0 - 8): ";
        tmpBooking.dateCode = inputAnInteger(0, 8);
        if (tmpBooking.dateCode == -1) {
            cout << "Input Error!" << endl << endl;
        }
        else if (!movies[tmpBooking.movieCode].dates[tmpBooking.dateCode]) {
            cout << "Date Not Available!" << endl << endl;
        }
    } while (tmpBooking.dateCode == -1 || !movies[tmpBooking.movieCode].dates[tmpBooking.dateCode]);
    do {
        cout << "Enter session time code (0 - 16): ";
        tmpBooking.sessionTimeCode = inputAnInteger(0, 16);
        if (tmpBooking.sessionTimeCode == -1) {
            cout << "Input Error!" << endl << endl;
        }
        else if (!movies[tmpBooking.movieCode].sessionTimes[tmpBooking.sessionTimeCode]) {
            cout << "Session Not Available!" << endl << endl;
        }
    } while (tmpBooking.sessionTimeCode == -1 || !movies[tmpBooking.movieCode].sessionTimes[tmpBooking.sessionTimeCode]);
    int totalTicket = 0;
    do {
        totalTicket = 0;
        do {
            cout << "Enter the number of adult tickets (0 - 6): ";
            tmpBooking.numTickets[0] = inputAnInteger(0, 6);
            if (tmpBooking.numTickets[0] == -1) {
                cout << "Input Error!" << endl << endl;
            }
        } while (tmpBooking.numTickets[0] == -1);
        totalTicket += tmpBooking.numTickets[0];
        do {
            cout << "Enter the number of concession tickets (0 - 6): ";
            tmpBooking.numTickets[1] = inputAnInteger(0, 6);
            if (tmpBooking.numTickets[1] == -1) {
                cout << "Input Error!" << endl << endl;
            }
        } while (tmpBooking.numTickets[1] == -1);
        totalTicket += tmpBooking.numTickets[1];
        do {
            cout << "Enter the number of disability tickets (0 - 6): ";
            tmpBooking.numTickets[2] = inputAnInteger(0, 6);
            if (tmpBooking.numTickets[2] == -1) {
                cout << "Input Error!" << endl << endl;
            }
        } while (tmpBooking.numTickets[2] == -1);
        totalTicket += tmpBooking.numTickets[2];
        do {
            cout << "Enter the number of elderly tickets (0 - 6): ";
            tmpBooking.numTickets[3] = inputAnInteger(0, 6);
            if (tmpBooking.numTickets[3] == -1) {
                cout << "Input Error!" << endl << endl;
            }
        } while (tmpBooking.numTickets[3] == -1);
        totalTicket += tmpBooking.numTickets[3];
        if (totalTicket<1) {
            cout << "You didn't buy any ticket!" << endl << endl;
        }
        if (totalTicket>6) {
            cout << "You bought too many ticket!" << endl << endl;
        }
    } while (totalTicket<1 || totalTicket>6);
    cout << endl;
    display(movies, tmpBooking);
    strcpy(bookingHistories[numBookings].email, email);
    bookingHistories[numBookings].movieCode = tmpBooking.movieCode;
    bookingHistories[numBookings].dateCode = tmpBooking.dateCode;
    bookingHistories[numBookings].sessionTimeCode = tmpBooking.sessionTimeCode;
    for (int i=0; i<5; i++) {
        bookingHistories[numBookings].numTickets[i] = tmpBooking.numTickets[i];
    }
    selectSeats(bookingHistories, numBookings, movies);
    numBookings++;
    cout << endl;
}

void display(Movie movies[], BookingInfo bookingHistory) {
    
    cout << "\t\t\t\t\t" << "No. of Tickets" << "\t\t" << "Price" << "\t\t" << "Subtotal" << endl;
    int Num=0, Price=0, Sub=0, Total=0;
    if (bookingHistory.numTickets[0] != 0) {
        Num = bookingHistory.numTickets[0];
        Price = movies[bookingHistory.movieCode].prices[0];
        Sub = Num * Price;
        Total += Sub;
        cout << "Adult ticket" << "\t\t" << Num << "\t\t\t\t\t" << Price << "\t\t\t" << Sub << endl;
    }
    if (bookingHistory.numTickets[1] != 0) {
        Num = bookingHistory.numTickets[1];
        Price = movies[bookingHistory.movieCode].prices[1];
        Sub = Num * Price;
        Total += Sub;
        cout << "Concession ticket" << "\t" << Num << "\t\t\t\t\t" << Price << "\t\t\t" << Sub << endl;
    }
    if (bookingHistory.numTickets[2] != 0) {
        Num = bookingHistory.numTickets[2];
        Price = movies[bookingHistory.movieCode].prices[2];
        Sub = Num * Price;
        Total += Sub;
        cout << "Disability tickets " << "\t" << Num << "\t\t\t\t\t" << Price << "\t\t\t" << Sub << endl;
    }
    if (bookingHistory.numTickets[3] != 0) {
        Num = bookingHistory.numTickets[3];
        Price = movies[bookingHistory.movieCode].prices[3];
        Sub = Num * Price;
        Total += Sub;
        cout << "Elderly ticket" << "\t\t" << Num << "\t\t\t\t\t" << Price << "\t\t\t" << Sub << endl;
    }
    cout << endl << "Total Amount For Tickets: " << Total << endl;
    
}

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies, char availableDates[][12], int numDates) {
    
    for (int i=0; i<numMovies; i++) {
        cout << i << ".\tMovie: \t\t\t" << movieNames[i] << endl;
        cout << "\tDate: \t\t\t";
        for (int j=0; j<numDates; j++) {
            if (movies[i].dates[j]) {
                cout << j << ". " << availableDates[j] << "\t";
            }
        }
        cout << endl;
        cout << "\tSession Time: \t";
        for (int k=0; k<17; k++) {
            if (movies[i].sessionTimes[k]) {
                cout << k << ". " << hours[k] << "\t\t";
            }
        }
        cout << endl << endl;;
    }
    
}

void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[], char movieNames[][60], char availableDates[][12], char email[]) {
    
    bool printed = false;
    for (int i=0; i<numBookings; i++) {
        if (strcmp(bookingHistories[i].email, email) == 0) {
            if (!printed) {
                printed = true;
                cout << "Booking History: " << endl << "----------------------------------------------" << endl;
            }
            cout << "Movie: " << movieNames[bookingHistories[i].movieCode] << endl;
            cout << "Date: " << availableDates[bookingHistories[i].dateCode] << endl;
            cout << "Show Time: " << hours[bookingHistories[i].sessionTimeCode] << endl;
            cout << "Seats: ";
            int totalTicket=0;
            for (int j=0; j<4; j++) {
                totalTicket += bookingHistories[i].numTickets[j];
            }
            for (int j=0; j<totalTicket; j++) {
                cout << bookingHistories[i].seletedSeats[j] << " ";
            }
            cout << endl << endl;
            display(movies, bookingHistories[i]);
            cout << "----------------------------------------------" << endl;
        }
    }
    if (!printed) {
        cout << "No bookings!" << endl;
    }
    
}

int inputAnInteger(int begin, int end) {
    int iInput;
    cin >> iInput;
    return (iInput>=begin && iInput <= end) ? iInput : -1;
}

bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int &recordNumber) {
    if (recordNumber == -1) {
        return true;
    }
    if(strcmp(password, memberDetails[recordNumber].password) == 0) {
        return false;
    }
    return true;
}

void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber) {
    
    //Print Account Infomations
    int choice = -1;
    cout << "1. Name: ";
    for (int j=0; j<strlen(memberDetails[recordNumber].name); j++) {
        cout << memberDetails[recordNumber].name[j];
    }
    cout << endl << "2. Email Address: ";
    for (int j=0; j<strlen(memberDetails[recordNumber].email); j++) {
        cout << memberDetails[recordNumber].email[j];
    }
    cout << endl << "3. Phone Number: ";
    for (int j=0; j<strlen(memberDetails[recordNumber].phone); j++) {
        cout << memberDetails[recordNumber].phone[j];
    }
    cout << endl << "4. ID Number: ";
    for (int j=0; j<strlen(memberDetails[recordNumber].IDNumber); j++) {
        cout << memberDetails[recordNumber].IDNumber[j];
    }
    cout << endl << "5. Password: ";
    for (int j=0; j<strlen(memberDetails[recordNumber].password); j++) {
        cout << memberDetails[recordNumber].password[j];
    }
    
    //Prompt for Data Edit
    cout << endl << endl << "Which one do you want to modify (0 – not modify)? ";
    while (choice == -1) {
        choice = inputAnInteger(0, 5);
        if (choice == -1) {
            cout << "Input Error! Please try again: ";
        }
    }
    
    //Menu
    switch (choice) {
        case 0:
            return;
        case 1:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].name;
            cout << endl << "Successful!" << endl;
            return;
        case 2:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].email;
            cout << endl << "Successful!" << endl;
            return;
        case 3:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].phone;
            cout << endl << "Successful!" << endl;
            return;
        case 4:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].IDNumber;
            cout << endl << "Successful!" << endl;
            return;
        case 5:
            cout << "Enter correct data: ";
            cin >> memberDetails[recordNumber].password;
            cout << endl << "Successful!" << endl;
            return;
    }
    
}

bool existingID(char newIDNumber[], MemberRecord memberDetails[], int &numMembers) {
    for (int i=0; i<numMembers; i++) {
        if (strcmp(newIDNumber, memberDetails[i].IDNumber) == 0) {
            return true;
        }
    }
    return false;
}

bool existingEmail(char newEmail[], MemberRecord memberDetails[], int &numMembers) {
    for (int i=0; i<numMembers; i++) {
        if (strcmp(newEmail, memberDetails[i].email) == 0) {
            return true;
        }
    }
    return false;
}

void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[]) {
    
    int movieCode = bookingHistories[numBookings].movieCode;
    int dateCode = bookingHistories[numBookings].dateCode;
    int sessionTimeCode = bookingHistories[numBookings].sessionTimeCode;
    int totalTicket = 0;
    for (int i=0; i<4; i++) {
        totalTicket += bookingHistories[numBookings].numTickets[i];
    }
    cout << endl << "  A B C D E F G H I J K L" << endl;
    for (int i=0; i<8; i++) {
        cout << i << " ";
        for (int j=0; j<12; j++) {
            cout << movies[movieCode].occupiedSeats[dateCode][sessionTimeCode][i][j] << " ";
        }
        cout << endl;
    }
    char tmpSeat[4];
    cout << endl << "Select " << totalTicket << " seats (e.g. 0A):" << endl;
    bool validSeat;
    for (int i=0; i<totalTicket; i++) {
        validSeat = false;
        do {
            cout << "? ";
            cin >> tmpSeat;
            tmpSeat[1] = toupper(tmpSeat[1]);
            if (!movies[movieCode].occupiedSeats[dateCode][sessionTimeCode][int(tmpSeat[0])-'0'][int(tmpSeat[1])-'A']) {
                validSeat = true;
                strcpy(bookingHistories[numBookings].seletedSeats[i], tmpSeat);
                movies[movieCode].occupiedSeats[dateCode][sessionTimeCode][int(tmpSeat[0])-'0'][int(tmpSeat[1])-'A'] = true;
            }
            else {
                cout << "This seat bas been occupied. Please select another seat." << endl << endl;
            }
        } while (!validSeat);
    }
    
}
