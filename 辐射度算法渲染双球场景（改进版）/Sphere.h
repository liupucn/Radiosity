#pragma once
#include "Facet.h"
#include "Material.h"

class CSphere  
{
public:
	CSphere();
	void SetParameter(double r, int Renumber);
	void SetMaterial(CMaterial* pMaterial);
	BOOL IsHide(CFacet& F0,CFacet& F1,CP3* Point);
	virtual ~CSphere();
private:
	void ReadVertex();
	void ReadPatch();
public:
	double r;//球的半径
	CP3 positionP;//球心位置
	int Renumber;//细分步长
	int nPoint, nPatch;//球面点、面个数
	CP3* P;//球面顶点一维数组
	CFacet** F;//小面的二维数组
	int N1, N2;//N1为纬度区域,N2为经度区域
};
