//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: User.cpp
//FileType: C++ Souce File
//Copy Rights : Quest Global
//Description : User Class Source File
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#define FILE_NAME "user.dat"
#include <iostream>
#include <fstream>
#include<cstring>
#include<iomanip>
#include <windows.h>
#include "User.h"
#include "Utility.h"

using namespace std;

// Default Constructor
User::User() {
	this->userId=NULL;
	this->isLogged = false;
	this->isEnabled = true;
}

// Constructor to Create New User
User::User(long int userId, char* userName, char* role, char* password) {
	User temp;
	temp.userId = userId;
	strcpy(temp.userName, userName);
	strcpy(temp.role, role);
	strcpy(temp.password, password);

	ofstream output;

	output.open(FILE_NAME, ios::out | ios::app | ios::binary);
	if (output.is_open()) {
		output.write((char*)&temp, sizeof(User));
	}
	cout << "User Created Successfully." << endl;
	output.close();

}

// Method to Login
bool User::Login() {
	char usrName[256], pswd[256];
	bool returnFlag = false;
	cout << right << setw(100) << "------------------------------------------" << endl << endl;
	cout << right << setw(85) << "BUG TRACK" << endl<<endl;
	cout << right << setw(100) << "Software Bug Reporting and Tracking System" << endl;
	cout << right << setw(100) << "------------------------------------------" << endl<<endl;
	cout << right << setw(85) << "LOGIN" << endl << endl;
	cout << right << setw(85) << "Enter User Name: ";
	cin.ignore();
	cin.getline(usrName, 256);
	cout << right << setw(84) << "Enter Password: ";
	cin.getline(pswd, 256);
	ifstream input;
	input.open(FILE_NAME, ios::in | ios::binary);
	if (input.is_open()) {
		User temp;
		while (input.read((char*)&temp, sizeof(User))) {
			if (strstr(temp.userName, usrName) != nullptr) {
				if (strstr(temp.password, pswd) != nullptr) {
					if (temp.isEnabled) {
						this->isLogged = true;
						this->userId = temp.userId;
						strcpy(this->userName, temp.userName);
						strcpy(this->role, temp.role);
						this->isEnabled = temp.isEnabled;
						break;
					}
				}
			}

		}
	}
	input.close();
	
	if (this->isLogged) {
		returnFlag = true;
	}
	return returnFlag;
}

// Method to Load User Specific Dashboard
void User::LoadUserDashboard() {
	system("cls");
	cout << right << setw(480) << "Current User : " << this->userName << endl;
	Utility::ShowStatistics(*this);
	cout << endl;
	if ((string)this->role == "admin") {
		int option;
		do
		{
			cout << "Menu" << endl;
			cout << "1 : Active Bugs" << endl;
			cout << "2 : Bug History" << endl;
			cout << "3 : Manage Users" << endl;
			cout << "4 : Logout" << endl;

			cout << "\nPlease Select an Option:  ";
			cin >> option;
			switch (option)
			{
			case 1:
				Utility::ActiveBugsData(*this);
				break;
			case 2:
				Utility::BugHistoryData(*this);
				break;
			case 3:
				Utility::ManageUsers(*this, "all");
				break;
			case 4:
				this->Logout();
				break;
			default:
				cout << "Invalid Option!\n";
				break;
			}
		} while (true);
	}
	else if ((string)this->role == "customer") {
		int option;
		do
		{
			cout << "Menu" << endl;
			cout << "1 : Report Bug" << endl;
			cout << "2 : Active Bugs" << endl;
			cout << "3 : Bug History" << endl;
			cout << "4 : Logout" << endl;

			cout << "\nPlease Select an Option:  ";
			cin >> option;

			switch (option)
			{
			case 1:
				Utility::ReportBug(*this);
				break;
			case 2:
				Utility::ActiveBugsData(*this);
				break;
			case 3:
				Utility::BugHistoryData(*this);
				break;
			case 4:
				this->Logout();
				break;
			default:
				cout << "Invalid Option!\n";
				break;
			}
		} while (true);
	}
	else if ((string)this->role == "engineer") {
		int option;
		do
		{
			cout << "Menu" << endl;
			cout << "1 : Active Bugs" << endl;
			cout << "2 : Bug History" << endl;
			cout << "3 : Logout" << endl;

			cout << "\nPlease Select an Option:  ";
			cin >> option;

			switch (option)
			{
			case 1:
				Utility::ActiveBugsData(*this);
				break;
			case 2:
				Utility::BugHistoryData(*this);
				break;
			case 3:
				this->Logout();
				break;
			default:
				cout << "Invalid Option!\n";
				break;
			}
		} while (true);
	}
}

// Method to Find Total No.of Users
int User::CountOfUsers() {
	int count = 0;
	ifstream input;
	input.open(FILE_NAME, ios::in | ios::binary);
	if (input.is_open()) {
		input.seekg(0, ios::end);
		count = input.tellg() / sizeof(User);
	}
	input.close();
	return count;
}

// Method to Find Details of All Users
User* User::GetUserDetails()
{
	int count = CountOfUsers();
	User* userDetailsArray = new User[count];
	int i = 0;
	ifstream input;
	input.open(FILE_NAME, ios::in | ios::binary);
	if (input.is_open()) {
		User temp;
		while (input.read((char*)&temp, sizeof(User))) {
			userDetailsArray[i] = temp;
			i++;
		}
	}
	return userDetailsArray;
}

// Method to Update User Password
bool User::UpdatePassword(long int id)
{
	char pswd[256];
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		User temp;
		int I = 0;
		while (inout.read((char*)&temp, sizeof(User))) {
			I++;
			if (temp.userId == id) {
				User emp = temp;
				cout << "User ID: " <<emp.userId<< endl;
				cout << "Name: " << emp.userName << endl;
				cout << "Role: " << emp.role << endl;
				cout << "Password: ";
				strcpy(emp.password, Utility::GenerateRandomPassword().c_str());
				cout << emp.password << endl;
				int offset = (I - 1) * sizeof(User);
				inout.seekg(offset, ios::beg);
				inout.write((char*)&emp, sizeof(User));
				break;
			}
		}
	}
	inout.close();
	return true;
}

// Method to Enable/Disable User Status
bool User::ChangeUserStatus(long int id)
{
	bool returnFlag = false;
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		User temp;
		int I = 0;
		while (inout.read((char*)&temp, sizeof(User))) {
			I++;
			if (temp.userId == id && (string)temp.role != "admin") {
				User emp = temp;

				if (emp.isEnabled) {
					emp.isEnabled = !(emp.isEnabled);
					cout << "User: "<<id<<" Disabled." << endl;
				}
				else {
					emp.isEnabled = !(emp.isEnabled);
					cout << "User: " << id << " Enabled." << endl;
				}

				int offset = (I - 1) * sizeof(User);
				inout.seekg(offset, ios::beg);
				inout.write((char*)&emp, sizeof(User));
				returnFlag = true;
				break;
			}
		}
	}
	inout.close();
	return returnFlag;
}

// Method to Check Login Status of User
bool User::IsLogged()
{
	return this->isLogged;
}

// Method to Logout
void User::Logout(){
	Utility::StartApp();
}

// Method to Check Validity of User ID
string User::IsValidUser(long int id) {
	string userRole = "";
	fstream inout;
	inout.open(FILE_NAME, ios::in | ios::out | ios::binary);
	if (inout.is_open()) {
		User temp;
		while (inout.read((char*)&temp, sizeof(User))) {
			if (temp.userId == id) {
				userRole = (string)temp.role;
				break;
			}
		}
	}
	inout.close();
	return userRole;
}

