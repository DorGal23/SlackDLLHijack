#pragma once

#include <Windows.h>

class SG_InputBox
{
public:
	static BOOL GetString(LPCTSTR szCaption, LPCTSTR szPrompt, HWND hWindow, LPWSTR userName, LPWSTR password, LPCTSTR szDefaultText = L"");
};