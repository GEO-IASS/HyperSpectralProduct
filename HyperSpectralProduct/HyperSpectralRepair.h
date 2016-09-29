/************************************************************************/
/*                       �߹���Ӱ���޸�����                             */
/************************************************************************/
#include <vector>
using namespace std;

#define _MAX_MATCH_DIS_ 9999999

struct RepairEdgePnt
{
	int x;
	int y;
};

class HyperSpectralRepair
{
public:
	//�����޸�
	virtual void HyperSpecRepair_RepairImage(const char* image,const char* imgMsk,const char* imageRepair) = 0;

	virtual void HyperSpecRepair_MakeRepairMaskRect(const char* image,const char* imgMsk,const char* imageRepair,RepairEdgePnt edgePnts[]);

protected:
	//��ȡӰ����޸�����߽��
	virtual void HyperSpecRepair_GetEdges(const unsigned char* imageMask,const int xsize,const int ysize,vector<RepairEdgePnt> &edgePnts);

	//��ȡ���д��޸��ĵ�
	virtual void HyperSpecRepair_GetRepair(const unsigned char* imageMask,const int xsize,const int ysize,vector<RepairEdgePnt> &edgePnts);

	//��ȡ���޸�����Χģ������
	virtual void HyperSpecRepair_GetTemplate(const float* imageBuffer,const unsigned char* imageMask,const int &xsize,const int &ysize,
																	const int &templateSize,const int &xpos,const int &ypos,float* imgTemplate)
	{
		int leftpos =max(min(xsize-1,xpos-templateSize),0);
		int rightpos=max(min(xsize-1,xpos+templateSize),0);
		int uppos   =max(min(ysize-1,ypos-templateSize),0);
		int bottompos=max(min(ysize-1,ypos+templateSize),0);

		for (int i=leftpos,m=0;i<rightpos;++i,++m)
		{
			for(int j=uppos,n=0;j<bottompos;++j,++n)
			{
				if(imageMask[j*xsize+i]!=0)
					imgTemplate[n*templateSize+m]=imageBuffer[j*xsize+i];
			}
		}
	}

	//��ָ�������ģ��ƥ��
	float HyperSpecRepair_MatchTemplate(const float* imageBuffer,const unsigned char* imageMask,const int &xsize,const int &ysize,
															  const int &templateSize,const int &xpos,const int &ypos,const float* imgTemplate)
	{
		int leftpos =max(min(xsize-1,xpos-templateSize),0);
		int rightpos=max(min(xsize-1,xpos+templateSize),0);
		int uppos   =max(min(ysize-1,ypos-templateSize),0);
		int bottompos=max(min(ysize-1,ypos+templateSize),0);

		float matchconf = 0.0f;
		int totalNum =0 ;
		for (int i=leftpos,m=0;i<rightpos;++i,++m)
		{
			for(int j=uppos,n=0;j<bottompos;++j,++n)
			{
				if(imageMask[j*xsize+i]==0)
					return _MAX_MATCH_DIS_;
				if(imgTemplate[n*templateSize+m]!=0)
				{
					matchconf+=fabs(imgTemplate[n*templateSize+m]-imageBuffer[j*xsize+i]);
					totalNum++;
				}
			}
		}
		return matchconf/*/float(totalNum)*/;
	}
};


//ƫ΢�ַ��̵��޸�����
class HyperSpectralRepairPDE : public HyperSpectralRepair
{
public:
	//����BSCB�޸�
	virtual void HyperSpecRepair_RepairImage(const char* image,const char* imgMsk,const char* imageRepair);

	//�޸��ĵ�������
	void HyperSpecRepair_Iter(float* image,float* repairImage,int xsize,int ysize);

private:
	//��Ϣ��ɢ����
	void HyperSpecRepair_Diffusion(float* image,float* imageDiffus,int xsize,int ysize,int xpos,int ypos);
	//�����޸��Ĺ���
	void HyperSpecRepair_RepairPnt(float* image,float* imageRepair,float delta,int xsize,int ysize,int xpos,int ypos);
	//�����ݶȲ��
	float HyperSpecRepair_Laplace(float* image,int xsize,int ysize,int xpos,int ypos);
	//�޸���ʼ��
	void HyperSpecRepair_Init(float* image,float* imageInit,float* imgMsk,int xsize,int ysize);

};

enum RepairType
{
	OD_POINT,	//˳������޸�
	OD_BLOCK,	//˳������޸�
	CD_POINT,	//���Ŷ�����޸�
	CD_BLOCK,	//���Ŷ�����޸�
	EP_POINT    //�߽���������޸�
};
//Ӱ��ģ��ƥ����޸�����
class HyperSpectralRepairExemplar : public HyperSpectralRepair
{
public:
	//����BSCB�޸�
	void HyperSpecRepair_SetMethod(RepairType repair_type=EP_POINT);
	virtual void HyperSpecRepair_RepairImage(const char* image,const char* imgMsk,const char* imageRepair);

	//��������
	void HyperSpecRepair_TestExample();

private:
	RepairType m_repair_type;
	
protected:
	//��ͬ���޸���ʽ�ӿ�
	void HyperSpecRepair_Repair_OD_POINT(const char* image,const char* imgMsk,const char* imageRepair);
	void HyperSpecRepair_Repair_OD_BLOCK(const char* image,const char* imgMsk,const char* imageRepair);
	void HyperSpecRepair_Repair_CD_POINT(const char* image,const char* imgMsk,const char* imageRepair);
	void HyperSpecRepair_Repair_CD_BLOCK(const char* image,const char* imgMsk,const char* imageRepair);
	void HyperSpecRepair_Repair_EP_POINT(const char* image,const char* imgMsk,const char* imageRepair);

private:
	//��������޸�
	void HyperSpecRepair_RepairPoint(float* image,unsigned char* imgMsk,int xsize,int ysize,int xpos,int ypos);
	void HyperSpecRepair_RepairBlock(float* image,unsigned char* imgMsk,int xsize,int ysize,int xpos,int ypos);

	//���������޸�
	void HyperSpecRepair_Iterator(float* image,unsigned char* imgMsk,int xsize,int ysize,RepairType repair_type=EP_POINT);
	//����߽��޸����Ŷ�
	RepairEdgePnt HyperSpecRepair_MaxConfPnt(float* image,unsigned char* imgMsk,int xsize,int ysize,vector<RepairEdgePnt>&edgePnts);

	//����Np��Ip
	void HyperSpecRepair_IP(float* image,unsigned char* imgMsk,int xsize,int ysize,int xpos,int ypos,float* ip);
	void HyperSpecRepair_NP(float* image,unsigned char* imgMsk,int xsize,int ysize,int xpos,int ypos,float* np);

};

//Ӱ���������޸�����
class HyperSpectralRepairSpecral : public HyperSpectralRepair
{
public:
	void HyperSpecRepair_RepairImage(const char* image,const char* imgMsk,const char* imageRepair){}

	void HyperSpecRepair_TestExample();

private:
	//���ֹ��׷�Χ�Ĺ���ƥ��
	void HyperSpecRepair_PartSpectralMacth(float* image,unsigned char* imgMsk,int xsize,int ysize,int bands,RepairEdgePnt &pntRepair,vector<RepairEdgePnt> &pntMatches, float conf = 80);
	//�޸���������
	void HyperSpecRepair_PartRepairPer(float* image,int xsize,int ysize,int bands,RepairEdgePnt &pntRepair,vector<RepairEdgePnt> &pntMatches);
	//����ƥ��
	void HyperSpecRepair_SpectralRepair(float* image,unsigned char* imgMsk,int xsize,int ysize,int bands);
	//����ƥ���Ӱ���޸�
	void HyperSpecRepair_SpecMatchRepair(const char* pathImage,const char* pathImgMsk,const char* pathDst);

	//���ݷ�ȶԶ�Ԫ���׽����ؽ�
	void HyperSpecRepair_SpectralAbundance(const char* pathImg,const char* pathEnd,const char* pathRed,int bands,int endNumbers,int begRepair,int endRepair);
	void HyperSpecRepair_AbundanceRestruct(float* image,unsigned char* imgMsk,float* endMember,const char* pathRed,int xsize,int ysize,int bands,int endNumber);
	
	//���ݶ�Ԫ��ȶԹ��׽���
	void HyperSpecRepair_EndMemberRepair(const char* pathImg, const char* pathEnd,const char* pathMsk,const char* pathDst,int bands,int endNumber);
};