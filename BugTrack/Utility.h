//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: Utility.h
//FileType: C++ Heder file
//Copy Rights : Quest Global
//Description : Utility Class Header File
////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
#include "User.h"
#include "Bug.h"

class Utility {
public:
	static void StartApp();
	static void ReportBug(User userObj);
	static void ManageResponsibility(User userObj, long int bugId);
	static void UpdateBug(User userObj, long int bugId);
	static void BugMore(User userObj, long int bugId);
	static void ActiveBugsData(User userObj);
	static void BugHistoryData(User userObj);
	static string GenerateRandomPassword();
	static void CreateUser(User userObj);
	static void UpdateUser(User userObj);
	static void UpdateUserStatus(User userObj);
	static void ManageUsers(User userObj, string filter);
	static void ShowStatistics(User userObj);
	static void ShowUserTable(User userObj, string filter);
};
