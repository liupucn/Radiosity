#include "stdafx.h"
#include "test.h"
#include "Facet.h"

CFacet::CFacet(void)
{
	ptI = NULL;
	fNormal = CVector3(CP3(0.0, 0.0, 1.0));
	Emitter = CRGB(0.0, 0.0, 0.0);
	InEnergy = CRGB(0.0, 0.0, 0.0);
	OutEnergy = CRGB(0.0, 0.0, 0.0);
	Diffuse = CRGB(0.0, 0.0, 0.0);
}

CFacet::~CFacet(void)
{
	if (NULL != ptI)
		delete[] ptI;
}

void CFacet::SetNum(int ptNum)
{
	this->ptNum = ptNum;
	ptI = new int[ptNum];
}

void CFacet::MergeFacet(int nFacet)
{
	for (int i = 0;i < ptNum;i++)
		this->ptI[i] += nFacet;
}


void CFacet::SetFacetNormal(CP3 pt0, CP3 pt1, CP3 pt2)//计算小面法矢量
{
	CVector3 vector01(pt0, pt1);
	CVector3 vector02(pt0, pt2);
	fNormal = CrossProduct(vector01, vector02).Normalize();
}
