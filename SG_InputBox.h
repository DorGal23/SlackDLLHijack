#pragma once
#define ASPECT_RATIO_X	2
#define ASPECT_RATIO_Y	2
#define TOP_EDGE		10 * ASPECT_RATIO_Y
#define INPUTBOX_WIDTH	290 * ASPECT_RATIO_X
#define INPUTBOX_HEIGHT 160 * ASPECT_RATIO_Y
#define TEXTEDIT_HEIGHT	15 * ASPECT_RATIO_Y
#define BUTTON_HEIGHT	25 * ASPECT_RATIO_Y
#define BUTTON_WIDTH	80 * ASPECT_RATIO_X
#define FONT_HEIGHT		10 * ASPECT_RATIO_Y

#define CLASSNAME					L"SG_Inputbox"
#define PUSH_BUTTON					L"Button"
#define FONT_NAME					_T("David")
#define TEXTEDIT_CLASS				L"edit"
#define SetFontToControl(n)			SendMessage((n), WM_SETFONT, (WPARAM)m_hFont, 0);
#include <windows.h>

HFONT m_hFont = NULL;
HWND  m_hWndInputBox = NULL;
HWND  m_hWndParent = NULL;
HWND  m_hWndEdit1 = NULL;
HWND  m_hWndOK = NULL;
HWND  m_hWndCancel = NULL;
HWND  m_hWndPrompt = NULL;
wchar_t m_String1[320];
wchar_t m_String2[320];
static HBRUSH hbrBkgnd = NULL;


class SG_InputBox
{

	static HFONT m_hFont;
	static HWND  m_hWndInputBox;
	static HWND  m_hWndParent;
	static HWND  m_hWndEdit1;
	static HWND  m_hWndEdit2;
	static HWND  m_hWndOK;
	static HWND  m_hWndCancel;
	static HWND  m_hWndPrompt;
	static HWND  m_hWndUsername;
	static HWND  m_hWndPassword;
	static wchar_t m_String1[320];
	static wchar_t m_String2[320];
	static HBRUSH hbrBkgnd;


	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

public:
	static BOOL GetString(LPCTSTR szCaption, LPCTSTR szPrompt, HWND hWindow, wchar_t* userName, wchar_t* password, LPCTSTR szDefaultText = L"");

};

