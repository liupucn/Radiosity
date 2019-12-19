#include "StdAfx.h"
#include "Radiating.h"
#include <math.h>
#define PI 3.1415

CRadiating::CRadiating()
{
}

CRadiating::~CRadiating()
{
}

CRGB CRadiating::Illuminate(CFacet& Object, CFacet& Energy, CP3* Point)
{
	double d = 1.0;//入射能量被反射的比率
	CRGB OutEnergy = Energy.Emitter * d;//出射能量
	double Fij;//形状因子

	//计算形状因子
	CVector3 vectorij(Point[Energy.ptI[0]], Point[Object.ptI[0]]);
	vectorij = vectorij.Normalize();
	Energy.SetFacetNormal(Point[Energy.ptI[0]], Point[Energy.ptI[1]], Point[Energy.ptI[2]]);
	double cosinei = DotProduct(vectorij, Energy.fNormal);//两面的夹角cos值

	CVector3 vectorji(Point[Object.ptI[0]], Point[Energy.ptI[0]]);
	vectorji = vectorji.Normalize();
	Object.SetFacetNormal(Point[Object.ptI[0]], Point[Object.ptI[1]], Point[Object.ptI[2]]);
	double cosinej = DotProduct(vectorji, Object.fNormal);//两面的夹角cos值

	double length = sqrt(pow((Point[Energy.ptI[0]].x - Point[Object.ptI[0]].x), 2.0)
		+ pow((Point[Energy.ptI[0]].y - Point[Object.ptI[0]].y), 2.0)
		+ pow((Point[Energy.ptI[0]].z - Point[Object.ptI[0]].z), 2.0));//两面的间距

	double areaj;
	if (Energy.ptNum == 3)
		areaj = GetTriangleArea(Point[Energy.ptI[0]], Point[Energy.ptI[1]], Point[Energy.ptI[2]]);//计算Fj面积
	else
	{
		areaj = GetTriangleArea(Point[Energy.ptI[0]], Point[Energy.ptI[1]], Point[Energy.ptI[2]]);//计算Fj面积
		areaj += GetTriangleArea(Point[Energy.ptI[0]], Point[Energy.ptI[2]], Point[Energy.ptI[3]]);//计算Fj面积
	}
	Fij = (cosinei * cosinej) * areaj / (PI * length * length);

	//计算接受的辐射能
	Object.InEnergy += OutEnergy * Fij * Object.Diffuse;
	//规范化到[0,1]区间
	Object.InEnergy.Normalize();
	return Object.InEnergy;
} 

double CRadiating::GetTriangleArea(CP3 P0, CP3 P1, CP3 P2)//计算三角形面积
{
	double a = sqrt(pow((P0.x - P1.x), 2.0) + pow((P0.y - P1.y), 2.0) + pow((P0.z - P1.z), 2.0));
	double b = sqrt(pow((P0.x - P2.x), 2.0) + pow((P0.y - P2.y), 2.0) + pow((P0.z - P2.z), 2.0));
	double c = sqrt(pow((P1.x - P2.x), 2.0) + pow((P1.y - P2.y), 2.0) + pow((P1.z - P2.z), 2.0));
	double p = (a + b + c) / 2.0;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}