// KLogger_DLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "KLogger_DLL.h"


// ���ǵ���������һ��ʾ��
KLOGGER_DLL_API int nKLogger_DLL=0;

// ���ǵ���������һ��ʾ����
KLOGGER_DLL_API int fnKLogger_DLL(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� KLogger_DLL.h
CKLogger_DLL::CKLogger_DLL()
{
    return;
}
