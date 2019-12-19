#include "stdafx.h"
#include "Cone.h"
#define PI 3.1415926//Բ����
#include <math.h>
#define ROUND(d) int(d + 0.5)//��������궨��

CCone::CCone(void)
{
	P = NULL, F = NULL;
}

CCone::~CCone(void)
{
	if(P != NULL)
	{
		delete[] P;
		P = NULL;
	}
	for(int n = 0;n < N2 + 1;n++)//ע�⳷������,���к���,�������෴
	{
		delete[] F[n];
		F[n] = NULL;
	}
	delete[] F;
	F = NULL;
}

void CCone::SetParameter(double r, double h, CP3 positionP)
{
	this->r = r;
	this->h = h;
	this->positionP = positionP;
	Initial();
}

void CCone::Initial(void)
{
	ReadVertex();
	ReadPatch();
	transform.SetMatrix(P, N1 * N2 + 2);
	transform.Translate(positionP.x, positionP.y, positionP.z);
}

void CCone::ReadVertex(void)//���
{
	int cTheta = 10;//����н�
	N1 = 360 / cTheta;//N1��������
	int cNum = 10;//������
	N2 = ROUND(h / cNum);//N2Ϊ����������
	P = new CP3[nPoint=N1 * N2 + 2];
	double cTheta1, cNum1;
	P[0].x = 0;//Բ׶��������
	P[0].y = 0;
	P[0].z = 0;
    for (int i = 0; i < N2; i++)//���������
	{
		cNum1 = i * cNum;
		for (int j= 0; j < N1; j++)//���������
		{
			cTheta1 = j * cTheta * PI / 180;
		    double r1 = (N2 - i) * r / N2;
			P[i*N1 + j+1].x = r1 * cos(cTheta1);
			P[i*N1 + j+1].y =i * cNum;	
			P[i*N1 + j+1].z = r1 * sin(cTheta1);
		}
	}
    P[N1 * N2 + 1].x = 0;//Բ׶����
	P[N1 * N2 + 1].y = h;
	P[N1 * N2 + 1].z = 0;
}

void CCone::ReadPatch(void)//���
{
	//���ö�ά��̬����
	F = new CFacet *[N2 + 1];//������
	for (int n = 0; n < N2 + 1; n++)
	{
		F[n] = new CFacet[N1];//������
	}
	nPatch = (N2 + 1) * N1;
	for (int j = 0; j < N1; j++)//����ײ�����������
	{
		int tempj = j + 1;
		if (tempj == N1) tempj = 0;//�������β����
		int BottomIndex[3];//�ײ���������������������
		BottomIndex[0] = 0;
		BottomIndex[1] = j + 1;
		BottomIndex[2] = tempj + 1;
		F[0][j].SetNum(3);
		for (int k = 0; k < F[0][j].ptNum; k++)//�������е������
			F[0][j].ptI[k] = BottomIndex[k];
	}
	for (int i=1; i < N2; i++)//����Բ׶������ı�������
	{
		for (int j=0; j < N1; j++)
	    {
			int tempi = i + 1;
			int tempj = j + 1;
			if(N1 == tempj) tempj = 0;
			int BodyIndex[4];//Բ׶���ı�����������������
			BodyIndex[0] = (i - 1)*N1+j+1;
			BodyIndex[1] = (tempi-1)*N1+j+1;
			BodyIndex[2] = (tempi-1)*N1+tempj+1;
			BodyIndex[3] =(i- 1)*N1+tempj+1;
			F[i][j].SetNum(4);
			for(int k = 0;k < F[i][j].ptNum;k++)
				F[i][j].ptI[k] = BodyIndex[k];
		}
	}
	for (int j=0; j < N1; j++)//������涥�Ǹ���������������
	{
		int tempj = j + 1;
		if(N1 == tempj) tempj = 0;
		int TopIndex[3];//������������������������
		TopIndex[0] = N1 * N2 +1;
		TopIndex[1] = (N1 * (N2 - 1)) + tempj + 1;
		TopIndex[2] = (N1 * (N2 - 1)) + j + 1;
		F[N2][j].SetNum(3);
		for(int k = 0;k < F[N2][j].ptNum;k++)
			F[N2][j].ptI[k] = TopIndex[k];
	}
	for (int i = 0;i < N2 + 1;i++)
		for (int j = 0;j < N1;j++)
		{
			F[i][j].InEnergy = CRGB(0, 0, 0);
			F[i][j].OutEnergy = CRGB(0, 0, 0);
			F[i][j].Diffuse = CRGB(1, 1, 1);
		}
}

void CCone::Draw(CDC* pDC)
{
	CLine* pLine = new CLine;
	CP2 Point3[3];//�ϱ�����������
	CP2 Point4[4];//���嶥������
	for (int i = 0; i < N2 + 1; i++)//N2+1
	{
		for (int j=0; j < N1; j++)
		{
			if (3 == F[i][j].ptNum)//����������
			{
				for (int loop = 0; loop < F[i][j].ptNum; loop++)
					Point3[loop] = projection.PerspectiveProjection(P[F[i][j].ptI[loop]]);
				for (int n = 0;n < 3;n++)
				{
					if (0 == n)
						pLine->MoveTo(pDC, Point3[n]);
					else
						pLine->LineTo(pDC, Point3[n]);
				}
				pLine->LineTo(pDC, Point3[0]);//�պ�������
			}
			else//�ı�������
			{
				for (int loop = 0; loop < F[i][j].ptNum; loop++)
					Point4[loop] = projection.PerspectiveProjection(P[F[i][j].ptI[loop]]);	
				for (int n = 0; n < 4; n++)
				{
					if (0 == n)
						pLine->MoveTo(pDC, Point4[n]);
					else
						pLine->LineTo(pDC, Point4[n]);
				}
				pLine->LineTo(pDC, Point4[0]);//�պ��ı���
			}
		}
	}
	delete pLine;
}
