// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"
#include "KDLL.h"

//
//                       _oo0oo_
//                      o8888888o
//                      88" . "88
//                      (| -_- |)
//                      0\  =  /0
//                    ___/`---'\___
//                  .' \\|     |// '.
//                 / \\|||  :  |||// \
//                / _||||| -:- |||||- \
//               |   | \\\  -  /// |   |
//               | \_|  ''\---/''  |_/ |
//               \  .-\__  '-'  ___/-. /
//             ___'. .'  /--.--\  `. .'___
//          ."" '<  `.___\_<|>_/___.' >' "".
//         | | :  `- \`.;`\ _ /`;.`/ - ` : | |
//         \  \ `_.   \_ __\ /__ _/   .-` /  /
//     =====`-.____`.___ \_____/___.-`___.-'=====
//                       `=---='
//
//
//     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
//               佛祖保佑         永无BUG
//
//			很奇怪,全局钩子不报毒了？？？

HINSTANCE hInst;

BOOL APIENTRY DllMain( HMODULE hModule,					//当前 DLL 的句柄
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)			//dll 被load的原因
	{
	case DLL_PROCESS_ATTACH:
		wprintf(L"\n DLL Load SUCCESSFULLY! \n");
		
		initCondition();
		count = 0;
		
		hInst = hModule;	//保存Dll句柄 方便安装全局钩子
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}

