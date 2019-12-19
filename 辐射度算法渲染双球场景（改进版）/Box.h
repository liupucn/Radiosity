#pragma once
#include "Facet.h"
#include "Line.h"
#include "Material.h"
#include "Projection.h"
#include "Transform3.h"

class CBox  
{
public:
	CBox(void);
	virtual ~CBox(void);
	void SetParameter(double a, int ReNumber);
	void SetUpMaterial(CMaterial* pMaterial);
	void SetDownMaterial(CMaterial* pMaterial);
	void SetLeftMaterial(CMaterial* pMaterial);
	void SetRightMaterial(CMaterial* pMaterial);
	void SetFrondMaterial(CMaterial* pMaterial);
	void SetBackMaterial(CMaterial* pMaterial);
private:
	void ReadVertex(void);
	void ReadPatch(void);
public:
	double a;//���ӵİ�߳�
	int ReNumber;
	int nPoint, nPatch;//����
	CP3 positionP;//��������λ��
	CP3 *P;//����һά����
	CFacet *F;//��Ķ�ά����
	CMaterial material[3];
	CProjection projection;//ͶӰ����
	CTransform3 transform;//�任����
};
