#include "stdafx.h"
#include "Test.h"
#include "Matrix44.h"

CMatrix44::CMatrix44(void)
{

}

CMatrix44::~CMatrix44(void)
{

}

void CMatrix44::LoadZero(void)
{
	for(int row = 0; row < 4; row++)
		for(int colum = 0; colum < 4; colum++)
		matrix[row][colum] = 0.0;
}

void CMatrix44::LoadIdentity(void)
{
	matrix[0][0] = 1.0; matrix[0][1] = 0.0; matrix[0][2] = 0.0; matrix[0][3] = 0.0;
	matrix[1][0] = 0.0; matrix[1][1] = 1.0; matrix[1][2] = 0.0; matrix[1][3] = 0.0;
	matrix[2][0] = 0.0; matrix[2][1] = 0.0; matrix[2][2] = 1.0; matrix[2][3] = 0.0;
	matrix[3][0] = 0.0; matrix[3][1] = 0.0; matrix[3][2] = 0.0; matrix[3][3] = 1.0;
}

CMatrix44 CMatrix44::Transpose()
{
	CMatrix44 result;
	for(int row = 0; row < 4; row++)
		for(int colum = 0; colum < 4; colum++)
			result.matrix[colum][row] = matrix[row][colum];
	return result;
}

CMatrix44 operator + (const CMatrix44 &m1, const CMatrix44 &m2)
{
	CMatrix44 result;
	for(int row = 0; row < 4; row++)
		for(int column = 0; column < 4; column++)
			result.matrix[row][column] = m1.matrix[row][column] + m2.matrix[row][column];
	return result;
}

CMatrix44 operator - (const CMatrix44 &m1, const CMatrix44 &m2)
{
	CMatrix44 result;
	for(int row = 0; row < 4; row++)
		for(int column = 0; column < 4; column++)
			result.matrix[row][column] = m1.matrix[row][column] - m2.matrix[row][column];
	return result;
}

CMatrix44 operator * (const CMatrix44 &m1, const double scalar)
{
	CMatrix44 result;
	for(int row = 0; row < 4; row++)
		for(int column = 0; column < 4; column++)
			result.matrix[row][column] = m1.matrix[row][column] * scalar;
	return result;
}

CMatrix44 operator * (const CMatrix44 &m1, const CMatrix44 &m2)
{
	CMatrix44 result;
	for(int row = 0; row < 4; row++)
		for(int column = 0; column < 4; column++)
			result.matrix[row][column] = m1.matrix[row][0] * m2.matrix[0][column] + m1.matrix[row][1] * m2.matrix[1][column] + m1.matrix[row][2] * m2.matrix[2][column] + m1.matrix[row][3] * m2.matrix[3][column];
	return result;
}

