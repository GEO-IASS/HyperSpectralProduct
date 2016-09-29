#pragma once
#include "Level2Process.h"
#include "opencv/include/opencv2/core/core.hpp"
#include "opencv/include/opencv2/imgproc.hpp"
#include "opencv/include/opencv2/highgui/highgui.hpp"
#include "opencv/include/opencv2/calib3d.hpp"
#include "opencv/include/opencv2/stitching/detail/camera.hpp"
#include "opencv/include/opencv2/stitching/detail/matchers.hpp"

class LevelUAVProcess : public Level2Process
{
//����POS���ݶ����˻�Ӱ����м���У��
public:
	//����2�����������Ľӿ�
	virtual long Level2Proc_Interface(const char* pathOrderFile){return 0;}
	//�ӿ�
	long Level2Proc_Product2A(const char *pFile, const char *pCFile, const char *pEOFile, float fGSDX, float fGSDY, double fElevation, int nEOOffset,
		float fFov, float fIFov, float fFocalLen, bool bIGM, const char *pIGMFile, bool bInverse = false){return 0;}
	//�ӿ�
	//��2A�����ݲ�Ʒ�����������2B�����ݲ�Ʒ����������Ҫ���ӵĽӿ�ΪDEM����·����������·��ΪNULL���������ͬ���������DEM������DEM���н���
	long Level2Proc_Product2B(const char *pFile, const char *pCFile, const char *pEOFile, float fGSDX, float fGSDY, double fElevation, int nEOOffset,
		float fFov, float fIFov, float fFocalLen, const char* pDEMFile, bool bIGM, const char *pIGMFile, bool bInverse = false){return 0;}
//////////////////////////////////////////////////////////////////////////
	//1.��Ӱ�񼯽���У��
	long UAVGeoCorrection_GeoCorrect(const char* pathSrcDir, const char* pathDstDir, const char* pathPOS, const char* pathDEM,int IMGbegline, int POSbegline, int lines,double fLen , double fGSD, double AvgHeight);

	//2.�Ե���Ӱ�����У��
	long UAVGeoCorrection_GeoCorrect(const char* pathSrc, const char* pathDst, EO  m_preeo, double dL, double dB, double fLen, double fGSD, double AvgHeight, char* pathDEM = NULL);

	//3.����ÿ����ĵ�������
	long UAVGeoCorrection_GeoPntsProb(double dB, double dL, double dH, EO pEO, double fLen, int width, int height, THREEDPOINT *pGoundPnt, DPOINT* pMapImgPnt, int pntNum);

	//4.��ȷ����ÿ���������Ȼ�����У��
	long UAVGeoCorrection_GeoPntsAccu(double dB, double dL, double dH, EO pEO, double fLen, int width, int height, THREEDPOINT *pGoundPnt,const char* pathDEM);

	//���ݲ���
	long UAVGeoCorrect_Test();

public:
	double m_ccdSize;	/*����ת��Ϊm������*/
	double m_x0;		//����������
	double m_y0;
	char   m_posFormat[128];
};

//�������ǲ�������
class LevelAerialTriangle
{
public:
	//��ʼ��
	LevelAerialTriangle(){
		m_mat[0]=1;m_mat[1]=0;
		m_mat[2]=0;m_mat[3]=1;
		m_x0=m_y0=0;
		m_flen=153033;	//��������ǲ������ݵĽ���
		m_pixel_size=1;
	}

	//Ӱ���ڶ���
	virtual long LevelATProc_InnerOrientation(vector<Pointf> &pnt,vector<Pointf> &pntInner);

	//������Ӱ���л�ȡӰ��ƥ���
	//�Կ�������Ҫ�Դ�Ƚϴ���Կ��������Դ治��û���ﵽ��Ҫ��Ч��
	//����Ӱ���ƥ��ʵ����ֻ�ǲ��Ժ������ѣ���Ϊʵ��ƥ�䲻������������
	//ʵ��ƥ��õ���Ӧ����Ӱ��ƥ����idx�������㣬Ȼ������������û���õĵ�
	virtual long LevelATProc_GetMatchPntsTest(const char* path1,const char* path2);
	//����Ӱ��ƥ���
	virtual long LevelATProc_MatchExtract(vector<string> imageList,vector<MatchPair> &match_pairs,vector<vector<Pointf>> &featureList);

	//Ӱ��ƥ���
	virtual long LevelATProc_MatchFeature(vector<string> imageList,vector<cv::detail::ImageFeatures> &fetures,vector<cv::detail::MatchesInfo> &match_pairs);

	//��������������Ϊ��ʾ����Ҫ�����Դ�ENVI���뵼������鿴
	//��ENVI�ж�ȡӰ��ƥ���
	virtual long LevelATProc_ReadENVIPts(const char* pathENVI);
	//���㵼����ENVI��
	virtual long LevelATProc_SaveAsENVI(const char* pathENVI);

protected:
	vector<Pointf> m_matchPoint;//����������Ϊһ��ƥ����
	int m_mat[4];				//��������Ϊ��λ��Ӱ��ת��Ϊ��mmΪ��λ
	int m_x0,m_y0,m_flen;
	float m_pixel_size;
};

//�������������ǲ�����������Ӱ������һϵ�д���
//ֻ����һ������������Ժ;��Զ���(Ӱ��˳��Ϊ�����ҵ�˳��)
class LevelFlightLineAT: public LevelAerialTriangle
{
public:
	//��Զ�������Ӱ��ƥ��㣬���Ϊ��Զ���Ԫ��
	virtual long LevelATProc_RelativeOrientation(vector<Pointf> pnt1,REO &relOrientation1,vector<Pointf> pnt2,REO &relOrientation2);

	//��ȡӰ��ģ�͵�����
	virtual long LevelATProc_ModelPoint(vector<Pointf> pnt1,REO &relOrientation1,vector<Pointf> pnt2,REO &relOrientation2,vector<Point3f> &modelPoint);
	
	//ģ�͵������һ��������ģ�͵���������
	//�����ǵ�����ģ�ͣ�����Ӱ��ƥ��һ���Ǵ���������ƥ��
	virtual long LevelATProc_ModelPointNorm(vector<vector<Pointf>> &imgPntList,vector<vector<Point3f>> &modelPointList,vector<Point3f> &phoCoordi,vector<REO> &relOrientationList);


	//���Զ�������Ӱ��ƥ��㣬������Զ���Ԫ��
	virtual long LevelATProc_AbsluteOrientation(vector<SetupGCP> pntGcps,EO &absEO){return 0;}

public:
	void LevelATProc_RelativeOrientationTest();
	
};

//���ü�����Ӿ��ķ�������ͼ��任����Ĺ��ƣ��������ǹ���Ӱ��ĵ�Ӧ����Ȼ��ͨ����Ӧ�������������������й�����ƽ��
//
class LevelFlightLineComputerVision : public LevelAerialTriangle
{
public:
	//����Ӱ��֮��ĵ�Ӧ����
	virtual long LevelATProc_HomographyMatrix(vector<vector<Pointf>> &imgPntList,vector<cv::Mat> &homoMatrixList);

	//������������Ӧ����
	virtual long LevelATProc_HomoBundler(vector<vector<Pointf>> &imgPntList,vector<cv::Size> &imgSizeList,vector<cv::Mat> &homoMatrixList,vector<cv::detail::CameraParams> &vec_Cameras);
	virtual long LevelATProc_HomoBundler(vector<cv::detail::ImageFeatures> &fetures,vector<cv::detail::MatchesInfo> &match_pairs,vector<cv::detail::CameraParams> &vec_Cameras);

private:
	//���ݵ�Ӧ�������Ӱ��Ľ���
	virtual long LevelATProc_HomographyFocal(vector<vector<Pointf>> &imgPntList,vector<cv::Size> &imgSizeList,vector<cv::Mat> &homoMatrixList,vector<double> &focals);

public:
	void LevelATProc_HomographTest();

};