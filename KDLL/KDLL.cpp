// KDLL.cpp : 定义 DLL 应用程序的导出函数。
//
#include "stdafx.h"
#include "KDLL.h"

extern HINSTANCE hInst;

// 这是导出变量的一个示例
int nKDLL=0;



// 这是导出函数的一个示例。
INT __stdcall fnAdd(int a, int b)
{
	return  a + b;
}


