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
		INT(_stdcall *appFunc)(int, int); //���ﶨ��һ������ָ�룬Ҳ����ͨ�� typedef ����������
		
		(FARPROC&)appFunc = GetProcAddress(hDll, LPCSTR(MAKEINTRESOURCE(2)));

		if (appFunc)
		{
			
			INT ret = appFunc(5, 3);
			TCHAR retBuf[16] = {0};
			wsprintf(retBuf, L"%d", ret);	//��֮ǰ����sprintf ��������
			
			MessageBox(NULL, retBuf, L"warning", MB_OK);

		}
		else
		{
			FreeLibrary(hDll);
			MessageBox(NULL, L"warning", L"Get ADDRESS FAILED!", MB_OK);
		}

		FreeLibrary(hDll);	//�����ͷ� DLL �ļ�
	}	
	else
	{
		//INT eno = GetLastError();

		MessageBox(NULL, L"warning", L"Load DLL File FAILED!", MB_OK);
	}
	
	return 0;
}