//
//  main.cpp
//  Hw10
//  Simplified Vieshow Cinemas Member System
//
//  Created by Tomy Hsieh on 2017/11/27.
//  Copyright © 2017年 Tomy Hsieh. All rights reserved.
//

#include <iostream>
#include <fstream>
using namespace std;

struct MemberRecord {
    char email[40];
    char password[24];
    char IDNumber[12];
    char name[12];
    char phone[12];
};

void loadFromMemberFile(ifstream &inMemberFile, MemberRecord memberDetails[], int &numMembers);                         //Load File Data to memberDetails
void PrintLoadedData(MemberRecord memberDetails[], int &numMembers);                                                    //Tester
int inputAnInteger(int begin, int end);                                                                                 //Return a Valid Input
void login(MemberRecord memberDetails[], int numMembers);                                                               //Login Menu
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int &recordNumber);           //Cehck if Email or Password is Wrong
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber);                                      //Account Information Menu
void newMember(MemberRecord memberDetails[], int &numMembers);                                                          //Add New Member Info to memberDetails
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int &numMembers);                                     //Cehck if ID is Already Exists
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int &numMembers);                                     //Cehck if Email is Already Exists
void saveToMemberFile(ofstream &outMemberFile, MemberRecord memberDetails[], int numMembers);                           //Save memberDetails back to File

int main() {
    
    //System Initialization
    MemberRecord memberDetails[100] = {"", "", "", "", ""};
    int numMembers = 0;
    ifstream inMemberFile;
    ofstream outMemberFile;
    loadFromMemberFile(inMemberFile, memberDetails, numMembers);
    
    //Start Menu
    cout << "Welcome to Vieshow Cinemas member system" << endl << endl;
    while(true) {
        
        cout << "Enter your choice:" << endl;
        cout << "1. Sign In" << endl;
        cout << "2. New Member" << endl;
        cout << "3. Sign Out" << endl;
        cout << "? ";
        
        int choice = inputAnInteger(1, 3);
        cout << endl;
        
        switch (choice) {
            case 1:
                login(memberDetails, numMembers);
                break;
            case 2:
                newMember(memberDetails, numMembers);
                break;
            case 3:
                saveToMemberFile(outMemberFile, memberDetails, numMembers);
                cout << "Thank you..." << endl << endl;
                return 0;
            default:
                cout << "Input Error!" << endl << endl;
                break;
        }
    }
}

void loadFromMemberFile(ifstream &inMemberFile, MemberRecord memberDetails[], int &numMembers) {
    
    inMemberFile.open("MemberInfo.dat", ios::in | ios::binary);
    while (inMemberFile.peek() != EOF) {
        inMemberFile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(MemberRecord));
        numMembers++;
    }
//    PrintLoadedData(memberDetails, numMembers);
    inMemberFile.close();
    
}

void PrintLoadedData(MemberRecord memberDetails[], int &numMembers) {
    
    for (int i=0; i<numMembers; i++) {
        cout << "Data #" << i+1 << ": " << endl;
        
        for (int j=0; j<40; j++) {
            cout << memberDetails[i].email[j];
        }
        cout << endl;
        
        for (int j=0; j<24; j++) {
            cout << memberDetails[i].password[j];
        }
        cout << endl;
        
        for (int j=0; j<12; j++) {
            cout << memberDetails[i].IDNumber[j];
        }
        cout << endl;
        
        for (int j=0; j<12; j++) {
            cout << memberDetails[i].name[j];
        }
        cout << endl;
        
        for (int j=0; j<12; j++) {
            cout << memberDetails[i].phone[j];
        }
        cout << endl << endl;
        
    }
    
}

int inputAnInteger(int begin, int end) {
    int iInput;
    cin >> iInput;
    return (iInput>=begin && iInput <= end) ? iInput : -1;
}

void login(MemberRecord memberDetails[], int numMembers) {
    
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
        cout << "3. End" << endl;
        cout << "? ";
        int choice = inputAnInteger(1, 3);
        cout << endl;
        
        switch (choice) {
            case 1:
                accountInfor(memberDetails, numMembers, recordNumber);
                break;
            case 2:
                cout << "This Function has not been implemented yet" << endl;
                break;
            case 3:
                return;
            default:
                cout << "Input Error!" << endl << endl;
                break;
        }
    }
    
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

void newMember(MemberRecord memberDetails[], int &numMembers) {
    
    //Create TempMember
    MemberRecord tmpMember;
    cout << "Enter your ID number: ";
    cin >> tmpMember.IDNumber;
    if (existingID(tmpMember.IDNumber, memberDetails, numMembers)) {
        cout << "An account already exists with the ID number!" << endl;
        return;
    }
    cout << "Enter your name: ";
    cin >> tmpMember.name;
    cout << "Enter an email address: ";
    cin >> tmpMember.email;
    if (existingEmail(tmpMember.email, memberDetails, numMembers)) {
        cout << "An account already exists with the Email!" << endl;
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

void saveToMemberFile(ofstream &outMemberFile, MemberRecord memberDetails[], int numMembers) {
    
    //Initialize ofstream
    outMemberFile.open("MemberInfo.dat", ios::out | ios::binary);
    if (!outMemberFile) {
        cerr << "File could not be opened" << endl;
        exit(1);
    }
    
    //Save Data
    for (int i=0; i<numMembers; i++) {
        outMemberFile.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(MemberRecord));
    }
    
    //Close ofstream
    outMemberFile.close();
    
}

