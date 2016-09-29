#pragma once 

//��Ԫ������Ľ�����Ƿ��Ӱ��
//��˶�ȡ��ȵ�ʱ��Ҳ�Ƕ�ȡ���Ӱ��
class HyperSpectralEndMember
{
public:
	//��ȡ��Ԫ���ף�ENVI��ʽ��
	bool HyperSpectralEnd_ImportEndmember(const char* pathEnd,int bands,int endnumbers,float* endmember);
	bool HyperSpectralEnd_ImportEndmember(const char* pathEnd,int bands,int endnumbers,double* endmember);

	//����Ԫ����������ļ���
	void HyperSpectralEnd_ExportEndmember(const char* path,float *enddata,int bands,int endnumbers);
	void HyperSpectralEnd_ExportEndmember(const char* path,double *enddata,int bands,int endnumbers);

	//��С���˹��׽��
	void HyperSpectralEnd_UnmixLSE(const char* pathEnd,char* pathImg,const char* pathRed,int endnumbers);
	//ʹ���ض����ν�����С���˽��
	void HyperSpectralEnd_UnmixLSE_SetBands(const char* pathEnd,const char* pathImg,const char* pathRed,int endnumbers,int* bandIdx,int bandIdxNum);

	//������в�
	void HyperSpectralEnd_Residual(const char* pathimg,const char* pathend,const char* pathred,const char* pathres,int endnumbers);

	//�������ķ�Ƚ������(�����Ϸ�Ⱥ�Ӧ�õ���1)
	void HyperSpectralEnd_ReduTotal(const char* pathRed,const char* pathTotal);

	//������Ӧ����
	//ͨ���߹��׶�Ԫ��ȡ����׶�Ԫ
	//�ж�������Ķ���ײ��ε�ÿ�����ι��׷�Χ�������Ĳ���
	//��������Ĳ�������ͨ���Ƚϲ�������ĸ߹��ײ��μ��������Ӧ
	//����ǹ��׷�Χ��ѡ��Χ�ڵĸ߹��ײ��μ��������Ӧ
	/*
		char* pathHy:����ĸ߹��׶�Ԫ
		char* pathM	:����Ķ���׶�Ԫ
		float* hysp int bandsHy:�߹��ײ��ε����Ĳ���&������
		float* msp  int bandm:����ײ��ε����Ĳ����򲨳���Χ&������
		int endnumber:	��Ԫ��Ŀ
		bool range:�ж�������ǹ��׷�Χ�������Ĳ���
	*/
	void HyperSpectralEnd_Response(const char* pathHy,const char* pathM,float* hysp,int bandsHy,float* msp,int bandm,int endnumber,bool range);
	void HyperSpectralEnd_Response_Image(const char* pathHyImage,const char* pathMImage,float* hysp,int bandsHy,float* msp,int bandm,int endnumber,bool range);

	//�ռ����ɢ���������ø�˹�������н�����
	void HyperSpectralEnd_Spatial_Spread(const char* pathImg,const char* pathSample);
};