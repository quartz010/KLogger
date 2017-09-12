// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

HINSTANCE hInst;

BOOL APIENTRY DllMain( HMODULE hModule,					//当前 DLL 的句柄
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)			//dll 被load的原因
	{
	case DLL_PROCESS_ATTACH:
		hInst = hModule;

		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

