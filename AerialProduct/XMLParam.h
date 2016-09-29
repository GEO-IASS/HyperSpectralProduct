#pragma once
#include"AerialCore.h"
#include <string>
#include<vector>
using namespace std;

class XMLParam
{
public:
	//ԭʼ����Ԫ���ݶ�ȡ
	virtual long LoadProcMeta(const char* pMetaFile) = 0;

	//ԭʼ����Ԫ����д��
	virtual long SaveProcMeta(const char* pMetaFile,ParamMeta &m_Meta_Param) = 0;


	//��������Ԥ�������ļ���ȡ����Ԥ�������
	virtual long LoadPreProcXML(const char* pCatalogOrderFile) = 0;

	//������Ԥ�������д�붩���ļ���
	virtual long SavePreProcXML(const char* pCatalogOrderFile,ParamPre &pPreProc_Param)=0;

	//����0�����ݴ������ļ���ȡ����0�����ݶ����ļ�����
	virtual long LoadP0ProcXML(const char* pCatalogOrderFile) = 0;

	//��0�����ݴ������д�붩���ļ���
	virtual long SaveP0ProcXML(const char* pCatalogOrderFile,ParamP0 &pP0Proc_Param)=0;

	//����1�����ݴ������ļ���ȡ����1�����ݴ������ļ�
	virtual long LoadP1ProcXML(const char* pCatalogOrderFile) = 0;

	//��1�����ݴ������д�붩���ļ���
	virtual long SaveP1ProcXML(const char* pCatalogOrderFile,ParamP1 &pP1Proc_Param)=0;

	//����2�����ݴ������ļ���ȡ����Ԥ�������
	virtual long LoadP2ProcXML(const char* pCatalogOrderFile) = 0;

	//��2�����ݴ������д�붩���ļ���
	virtual long SaveP2ProcXML(const char* pCatalogOrderFile,ParamP2 &pP2Proc_Param)=0;

protected:
	ParamMeta		m_Meta_Param;
	ParamPre		m_PreProc_Param;
	ParamP0			m_P0Proc_Param;
	ParamP1			m_P1Proc_Param;
	ParamP2			m_P2Proc_Param;
};

//����ȫ�׶����ݶ����ļ�����
class QPDXMLParam : public XMLParam
{
	friend class LevelPreProcess;
	friend class Level0Process;
	friend class Level1Process;
	friend class Level2Process;

public:
	//ԭʼ����Ԫ���ݶ�ȡ
	virtual long LoadProcMeta(const char* pMetaFile);
	//ԭʼ����Ԫ����д��
	virtual long SaveProcMeta(const char* pMetaFile,ParamMeta &m_Meta_Param);

	//��������Ԥ�������ļ���ȡ����Ԥ�������
	virtual long LoadPreProcXML(const char* pCatalogOrderFile);
	//������Ԥ�������д�붩���ļ���
	virtual long SavePreProcXML(const char* pCatalogOrderFile,ParamPre &pPreProc_Param);

	//����0�����ݴ������ļ���ȡ����0�����ݶ����ļ�����
	virtual long LoadP0ProcXML(const char* pCatalogOrderFile);
	//��0�����ݴ������д�붩���ļ���
	virtual long SaveP0ProcXML(const char* pCatalogOrderFile,ParamP0 &pP0Proc_Param);

	//����1�����ݴ������ļ���ȡ����1�����ݴ������ļ�
	virtual long LoadP1ProcXML(const char* pCatalogOrderFile);
	//��1�����ݴ������д�붩���ļ���
	virtual long SaveP1ProcXML(const char* pCatalogOrderFile,ParamP1 &pP1Proc_Param);

	//����2�����ݴ������ļ���ȡ����Ԥ�������
	virtual long LoadP2ProcXML(const char* pCatalogOrderFile) ;
	//��2�����ݴ������д�붩���ļ���
	virtual long SaveP2ProcXML(const char* pCatalogOrderFile,ParamP2 &pP2Proc_Param);
};