#pragma once

#include "P2.h"
#include "RGB.h"

class CLine  
{
public:
	CLine();
	virtual ~CLine();
	void MoveTo(CDC* pDC, CP2 p0);//�ƶ���ָ��λ��
	void MoveTo(CDC* pDC, double x0, double y0);//���غ���
	void MoveTo(CDC* pDC, double x0, double y0, CRGB c0);//���غ���
	void LineTo(CDC* pDC, CP2 p1);//����ֱ�ߣ������յ�
	void LineTo(CDC* pDC, double x1, double y1);//���غ���
	void LineTo(CDC* pDC, double x1, double y1, CRGB c1);//���غ���
private:
	CP2 P0;//���
	CP2 P1;//�յ�
};