// dllmain.cpp : ���� DLL Ӧ�ó������ڵ㡣
#include "stdafx.h"
#include "KDLL.h"

HINSTANCE hInst;

BOOL APIENTRY DllMain( HMODULE hModule,					//��ǰ DLL �ľ��
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)			//dll ��load��ԭ��
	{
	case DLL_PROCESS_ATTACH:
		printf("\n DLL Load SUCCESSFULLY! \n");
		
		initCondition();
		count = 0;
		
		hInst = hModule;
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

