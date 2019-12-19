#pragma once
#include "Vector3.h"

class CFacet  
{
public:
	CFacet(void);
	virtual ~CFacet(void);
	void SetNum(int ptNum);//设置面的顶点数
	void MergeFacet(int nFacet);
	void SetFacetNormal(CP3 pt0, CP3 pt1, CP3 pt2);//设置小面法矢量
public:
	int ptNum; //面的顶点数
	int* ptI;//面的顶点索引
	CVector3 fNormal; //小面的法矢量
	CRGB Emitter;//面元拥有的能量
	CRGB InEnergy;//面元入射能量
	CRGB OutEnergy;//面元出射能量
	CRGB Diffuse;//面元漫反射率
};
