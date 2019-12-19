#pragma once

#include"Facet.h"
#include"Projection.h"
#include"Material.h"

class CLamp
{
public:
	CLamp(void);
	virtual ~CLamp(void);
	void SetParameter(double a, double h, int Renumber);//设置参数
	void SetMaterial(CMaterial* pMaterial);	//初始化材质
	void ReadVertex(void);//读入点表
	void ReadFacet(void);//读入面表
public:
	int nPoint;
	int nPatch;	
	CP3* P;//点表
	CFacet* F;//面表	
private:
	int ReNumber;//细分步数
	double a, h;//边长、高度
	CProjection m_projection;//投影
};

