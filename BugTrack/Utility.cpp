//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: Utility.cpp
//FileType: C++ Souce File
//Copy Rights : Quest Global
//Description : Utility Class Source File
////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <string>
#include <iomanip>
#include <ctime>
#include <cstring>
#include <fstream>
#include "Utility.h"
#include "User.h"
#include "Bug.h"

using namespace std;

// Function to start application
void Utility::StartApp() {
	system("cls");
	User userObj;

	if (!userObj.IsLogged()) {
		bool loginStatus;
		do {
			cout << endl;
			loginStatus = userObj.Login();
			if (!loginStatus) {
				cout << endl << right << setw(90) << "Invalid Login Credentials!" << endl;
				Sleep(1000);
				system("cls");
			}
		} while (!loginStatus);
		cout << endl << right << setw(90) << "User Login Successful!" << endl;
		Sleep(1000);
		userObj.LoadUserDashboard();
	}
	else {
		cout << right << setw(85) << "Warning: Previous User Session is Active." << endl;
	}
}

// Function to Report New Bug
void Utility::ReportBug(User userObj) {
	system("cls");
	long int bugId;
	Bug bugObj;
	char category[256];
	char description[256];
	char details[256];
	char evidence[256];
	char priority[256];
	long int customerId = userObj.userId;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Report New Bug" << endl;
	bugId = bugObj.LastBugId() + 1;
	cout << "ID : " << bugId << endl;
	cin.ignore();
	cout << "Category :";
	cin.getline(category, 256);
	cout << "Details :";
	cin.getline(details, 256);
	cout << "Evidence :";
	cin.getline(evidence, 256);
	int selection;
	do {
		cout << "Select Priority:-"<<endl;
		cout << "1: Low\t2: Medium\t3: High" << endl;
		cin >> selection;
		switch (selection) {
		case 1:
			strcpy(priority, "Low");
			break;
		case 2:
			strcpy(priority, "Medium");
			break;
		case 3:
			strcpy(priority, "High");
			break;
		default:
			cout << "Invalid Option Selected!" << endl;
		}
		if (selection == 1 || selection == 2 || selection == 3) {
			break;
		}
	} while (true);

	Bug bug = Bug(bugId, category, details, evidence, customerId, priority);
	cout << "Bug Reported Successfully!" << endl;
}

// Function to Assign Engineer to Bug
void Utility::ManageResponsibility(User userObj, long int bugId) {
	system("cls");
	long int engineerId;
	Bug bugObj;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Manage Bug Responsibilty" << endl;
	Utility::ShowUserTable(userObj, "engineer");
	cout << "\n\n" << endl;
	cout << "Bug ID: " <<bugId<< endl;
	cout << "Enter Engineer ID: ";
	cin >> engineerId;

	if (bugObj.SetEngineer(bugId,engineerId)) {
		cout << "Bug: " << bugId << " assigned to Engineer: " << engineerId << "." << endl;
	}
	else {
		cout << "Unable to Assign Responsibility!" << endl;
	}

	int option;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "1 : Back" << endl;
		cout << "2 : Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			BugMore(userObj, bugId);
			break;

		case 2:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);
}

// Function to Update Bug Status
void Utility::UpdateBug(User userObj, long int bugId) {
	system("cls");
	Bug bugObj;
	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Update Bug Status" << endl;
	if (bugObj.UpdateStatus(userObj.userId, bugId)) {
		cout << "Bug Status Updated Successfully!" << endl;
	}
	else {
		cout << "Unable to Update this Bug." << endl;
	}
	
	int option;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "1 : Back" << endl;
		cout << "2 : Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			userObj.LoadUserDashboard();
			break;

		case 2:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);
}

// Function to Display More Details About Bug
void Utility::BugMore(User userObj, long int bugId) {
	system("cls");
	Bug bugObj;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "More Details" << endl;
	cout << setw(200) << " " << setfill(' ') << endl;
	if (!bugObj.GetMoreDetails(bugId)) {
		cout << "Unable Load Bug Details!" << endl;
	}
	if ((string)userObj.role == "admin") {
		int option;
		do
		{
			cout << "\n\n\n Menu" << endl;
			cout << "\n1 : Manage Responsibility" << endl;
			cout << "2 : Back" << endl;
			cout << "3 : Logout" << endl;

			cout << "\nPlease Select an Option:  ";
			cin >> option;

			switch (option)
			{
			case 1:
				ManageResponsibility(userObj, bugId);
				break;
			case 2:
				ActiveBugsData(userObj);
				break;

			case 3:
				userObj.Logout();
				break;

			default:
				cout << "Invalid Option!\n";
				break;
			}
		} while (true);
	}
	else if ((string)userObj.role == "engineer") {
		int option;
		do
		{
			cout << "\n\n\n Menu" << endl;
			cout << "\n1 : Update Bug Status" << endl;
			cout << "2 : Back" << endl;
			cout << "3 : Logout" << endl;

			cout << "\nPlease Select an Option:  ";
			cin >> option;

			switch (option)
			{
			case 1:
				Utility::UpdateBug(userObj, bugId);
				break;
			case 2:
				ActiveBugsData(userObj);
				break;

			case 3:
				userObj.Logout();
				break;

			default:
				cout << "Invalid Option!\n";
				break;
			}
		} while (true);

	}
	else if ((string)userObj.role == "customer") {
		int option;
		do
		{
			cout << "\n\n\n Menu" << endl;
			cout << "\n1 : Delete Bug" << endl;
			cout << "2 : Back" << endl;
			cout << "3 : Logout" << endl;

			cout << "\nPlease Select an Option:  ";
			cin >> option;

			switch (option)
			{
			case 1:
				bugObj.DeleteBug(userObj.userId,bugId);
				break;
			case 2:
				ActiveBugsData(userObj);
				break;

			case 3:
				userObj.Logout();
				break;

			default:
				cout << "Invalid Option!\n";
				break;
			}
		} while (true);

	}
	
}

// Function to Display Table of Active Bugs
void Utility::ActiveBugsData(User userObj) {
	system("cls");
	Bug bugObj;
	int count = bugObj.CountOfBugs();
	Bug* activeBugs = new Bug[count];
	Bug* bugs = bugObj.GetBugDetails();
	int countActives = 0;
	
	if ((string)userObj.role == "admin") {
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((string)bugs[i].status != "Closed") {
				activeBugs[j] = bugs[i];
				j++;
				countActives++;
			}
		}
		
	}
	else if ((string)userObj.role == "customer") {
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((bugs[i].customerId == userObj.userId) && ((string)bugs[i].status != "Closed")) {
				activeBugs[j] = bugs[i];
				countActives++;
				j++;
			}
		}
		
	}
	else if ((string)userObj.role == "engineer") {
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((bugs[i].engineerId == userObj.userId) && ((string)bugs[i].status != "Closed")) {
				activeBugs[j] = bugs[i];
				j++;
				countActives++;
			}
		}
	}

	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Active Bugs" << endl;
	if (countActives == 0) {
		cout << left << setw(80) << "No Data Availabale.";
	}
	else {
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		cout << left << setw(20) << "ID";
		cout << left << setw(20) << "Category";
		cout << left << setw(20) << "Priority";
		cout << left << setw(20) << "Reported By";
		cout << left << setw(20) << "Assigned To";
		cout << left << setw(20) << "Status";
		cout << endl;
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;

		for (int i = 0; i < countActives; i++) {
			cout << left << setw(20) << activeBugs[i].bugId;
			cout << left << setw(20) << activeBugs[i].category;
			cout << left << setw(20) << activeBugs[i].priority;
			cout << left << setw(20) << activeBugs[i].customerId;
			cout << left << setw(20) << activeBugs[i].engineerId;
			cout << left << setw(20) << activeBugs[i].status;
			cout << endl;
		}
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		cout << endl;
	}

	delete[] activeBugs;
	int option;
	long int bugId;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "\n1 : More Details" << endl;
		cout << "2 : Back" << endl;
		cout << "3 : Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			cout << "Enter Bug ID: ";
			cin >> bugId;
			BugMore(userObj, bugId);
			break;
		case 2:
			userObj.LoadUserDashboard();
			break;
		case 3:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);
}

// Function to Display Table of Bug History
void Utility::BugHistoryData(User userObj) {
	system("cls");
	Bug bugObj;
	int count = bugObj.CountOfBugs();
	Bug* bugHistory = new Bug[count];
	Bug* bugs = bugObj.GetBugDetails();
	int countHistory = 0;

	if ((string)userObj.role == "admin") {
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((string)bugs[i].status == "Closed") {
				bugHistory[j] = bugs[i];
				i++;
				countHistory++;
			}
		}

	}
	else if ((string)userObj.role == "customer") {
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((bugs[i].customerId == userObj.userId) && ((string)bugs[i].status == "Closed")) {
				bugHistory[j] = bugs[i];
				i++;
				countHistory++;
			}
		}
	}
	else if ((string)userObj.role == "engineer") {
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((bugs[i].engineerId == userObj.userId) && ((string)bugs[i].status == "Closed")) {
				bugHistory[j] = bugs[i];
				i++;
				countHistory++;
			}
		}
	}

	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Bug History" << endl;
	if (countHistory == 0) {
		cout << "No Data Available."<<endl;
	}
	else {
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		cout << left << setw(20) << "ID";
		cout << left << setw(20) << "Category";
		cout << left << setw(20) << "Priority";
		cout << left << setw(20) << "Reported By";
		cout << left << setw(20) << "Assigned To";
		cout << endl;
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;

		for (int i = 0; i < countHistory; i++) {
			cout << left << setw(20) << bugHistory[i].bugId;
			cout << left << setw(20) << bugHistory[i].category;
			cout << left << setw(20) << bugHistory[i].priority;
			cout << left << setw(20) << bugHistory[i].customerId;
			cout << left << setw(20) << bugHistory[i].engineerId;
			cout << endl;
		}
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		cout << endl;
	}


	delete[] bugHistory;
	long int bugId;
	int option;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "\n1: More Details" << endl;
		cout << "2 : Back" << endl;
		cout << "3 : Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;


		switch (option)
		{
		case 1:
			cout << "Enter Bug ID: ";
			cin >> bugId;
			BugMore(userObj, bugId);
			break;
		case 2:
			userObj.LoadUserDashboard();
			break;
		case 3:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);
}

// Function to Generate Random Password
string Utility::GenerateRandomPassword() {
	string password;
	const char alphanum[] = "0123456789!@#$%^&*abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	int string_length = sizeof(alphanum) - 1;
	srand(time(0));
	for (int i = 0; i < 8; i++)
		password= password+(alphanum[rand() % string_length]);

	return password;
}

// Function to Create New User
void Utility::CreateUser(User userObj) {
	system("cls");
	long int userId;
	char name[256];
	char role[256];
	char password[256];
	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Create New User Account" << endl;
	cout << setw(200) << " " << setfill(' ') << endl;
	cout << "User ID: ";
	cin >> userId;
	cin.ignore();
	cout << "Name: ";
	cin.getline(name, 256);
	int selection;
	do {
		cout << "Select Role:-" << endl;
		cout << "1: Customer\t2: Engineer" << endl;
		cin >> selection;
		switch (selection) {
		case 1:
			strcpy(role, "customer");
			break;
		case 2:
			strcpy(role, "engineer");
			break;
		default:
			cout << "Invalid Option Selected!" << endl;
		}
		if (selection == 1 || selection == 2) {
			break;
		}
	} while (true);
	cout << "Password: ";
	strcpy(password, GenerateRandomPassword().c_str());
	cout << password << endl;
	User newUser = User(userId, name, role,password);

	int option;
	do
	{
		cout << "\nMenu" << endl;
		cout << "1 : Back" << endl;
		cout << "2 : Logout" << endl;

		cout << "Please Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			ManageUsers(userObj,"all");
			break;

		case 2:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);

}

// Function to Update User Password
void Utility::UpdateUser(User userObj) {
	system("cls");
	long int userId;
	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Update User Password" << endl;
	cout << "Enter User ID: ";
	cin >> userId;
	cout << setw(200) << " " << setfill(' ') << endl << endl;
	if (userObj.UpdatePassword(userId)) {
		cout << "User Password Updated successfully!" << endl;
	}
	else {
		cout << "Unable to Update User!" << endl;
	}
	int option;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "1 : Back" << endl;
		cout << "2 : Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			ManageUsers(userObj,"all");
			break;

		case 2:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);

}

// Function to Enable/Disable User
void Utility::UpdateUserStatus(User userObj) {
	system("cls");
	long int userId;
	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	cout << "Enable/Disable User" << endl;
	cout << "Enter User ID: ";
	cin >> userId;
	if (!userObj.ChangeUserStatus(userId)) {
		cout << "Unable to Update this User." << endl;
	}

	int option;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "1 : Back" << endl;
		cout << "2 : Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			ManageUsers(userObj,"all");
			break;

		case 2:
			userObj.Logout();
			break;

		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);
}

// Function to Display User Table
void Utility::ShowUserTable(User userObj, string filter) {
	User* users = userObj.GetUserDetails();
	int count = userObj.CountOfUsers();
	User* userList = new User[count];
	int countUsers = 0;

	if (filter == "all") {
		cout << "All Users" << endl;
		countUsers = count;
		userList = users;
	}
	else if (filter == "engineer") {
		cout << "All Engineers" << endl;
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((string)users[i].role == "engineer") {
				userList[j] = users[i];
				j++;
				countUsers++;
			}
		}
	}
	else if (filter == "customer") {
		cout << "All Customers" << endl;
		int j = 0;
		for (int i = 0;i < count;i++) {
			if ((string)users[i].role == "customer") {
				userList[j] = users[i];
				j++;
				countUsers++;
			}
		}
	}

	if (countUsers == 0) {
		cout << "No Data Available." << endl;
	}
	else {
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		cout << left << setw(20) << "ID";
		cout << left << setw(20) << "Name";
		cout << left << setw(20) << "Role";
		cout << left << setw(20) << "Status";
		cout << left << setw(20) << "Associated Bugs";
		cout << endl;
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		for (int i = 0; i < countUsers; i++) {
			int countOfBugs = Bug::CountOfActiveBugsOfUser(userList[i].userId);
			if ((string)userList[i].role != "admin") {
				cout << left << setw(20) << userList[i].userId;
				cout << left << setw(20) << userList[i].userName;
				cout << left << setw(20) << userList[i].role;
				cout << left << setw(20) << userList[i].isEnabled;
				cout << left << setw(20) << countOfBugs;
			}
			cout << endl;
		}
		cout << setw(140) << setfill('-') << " " << setfill(' ') << endl;
		cout << endl;
	}
	delete[] userList;
}

// Function to Manage Users
void Utility::ManageUsers(User userObj, string filter) {
	system("cls");
	cout << endl;
	cout << right << setw(480) << "Current User : " << userObj.userName << endl;
	Utility::ShowUserTable(userObj, filter);
	long int userId;
	int option;
	do
	{
		cout << "\n\n\n Menu" << endl;
		cout << "\n1: All Users" << endl;
		cout << "2: Engineers" << endl;
		cout << "3: Customers" << endl;
		cout << "4: Create User Account" << endl;
		cout << "5: Update User Password" << endl;
		cout << "6: Disable/Enable User Account" << endl;
		cout << "7: Back" << endl;
		cout << "8: Logout" << endl;

		cout << "\nPlease Select an Option:  ";
		cin >> option;

		switch (option)
		{
		case 1:
			ManageUsers(userObj, "all");
			break;
		case 2:
			ManageUsers(userObj,"engineer");
			break;
		case 3:
			ManageUsers(userObj,"customer");
			break;
		case 4:
			CreateUser(userObj);
			break;
		case 5:
			UpdateUser(userObj);
			break;
		case 6:
			UpdateUserStatus(userObj);
			break;
		case 7:
			userObj.LoadUserDashboard();
			break;
		case 8:
			userObj.Logout();
			break;
		default:
			cout << "Invalid Option!\n";
			break;
		}
	} while (true);
}

// Function to Show Bug Statistics
void Utility::ShowStatistics(User userObj) {

	Bug bugObj;
	int count = bugObj.CountOfBugs();
	Bug* bugs = bugObj.GetBugDetails();
	int total = 0;
	int active = 0;
	int closed = 0;

	if ((string)userObj.role == "admin") {
		for (int i = 0;i < count;i++) {
			total++;
			if ((string)bugs[i].status == "Closed") {
				closed++;
			}
			else {
				active++;
			}
		}

	}
	else if ((string)userObj.role == "customer") {
		for (int i = 0;i < count;i++) {
			
			if ((bugs[i].customerId == userObj.userId) && ((string)bugs[i].status == "Closed")) {
				total++;
				closed++;
			}
			else if((bugs[i].customerId == userObj.userId) && ((string)bugs[i].status != "Closed")){
				total++;
				active++;
			}
		}

	}
	else if ((string)userObj.role == "engineer") {
		
		for (int i = 0;i < count;i++) {
			if ((bugs[i].engineerId == userObj.userId) && ((string)bugs[i].status == "Closed")) {
				total++;
				closed++;
			}
			else if ((bugs[i].engineerId == userObj.userId) && ((string)bugs[i].status != "Closed")) {
				total++;
				active++;
			}
		}
	}

	cout << right << setw(100) << "------------------------------------------" << endl << endl;
	time_t now = time(0);
	int currentYear = 1970 + now / 31537970;
	cout << right << setw(85) << "Bug Statsitics (" << currentYear << ")" << endl<<endl;
	cout << right << setw(65) <<"Total: " << left << setw(10)<<total;
	cout << right << setw(10) << "Closed: " << left << setw(10) << closed;
	cout << right << setw(10) <<"Active: "<< left << setw(10) << active;
	cout << endl;
	cout << right << setw(100) << "------------------------------------------" << endl << endl;
}