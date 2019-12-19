#include "stdafx.h"
#include "Sphere.h"
#include"math.h"
#define PI 3.1415926

CSphere::CSphere()
{
	P = NULL, F = NULL;
}

CSphere::~CSphere()
{
	if (P != NULL)
	{
		delete[] P;
		P = NULL;
	}
	for (int n = 0; n < N1; n++)//ע�⳷������,���к���,�������෴
	{
		delete[] F[n];
		F[n] = NULL;
	}
	delete[] F;
	F = NULL;
}

void CSphere::SetParameter(double r, int Renumber)
{
	this->r = r;
	this->Renumber = Renumber;
	ReadVertex();
	ReadPatch();
}

void CSphere::SetMaterial(CMaterial* pMaterial)
{
	for (int i = 0;i < N1;i++)
		for (int j = 0;j < N2;j++)
		{
			F[i][j].Emitter = pMaterial->Emitter;
			F[i][j].Diffuse = pMaterial->Diffuse;
		}
}

void CSphere::ReadVertex()//���붥���
{
	N1 = Renumber, N2 = Renumber * 2;//N1Ϊγ������,N2Ϊ��������
	P = new CP3[nPoint=(N1 - 1) * N2 + 2];//PΪ��Ķ���
	P[0].x = 0; P[0].y = r; P[0].z = 0;//����������
	//����ѭ���������������ϵĵ�����
	double gAlpha1, gBeta1;
	for (int i = 0; i < N1 - 1; i++)
	{
		gAlpha1 = (i + 1) * (180 / Renumber) * PI / 180;
		for (int j = 0; j < N2; j++)
	    {
			gBeta1 = j * (180 / Renumber) * PI / 180;
			P[i*N2+j+1].x = r * sin(gAlpha1) * sin(gBeta1);
			P[i*N2+j+1].y = r * cos(gAlpha1);	
			P[i*N2+j+1].z = r * sin(gAlpha1) * cos(gBeta1);
		}
	}
	//�����ϼ�������
	P[(N1-1) * N2 + 1].x = 0; P[(N1 - 1) * N2 + 1].y = -r; P[(N1 - 1) * N2 + 1].z = 0;
	positionP = CP3(0, 0, 0);
}

void CSphere::ReadPatch()//�������
{
	//���ö�ά��̬����
	F = new CFacet *[N1];//������
	for (int n = 0; n  <N1; n++)
		F[n] =new CFacet[N2];//������
	nPatch = N1 * N2;
	for (int j = 0; j < N2; j++)//���챱������������
	{
		int tempj = j + 1;
		if (N2 == tempj) tempj =0;//�������β����
		int NorthIndex[3];//������������������������
		NorthIndex[0] = 0;
		NorthIndex[1] = j + 1;
		NorthIndex[2] = tempj +1;
		F[0][j].SetNum(3);
		for (int k = 0; k < F[0][j].ptNum; k++)
			F[0][j].ptI[k] = NorthIndex[k];
	}
	for(int i = 1;i < N1 - 1;i++)//���������ı�������
	{
		for(int j = 0;j < N2;j++)
	    {
			int tempi = i + 1;
			int tempj = j + 1;
			if(tempj == N2) tempj = 0;
			int BodyIndex[4];//�����ı�����������������
			BodyIndex[0] =(i - 1) * N2 +  j+ 1;
			BodyIndex[1] = (tempi - 1) * N2 + j + 1;
			BodyIndex[2] = (tempi - 1) * N2 + tempj + 1;
			BodyIndex[3] = (i - 1) * N2 + tempj + 1;
			F[i][j].SetNum(4);
			for(int k = 0;k < F[i][j].ptNum;k++)
				F[i][j].ptI[k] = BodyIndex[k];
		}
	}
	for(int j = 0;j < N2;j++)//�����ϼ�����������
	{
		int tempj = j +1;
		if (N2 == tempj) tempj  =0;
		int SouthIndex[3];//�ϼ���������������������
		SouthIndex[0] = (N1 - 2) * N2 + j + 1;
		SouthIndex[1] = (N1 - 1) * N2 + 1;
		SouthIndex[2] = (N1 - 2) * N2 + tempj + 1;
		F[N1 - 1][j].SetNum(3);	
		for(int k = 0; k < F[N1 - 1][j].ptNum; k++)
			F[N1-1][j].ptI[k] = SouthIndex[k];
	}
}

BOOL CSphere::IsHide(CFacet& F0, CFacet& F1, CP3* Point)
{
	//���������ڵ�  F0��F1
	CP3 A = Point[F0.ptI[0]];
	CP3 B = Point[F1.ptI[0]] - Point[F0.ptI[0]];
	CP3 C = positionP;//����
	double R = r;//�뾶
	double a = dot(B, B);
	double b = 2 * dot(B, (A - C));
	double c = dot((A - C), (A - C)) - R * R;

	double Result = 2;
	if (b * b - 4 * a * c >= 0)//�����ڵ�
	{
		if ((-b + sqrt(b * b - 4 * a * c)) / (2 * a) == 1)
			Result = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		else
			Result = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);

		if (Result > 1)//�����Դ������������Ĵ���
			return TRUE;
		else
			return FALSE;
	}
	return TRUE;
}
