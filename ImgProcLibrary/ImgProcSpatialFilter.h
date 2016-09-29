#pragma once

#ifndef _SPFilter_
#define _SPFilter_

//GDAL��װ
#include <vector>
#include <algorithm>

#ifndef PI
#define PI 3.1415926534
#endif

#ifndef DllExport
#define DllExport   __declspec( dllexport)
#endif

#include "..\gdal/include/gdal_priv.h"
#pragma comment(lib,"..//GDAL//lib//gdal_i.lib")
#include "ImgProcBlock.h"

using namespace std;

//Ӱ������˲�
class DllExport spFilter
{
public:

	//���캯��������������ʼ��
	spFilter(){
		m_is_core=false;
		m_Filter_core=NULL;
	}
	~spFilter(){
		if (m_is_core&&m_Filter_core!=NULL)
		{
			for (int i=0;i<m_core_ysize;i++)
			{
				delete[]m_Filter_core[i];
			}
			delete[]m_Filter_core;
		}
	}

	//�����˲���
	void spFilterCore(float** core,int xsize,int ysize);
	void spFilterCore(float*  core,int xsize,int ysize);

	//�����˲�����
	//GDAL��װ
	void spitalFilter(char* pathSrc,char* pathDst,int xpos,int ypos,int xoffset,int yoffset);
	void spitalFilter(char* pathSrc,char* pathDst);

	//������˹���ӽ����˲�
	void LaplaceFilter(char* pathSrc,char* pathDst,int xpos,int ypos,int xoffset,int yoffset);
	void LaplaceFilter(char* pathSrc,char* pathDst);

	//sobel���ӽ����˲�
	void SobelFilter(char* pathSrc,char* pathDst,int xpos,int ypos,int xoffset,int yoffset);
	void SobelFilter(char* pathSrc,char* pathDst);

	//��ֵ�˲�
	void MeanFilter(char* pathSrc,char* pathDst,int xpos,int ypos,int xoffset,int yoffset);
	void MeanFilter(char* pathSrc,char* pathDst);

	//0ֵ�˲�
	void ZeroFilter(char* pathSrc,char* pathDst,int xpos,int ypos,int xoffset,int yoffset);
	void ZeroFilter(char* pathSrc,char* pathDst);


	//��ֵ�˲�
	void MedFilter(float*imgBufferIn,int width,int heigh,int xpos,int ypos,
		int xoffset,int yoffset,int xfsize,int yfsize,float* imgBufferOut);
	void MedFilter(char* pathSrc,char* pathDst,int xpos,int ypos,int xoffset,int yoffset);
	void MedFilter(char* pathSrc,char* pathDst);


	//�˲�������
	void spFilterOperation(float*imgBufferIn,int width,int heigh,int xpos,int ypos,int xoffset,int yoffset,float* imgBufferOut);
private:

	//�˲�������
	float __fastcall spFilterOperationCore(float*imgBufferIn,int xpos,int ypos);

	//��Ա����
	bool m_is_core;				//�˲����Ƿ����
	int m_core_xsize;			//�˲���x�ߴ��С
	int m_core_ysize;			//�˲���y�ߴ��С
	int m_width;				//Ӱ���width
	int m_heigh;				//Ӱ���heigh
	float **m_Filter_core;		//Ӱ���˲���
};


//���ø�˹�˲��˺���
long DllExport SetGaussCore(float **kernel,float sigma, int xsize=3,int ysize=3);
long DllExport SetGaussCore(float *kernel, float sigma, int xsize=3,int ysize=3);


//Ӱ����и�˹�˲�
long DllExport GaussFilter(float *srcImg,float *dstImg,int xImg,int yImg,float ** kernel,int xkernel=3,int ykernel=3);

//GDAL��װӰ���˹�˲�
long DllExport GaussFilter(char* pathSrc,char* pathDst,float** kernel, int xkernel=3, int ykernel=3);


//���и�˹���
long DllExport GaussDifference(float* srcImg1,float* srcImg2,float* dstImg,int xImg,int yImg);

//GDAL��װ�ĸ�˹���
long DllExport GaussDifference(char* pathsrc1,char* pathsrc2,char* pathdst);


//  [2/6/2015 wuwei just you]
//TODO��Ӱ��ֿ�����˲����˲���Ӱ��ֿ�д���ļ���
//		���Ӷ��̴߳����������Ч��
//Ӱ��ֿ��˲�
long DllExport ImageSpaitalBlockFilter(char* pathsrc,char* pathdst,float* FilterCore,int xcoresize,int ycoresize);

//���߳�Ӱ��ֿ��˲�
long DllExport ThreadImageSpaitalFilter(char* pathsrc,char* pathdst,float* FilterCore,int xcoresize,int ycoresize);


//  [4/11/2015 wuwei just you]
//Ӱ����̬ѧ�˲�����̬ѧ�˲������Ͼ������ֵ����Сֵ�˲�
//���ú��ʵ��˲����ں��˲������ĵ�λ��
class DllExport MorphologyFilter
{
	//���캯��������������ʼ��
	MorphologyFilter(){
		m_is_core=false;
		m_Filter_core=NULL;
	}
	~MorphologyFilter(){
		if (m_is_core&&m_Filter_core!=NULL)
		{
			for (int i=0;i<m_core_ysize;i++)
			{
				delete[]m_Filter_core[i];
			}
			delete[]m_Filter_core;
		}
	}

	//������̬ѧ�˲���
	void MorphologyCore(float** core,int xsize,int ysize,int centerx,int centery);
	void MorphologyCore(float*  core,int xsize,int ysize,int centerx,int centery);

	//��̬ѧ��ʴ
	void MorphologyCorrode(float* dataIn,int sizex,int sizey,int bands,float* dataOut);

	//��̬ѧ����
	void MorphologyDilation(float* dataIn,int sizex,int sizey,int bands,float* dataOut);

	//GDAL��װ����̬ѧ��ʴ������
	//��̬ѧ��ʴ
	void MorphologyCorrode(char* pathIn,char* pathOut);

	//��̬ѧ����
	void MorphologyDilation(char* pathIn,char* pathOut);

private:
	//��Ա����
	bool m_is_core;				//�˲����Ƿ����
	int m_core_xsize;			//�˲���x�ߴ��С
	int m_core_ysize;			//�˲���y�ߴ��С
	int m_width;				//Ӱ���width
	int m_heigh;				//Ӱ���heigh
	int m_centerx;				//�˲�������xλ��
	int m_centery;				//�˲�������yλ��
	float **m_Filter_core;		//Ӱ���˲���
};

#endif
//  [4/9/2014 wuwei just you]
//	version 1.0Ӱ��Ŀռ����˲��͸�˹�˲�
