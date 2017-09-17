#include "stdafx.h"
#include "Klogger.h"
#include "console.h"

#define KLOG_DEBUG	//console 的调试开关

typedef VOID(_stdcall* LPFNDLLFUNC)(VOID);
typedef INT(_stdcall* LPFNDLLFUNC1)(INT, INT);

static HHOOK hKBHook = 0;
static LPFNDLLFUNC lpfnDllUnHook = 0;
static 	HMODULE hHookDll;
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);





int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{	

	TCHAR currentDir[MAX_PATH];
	std::exception mException;

#ifdef KLOG_DEBUG
	console_init();
#endif

	

	if (!(hKBHook = SetWindowsHookEx(WH_KEYBOARD_LL, (HOOKPROC)KeyboardProc, NULL, 0)))
	{
		MessageBox(NULL, L"Failed to install KB hook!", L"Error", MB_ICONERROR);
	}

	GetCurrentDirectory(MAX_PATH, currentDir);	//get当前的路径
	DebugPrint(currentDir);

	try
	{
		hHookDll = LoadLibrary(L"./KDLL.dll");

		if (hHookDll)
		{
			DebugPrint(L"DLL loaded! \n");
		
			LPFNDLLFUNC lpfnDllSetHook = (LPFNDLLFUNC) GetProcAddress(hHookDll, "fnSetKbHook");
			lpfnDllUnHook = (LPFNDLLFUNC) GetProcAddress(hHookDll, "fnRemoveKbHook");
			
			DebugPrint(L"%d", (int)lpfnDllUnHook);
			//INT(_stdcall *appFunc)(INT, INT); //这里定义一个函数指针，也可以通过 typedef 定义新类型
			//获得动态库函数指针
			//(FARPROC&)appFunc = GetProcAddress(hHookDll, LPCSTR(MAKEINTRESOURCE(1)));

			if (lpfnDllSetHook)
			{
				lpfnDllSetHook();
			}
			else
			{
				DebugPrint(L"invalid Function Pointer!");
				throw mException;
			}
		}
		else
		{
			//INT eno = GetLastError();
			throw mException;
			//MessageBox(NULL, L"warning", L"Load DLL File FAILED!", MB_OK);
		}

	}
	catch (const std::exception& e)
	{	
		USES_CONVERSION;

		TCHAR textBuf[64];
		
		FreeLibrary(hHookDll);
		//wsprintf(textBuf, L"Load DLL FAILED! \n%s", CA2W(e.what()));

		MessageBox(GetDesktopWindow(), L"Load DLL FAILED", L"warning",  MB_OK);
	}
				

	MSG msg;	//保持应用运行 (保持句柄这样DLL 不会被回收)
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
	return msg.wParam;

#ifndef KLOG_DEBUG
#endif
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	
	if (nCode >= 0)
	{
		// the action is valid: HC_ACTION.
		if (wParam == WM_KEYDOWN)
		{
			// lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
			KBDLLHOOKSTRUCT kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

			switch (kbdStruct.vkCode)
			{
			case VK_F10:				//程序退出快捷键
				
				//MessageBox(GetDesktopWindow(), L"F10", L"info", NULL);
				DebugPrint(L"%d", (int)lpfnDllUnHook);

				lpfnDllUnHook();
				FreeLibrary(hHookDll);	//这里释放 DLL 文件

				exit(0);
				break;
			default:
				break;
			}
			
		}
	}
	
	
	return CallNextHookEx(hKBHook, nCode, wParam, lParam); //要把消息传到下一个钩子 ，不然键盘就没用了！

}

