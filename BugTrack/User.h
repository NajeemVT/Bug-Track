//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: User.h
//FileType: C++ Heder file
//Copy Rights : Quest Global
//Description : User Class Header File
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include<string>
#include "Bug.h"

using namespace std;

class User
{
public:
	long int userId;
	char role[256];
	bool isLogged;
	bool isEnabled;
	char userName[256];
private:
	char password[256];

public:
	User();
	User(long int userId, char* userName, char* role, char* password);
	bool Login();
	void LoadUserDashboard();
	int CountOfUsers();
	static string IsValidUser(long int userId);
	User* GetUserDetails();
	bool UpdatePassword(long int userId);
	bool ChangeUserStatus(long int id);
	bool IsLogged();
	void Logout();
};



