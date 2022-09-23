#include <iostream>
#include <iomanip>
#include <windows.h>
#include "User.h"
//////////////////////////////////////////////////////////////////////////////////////////////////
//FileName: BugTrack.cpp
//FileType: C++ Souce File
//Copy Rights : Quest Global
//Description : Driver Code
////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Bug.h"
#include "Utility.h"

using namespace std;

int main() {
	// Make Console Window Full Screen
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_SHOWMAXIMIZED);

	Utility::StartApp();
	return 0;
}