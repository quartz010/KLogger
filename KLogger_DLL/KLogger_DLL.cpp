// KLogger_DLL.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "KLogger_DLL.h"


// 这是导出变量的一个示例
KLOGGER_DLL_API int nKLogger_DLL=0;

// 这是导出函数的一个示例。
KLOGGER_DLL_API int fnKLogger_DLL(void)
{
    return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 KLogger_DLL.h
CKLogger_DLL::CKLogger_DLL()
{
    return;
}
