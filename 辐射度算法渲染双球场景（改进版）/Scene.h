#pragma once
#include "Box.h"
#include "Sphere.h"
#include "Lamp.h"
#include "Triangle.h"
#include "Material.h"
#include "Radiating.h"

class CScene
{
public:
	CScene(void);
	virtual ~CScene(void);
	void SetParameter(int Renumber, int nErgodic, int Energy);
	void Draw(CDC* pDC);
private:
	CSphere sphere[2];//球体
	CBox box;//包围盒
	CLamp lamp;//光源
	int nPoint, nPatch;//场景中点面个数
	CP3* Point;//点表
	CFacet* Facet;//面表
	int Renumber;//细分参数
	int nErgodic;//能量传递次数
	int Energy;//光源的能量
	CMaterial* pMaterial;//材质
	CRadiating pRadiation;//辐射
	CProjection projection;//投影对象

	void Initial();//初始化
	void ReadPoint(void);
	void ReadFacet(void);
	void CopyFacet(CFacet&, CFacet&);
	void AverageColor();//平均每点的颜色值
	void EnergyTransfer();	//计算场景的能量传递
	BOOL SurFaceDistribution(CFacet&, CFacet&);//检测两面之间是否可以相互辐射
};

