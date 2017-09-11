#include "stdaxf.h"
#include "Klogger.h"



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	
	HMODULE hDll = LoadLibrary(L"./m.dll");
	if (hDll)
	{
		INT(_stdcall *appFunc)(int, int); //这里定义一个函数指针，也可以通过 typedef 定义新类型
		
		(FARPROC&)appFunc = GetProcAddress(hDll, LPCSTR(MAKEINTRESOURCE(2)));

		if (appFunc)
		{
			
			INT ret = appFunc(5, 3);
			TCHAR retBuf[16] = {0};
			wsprintf(retBuf, L"%d", ret);	//用之前成了sprintf 导致乱码
			
			MessageBox(NULL, retBuf, L"warning", MB_OK);

		}
		else
		{
			FreeLibrary(hDll);
			MessageBox(NULL, L"warning", L"Get ADDRESS FAILED!", MB_OK);
		}

		FreeLibrary(hDll);	//这里释放 DLL 文件
	}	
	else
	{
		//INT eno = GetLastError();

		MessageBox(NULL, L"warning", L"Load DLL File FAILED!", MB_OK);
	}
	
	return 0;
}