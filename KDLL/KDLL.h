// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� KDLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// KDLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�

#ifdef KDLL_EXPORTS
#define KDLL_API __declspec(dllexport)
#else
#define KDLL_API __declspec(dllimport)
#endif





extern KDLL_API int nKDLL;

INT _stdcall fnAdd(int, int);
void initCondition(void);	//������ʼ������
extern int count;