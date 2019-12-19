
#pragma once

class CMatrix44 //4¡Á4¾ØÕó 
{
public:
	CMatrix44();
	virtual ~CMatrix44();
	void LoadZero();//Áã¾ØÕó
	void LoadIdentity();//µ¥Î»Õó
	CMatrix44 Transpose();
	friend CMatrix44 operator+ (const CMatrix44 &m1, const CMatrix44 &m2);//¾ØÕó¡°+¡±
	friend CMatrix44 operator- (const CMatrix44 &m1, const CMatrix44 &m2);//¾ØÕó¡°-¡±
	friend CMatrix44 operator* (const CMatrix44 &m1, const double scalar);//¾ØÕóÊı³Ë
	friend CMatrix44 operator* (const CMatrix44 &m1, const CMatrix44 &m2);//¾ØÕó¡°*¡±
public:
	double matrix[4][4];
};
