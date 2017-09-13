#include "stdafx.h"
#include "Klogger.h"
#include "console.h"


#define KLOG_DEBUG

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	USES_CONVERSION;
	
	HMODULE hHookDll;
	TCHAR currentDir[MAX_PATH];
	std::exception mException;

#ifdef KLOG_DEBUG
	console_init();
#endif

	GetCurrentDirectory(MAX_PATH, currentDir);	//get当前的路径
	
	DebugPrint(currentDir);

	try
	{
		hHookDll = LoadLibrary(L"./KDLL.dll");
		

		
		if (hHookDll)
		{	
			typedef VOID(_stdcall* LPFNDLLFUNC)(VOID);
			typedef INT(_stdcall* LPFNDLLFUNC1)(INT, INT);


			//INT(_stdcall *appFunc)(INT, INT); //这里定义一个函数指针，也可以通过 typedef 定义新类型

			LPFNDLLFUNC lpfnDllFunc = (LPFNDLLFUNC) GetProcAddress(hHookDll, "fnSetKbHook");
			
			//获得动态库函数指针
			//(FARPROC&)appFunc = GetProcAddress(hHookDll, LPCSTR(MAKEINTRESOURCE(1)));

			if (lpfnDllFunc)
			{

				//TCHAR retBuf[16] = { 0 };
				//INT ret = appFunc(5, 3);				
				//wsprintf(retBuf, L"%d", ret);	//用之前成了sprintf 导致乱码
				//MessageBox(NULL, retBuf, L"warning", MB_OK);

				lpfnDllFunc();
			}
			else
			{
				DebugPrint(L"invalid Function Pointer!");
				throw mException;
			}

			FreeLibrary(hHookDll);	//这里释放 DLL 文件
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
		wsprintf(textBuf, L"Load DLL FAILED! \n%s", CA2W(e.what()));

		MessageBox(GetDesktopWindow(), textBuf, L"warning",  MB_OK);
	}
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
	return msg.wParam;
#ifndef KLOG_DEBUG
#endif
}