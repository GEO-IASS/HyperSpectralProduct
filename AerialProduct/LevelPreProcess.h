#pragma once

#include "AerialCore.h"
#include<vector>
using namespace std;

//����Ԥ�������ɵ���0������
//����Ԥ����Ĳ�����Ҫ�Ƕ�ԭʼ���ݽ��м�⣬���ԭʼ�����Ƿ����©�в�����©���޸�
class PreProcess
{
public:
	//��������Ԥ����Ľӿ�
	virtual long PreProc_Interface(const char* pathOrderFile) = 0;

public:
	//��ȡ����ͷ��Ϣ
	virtual long PreProc_GetHeadInfo(FILE *fRAW,DINFO &mDataHeader,vector<short>& nLeakFrameType,vector<int> &nLeadFrameSize,int &nLeakFrameCount) = 0;

	//����©�м�����޸�
	//����©�м��ԭ���˵��������Ӱ��Ĵ洢��ʽ��BIL���ڼ���������һ����ʶΪ��ʶ�кţ����������ʶλ�Լ����ݴ�С���Ի�ȡ©�е���ϢȻ����в�ֵ�޸�
	//nLeakFrameType 0Ϊ��©�У�1Ϊ©����֡��2Ϊ©�У�3Ϊ©����©֡ͷ�ļ�
	virtual long PreProc_LeakLineCheck(const char *pRAWData, DINFO &mDataHeader, vector<short> &nLeakFrameType, vector<int> &nLeakFrameSize, int &nLeakFrameCount) = 0;

	virtual long PreProc_LeakLineInterpolate(FILE *fRAW, unsigned short *pRepairBuffer, DINFO mDataHeader, vector<short> nLeakFrameType,vector<int> nLeakFrameSize, 
									   int nLoc, __int64 nOffset, unsigned short *pfBuffer, unsigned short *plBuffer, unsigned short *pLeakBuffer)=0;

	//����0�����ݣ�0������ָ©���޸��������
	virtual long PreProc_GenerateD0Data(const char *pRAWData, const  char *pData, DINFO &mDataHeader, vector<short> &nLeakFrameType, vector<int> &nLeakFrameSize, int &nLeakFrameCount, const int nFixLines)=0;
};


//ȫ�׶�����Ԥ����
class QPDPreProcess: public PreProcess
{
public:
	//��������Ԥ����Ľӿ�
	virtual long PreProc_Interface(const char* pathOrderFile){return 0;}

public:
	long PreProc_GetHeadInfo(FILE *fRAW, DINFO &mDataHeader, vector<short> &nLeakFrameType, vector<int> &nLeakFrameSize, int &nLeakFrameCount);

	long PreProc_LeakLineCheck(const char *pRAWData, DINFO &mDataHeader, vector<short> &nLeakFrameType, vector<int> &nLeakFrameSize, int &nLeakFrameCount);

	long PreProc_LeakLineInterpolate(FILE *fRAW, unsigned short *pRepairBuffer, DINFO mDataHeader, vector<short> nLeakFrameType, vector<int> nLeakFrameSize,
								int nLoc, __int64 nOffset, unsigned short *pfBuffer, unsigned short *plBuffer, unsigned short *pLeakBuffer);

	long PreProc_GenerateD0Data(const char *pRAWData, const  char *pData, DINFO &mDataHeader, vector<short> &nLeakFrameType, vector<int> &nLeakFrameSize, int &nLeakFrameCount, const int nFixLines);

	//��©����Ϣд���ļ���
	long PrePRoc_WriteLeakInfo(char *pLeakFile, vector<short> nLeakFrameType, vector<int> nLeakFrameSize, int nLeakFrameCount);

	//���ļ��ж�ȡ©����Ϣ
	long PreProc_ReadLeakFile(char *pLeakFile, vector<short> &nLeakFrameType, vector<int> &nLeakFrameSize, int &nLeakFrameCount);
};
