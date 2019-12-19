
#pragma once

class CMatrix44 //4��4���� 
{
public:
	CMatrix44();
	virtual ~CMatrix44();
	void LoadZero();//�����
	void LoadIdentity();//��λ��
	CMatrix44 Transpose();
	friend CMatrix44 operator+ (const CMatrix44 &m1, const CMatrix44 &m2);//����+��
	friend CMatrix44 operator- (const CMatrix44 &m1, const CMatrix44 &m2);//����-��
	friend CMatrix44 operator* (const CMatrix44 &m1, const double scalar);//��������
	friend CMatrix44 operator* (const CMatrix44 &m1, const CMatrix44 &m2);//����*��
public:
	double matrix[4][4];
};
