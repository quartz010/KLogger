// KDLL.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"
#include "KDLL.h"

extern HINSTANCE hInst;

// ���ǵ���������һ��ʾ��
int nKDLL=0;



// ���ǵ���������һ��ʾ����
INT __stdcall fnAdd(int a, int b)
{
	return  a + b;
}


