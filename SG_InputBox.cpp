#include "stdafx.h"
#include "SG_InputBox.h"
#include "utils.h"
#include <Windows.h>


HFONT SG_InputBox::m_hFont = NULL;
HWND  SG_InputBox::m_hWndInputBox = NULL;
HWND  SG_InputBox::m_hWndParent = NULL;
HWND  SG_InputBox::m_hWndEdit1 = NULL;
HWND  SG_InputBox::m_hWndEdit2 = NULL;
HWND  SG_InputBox::m_hWndOK = NULL;
HWND  SG_InputBox::m_hWndCancel = NULL;
HWND  SG_InputBox::m_hWndPrompt = NULL;
HWND  SG_InputBox::m_hWndUsername = NULL;
HWND  SG_InputBox::m_hWndPassword = NULL;
wchar_t SG_InputBox::m_String1[320];
wchar_t SG_InputBox::m_String2[320];
HBRUSH SG_InputBox::hbrBkgnd = NULL;

#define SOFT_BLUE RGB(206,214,240)
LRESULT CALLBACK SG_InputBox::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	LOGFONT lfont;
	HINSTANCE m_hInst = NULL;
	switch (message)
	{
		/*case WM_CTLCOLORSTATIC:
		{
			HDC hdcStatic = (HDC)wParam;
			if (hbrBkgnd == NULL)
			{
				hbrBkgnd = CreateSolidBrush(SOFT_BLUE);
			}
			SetTextColor(hdcStatic, RGB(0, 0, 0));
			SetBkColor(hdcStatic, SOFT_BLUE);

			return (INT_PTR)hbrBkgnd;
		}
		break;*/
	case WM_CREATE:
		// Define out font
		memset(&lfont, 0, sizeof(lfont));
		lstrcpy(lfont.lfFaceName, FONT_NAME);
		lfont.lfHeight = FONT_HEIGHT;
		lfont.lfWeight = FW_NORMAL;//FW_BOLD;
		lfont.lfItalic = FALSE;
		lfont.lfCharSet = DEFAULT_CHARSET;
		lfont.lfOutPrecision = OUT_DEFAULT_PRECIS;
		lfont.lfClipPrecision = CLIP_DEFAULT_PRECIS;
		lfont.lfQuality = DEFAULT_QUALITY;
		lfont.lfPitchAndFamily = DEFAULT_PITCH;
		m_hFont = CreateFontIndirect(&lfont);
		// 
		m_hInst = GetModuleHandle(NULL);


		// Username textbox
		m_hWndUsername = CreateWindowEx(0x00000020L,
			L"static", L"User Name:",
			WS_VISIBLE | WS_CHILD,
			15, TOP_EDGE + 25 * 2 + 30, 100, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndUsername == NULL)
		{
			REPORTERROR;
			return NULL;
		}

		// setting font
		SetFontToControl(m_hWndUsername);

		// The TextEdit Control - For the text to be input
		m_hWndEdit1 = CreateWindowEx(WS_EX_STATICEDGE,
			TEXTEDIT_CLASS, L"",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL,
			140, TOP_EDGE + 25 * 2 + 30, INPUTBOX_WIDTH - 200, TEXTEDIT_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndEdit1 == NULL)
		{
			REPORTERROR;
			return NULL;
		}

		SetFontToControl(m_hWndEdit1);

		// Password textbox
		m_hWndPassword = CreateWindowEx(0x00000020L,
			L"static", L"Password:",
			WS_VISIBLE | WS_CHILD,
			15, TOP_EDGE + BUTTON_HEIGHT * 2 + 30, 100, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndPassword == NULL)
		{
			REPORTERROR;
			return NULL;
		}

		// setting font
		SetFontToControl(m_hWndPassword);

		m_hWndEdit2 = CreateWindowEx(WS_EX_STATICEDGE,
			TEXTEDIT_CLASS, L"",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP | ES_AUTOHSCROLL | ES_PASSWORD,
			140, TOP_EDGE + BUTTON_HEIGHT * 2 + 30, INPUTBOX_WIDTH - 200, TEXTEDIT_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndEdit2 == NULL)
		{
			REPORTERROR;
			return NULL;
		}

		SetFontToControl(m_hWndEdit2);

		// The Confirm button
		m_hWndOK = CreateWindowEx(WS_EX_STATICEDGE,
			PUSH_BUTTON, L"Log In",
			WS_VISIBLE | WS_CHILD | WS_TABSTOP,
			INPUTBOX_WIDTH - BUTTON_WIDTH - 60, 210, 150, 30,
			hWnd,
			NULL,
			m_hInst,
			NULL);
		if (m_hWndOK == NULL)
		{
			REPORTERROR;
			return NULL;
		}
		// setting font
		SetFontToControl(m_hWndOK);

		// The Cancel button
		//m_hWndCancel = CreateWindowEx(WS_EX_STATICEDGE,
		//	PUSH_BUTTON, L"Cancel",
		//	WS_VISIBLE | WS_CHILD | WS_TABSTOP,
		//	INPUTBOX_WIDTH - BUTTON_WIDTH - 240, 210, 150, 30,
		//	hWnd,
		//	NULL,
		//	m_hInst,
		//	NULL);

		//if (m_hWndCancel == NULL)
		//{
		//	REPORTERROR;
		//	return NULL;
		//}

		//// setting font
		//SetFontToControl(m_hWndCancel);

		// The SG_InputBox Caption Static text
		m_hWndPrompt = CreateWindowEx(0x00000020L,
			L"static", L"The server http ://192.168.0.1:80 requires a username and password. The server says: NETGEAR DGN2000.",
			WS_VISIBLE | WS_CHILD,
			15, TOP_EDGE, 500, BUTTON_HEIGHT,
			hWnd,
			NULL,
			m_hInst,
			NULL);

		if (m_hWndPrompt == NULL)
		{
			REPORTERROR;
			return NULL;
		}

		// setting font
		SetFontToControl(m_hWndPrompt);
		SetFocus(m_hWndEdit1);

		break;
	case WM_DESTROY:

		DeleteObject(m_hFont);


		EnableWindow(m_hWndParent, TRUE);
		SetForegroundWindow(m_hWndParent);
		DestroyWindow(hWnd);
		PostQuitMessage(0);

		break;
	case WM_COMMAND:
		switch (HIWORD(wParam))
		{

		case BN_CLICKED:
			if ((HWND)lParam == m_hWndOK)
				PostMessage(m_hWndInputBox, WM_KEYDOWN, VK_RETURN, 0);
			if ((HWND)lParam == m_hWndCancel)
				PostMessage(m_hWndInputBox, WM_KEYDOWN, VK_ESCAPE, 0);
			break;
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


BOOL SG_InputBox::GetString(LPCTSTR szCaption, LPCTSTR szPrompt, HWND hWindow, wchar_t* userName, wchar_t* password, LPCTSTR szDefaultText)
{
	RECT r;
	//HWND hWnd = GetDesktopWindow();
	HWND hWnd = (HWND)hWindow;
	GetWindowRect(hWnd, &r);

	HINSTANCE hInst = GetModuleHandle(NULL);
	//HINSTANCE hInst = (HINSTANCE)hWindow;

	WNDCLASSEX wcex;

	if (!GetClassInfoEx(hInst, CLASSNAME, &wcex))
	{
		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = (WNDPROC)WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInst;
		wcex.hIcon = NULL;//LoadIcon(hInst, (LPCTSTR)IDI_MYINPUTBOX);
		wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW);
		wcex.lpszMenuName = NULL;
		wcex.lpszClassName = CLASSNAME;
		wcex.hIconSm = NULL;

		if (RegisterClassEx(&wcex) == 0)
			REPORTERROR;

	}

	m_hWndParent = hWnd;

	m_hWndInputBox = CreateWindowEx(/*WS_EX_TOOLWINDOW*/WS_EX_DLGMODALFRAME,
		CLASSNAME,
		szCaption,
		WS_POPUPWINDOW | WS_CAPTION | WS_TABSTOP,
		(GetSystemMetrics(SM_CXSCREEN) - INPUTBOX_WIDTH) / 2, (GetSystemMetrics(SM_CYSCREEN) - INPUTBOX_HEIGHT) / 2,
		INPUTBOX_WIDTH, INPUTBOX_HEIGHT,
		m_hWndParent,
		NULL,
		NULL,
		NULL);
	if (m_hWndInputBox == NULL)
	{
		REPORTERROR;
		return NULL;
	}

	// Set text alingment
	/*setTextAlignment(m_hWndPrompt, SS_CENTER);
	SetWindowText(m_hWndPrompt, szPrompt);
	setTextAlignment(m_hWndEdit, SS_CENTER);
	SetForegroundWindow(m_hWndInputBox);*/

	// Set default button
	SendMessage((HWND)m_hWndOK, BM_SETSTYLE,
		(WPARAM)LOWORD(BS_DEFPUSHBUTTON), MAKELPARAM(TRUE, 0));
	SendMessage((HWND)m_hWndCancel, BM_SETSTYLE,
		(WPARAM)LOWORD(BS_PUSHBUTTON), MAKELPARAM(TRUE, 0));

	// Set default text
	SendMessage(m_hWndEdit1, EM_SETSEL, 0, -1);
	SendMessage(m_hWndEdit1, EM_REPLACESEL, 0, (LPARAM)szDefaultText);
	SendMessage(m_hWndEdit1, EM_SETSEL, 0, -1);
	SetFocus(m_hWndEdit1);

	SendMessage(m_hWndEdit2, EM_SETSEL, 0, -1);
	SendMessage(m_hWndEdit2, EM_REPLACESEL, 0, (LPARAM)szDefaultText);
	SendMessage(m_hWndEdit2, EM_SETSEL, 0, -1);
	SetFocus(m_hWndEdit1);



	EnableWindow(m_hWndParent, FALSE);

	ShowWindow(m_hWndInputBox, SW_SHOW);
	UpdateWindow(m_hWndInputBox);

	BOOL ret = 0;

	MSG msg;

	HWND hWndFocused;

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (msg.message == WM_KEYDOWN)
		{
			/*if (msg.wParam == VK_ESCAPE)
			{
				SendMessage(m_hWndInputBox, WM_DESTROY, 0, 0);
				ret = 0;
			}*/
			if (msg.wParam == VK_RETURN)
			{
				int nCount = GetWindowTextLength(m_hWndEdit1);
				nCount++;
				GetWindowText(m_hWndEdit1, userName, nCount);
				//SendMessage(m_hWndInputBox, WM_DESTROY, 0, 0);

				nCount = GetWindowTextLength(m_hWndEdit2);
				nCount++;
				GetWindowText(m_hWndEdit2, password, nCount);
				SendMessage(m_hWndInputBox, WM_DESTROY, 0, 0);
				
				if (wcscmp(password, L"") == 0 || wcscmp(userName, L"") == 0) {
					ret = 0;
				}
				else
					ret = 1;
			}
			if (msg.wParam == VK_TAB)
			{
				hWndFocused = GetFocus();
				if (hWndFocused == m_hWndEdit1) SetFocus(m_hWndEdit2);
				if (hWndFocused == m_hWndEdit2) SetFocus(m_hWndOK);
				if (hWndFocused == m_hWndOK) SetFocus(m_hWndCancel);
			}

		}
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return ret;
}
