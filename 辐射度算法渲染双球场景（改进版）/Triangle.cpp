#include "StdAfx.h"
#include "Triangle.h"
#include <math.h>
#define ROUND(d) int(d + 0.5)

CTriangle::CTriangle(void)
{

}

CTriangle::~CTriangle(void)
{

}

void CTriangle::SetPoint(CP2 P0, CP2 P1, CP2 P2)
{
	point0.x = ROUND(P0.x);
	point0.y = ROUND(P0.y);
	point0.c = P0.c;
	point1.x = ROUND(P1.x);
	point1.y = ROUND(P1.y);
	point1.c = P1.c;
	point2.x = ROUND(P2.x);
	point2.y = ROUND(P2.y);
	point2.c = P2.c;
}

void CTriangle::GouraudShading(CDC* pDC)
{
	SortVertex();//point0��Ϊy������С�ĵ�,point1��Ϊy�������ĵ�,point2���y����λ�ڶ���֮�䡣���yֵ��ͬ��ȡx��С�ĵ�
	//���������θ��ǵ�ɨ��������
	int nTotalScanLine = point1.y - point0.y + 1;
	//����span��������յ�����
	pLeft  = new CPoint2[nTotalScanLine];
	pRight = new CPoint2[nTotalScanLine];
	//�ж���������P0P1�ߵ�λ�ù�ϵ��0-1-2Ϊ����ϵ
	int nDeltz = (point1.x - point0.x) * (point2.y - point1.y) - (point1.y - point0.y) * (point2.x - point1.x);//�����������z����
	if(nDeltz > 0)//������λ��P0P1�ߵ����
	{
		nIndex = 0;
		EdgeFlag(point0, point2, TRUE);
		EdgeFlag(point2, point1, TRUE);
		nIndex = 0;
		EdgeFlag(point0, point1, FALSE);
	}
	else//������λ��P0P1�ߵ��Ҳ�
	{
		nIndex = 0;
		EdgeFlag(point0, point1, TRUE);
		nIndex = 0;	
		EdgeFlag(point0, point2, FALSE);
		EdgeFlag(point2, point1, FALSE);
	}
	CRGB clr;
	for(int y = point0.y ; y < point1.y; y++)//�±��Ͽ�
	{
		int n = y - point0.y;
		for(int x = pLeft[n].x; x < pRight[n].x; x++)//����ҿ�
		{
			clr = LinearInterp(x, pLeft[n].x, pRight[n].x, pLeft[n].c, pRight[n].c);
			pDC->SetPixelV(x, y, RGB(clr.red * 255, clr.green * 255, clr.blue * 255));
		}
	}
	if(pLeft)
	{
		delete []pLeft;
		pLeft = NULL;
	}
	if(pRight)
	{
		delete []pRight;
		pRight = NULL;
	}
}

void CTriangle::EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature)
{
	CRGB crColor = PStart.c;
	int dx = abs(PEnd.x - PStart.x);
	int dy = abs(PEnd.y - PStart.y);
	BOOL bInterChange = FALSE;//bInterChangeΪ�٣���λ�Ʒ���Ϊx����
	int e, s1, s2, temp;
	s1 = (PEnd.x > PStart.x) ? 1 :((PEnd.x < PStart.x) ? -1 : 0);
	s2 = (PEnd.y > PStart.y) ? 1 :((PEnd.y < PStart.y) ? -1 : 0);
	if(dy > dx)//bInterChangeΪ�棬��λ�Ʒ���Ϊy����
	{
		temp = dx;
		dx = dy;
		dy = temp;
		bInterChange = TRUE;
	}
	e = -dx;
	int x = PStart.x , y  = PStart.y;
	for(int i = 0;i < dx; i++)
	{
		if(bFeature)
			pLeft[nIndex] = CPoint2(x, y, crColor);
		else
			pRight[nIndex] = CPoint2(x, y, crColor);
		if(bInterChange)
		{
			y += s2;
			crColor = LinearInterp(y, PStart.y, PEnd.y, PStart.c, PEnd.c);
			if(bFeature)
				pLeft[++nIndex] = CPoint2(x, y, crColor);
			else
				pRight[++nIndex] = CPoint2(x, y, crColor);
		}
		else 
		{
			x += s1;
			crColor = LinearInterp(x, PStart.x, PEnd.x, PStart.c, PEnd.c);
		}
		e += 2 * dy;
		if(e >= 0)
		{
			if(bInterChange)
			{
				x += s1;
				crColor = LinearInterp(y, PStart.y, PEnd.y, PStart.c, PEnd.c);
			}
			else
			{
				y += s2;
				crColor = LinearInterp(x, PStart.x, PEnd.x, PStart.c, PEnd.c);
				if(bFeature)
					pLeft[++nIndex] = CPoint2(x, y, crColor);
				else
					pRight[++nIndex] = CPoint2(x, y, crColor);
			}
			e -= 2 * dx;
		}
	}
}

void CTriangle::SortVertex(void)
{
	CPoint2 pt[3];
	pt[0] = point0;
	pt[1] = point1;
	pt[2] = point2;
	for(int i = 0; i < 2; i++)
	{
		for(int j = i + 1;j < 3; j++)
		{
			int k = i;
			if(pt[k].y >= pt[j].y)
				k = j;
			if(k == j)
			{
				CPoint2 ptTemp = pt[i];
				pt[i] = pt[k];
				pt[k] = ptTemp;
			}
		}
	}
	point0 = pt[0];
	point1 = pt[2];
	point2 = pt[1];
}

CRGB CTriangle::LinearInterp(double t, double tStart, double tEnd, CRGB IStart, CRGB IEnd)//��ʸ���Բ�ֵ
{
	CRGB color;
	color = (tEnd - t) / (tEnd - tStart) * IStart + (t - tStart) / (tEnd - tStart) * IEnd;
	return color;
}