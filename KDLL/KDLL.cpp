// KDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "KDLL.h"

extern HINSTANCE hInst;

// ���ǵ���������һ��ʾ��
KDLL_API int nKDLL=0;

// ���ǵ���������һ��ʾ����
KDLL_API int fnKDLL(void)
{
    return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� KDLL.h
CKDLL::CKDLL()
{
    return;
}
