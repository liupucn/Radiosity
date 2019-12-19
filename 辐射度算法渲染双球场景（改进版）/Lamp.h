#pragma once

#include"Facet.h"
#include"Projection.h"
#include"Material.h"

class CLamp
{
public:
	CLamp(void);
	virtual ~CLamp(void);
	void SetParameter(double a, double h, int Renumber);//���ò���
	void SetMaterial(CMaterial* pMaterial);	//��ʼ������
	void ReadVertex(void);//������
	void ReadFacet(void);//�������
public:
	int nPoint;
	int nPatch;	
	CP3* P;//���
	CFacet* F;//���	
private:
	int ReNumber;//ϸ�ֲ���
	double a, h;//�߳����߶�
	CProjection m_projection;//ͶӰ
};

