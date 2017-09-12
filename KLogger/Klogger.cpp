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

#ifdef KLOG_DEBUG
	console_init();
#endif

	GetCurrentDirectory(MAX_PATH, currentDir);	//get��ǰ��·��
	
	DebugPrint(currentDir);

	try
	{
		hHookDll = LoadLibrary(L"./m.dll");
		std::exception mException;

		
		if (hHookDll)
		{
			INT(_stdcall *appFunc)(int, int); //���ﶨ��һ������ָ�룬Ҳ����ͨ�� typedef ����������

			(FARPROC&)appFunc = GetProcAddress(hHookDll, LPCSTR(MAKEINTRESOURCE(1)));

			if (appFunc)
			{

				INT ret = appFunc(5, 3);
				TCHAR retBuf[16] = { 0 };
				wsprintf(retBuf, L"%d", ret);	//��֮ǰ����sprintf ��������

				MessageBox(NULL, retBuf, L"warning", MB_OK);

			}
			else
			{
				throw mException;
			}

			FreeLibrary(hHookDll);	//�����ͷ� DLL �ļ�
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
		TCHAR textBuf[64];
		
		FreeLibrary(hHookDll);
		wsprintf(textBuf, L"Load DLL FAILED! \n%s", CA2W(e.what()));

		MessageBox(GetDesktopWindow(), textBuf, L"warning",  MB_OK);
	}
#ifndef KLOG_DEBUG
	MSG msg;
	while (GetMessage(&msg, 0, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	};
	return msg.wParam;
#endif
}