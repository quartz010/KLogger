#include "stdafx.h"
#include <string.h>
#include <wchar.h>

HANDLE hOutput;
BOOL isInited = FALSE;

void console_init(void)
{
	AllocConsole();
	SetConsoleTitleW(L"Debug Window");
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	
	isInited = TRUE;

	//FreeConsole();    
}

void DebugPrint(TCHAR *fmt, ...)	//��д�Ŀ��ֽڰ汾
{
	if (isInited)
	{
		DWORD uLen;
		TCHAR buffer[4096];
		int arg;

		arg = (int)&fmt + sizeof(int);
		wsprintf(buffer, fmt, (char *)arg);
		lstrcatW(buffer, L"\n");
		WriteConsole(hOutput, buffer, wcslen(buffer), &uLen, NULL);	//���ֽڵ�strlen �� wcslen
	}
}