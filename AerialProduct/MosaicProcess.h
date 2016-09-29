#pragma once
#include <vector>
#include "opencv/include/opencv2/core/core.hpp"
#include "opencv/include/opencv2/stitching/detail/camera.hpp"
using namespace  std;

class MosaicProcessHomo
{
public:
	//ͼ��ƴ�Ӵ����ȡƴ�Ӻ�Ӱ��ķ�Χ
	void MosaicProc_Range(vector<string> imgList,cv::Point2f &pntMin,cv::Point2f &pntMax,vector<cv::Mat> homoList);

	//Ӱ��ƴ��
	void MosaicProc_Mosaic(vector<string> imgList,const char* pathOut,cv::Point2f pntMin,cv::Point2f pntMax,vector<cv::Mat> homoList);
};

class MosaicProcessRoationTranslate
{
public:
	//ͼ��ƴ�Ӵ����ȡƴ�Ӻ�Ӱ��ķ�Χ
	void MosaicProc_RangePlane(vector<string> imgList,cv::Point2f &pntMin,cv::Point2f &pntMax,vector<cv::detail::CameraParams> &cameras);

	//Ӱ��ƴ��
	void MosaicProc_MosaicPlane(vector<string> imgList,const char* pathOut,cv::Point2f pntMin,cv::Point2f pntMax,vector<cv::detail::CameraParams> &cameras);

private:
	//ת��Ϊ������ʽ
	void MosaicProc_TransMat(cv::detail::CameraParams &camera,double* rot,double* trans);
};

