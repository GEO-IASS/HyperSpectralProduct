#pragma once
//����ϵ��ת������֪���ǲ��ǿ��Բ��ö������ṹ
//author��	��ε
//version:	2.0

#include "AerialCore.h"

class CoordinateTransBasic
{
public:
	//��γ�Ⱥ͸߶ȵ�����ֱ������ϵ��ת�������ת���ǽ�����WGS84����ϵ�£���һ������ϵ��Ҫ�Լ���չ��
	virtual long BLHToXYZ(double dB,double dL,double dH,THREEDPOINT &XYZPnt);

	//�����ͼ����ϵ�����ĵ�ľ�γ������
	virtual long XYZToBLHS(double dB,double dL,double dH,THREEDPOINT *pGroundPnt,int pixelNum);

	//�������ֱ������ϵ�ĵ��Ӧ�ľ�γ�ȵ�ֵ
	virtual long XYZToBLH(THREEDPOINT XYZPnt,double &dB,double &dL,double &dH);
};

