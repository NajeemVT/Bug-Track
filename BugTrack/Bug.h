//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: Bug.h
//FileType: C++ Heder file
//Copy Rights : Quest Global
//Description : Bug Class Header File
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include<string>
using namespace std;

class User;

class Bug
{
public:
	long int bugId;
	char category[256];
	char description[256];
	char evidence[256];
	char createdAt[256];
	long int customerId;
	long int engineerId;
	char priority[256];
	char status[256];
	char response[256];

public:
	Bug();
	Bug(long int bugId, char* category, char* description, char* evidence, long int customerId, char* priority);
	long int DeleteBug(long int customerId,long int bugId);
	int CountOfBugs();
	static int CountOfActiveBugsOfUser(long int userId);
	Bug* GetBugDetails();
	bool GetMoreDetails(long int bugId);
	bool SetEngineer(long int bugId,long int engineerId);
	bool UpdateStatus(long int id, long int bugId);
	long int LastBugId();
};

