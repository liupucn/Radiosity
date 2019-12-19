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

class CTransform3  //三维变换类
{
public:
	CTransform3();
	virtual ~CTransform3();
	void SetMatrix(CP3* P, int ptNumber);
	void Translate(double tx, double ty, double tz);//平移变换矩阵
	void Scale(double sx, double sy, double sz);//比例变换矩阵
	void Scale(double sx, double sy, double sz, CP3 p);//相对于任意点的比例变换矩阵
	void RotateX(double beta);//绕X轴旋转变换矩阵
	void RotateX(double beta, CP3 p);//相对于任意点的绕X轴旋转变换矩阵
	void RotateY(double beta);//绕Y轴旋转变换矩阵
	void RotateY(double beta, CP3 p);//相对于任意点的绕Y轴旋转变换矩阵
	void RotateZ(double beta);//绕Z轴旋转变换矩阵
	void RotateZ(double beta, CP3 p);//相对于任意点的绕Z轴旋转变换矩阵
	void ReflectX();//X轴反射变换矩阵
	void ReflectY();//Y轴反射变换矩阵
	void ReflectZ();//Z轴反射变换矩阵
	void ReflectXOY();//XOY面反射变换矩阵
	void ReflectYOZ();//YOZ面反射变换矩阵
	void ReflectXOZ();//XOZ面反射变换矩阵
	void ShearX(double d, double g);//X方向错切变换矩阵
	void ShearY(double b, double h);//Y方向错切变换矩阵
	void ShearZ(double c, double f);//Z方向错切变换矩阵
	void MultiplyMatrix();//矩阵相乘
public:
	CMatrix44 T;
	CP3*   ptOld;
	int    ptNumber;
};


#endif // !defined(AFX_TRANSFORM3_H__78DC7735_4C54_46CB_A94A_0EC209E20F47__INCLUDED_)
