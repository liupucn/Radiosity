#pragma once
#include "Facet.h"
#include "Line.h"
#include "Material.h"
#include "Projection.h"
#include "Transform3.h"

class CBox  
{
public:
	CBox(void);
	virtual ~CBox(void);
	void SetParameter(double a, int ReNumber);
	void SetUpMaterial(CMaterial* pMaterial);
	void SetDownMaterial(CMaterial* pMaterial);
	void SetLeftMaterial(CMaterial* pMaterial);
	void SetRightMaterial(CMaterial* pMaterial);
	void SetFrondMaterial(CMaterial* pMaterial);
	void SetBackMaterial(CMaterial* pMaterial);
private:
	void ReadVertex(void);
	void ReadPatch(void);
public:
	double a;//盒子的半边长
	int ReNumber;
	int nPoint, nPatch;//个数
	CP3 positionP;//盒子中心位置
	CP3 *P;//顶点一维数组
	CFacet *F;//面的二维数组
	CMaterial material[3];
	CProjection projection;//投影对象
	CTransform3 transform;//变换对象
};
