#pragma once
/*//////////////////////////////////////////////////////////////////////////
����������


/////////////////////////////////////////////////////////////////////////*/


//�����ĸ
int SEU_RandEx(int min, int max);

//�ͷ���Դ
BOOL ReleaseResource(HMODULE hModule, WORD wResourceID, LPCTSTR lpType, LPCTSTR lpFilePath);

//����ɾ��(����)
void DelSelf();

//����Ȩ��
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);

//���ݽ�������PID
DWORD GetPidByName(LPCSTR szProcName);


BOOL KillProcessByPid(DWORD dwPid);

BOOL KillProcessByName(LPCSTR szProcName);
