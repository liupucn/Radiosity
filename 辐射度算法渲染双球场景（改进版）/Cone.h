#pragma once
#include "Facet.h"
#include "Line.h"
#include "Projection.h"
#include "Transform3.h"

class CCone  
{
public:
	CCone(void);
	virtual ~CCone(void);	
	void SetParameter(double r, double h, CP3 positionP = CP3(0.0, 0.0, 0.0));
	void Draw(CDC* pDC);
private:
	void Initial();
	void ReadVertex();
	void ReadPatch();
public:
	double r;//Բ׶����뾶
	double h;//Բ׶�߶�
	CP3 positionP;//��������λ��
	int nPoint, nPatch;//����
	CP3* P;//Բ׶�涥��һά����
	CFacet** F;//С��Ķ�ά����
	int N1,N2;//N1Ϊ��������,N2��������
	CProjection projection;
	CTransform3 transform;
};
