#pragma once
#include"AerialCore.h"
#include<vector>
using namespace std;

class QPDLevel2Process;

//����һ������࣬�����ض���POS������Ҫ�̳�������
class GeoPOSProcess
{
public:
	//��ȡPOS���ݣ�����ʼ�ж�ȡָ��������POS����
	virtual long GeoPOSProc_ReadPartPOS(const char* pPOSFile,int nLines,int nBeginLine) = 0;

	//��SBET�н�����POS���ݣ�Ӧ���ò��ϣ�
	virtual long GeoPOSProc_ExtractSBET(const char* pSBETFile,const char* pEVENTFile,const char* pPOSFile,float fOffsetGPS = 17)=0;

	//���ļ��ж�ȡEOԪ��
	virtual long GeoPOSProc_ReadEOFile(const char* pEOFile,double &dB,double &dL,double &dH);

	//��POS�����н�����ⷽλԪ��
	virtual long GeoPOSProc_ExtractEO(const char* pPOSFile,const char* pEOFile,int nLines,int nBeginLine,THREEDPOINT THETA,float* fSetupAngle);

	//����POS���ݼ��㺽�����ڵ����ޣ�EMMatrixΪ��������ϵ����ͼ����ϵ��ת��
	virtual long GeoPOSProc_EOQuadrant(int nLines,double EMMatrix[],THREEDPOINT &XYZPnt);
	virtual long GeoPOSProc_EOQuadrant(POS curPos,double EMMatrix[],THREEDPOINT &XYZPnt);

	//����POS��ȡEOԪ�غ���ת����������ļ���
	virtual long GeoPOSProc_EOMatrixTurn(int nCurLine,THREEDPOINT &XYZPnt,int nQuadNum,double EMMatrix[],THREEDPOINT ANGLETHETA, THREEDPOINT POSISTTHETA ,FILE* fEO);

	//���ݵ���POS���ݻ�ȡEOԪ��
	virtual long GeoPOSProc_EOMatrixTurn(POS pdfPOS,THREEDPOINT &XYZPnt,THREEDPOINT THETA,float* pVector ,int nQuadNum,double EMMatrix[],EO &pdfEO);

protected:
	//POS��EO���ݵĶ���
	vector<POS> m_Geo_Pos;
	vector<EO>  m_Geo_EO;

	//�������ľ�γ�Ⱥ�ƽ���߶�
	double      m_Center_Geo_dB;
	double      m_Center_Geo_dL;
	double      m_Center_Geo_dH;
};

//ȫ�׶����ݴ���
class QPDGeoPOSProcess : public GeoPOSProcess
{
public:
	friend class QPDLevel2Process;

	//��ȡPOS����
	virtual long GeoPOSProc_ReadPartPOS(const char* pPOSFile,int nLines,int nBeginLine);

	//��SBET�ļ��н����POS����
	virtual long GeoPOSProc_ExtractSBET(const char* pathSBET, const char* pathEvent, const char* pathPOS, float fOffsetGPS = 17);

	//��ȡEOԪ�ص�����
	virtual long GeoPOSProc_GetEOLines(const char *pEoFile, int &nEOLines);
};

class UAVGeoPOSProcess : public GeoPOSProcess
{
public:
	friend class LevelUAVProcess;

public:
	//��ȡPOS���ݣ�����ʼ�ж�ȡָ��������POS����
	virtual long GeoPOSProc_ReadPartPOS(const char* pPOSFile,int nLines,int nBeginLine);

	//��SBET�н�����POS���ݣ�Ӧ���ò��ϣ�
	virtual long GeoPOSProc_ExtractSBET(const char* pSBETFile,const char* pEVENTFile,const char* pPOSFile,float fOffsetGPS = 17){return 0;}
public:
	//���ö�ȡPOS���ݸ�ʽ
	//���ȿ���ΪdL/longitude��1 γ��ΪdB/latitude��2 �߶�ΪdH/height��3 ��Ԫ��Ϊ roll-pitch-yaw����4��5��6�������з��Ŷ�Ϊ���λ 0
	long GeoPOSProc_SetPOSFormat(char* formatStr,bool arc);
	
	//�ɵ���POS���ݽ���õ�EOԪ��
	long GeoPOSProc_ExtractEO(POS m_perpos, EO &m_pereo);

private:
	//POS���ݸ�ʽ
	vector<int> formatVec;
	bool        m_arc;
};