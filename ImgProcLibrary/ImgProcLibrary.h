// ���� ifdef ���Ǵ���ʹ�� DLL �������򵥵�
// ��ı�׼�������� DLL �е������ļ��������������϶���� IMGPROCLIBRARY_EXPORTS
// ���ű���ġ���ʹ�ô� DLL ��
// �κ�������Ŀ�ϲ�Ӧ����˷��š�������Դ�ļ��а������ļ����κ�������Ŀ���Ὣ
// IMGPROCLIBRARY_API ������Ϊ�Ǵ� DLL ����ģ����� DLL ���ô˺궨���
// ������Ϊ�Ǳ������ġ�
#ifdef IMGPROCLIBRARY_EXPORTS
#define IMGPROCLIBRARY_API __declspec(dllexport)
#else
#define IMGPROCLIBRARY_API __declspec(dllimport)
#endif

// �����Ǵ� ImgProcLibrary.dll ������
class IMGPROCLIBRARY_API CImgProcLibrary {
public:
	CImgProcLibrary(void);
	// TODO: �ڴ�������ķ�����
};

extern IMGPROCLIBRARY_API int nImgProcLibrary;

IMGPROCLIBRARY_API int fnImgProcLibrary(void);
