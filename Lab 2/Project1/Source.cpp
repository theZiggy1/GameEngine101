#include <windows.h>
#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;



bool IsOnlyInstance(LPCTSTR gameTitle) {
	HANDLE handle = CreateMutex(NULL, TRUE, gameTitle);
	if (GetLastError() != ERROR_SUCCESS)
	{
		HWND hWnd = FindWindow(gameTitle, NULL);
		if (hWnd) {
			// An instance of your game is already running. 
			ShowWindow(hWnd, SW_SHOWNORMAL);
			SetFocus(hWnd);
			SetForegroundWindow(hWnd);
			SetActiveWindow(hWnd);
			cout << "Program is already running";
			return false;
		}
	}
	return true;
}


bool CheckStorage(const DWORDLONG diskSpaceNeeded) {
	LPCTSTR lpDirectoryName = NULL;
	__int64 lpFreeBytesAvailable, lpTotalNumberofBytes, lpTotalNumberofFreeBytes;
	GetDiskFreeSpaceEx(lpDirectoryName, (PULARGE_INTEGER)&lpFreeBytesAvailable, (PULARGE_INTEGER)&lpTotalNumberofBytes, (PULARGE_INTEGER)&lpTotalNumberofFreeBytes);
	if ((DWORD)lpTotalNumberofBytes >= diskSpaceNeeded)
	{
		cout << "There is enough Free Space!" << endl;
		return false;
	}
	cout << "There isnt enough free space";
	return true;
}

bool CheckMemory(const DWORDLONG physicalRAMNeeded, const
	DWORDLONG virtualRAMNeeded) {
	MEMORYSTATUSEX status;
	GlobalMemoryStatusEx(&status);
	cout << "Physical RAM : " << status.ullTotalPhys << endl;
	if (status.ullTotalPhys < physicalRAMNeeded) {
		/* you don’t have enough physical memory. Tell the
		player to go get a real computer and give this one to
		his mother.
		*/
		cout << "Insufficient Memory" << endl;
		return false;
	}
	// Check for enough free memory.
	cout << "Virtual RAM : " << status.ullAvailVirtual << endl;
	if (status.ullAvailVirtual < virtualRAMNeeded) {
		// you don’t have enough virtual memory available.
		// Tell the player to shut down the copy of Visual 
		//Studio running in the background.
		cout << "Insufficient Memory" << endl;
		return false;
	}
}

DWORD ReadCPUSpeed() {
	DWORD BufSize = sizeof(DWORD);
	DWORD dwMHz = 0;
	DWORD type = REG_DWORD;
	HKEY hKey;
	// open the key where the proc speed is hidden: 
	long lError = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "HARDWARE\\DESCRIPTION\\System\\CentralProcessor\\0", 0,
		KEY_READ, &hKey);
	if (lError == ERROR_SUCCESS) {
		// query the key:  
		RegQueryValueEx(hKey, "~MHz", NULL, &type, (LPBYTE)&dwMHz, &BufSize);
	}
	return dwMHz;

}
int main()
{
	
	LPCTSTR gameTitle = "";
	if (!IsOnlyInstance(gameTitle)) 
	{
	}
	DWORD diskSpaceNeeded = 300;
	if (CheckStorage(diskSpaceNeeded))
	{
		
	}
	DWORDLONG ramNeeded = 0;
	CheckMemory(ramNeeded, ramNeeded);
	cout << "CPU Speed: " << ReadCPUSpeed() << endl;
	SYSTEM_INFO siSysInfo;
	GetSystemInfo(&siSysInfo);
	cout << "CPU Architecture: " << siSysInfo.dwProcessorType << endl;
	system("PAUSE");
	return 0;
}