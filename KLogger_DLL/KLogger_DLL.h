// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� KLOGGER_DLL_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// KLOGGER_DLL_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef KLOGGER_DLL_EXPORTS
#define KLOGGER_DLL_API __declspec(dllexport)
#else
#define KLOGGER_DLL_API __declspec(dllimport)
#endif

// �����Ǵ� KLogger_DLL.dll ������
class KLOGGER_DLL_API CKLogger_DLL {
public:
	CKLogger_DLL(void);
	// TODO:  �ڴ�������ķ�����
};

extern KLOGGER_DLL_API int nKLogger_DLL;

KLOGGER_DLL_API int fnKLogger_DLL(void);
