#pragma once
#include "Facet.h"
#include "Line.h"
#include "Projection.h"
#include "Transform3.h"

class CCone  
{
public:
	CCone(void);
	virtual ~CCone(void);	
	void SetParameter(double r, double h, CP3 positionP = CP3(0.0, 0.0, 0.0));
	void Draw(CDC* pDC);
private:
	void Initial();
	void ReadVertex();
	void ReadPatch();
public:
	double r;//圆锥底面半径
	double h;//圆锥高度
	CP3 positionP;//底面中心位置
	int nPoint, nPatch;//个数
	CP3* P;//圆锥面顶点一维数组
	CFacet** F;//小面的二维数组
	int N1,N2;//N1为周向网格,N2纵向网格
	CProjection projection;
	CTransform3 transform;
};
