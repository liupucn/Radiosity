#include "StdAfx.h"
#include "Scene.h"
#include <math.h>
#define PI 3.1415

CScene::CScene(void)
{
	Point = NULL;
	Facet = NULL;
	pMaterial = NULL;
	Renumber = 10;
	nErgodic = 2;
	Energy = 12;
}

CScene::~CScene(void)
{
	if (Point != NULL)
		delete[] Point;
	if (Facet != NULL)
		delete[] Facet;
	if (pMaterial != NULL)
		delete[] pMaterial;

}

void CScene::SetParameter(int Renumber, int nErgodic, int Energy)
{
	this->Renumber = Renumber;
	this->nErgodic = nErgodic;
	this->Energy = Energy;
	Initial();

	for (int i = 0;i < nErgodic;++i)
		EnergyTransfer();//�������
	AverageColor();//��������
}

void CScene::Initial(void)
{
	CTransform3 transform;
	//����
	pMaterial = new CMaterial[4];
	pMaterial[0].SetEnergy(CRGB(Energy, Energy, Energy));//����������ɫ
	pMaterial[0].SetDiffuse(CRGB(1.0, 1.0, 1.0));

	pMaterial[1].SetEnergy(CRGB(0.0, 0.0, 0.0));//����������ɫ
	pMaterial[1].SetDiffuse(CRGB(1.0, 1.0, 1.0));

	pMaterial[2].SetEnergy(CRGB(0.0, 0.0, 0.0));//����������ɫ
	pMaterial[2].SetDiffuse(CRGB(1.0, 0.0, 0.0));

	pMaterial[3].SetEnergy(CRGB(0.0, 0.0, 0.0));//����������ɫ
	pMaterial[3].SetDiffuse(CRGB(0.0, 1.0, 0.0));
	//����
	//Cornell����
	box.SetParameter(330, Renumber);//��С��ϸ�ֲ���
	box.SetFrondMaterial(&pMaterial[1]);
	box.SetBackMaterial(&pMaterial[1]);
	box.SetLeftMaterial(&pMaterial[2]);
	box.SetRightMaterial(&pMaterial[3]);
	box.SetUpMaterial(&pMaterial[1]);
	box.SetDownMaterial(&pMaterial[1]);

	//��
	lamp.SetParameter(120, 325, Renumber);//��С���߶ȡ�ϸ�ֲ���
	lamp.SetMaterial(&pMaterial[0]);

	//����
	sphere[0].SetParameter(130, Renumber);//�뾶��ϸ�ֲ���
	sphere[0].SetMaterial(&pMaterial[1]);
	transform.SetMatrix(sphere[0].P, sphere[0].nPoint);
	transform.Translate(-100, -200, -100);
	transform.SetMatrix(&sphere[0].positionP, 1);
	transform.Translate(-100, -200, -100);

	//С��
	sphere[1].SetParameter(80, Renumber);//�뾶��ϸ�ֲ���
	sphere[1].SetMaterial(&pMaterial[1]);
	transform.SetMatrix(sphere[1].P, sphere[1].nPoint);
	transform.Translate(100, -250, 100);
	transform.SetMatrix(&sphere[1].positionP, 1);
	transform.Translate(100, -250, 100);
	ReadPoint();
	ReadFacet();
}

void CScene::ReadPoint(void)
{
	nPoint = box.nPoint + lamp.nPoint + sphere[0].nPoint + sphere[1].nPoint;
	Point = new CP3[nPoint];
	int k = 0;
	for (int i = 0;i < box.nPoint;i++)
		Point[k++] = box.P[i];
	for (int i = 0;i < lamp.nPoint;i++)
		Point[k++] = lamp.P[i];
	for (int i = 0;i < sphere[0].nPoint;i++)
		Point[k++] = sphere[0].P[i];
	for (int i = 0;i < sphere[1].nPoint;i++)
		Point[k++] = sphere[1].P[i];
}

void CScene::ReadFacet(void)
{
	nPatch = box.nPatch + lamp.nPatch + sphere[0].nPatch + sphere[1].nPatch;
	Facet = new CFacet[nPatch];
	int k = 0;
	for (int i = 0;i < box.nPatch;i++)
		CopyFacet(box.F[i], Facet[k++]);

	for (int i = 0;i < lamp.nPatch;i++)
	{
		lamp.F[i].MergeFacet(box.nPoint);
		CopyFacet(lamp.F[i], Facet[k++]);
	}
	for (int i = 0;i < sphere[0].N1;i++)
		for (int j = 0;j < sphere[0].N2;j++)
		{
			sphere[0].F[i][j].MergeFacet(lamp.nPoint + box.nPoint);
			CopyFacet(sphere[0].F[i][j], Facet[k++]);
		}
	for (int i = 0;i < sphere[1].N1;i++)
		for (int j = 0;j < sphere[1].N2;j++)
		{
			sphere[1].F[i][j].MergeFacet(lamp.nPoint + box.nPoint + sphere[0].nPoint);
			CopyFacet(sphere[1].F[i][j], Facet[k++]);
		}
}

void CScene::Draw(CDC* pDC)
{
	CTriangle Triangle;
	CP3 Point3[3];//�ϱ�����������
	CP3 Point4[4];//���嶥������
	
	for (int i = 0; i < nPatch; i++)
	{
		CVector3 ViewVector(Point[Facet[i].ptI[0]], projection.EyePoint);//�����ʸ��
		ViewVector = ViewVector.Normalize();//��λ����ʸ��
		Facet[i].SetFacetNormal(Point[Facet[i].ptI[0]], Point[Facet[i].ptI[1]], Point[Facet[i].ptI[2]]);
		CVector3 FacetNormal = Facet[i].fNormal.Normalize();//��λ����ʸ��
		double dotproduct = DotProduct(ViewVector, FacetNormal);
		if (dotproduct >= 0)
		{
			if (3 == Facet[i].ptNum)//����������
			{
				for (int loop = 0; loop < Facet[i].ptNum; loop++)
				{
					Point3[loop] = projection.PerspectiveProjection(Point[Facet[i].ptI[loop]]);
					Point3[loop].c = Point[Facet[i].ptI[loop]].c;
				}
				Triangle.SetPoint(Point3[0], Point3[1], Point3[2]);
				Triangle.GouraudShading(pDC);
			}
			else//�ı�������
			{
				for (int loop = 0; loop < Facet[i].ptNum; loop++)
				{
					Point4[loop] = projection.PerspectiveProjection(Point[Facet[i].ptI[loop]]);
					Point4[loop].c = Point[Facet[i].ptI[loop]].c;
				}
				Triangle.SetPoint(Point4[0], Point4[1], Point4[2]);
				Triangle.GouraudShading(pDC);
				Triangle.SetPoint(Point4[0], Point4[2], Point4[3]);
				Triangle.GouraudShading(pDC);
			}
		}
	}
}

//�ɼ����ж�
BOOL CScene::SurFaceDistribution(CFacet& Fi, CFacet& Fj)
{
	//����ļн�cosֵ
	CVector3 vectorij(Point[Fi.ptI[0]], Point[Fj.ptI[0]]);
	vectorij = vectorij.Normalize();
	Fi.SetFacetNormal(Point[Fi.ptI[0]], Point[Fi.ptI[1]], Point[Fi.ptI[2]]);
	double cosinei = DotProduct(vectorij, Fi.fNormal);
	CVector3 vectorji(Point[Fj.ptI[0]], Point[Fi.ptI[0]]);
	vectorji = vectorji.Normalize();
	Fj.SetFacetNormal(Point[Fj.ptI[0]], Point[Fj.ptI[1]], Point[Fj.ptI[2]]);
	double cosinej = DotProduct(vectorji, Fj.fNormal);

	if (cosinei < 0 || cosinej < 0)//�����޳�
		return FALSE;
	else
	{  //���ο��ǳ����е������ڵ�
		BOOL IsHide;
		IsHide = sphere[0].IsHide(Fj, Fi, Point);
		if (!IsHide)return IsHide;
		IsHide = sphere[1].IsHide(Fj, Fi, Point);
		return IsHide;
	}
}

//���������Ĵ���
void CScene::EnergyTransfer(void)
{
	for (int i = 0;i < nPatch;++i)
		for (int j = 0;j < nPatch;++j)
			if (SurFaceDistribution(Facet[i], Facet[j]))
				Facet[i].Emitter = pRadiation.Illuminate(Facet[i], Facet[j], Point);
}

//��������
void CScene::AverageColor()
{
	for (int i = 0;i < nPatch;++i)
		for (int j = 0;j < Facet[i].ptNum;j++)
		{
			Point[Facet[i].ptI[j]].c += Facet[i].Emitter;
			Point[Facet[i].ptI[j]].num++;
		}
	for (int i = 0;i < nPoint;++i)
		Point[i].c /= Point[i].num;

	//��Դ��������������
	for (int i = box.nPatch;i < lamp.nPatch + box.nPatch;i++)
		for (int j = 0;j < Facet[i].ptNum;j++)
		{
			Point[Facet[i].ptI[j]].c = Facet[i].Diffuse;
		}
}

//������Ƭ
void CScene::CopyFacet(CFacet&F1, CFacet&F2)
{
	F2.Diffuse = F1.Diffuse;
	F2.fNormal = F1.fNormal;
	F2.Emitter = F1.Emitter;
	F2.InEnergy = F1.InEnergy;
	F2.OutEnergy = F1.OutEnergy;
	F2.SetNum(F1.ptNum);
	for (int i = 0;i < F1.ptNum;i++)
	{
		F2.ptI[i] = F1.ptI[i];
	}
}
