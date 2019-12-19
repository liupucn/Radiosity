// Transform3.cpp: implementation of the CTransform3 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Test.h"
#include "Transform3.h"
#include "math.h"
#define PI 3.14159
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTransform3::CTransform3()
{

}

CTransform3::~CTransform3()
{

}

void CTransform3::SetMatrix(CP3* P, int ptNumber)
{
	ptOld = P;
	this->ptNumber = ptNumber;
}

void CTransform3::Translate(double tx, double ty, double tz)//ƽ�Ʊ任����
{
	T.LoadIdentity();
	T.matrix[3][0] = tx; 
	T.matrix[3][1] = ty; 
	T.matrix[3][2] = tz; 
	MultiplyMatrix();
}

void CTransform3::Scale(double sx, double sy, double sz)//�����任����
{
	T.LoadIdentity();
	T.matrix[0][0] = sx; 
	T.matrix[1][1] = sy; 
	T.matrix[2][2] = sz; 
	MultiplyMatrix();
}

void CTransform3::Scale(double sx, double sy, double sz, CP3 p)//����������ı����任����
{
	Translate(-p.x, -p.y, -p.z);
	Scale(sx, sy, sz);
	Translate(p.x, p.y, p.z);
}

void CTransform3::RotateX(double beta)//��X����ת�任����
{
	T.LoadIdentity();
	double rad = beta * PI / 180;
	T.matrix[1][1] =  cos(rad);T.matrix[1][2] = sin(rad);
	T.matrix[2][1] = -sin(rad);T.matrix[2][2] = cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateX(double beta, CP3 p)//�������������X����ת�任����
{
	Translate(-p.x, -p.y, -p.z);
	RotateX(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform3::RotateY(double beta)//��Y����ת�任����
{
	T.LoadIdentity();
	double rad = beta * PI / 180;
	T.matrix[0][0] = cos(rad);T.matrix[0][2] = -sin(rad);
	T.matrix[2][0] = sin(rad);T.matrix[2][2] =  cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateY(double beta, CP3 p)//�������������Y����ת�任����
{
	Translate(-p.x, -p.y, -p.z);
	RotateY(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform3::RotateZ(double beta)//��Z����ת�任����
{
	T.LoadIdentity();
	double rad = beta * PI / 180;
	T.matrix[0][0] =  cos(rad);T.matrix[0][1] = sin(rad);
	T.matrix[1][0] = -sin(rad);T.matrix[1][1] = cos(rad);
	MultiplyMatrix();
}

void CTransform3::RotateZ(double beta, CP3 p)//�������������Z����ת�任����
{
	Translate(-p.x, -p.y, -p.z);
	RotateZ(beta);
	Translate(p.x, p.y, p.z);
}

void CTransform3::ReflectX()//X�ᷴ��任����
{
	T.LoadIdentity();
	T.matrix[1][1] = -1;
	T.matrix[2][2] = -1;
	MultiplyMatrix();
}

void CTransform3::ReflectY()//Y�ᷴ��任����
{
	T.LoadIdentity();
	T.matrix[0][0] = -1;
	T.matrix[2][2] = -1;
	MultiplyMatrix();
}

void CTransform3::ReflectZ()//Z�ᷴ��任����
{
	T.LoadIdentity();
	T.matrix[0][0] = -1;
	T.matrix[1][1] = -1;
	MultiplyMatrix();
}

void CTransform3::ReflectXOY()//XOY�淴��任����
{
	T.LoadIdentity();
	T.matrix[2][2] = -1;
	MultiplyMatrix();
}

void CTransform3::ReflectYOZ()//YOZ�淴��任����
{
	T.LoadIdentity();
	T.matrix[0][0] = -1;
	MultiplyMatrix();
}

void CTransform3::ReflectXOZ()//ZOX�淴��任����
{
	T.LoadIdentity();
	T.matrix[1][1] = -1;
	MultiplyMatrix();
}

void CTransform3::ShearX(double d, double g)//X������б任����
{
	T.LoadIdentity();
	T.matrix[1][0] = d;
	T.matrix[2][0] = g;
	MultiplyMatrix();
}

void CTransform3::ShearY(double b, double h)//Y������б任����
{
	T.LoadIdentity();
	T.matrix[0][1] = b;
	T.matrix[2][1] = h;
	MultiplyMatrix();
}

void CTransform3::ShearZ(double c, double f)//Z������б任����
{
	T.LoadIdentity();
	T.matrix[0][2] = c;
	T.matrix[1][2] = f;
	MultiplyMatrix();
}

void CTransform3::MultiplyMatrix()//�������
{
	CP3* ptNew = new CP3[ptNumber];	
	for	(int i = 0;	i < ptNumber; i++)
	{
		ptNew[i] = ptOld[i];
	}
	for	(int j = 0;	j< ptNumber;	j++)
	{
		ptOld[j].x = ptNew[j].x * T.matrix[0][0] + ptNew[j].y * T.matrix[1][0] + ptNew[j].z * T.matrix[2][0] + ptNew[j].w * T.matrix[3][0];
		ptOld[j].y = ptNew[j].x * T.matrix[0][1] + ptNew[j].y * T.matrix[1][1] + ptNew[j].z * T.matrix[2][1] + ptNew[j].w * T.matrix[3][1];
		ptOld[j].z = ptNew[j].x * T.matrix[0][2] + ptNew[j].y * T.matrix[1][2] + ptNew[j].z * T.matrix[2][2] + ptNew[j].w * T.matrix[3][2];
		ptOld[j].w = ptNew[j].x * T.matrix[0][3] + ptNew[j].y * T.matrix[1][3] + ptNew[j].z * T.matrix[2][3] + ptNew[j].w * T.matrix[3][3];
	}
	delete []ptNew;
}

