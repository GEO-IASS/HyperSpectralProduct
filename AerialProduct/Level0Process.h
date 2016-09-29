#pragma once

//0�����ݲ�Ʒ�������,0�����ݲ�Ʒ�����������0�����ݣ��õ�����0����Ʒ
//0�����ݲ�Ʒ������Ҫ�������ݸ�ʽת����Ӱ��Ǿ�����У����EVENT���ݽ����Ȳ���
class Level0Process
{
public:
	//����0����Ʒ�����Ľӿ�
	virtual long Level0Proc_Interface(const char* pathOrderFile) = 0;

public:
	//0������BIL��ʽת��ΪBSQ��ʽ
	virtual long Level0Proc_RawToBSQ(const char* pRawBIL,const char* pD0BSQ);

	//����ʵ���Ҷ������ݺͰ��������ݽ��зǾ�����У��
	virtual long Level0Proc_NonUniform(const char* pD0BSQ,const char* pNonUniform,const char* pCalibFile=NULL,const char* pDarkFile = NULL);

	//����õ�EVENT�ļ�
	virtual long Level0Proc_ExtractEvent(const char* pRawBIL,const char* pEventFile,const int nEventOffset) = 0;

private:
	void GetNonUniformParameters(const char* pCalibFile,const char* pDarkFile,float *params);
};

//��ȫ�׶ε�0�����ݽ��д���õ�0�����ݲ�Ʒ
class QPDLevel0Process : public Level0Process
{
public:
	//����0����Ʒ�����Ľӿ�
	virtual long Level0Proc_Interface(const char* pathOrderFile) {return 0;}

public:
	//��Ӱ���л�ȡEVENT�ļ���Ϣ
	long Level0Proc_ExtractEvent(const char* pRawBIL,const char* pEventFile,const int nEventOffset);

	//�޸Ķ̲�����Event��Ϣ�����ڶ���ȫ�׶����ݶ̲�Event�İ�΢������ȷ�ģ�����������쳣
	//�����Ҫ��ȫ�׶ζ̲����ݽ��д���
	long Level0Proc_ModifySWIREvent(const char* pathEvent,const char* pathExEvent, float fTime);

	//�̲������Ƿ���������ת��ΪBSQ��ʱ��Ҫ˳�㷴������
	//�ڽ��д����ʱ���һ��inverse�����ж��Ƿ���Ҫ���з�������
	long Level0Proc_RawToBSQ(const char* pathRawBIL, const char* pathBSQ, bool inverse );
};
