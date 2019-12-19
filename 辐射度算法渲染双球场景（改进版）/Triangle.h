#pragma once
#include "P2.h"//����ɫ�ĸ�������ά����
#include "Point2.h"//����ɫ��������ά����

class CTriangle//�����������
{
public:
	CTriangle(void);	
	virtual ~CTriangle(void);
	void SetPoint(CP2 P0, CP2 P1, CP2 P2);//���������㹹��������
	void GouraudShading(CDC* pDC);//���������
private:
	void EdgeFlag(CPoint2 PStart, CPoint2 PEnd, BOOL bFeature);//�߱��
	CRGB LinearInterp(double t, double tStart, double tEnd, CRGB IStart, CRGB IEnd);//��ǿ���Բ�ֵ
	void SortVertex(void);//�����ζ�������
private:
	CPoint2 point0, point1, point2;//�����ε���������
	CPoint2* pLeft; //��ȵ���������־
	CPoint2* pRight;//��ȵ��յ������־
	int nIndex;//ɨ��������
};

