#pragma once
#include "Vector3.h"

class CFacet  
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetNum(int ptNum);//������Ķ�����
	void MergeFacet(int nFacet);
	void SetFacetNormal(CP3 pt0, CP3 pt1, CP3 pt2);//����С�淨ʸ��
public:
	int ptNum; //��Ķ�����
	int* ptI;//��Ķ�������
	CVector3 fNormal; //С��ķ�ʸ��
	CRGB Emitter;//��Ԫӵ�е�����
	CRGB InEnergy;//��Ԫ��������
	CRGB OutEnergy;//��Ԫ��������
	CRGB Diffuse;//��Ԫ��������
};
