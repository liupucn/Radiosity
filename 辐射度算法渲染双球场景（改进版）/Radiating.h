#pragma once
#include "Facet.h"
#include "Material.h"

class CRadiating
{
public:
	CRadiating(void);
	virtual ~CRadiating(void);
	CRGB Illuminate(CFacet& Object, CFacet& Energy, CP3* Point);//�������ɫ
private:
	double GetTriangleArea(CP3 P0, CP3 P1, CP3 P2);//�������������
};

