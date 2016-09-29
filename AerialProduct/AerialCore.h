//����ͷ�ļ��Ķ���
//author��	��ε
//version:	2.0
#include "stdafx.h"

#ifndef AERIAL_CORE_H_
#define AERIAL_CORE_H_
#include<string>
#include<vector>
using namespace std;

//���峣��
#define LOG_FILE_PATH 
#define PI 3.14159265358979323846264338
#define MAX_NUM  99999999
#define MIN_NUM -99999999
#define WGS84LRadius 6378137
#define WGS84Eccentricity 0.0066943850
#define EQUAL_LIMIT 0.000001
const double LIMIT = 0.00003;
#define OVER_LIMIT( var) fabs(var)>LIMIT
#define ISEQUAL(a,b) (fabs(a-b)) < EQUAL_LIMIT  ? true : false

//�����ݽṹ�Ķ���
//��ά�����ά�����ݽṹ
struct CPOINT
{
	int x;
	int y;
};
struct DPOINT
{
	double dX;
	double dY;
};
typedef struct FPOINT
{
	float x;
	float y;
}Pointf;
struct THREEDPOINT
{
	double dX;
	double dY;
	double dZ;
};
typedef struct F3POINT
{
	float x;
	float y;
	float z;
}Point3f;
struct MatchPair
{
	int img1_idx;		//Ӱ��ı��
	int img2_idx;

	//vector<int> pnt_idx;//ƥ���ı��2*i+0��2*i+1;
};

//EO��PO�͵Ͱ��Զ���Ԫ�����ݽṹ�Ķ���
typedef struct stExteriorOrientation
{
	//������Ԫ��
	double m_dX;
	double m_dY;
	double m_dZ;

	//������Ԫ��
	double m_phia;
	double m_omega;
	double m_kappa;

	//��ת����
	double m_dRMatrix[9];

	void PrintStruct()
	{
		printf("��Ԫ�أ�(%lf)����(%lf)����(%lf)\n",m_dX,m_dY,m_dZ);
		printf("��Ԫ�أ�(%lf)����(%lf)����(%lf)\n",m_phia,m_omega,m_kappa);
		printf("��ת����:\n");
		printf("(%lf)-(%lf)-(%lf)\n",m_dRMatrix[0],m_dRMatrix[1],m_dRMatrix[2]);
		printf("(%lf)-(%lf)-(%lf)\n",m_dRMatrix[3],m_dRMatrix[4],m_dRMatrix[5]);
		printf("(%lf)-(%lf)-(%lf)\n",m_dRMatrix[6],m_dRMatrix[7],m_dRMatrix[8]);
	}
}EO;
typedef struct stPositOrientationSys
{
	//��γ�Ⱥ͸߶�
	double m_latitude;
	double m_longitude;
	double m_height;

	//�����������ƫ��
	double m_roll;
	double m_pitch;
	double m_yaw;
}POS;
typedef struct stRelativeOrientation
{
	//������Ԫ��
	double m_Bx;
	double m_By;
	double m_Bz;
	//������Ԫ��
	double m_phia;
	double m_omega;
	double m_kappa;

	//��ת����
	double m_dRMatrix[9];
	void PrintStruct()
	{
		printf("��Ԫ�أ�(%lf)����(%lf)����(%lf)\n",m_Bx,m_By,m_Bz);
		printf("��Ԫ�أ�(%lf)����(%lf)����(%lf)\n",m_phia,m_omega,m_kappa);
		printf("��ת����:\n");
		printf("(%lf)-(%lf)-(%lf)\n",m_dRMatrix[0],m_dRMatrix[1],m_dRMatrix[2]);
		printf("(%lf)-(%lf)-(%lf)\n",m_dRMatrix[3],m_dRMatrix[4],m_dRMatrix[5]);
		printf("(%lf)-(%lf)-(%lf)\n",m_dRMatrix[6],m_dRMatrix[7],m_dRMatrix[8]);
	}
}REO;
typedef struct stSetupGroundControl
{
	//Ӱ���У�Ŀ��Ƶ�
	int m_Img_xPnt;
	int m_Img_yPnt;
	//WGS84����UTM����ϵ�µ�����
	double m_Ground_xUTMPnt;
	double m_Ground_yUTMPnt;
}SetupGCP;

//���ո߹�������ͷ��Ϣ
typedef struct stDataInfo
{
	unsigned int	nSensorType;
	unsigned int	nSensorOrder;
	unsigned int	nWidths;
	unsigned int	nSamples;
	unsigned int	nLines;
	unsigned int	nBands;
	unsigned int	nYear;
	unsigned int	nMonth;
	unsigned int	nDay;
	unsigned int	nSecond;
	unsigned int	nMode;
	__int64 nHeadOffset;
	__int64 nEofOffset;
}DINFO;

struct MapInfo {
	string projection;	//ͶӰ
	string directions;  //����
	double adfGeotransform[6];//������Ϣ
	int    zone;
};
typedef struct stImgHeader {
	//Ӱ�������Ϣ
	int imgWidth;
	int imgHeight;
	int imgBands;

	bool byteorder;	//�ֽ�˳�� һ����0 ����ĳЩ����ϵͳ�ֽڿ�����С����
	int  datatype;

	bool    bimgGeoProjection;	//�Ƿ����ͶӰ��Ϣ
	MapInfo mapInfo;			//ͶӰ�ֶ�
	string coordianteSys;	//�����ֶ�

	string interleave;		//Ӱ���Ų���ʽ

	//Ĭ����ʾ����
	bool bimgDefaultBands;
	vector<int> imgDefaultBands;

	//������
	bool bimgBandNames;
	vector<string> imgBandNnames;

	//������Ϣ
	bool bimgWaveLength;
	vector<float> imgWaveLength;

	//�벨����Ϣ
	bool bimgFWHM;
	vector<float> imgFWHM;

	//дͷ�ļ���Ϣ������1.ֻд������ͷ�ļ���Ϣ��2.д���ڵ�ͷ�ļ���Ϣ��3.д����ͷ�ļ���Ϣ
	bool WriteHeaderBasic(const char* pathHeader);
	bool WriteHeaderExist(const char* pathHeader);
	bool WriteHeaderTotal(const char* pathHeader);

}ENVIHeader;

//SBET�ļ��ṹ,һ����˵Ҫ��SBET�ļ�������POS����������һ���ܹ��õõ�����ֱ�������
typedef struct stSbetElement
{
	double dGpsTime;
	double dLatitude;
	double dLongitude;
	double dHeight;
	double dVx;
	double dVy;
	double dVz;
	double dRoll;
	double dPitch;
	double dHeading;
	double dWander;
	double dAx;
	double dAy;
	double dAz;
	double dArx;
	double dAry;
	double dArz;
}SBETELEMENT;

//Դ�����Լ������ļ����ݽ�������
struct ParamMeta
{
	int m_nSensorType;	
	int m_nSensorOrder;
	int m_nWidth;
	int m_nSamples;
	int m_nLines;
	int m_nBands;
	int m_nYear,m_nMonth,m_nDay,m_nSecond;
	__int64 m_nHeadOffset;
	__int64 m_nEofOffset;
	bool m_bDark;
	int m_DarkLine;
};
struct ParamPre
{
	//����·��
	vector<string> m_pRawFile;
	vector<string> m_pDarkFile;

	//���·��
	vector<string> m_pD0File;
	vector<string> m_pD0DarkFile;
	vector<string> m_pD0XMLFile;
	vector<string> m_pD0JPG;

	bool m_bSegment;		//�Ƿ���з־�
	int  m_nSegBeginLine;	//�־�����ʼ��
	int  m_nSegEndLine;		//�־�����ֹ��
	int  m_nAutoSegLine;	//�Զ��־�������

	bool m_bQuickView;		//�Ƿ��п���ͼ
	bool m_bGrey;			//�Ƿ�Ϊ��ͼ
	float m_fScale;			//����ͼ��������
	int m_nUVBand[3];		//�������ͼ����
	int m_nVNIRBand[3];		//�ɼ����������ͼ����
	int m_nSWIRBand[3];		//�̲��������ͼ����
	int m_nTIHBand[3];		//�Ⱥ������ͼ����

	string m_pProFile;		//��������ļ�
};
struct ParamP0
{
	vector<string> m_pD0File;	//0������
	vector<string> pD0MetaXML;	//0������Դ�ļ�
	vector<string> pD0DarkFile;
	vector<string> m_pP0Product;
	vector<string> m_pP0ProductXML;
	vector<string> m_pP0JPG;
	vector<string> m_pEvent;
	bool m_bQuickView;
	bool m_bGrey;
	float m_fScale; 
	int m_nUVBand[3];
	int m_nVNIRBand[3]; 
	int m_nSWIRBand[3]; 
	int m_nTIHBand[3];
	string m_pProFile;

};
struct ParamP1
{
	vector<string> m_pD0File;	//0������
	vector<string> pD0MetaXML;	//0������Դ�ļ�
	vector<string> pD0DarkFile;
	short m_nP0,  m_nP1A,  m_nP1B,  m_nP1C,  m_nP1D,  m_nP1E;
	vector<string> m_pP0Product;
	vector<string> m_pP0ProductXML;
	vector<string> m_pP0JPG;
	vector<string> m_pP1AData;
	vector<string> m_pP1AXML;
	vector<string> m_pP1AJPG;

	vector<string> m_pP1BData;
	vector<string> m_pP1BXML;
	vector<string> m_pP1BJPG; 

	vector<string> m_pP1CData; 
	vector<string> m_pP1CXML; 
	vector<string> m_pP1CJPG;

	vector<string> m_pP1DData; 
	vector<string> m_pP1DXML; 
	vector<string> m_pP1DJPG; 

	vector<string> m_pP1EData; 
	vector<string> m_pP1EXML; 
	vector<string> m_pP1EJPG;

	vector<string> &m_pReleCof; 
	vector<string> &m_pAbCof;
	string m_pModtran; 
	vector<string> m_pWaveLen; 
	vector<string> m_pEvent;
	float m_fFOLapX[8],  m_fFOLapY[8],  m_fSOLapX[3],  m_fSOLapY[3];
	bool m_bQuickView;
	bool m_bGrey;
	float m_fScale; 
	int m_nUVBand[3];
	int m_nVNIRBand[3]; 
	int m_nSWIRBand[3]; 
	int m_nTIHBand[3];
	string m_pProFile;
};
struct ParamP2
{
	vector<string> m_pD0File;	//0������
	vector<string> pD0MetaXML;	//0������Դ�ļ�
	vector<string> pD0DarkFile;
	short m_nP0,  m_nP1A,  m_nP1B,  m_nP1C,  m_nP1D,  m_nP1E;
	vector<string> m_pP0Product;
	vector<string> m_pP0ProductXML;
	vector<string> m_pP0JPG;
	vector<string> m_pP1AData;
	vector<string> m_pP1AXML;
	vector<string> m_pP1AJPG;

	vector<string> m_pP1BData;
	vector<string> m_pP1BXML;
	vector<string> m_pP1BJPG; 

	vector<string> m_pP1CData; 
	vector<string> m_pP1CXML; 
	vector<string> m_pP1CJPG;

	vector<string> m_pP1DData; 
	vector<string> m_pP1DXML; 
	vector<string> m_pP1DJPG; 

	vector<string> m_pP1EData; 
	vector<string> m_pP1EXML; 
	vector<string> m_pP1EJPG;

	vector<string> m_pP2AData; 
	vector<string> m_pP2AXML; 
	vector<string> m_pP2AJPG;

	vector<string> m_pP2BData; 
	vector<string> m_pP2BXML; 
	vector<string> m_pP2BJPG;

	vector<string> m_pP2CData; 
	vector<string> m_pP2CXML; 
	vector<string> m_pP2CJPG;

	vector<string> &m_pReleCof; 
	vector<string> &m_pAbCof;
	string m_pModtran; 
	vector<string> m_pWaveLen; 
	vector<string> m_pEvent;
	string m_pSBETFile;
	vector<string> m_pPOSFile;
	vector<string> m_pEOFile;
	string m_pDEMFile;

	float m_fFOLapX[8],  m_fFOLapY[8],  m_fSOLapX[3],  m_fSOLapY[3];
	float m_fFov[4], m_fIFov[8], m_fFocalLen[4];
	double m_dBoresightMis[3], m_dGNSSOffset[3], m_dXYZOffset[3];
	int m_nBand[4], m_nSamples[4];
	bool m_bQuickView;
	bool m_bGrey;
	float m_fScale; 
	int m_nUVBand[3];
	int m_nVNIRBand[3]; 
	int m_nSWIRBand[3]; 
	int m_nTIHBand[3];
	string m_pProFile;

};


#endif