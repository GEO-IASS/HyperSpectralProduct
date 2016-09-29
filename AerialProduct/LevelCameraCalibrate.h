#pragma once
#include "AerialCore.h"
#include <vector>
using namespace std;
//�������ͼ�У

//�԰��ýǣ�����ʸ�����м�У
//�����û��д����������ԭ������Ϊ�󵼹�����΢�е��鷳��û�������Ƶ���
class SetupCalibProcess
{
public:
	//���ýǼ�У�ӿ�
	long SetupCalibProc_SetupAngle(const char* pathPOSFile,float ifov,vector<SetupGCP> m_setup_GCPs,float &fLen,THREEDPOINT setupVec,float *setupAngle);

	//����ʸ����У�ӿ�
	long SetupCalibProc_SetupVector(const char* pathPOSFile,float ifov,vector<SetupGCP> m_setup_GCPs,float &fLen,THREEDPOINT &setupVec,float *setupAngle);

	//���ϼ�У�ӿ�
	long SetupCalibProc_SetupComb(const char* pathPOSFile,float ifov,vector<SetupGCP> m_setup_GCPs,float &fLen,THREEDPOINT &setupVec,float *setupAngle);

private:
	//��ȡָ�����е�POS����
	long SetupCalibProc_GetSelectPOS(const char* pathPOSFile,vector<SetupGCP> m_setup_GCPs,vector<POS> &m_selPOS);

	//��ָ���е�POS�����н����EO
	long SetupCalibProc_ExtractSelectEO(vector<POS> m_selPOS,vector<EO> &m_selEO,THREEDPOINT &setupVec,float *setupAngle);
};

//����ڲ�����У����
class CameraInstrinsicCalibProcess
{
public:
	//����ڲμ�У��������㹻��Ŀ��Ƶ㣬��ֱ�Ӻ󷽽����У�������
	void CameraInstrinsicCalibProc_Resection(vector<CPOINT> pntImage,vector<THREEDPOINT> pntGcps,float* instrinsicMat);

	//��OpenCV�еĶ��귽������������(���˫Ŀ�������֪��һ�����Ӧ����δ���)
	void CameraInstrinsicCalibProc_CV(vector<string> imagePairs);
};