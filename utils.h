#pragma once

#include <windows.h>

void setTextAlignment(HWND hwnd, int textalignment);
#define REPORTERROR ReportError(__FUNCTION__)
void ReportError(const char *CallingFunction);