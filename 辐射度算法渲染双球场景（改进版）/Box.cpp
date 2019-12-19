#include "stdafx.h"
#include "test.h"
#include "Box.h"

CBox::CBox(void)
{
	P = NULL;
	F = NULL;
}

CBox::~CBox(void)
{
	if (P != NULL)
		delete[] P;
	if (F != NULL)
		delete[] F;
}

void CBox::SetParameter(double a, int ReNumber)
{
	this->a = a;
	this->ReNumber = ReNumber;
	ReadVertex();
	ReadPatch();
}

void CBox::SetUpMaterial(CMaterial* pMaterial)
{
	for (int i = ReNumber * ReNumber;i < ReNumber * ReNumber * 2;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}
void CBox::SetDownMaterial(CMaterial* pMaterial)
{
	for (int i = ReNumber * ReNumber * 2;i < ReNumber * ReNumber * 3;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}
void CBox::SetLeftMaterial(CMaterial* pMaterial)
{
	for (int i = ReNumber * ReNumber * 4;i < ReNumber * ReNumber * 5;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}
void CBox::SetRightMaterial(CMaterial* pMaterial)
{
	for (int i = ReNumber * ReNumber * 3;i < ReNumber * ReNumber * 4;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}
void CBox::SetFrondMaterial(CMaterial* pMaterial)
{
	for (int i = ReNumber * ReNumber * 5;i < ReNumber * ReNumber * 6;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}
void CBox::SetBackMaterial(CMaterial* pMaterial)
{
	for (int i = 0;i < ReNumber * ReNumber;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}

void CBox::ReadVertex()//点表
{
	//顶点的三维坐标(x,y,z),边长为2a
	int k = 0;
	P = new CP3[nPoint = (ReNumber + 1) * (ReNumber + 1) * 6];
	double Ra = 2 * a / ReNumber;

	for (int i = 0;i <= ReNumber;i ++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(-a + j * Ra, -a + i * Ra, -a);//后面

	for (int i = 0;i <= ReNumber;i++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(-a + j * Ra, a, -a + i * Ra);//顶面

	for (int i = 0;i <= ReNumber;i++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(-a + j * Ra, -a, -a + i * Ra);//底面

	for (int i = 0;i <= ReNumber;i++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(a, -a + j * Ra, -a + i * Ra);//右面

	for (int i = 0;i <= ReNumber;i++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(-a, -a + j * Ra, -a + i * Ra);//左面

	for (int i = 0;i <= ReNumber;i++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(-a + j * Ra, -a + i * Ra, a);//前面
}

void CBox::ReadPatch()//面表
{
	//面的顶点数和面的顶点索引
	F = new CFacet[nPatch = ReNumber * ReNumber * 6];
	for (int i = 0;i < ReNumber * ReNumber;i++)
	{
		F[i].SetNum(4);
		F[i].ptI[0] = i / ReNumber + i + 1;
		F[i].ptI[1] = i / ReNumber + i + ReNumber + 2;
		F[i].ptI[2] = i / ReNumber + i + ReNumber + 1;
		F[i].ptI[3] = i / ReNumber + i;
	}
	for (int i = ReNumber * ReNumber;i < ReNumber * ReNumber*2;i++)
	{
		int k = i - ReNumber * ReNumber;
		int k1 = (ReNumber + 1) * (ReNumber + 1);
		F[i].SetNum(4);
		F[i].ptI[0] = k / ReNumber + k + 1 + k1;
		F[i].ptI[1] = k / ReNumber + k + ReNumber+2+ k1;
		F[i].ptI[2] = k / ReNumber + k + ReNumber+1 + k1;
		F[i].ptI[3] = k / ReNumber + k + k1;
	}
	for (int i = ReNumber * ReNumber * 2;i < ReNumber * ReNumber * 3;i++)
	{
		int k = i - ReNumber * ReNumber * 2;
		int k1 = (ReNumber + 1) * (ReNumber + 1) * 2;
		F[i].SetNum(4);
		F[i].ptI[0] = k / ReNumber + k + k1;
		F[i].ptI[1] = k / ReNumber + k + ReNumber + 1 + k1;
		F[i].ptI[2] = k / ReNumber + k + ReNumber + 2 + k1;
		F[i].ptI[3] = k / ReNumber + k + 1 + k1;
		F[i].Diffuse = CRGB(1, 1, 1);
	}
	for (int i = ReNumber * ReNumber * 3;i < ReNumber * ReNumber * 4;i++)
	{
		int k = i - ReNumber * ReNumber * 3;
		int k1 = (ReNumber + 1) * (ReNumber + 1) * 3;
		F[i].SetNum(4);
		F[i].ptI[0] = k / ReNumber + k + k1;
		F[i].ptI[1] = k / ReNumber + k + ReNumber + 1 + k1;
		F[i].ptI[2] = k / ReNumber + k + ReNumber + 2 + k1;
		F[i].ptI[3] = k / ReNumber + k + 1 + k1;
		F[i].Diffuse = CRGB(0, 0, 1);
	}
	for (int i = ReNumber * ReNumber * 4;i < ReNumber * ReNumber * 5;i++)
	{
		int k = i - ReNumber * ReNumber * 4;
		int k1 = (ReNumber + 1) * (ReNumber + 1) * 4;
		F[i].SetNum(4);
		F[i].ptI[0] = k / ReNumber + k + 1 + k1;
		F[i].ptI[1] = k / ReNumber + k + ReNumber + 2 + k1;
		F[i].ptI[2] = k / ReNumber + k + ReNumber + 1 + k1;
		F[i].ptI[3] = k / ReNumber + k + k1;
		F[i].Diffuse = CRGB(1, 0, 0);
	}
	for (int i = ReNumber * ReNumber * 5;i < ReNumber * ReNumber * 6;i++)
	{
		int k = i - ReNumber * ReNumber * 5;
		int k1 = (ReNumber + 1) * (ReNumber + 1) * 5;
		F[i].SetNum(4);
		F[i].ptI[0] = k / ReNumber + k + k1;
		F[i].ptI[1] = k / ReNumber + k + ReNumber + 1 + k1;
		F[i].ptI[2] = k / ReNumber + k + ReNumber + 2 + k1;
		F[i].ptI[3] = k / ReNumber + k + 1 + k1;
		F[i].Diffuse = CRGB(1, 1, 1);
	}
}