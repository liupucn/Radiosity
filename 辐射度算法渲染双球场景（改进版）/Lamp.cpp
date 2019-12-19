#include "StdAfx.h"
#include "Lamp.h"
#include <math.h>//包含数学头文件


CLamp::CLamp(void)
{
	F = NULL;
	P = NULL;
}


CLamp::~CLamp(void)
{
	if (NULL != F)
	{
		delete[]F;
		F = NULL;
	}

	if (NULL != P)
	{
		delete[]P;
		P = NULL;
	}
}

void CLamp::SetParameter(double a, double h, int Renumber)
{
	this->a = a;
	this->h = h;
	this->ReNumber = Renumber;
	ReadVertex();//读入点表
	ReadFacet();//读入面表
}

void CLamp::SetMaterial(CMaterial* pMaterial)
{
	for (int i = 0;i < ReNumber * ReNumber;i++)
	{
		F[i].Emitter = pMaterial->Emitter;
		F[i].Diffuse = pMaterial->Diffuse;
	}
}

void CLamp::ReadVertex(void)
{
	P = new CP3[nPoint = (ReNumber + 1) * (ReNumber + 1)];
	int k = 0;
	double Ra = 2 * a / ReNumber;
	for (int i = 0;i <= ReNumber;i++)
		for (int j = 0;j <= ReNumber;j++)
			P[k++] = CP3(-a + j * Ra, h, -a + i * Ra);//顶面
}

void CLamp::ReadFacet(void)
{
	F = new CFacet[nPatch = ReNumber * ReNumber];
	for (int i = 0;i < ReNumber * ReNumber;i++)
	{
		F[i].SetNum(4);
		F[i].ptI[0] = i / ReNumber + i + 1;
		F[i].ptI[1] = i / ReNumber + i + ReNumber + 2;
		F[i].ptI[2] = i / ReNumber + i + ReNumber + 1;
		F[i].ptI[3] = i / ReNumber + i;
	}
}