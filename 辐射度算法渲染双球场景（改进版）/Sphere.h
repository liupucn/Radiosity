#pragma once
#include "Facet.h"
#include "Material.h"

class CSphere  
{
public:
	CSphere();
	void SetParameter(double r, int Renumber);
	void SetMaterial(CMaterial* pMaterial);
	BOOL IsHide(CFacet& F0,CFacet& F1,CP3* Point);
	virtual ~CSphere();
private:
	void ReadVertex();
	void ReadPatch();
public:
	double r;//��İ뾶
	CP3 positionP;//����λ��
	int Renumber;//ϸ�ֲ���
	int nPoint, nPatch;//����㡢�����
	CP3* P;//���涥��һά����
	CFacet** F;//С��Ķ�ά����
	int N1, N2;//N1Ϊγ������,N2Ϊ��������
};
