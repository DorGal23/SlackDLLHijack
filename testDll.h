#pragma once
#include "stdafx.h"

#define DLLEXPORT __declspec(dllexport)__stdcall

//extern "C" LRESULT DLLEXPORT CALLBACK HostWndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

extern "C" LRESULT DLLEXPORT CALLBACK KeyboardProc(
	_In_ int    code,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
);

DWORD WINAPI run();

DWORD FindProcessId(WCHAR* processName);

HANDLE WINAPI hCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);


extern bool done;
