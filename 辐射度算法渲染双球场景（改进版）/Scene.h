#pragma once
#include "Box.h"
#include "Sphere.h"
#include "Lamp.h"
#include "Triangle.h"
#include "Material.h"
#include "Radiating.h"

class CScene
{
public:
	CScene(void);
	virtual ~CScene(void);
	void SetParameter(int Renumber, int nErgodic, int Energy);
	void Draw(CDC* pDC);
private:
	CSphere sphere[2];//����
	CBox box;//��Χ��
	CLamp lamp;//��Դ
	int nPoint, nPatch;//�����е������
	CP3* Point;//���
	CFacet* Facet;//���
	int Renumber;//ϸ�ֲ���
	int nErgodic;//�������ݴ���
	int Energy;//��Դ������
	CMaterial* pMaterial;//����
	CRadiating pRadiation;//����
	CProjection projection;//ͶӰ����

	void Initial();//��ʼ��
	void ReadPoint(void);
	void ReadFacet(void);
	void CopyFacet(CFacet&, CFacet&);
	void AverageColor();//ƽ��ÿ�����ɫֵ
	void EnergyTransfer();	//���㳡������������
	BOOL SurFaceDistribution(CFacet&, CFacet&);//�������֮���Ƿ�����໥����
};

