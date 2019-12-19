#pragma once

#include "P2.h"
#include "RGB.h"

class CLine  
{
public:
	CLine();
	virtual ~CLine();
	void MoveTo(CDC* pDC, CP2 p0);//移动到指定位置
	void MoveTo(CDC* pDC, double x0, double y0);//重载函数
	void MoveTo(CDC* pDC, double x0, double y0, CRGB c0);//重载函数
	void LineTo(CDC* pDC, CP2 p1);//绘制直线，不含终点
	void LineTo(CDC* pDC, double x1, double y1);//重载函数
	void LineTo(CDC* pDC, double x1, double y1, CRGB c1);//重载函数
private:
	CP2 P0;//起点
	CP2 P1;//终点
};