// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include "testDll.h"
#include <Windows.h>


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	HANDLE hThread = NULL;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	{
		//MessageBoxA(NULL, "Hi", "Hi", MB_OK);
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE) run, NULL, 0, NULL);
		break;
	}
	case DLL_PROCESS_DETACH:
		//CloseHandle(hThread);
		break;
	}

	return TRUE;
}