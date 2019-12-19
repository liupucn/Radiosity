// Transform3.h: interface for the CTransform3 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSFORM3_H__78DC7735_4C54_46CB_A94A_0EC209E20F47__INCLUDED_)
#define AFX_TRANSFORM3_H__78DC7735_4C54_46CB_A94A_0EC209E20F47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "P3.h"
#include "Matrix44.h"

class CTransform3  //��ά�任��
{
public:
	CTransform3();
	virtual ~CTransform3();
	void SetMatrix(CP3* P, int ptNumber);
	void Translate(double tx, double ty, double tz);//ƽ�Ʊ任����
	void Scale(double sx, double sy, double sz);//�����任����
	void Scale(double sx, double sy, double sz, CP3 p);//����������ı����任����
	void RotateX(double beta);//��X����ת�任����
	void RotateX(double beta, CP3 p);//�������������X����ת�任����
	void RotateY(double beta);//��Y����ת�任����
	void RotateY(double beta, CP3 p);//�������������Y����ת�任����
	void RotateZ(double beta);//��Z����ת�任����
	void RotateZ(double beta, CP3 p);//�������������Z����ת�任����
	void ReflectX();//X�ᷴ��任����
	void ReflectY();//Y�ᷴ��任����
	void ReflectZ();//Z�ᷴ��任����
	void ReflectXOY();//XOY�淴��任����
	void ReflectYOZ();//YOZ�淴��任����
	void ReflectXOZ();//XOZ�淴��任����
	void ShearX(double d, double g);//X������б任����
	void ShearY(double b, double h);//Y������б任����
	void ShearZ(double c, double f);//Z������б任����
	void MultiplyMatrix();//�������
public:
	CMatrix44 T;
	CP3*   ptOld;
	int    ptNumber;
};


#endif // !defined(AFX_TRANSFORM3_H__78DC7735_4C54_46CB_A94A_0EC209E20F47__INCLUDED_)
