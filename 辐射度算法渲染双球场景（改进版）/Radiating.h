#pragma once
#include "Facet.h"
#include "Material.h"

class CRadiating
{
public:
	CRadiating(void);
	virtual ~CRadiating(void);
	CRGB Illuminate(CFacet& Object, CFacet& Energy, CP3* Point);//辐射度着色
private:
	double GetTriangleArea(CP3 P0, CP3 P1, CP3 P2);//计算三角形面积
};

