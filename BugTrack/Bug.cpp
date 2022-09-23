//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: Bug.cpp
//FileType: C++ Souce File
//Copy Rights : Quest Global
//Description : Bug Class Source File
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#define FILE_NAME "bug.dat"
#define TEMP_FILE_NAME "bugTemp.dat"
#include<iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <ctime>
#include "User.h"
#include "Bug.h"

using namespace std;

// Default Constructor
Bug::Bug()
{
	this->bugId= NULL;
	this->customerId=NULL;
	this->engineerId=NULL;
}

// Constructor to Create New Bug
Bug::Bug(long int bugId, char* category, char* description, char* evidence, long int customerId, char* priority)
{
	Bug temp;
	temp.bugId = bugId;
	strcpy(temp.category, category);
	strcpy(temp.description, description);
	strcpy(temp.evidence, evidence);
	temp.customerId = customerId;
	strcpy(temp.priority, priority);
	strcpy(temp.status ,"Created");
	strcpy(temp.response, "");
	time_t now = time(0);
	strcpy(temp.createdAt, ctime(&now));
	ofstream output;

	output.open(FILE_NAME, ios::out | ios::app | ios::binary);
	if (output.is_open()) {
		output.write((char*)&temp, sizeof(Bug));
	}
	output.close();
}

// Method to Delete a Bug
long int Bug::DeleteBug(long int customerId,long int id)
{
	bool flag = false;
	ifstream in;
	ofstream out;
	in.open(FILE_NAME, ios::in | ios::binary);
	out.open(TEMP_FILE_NAME, ios::out | ios::trunc | ios::binary);
	if (in.is_open() && out.is_open()) {
		Bug temp;
		int I = 0;
		while (in.read((char*)&temp, sizeof(Bug))) {
			I++;
			if (temp.bugId == id) {
				if ((string)temp.status != "Created" || (temp.customerId != customerId)) {
					cout << "Unable to delete this bug." << endl;
					flag = true;
					break;
				}
			}
			else{
				out.write((char*)&temp, sizeof(Bug));
			}
		}
	}
	else if (!in.is_open()) {
		cout << "We cannot open the file " << FILE_NAME << endl;
	}
	else if (!out.is_open()) {
		cout << "We cannot open the file " << TEMP_FILE_NAME << endl;
	}
	out.close();
	in.close();
	if (!flag) {
		cout << "Bug: " << id << " Deleted!" << endl;
		remove(FILE_NAME);
		rename(TEMP_FILE_NAME, FILE_NAME);
	}
	
	return bugId;
}

// Method to Find Total No.of Bugs
int Bug::CountOfBugs() {
	int count = 0;
	ifstream input;
	input.open(FILE_NAME, ios::in | ios::binary);
	if (input.is_open()) {
		input.seekg(0, ios::end);
		count = input.tellg() / sizeof(Bug);
	}
	input.close();
	return count;
}

// Method to Find No.of Bugs Associated with a User
int Bug::CountOfActiveBugsOfUser(long int userId) {
	int count = 0;
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		Bug temp;
		while (inout.read((char*)&temp, sizeof(Bug))) {
			if ((temp.customerId == userId || temp.engineerId == userId)&&((string)temp.status != "Closed")) {
				count++;
			}
		}
	}
	inout.close();
	return count;
}

// Method to Find Details about All the Bugs
Bug* Bug::GetBugDetails()
{
	int count = CountOfBugs();
	Bug* bugDetailsArray = new Bug[count]{};
	int j = 0;
	ifstream input;
	input.open(FILE_NAME, ios::in | ios::binary);
	if (input.is_open()) {
		Bug temp;
		while (input.read((char*)&temp, sizeof(Bug))) {
			bugDetailsArray[j] = temp;
			j++;
		}
	}
	return bugDetailsArray;
}

// Method to Find More Details about a Particular Bug
bool Bug::GetMoreDetails(long int bugId) {
	bool returnFlag = false;
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		Bug temp;
		int I = 0;
		while (inout.read((char*)&temp, sizeof(Bug))) {
			I++;
			if (temp.bugId == bugId) {
				cout <<"------------------------------------------" << endl;
				cout << "ID: " << temp.bugId << endl;
				cout << "Category:  " << temp.category << endl;
				cout << "Description:  " << temp.description << endl;
				cout << "Evidence: " << temp.evidence << endl;
				cout << "Created Date: " << temp.createdAt << endl;
				cout << "Assigned to: " << temp.engineerId << endl;
				cout << "Status: " << temp.status << endl;
				cout << "Response: " << temp.response << endl;
				cout << "------------------------------------------" << endl;
				returnFlag = true;
				break;
			}
		}
	}
	inout.close();
	return returnFlag;
}

// Method to Assign Engineer to a Bug
bool Bug::SetEngineer(long int bugId, long int engineerId)
{
	bool returnFlag = false;
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		Bug temp;
		int I = 0;
		while (inout.read((char*)&temp, sizeof(Bug))) {
			I++;
			if ((temp.bugId == bugId) && ((string)temp.status=="Created"||(string)temp.status=="Assigned") ){
				if (User::IsValidUser(engineerId) == "engineer") {
					Bug emp = temp;

					emp.engineerId = engineerId;
					strcpy(emp.status, "Assigned");

					int offset = (I - 1) * sizeof(Bug);
					inout.seekg(offset, ios::beg);
					inout.write((char*)&emp, sizeof(Bug));
					returnFlag = true;
					break;
				}
			}
		}
	}
	inout.close();
	return returnFlag;
}

// Method to Update Bug Status
bool Bug::UpdateStatus(long int id, long int bugId)
{
	char status[256];
	char response[256];
	fstream inout;

	int selection;
	do {
		cout << "Select Status:-" << endl;
		cout << "1: In Progress\t2: Closed" << endl;
		cin >> selection;
		switch (selection) {
		case 1:
			strcpy(status, "In Progress");
			break;
		case 2:
			strcpy(status, "Closed");
			break;
		default:
			cout << "Invalid Option Selected!" << endl;
		}
		if (selection == 1 || selection == 2) {
			break;
		}
	} while (true);
	
	cout << "Enter Response: ";
	cin.ignore();
	cin.getline(response, 256);
	bool returnFlag = false;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		Bug temp;
		int I = 0;
		while (inout.read((char*)&temp, sizeof(Bug))) {
			I++;
			if (temp.bugId == bugId && temp.engineerId == id) {
				Bug emp = temp;

				strcpy(emp.status, status);
				strcpy(emp.response, response);

				int offset = (I - 1) * sizeof(Bug);
				inout.seekg(offset, ios::beg);
				inout.write((char*)&emp, sizeof(Bug));
				returnFlag = true;
				break;
			}
		}
	}
	inout.close();
	return returnFlag;
}

// Method to Find ID of Last Reported Bug
long int Bug::LastBugId() {
	int count = this->CountOfBugs();
	long int lastId= 0;
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		Bug temp;
		int i = 0;
		while (inout.read((char*)&temp, sizeof(Bug))) {
			i++;
			if (i == count) {
				lastId = temp.bugId;
			}
		}
	}
	inout.close();
	return lastId;
}