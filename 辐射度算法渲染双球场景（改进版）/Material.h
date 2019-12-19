#pragma once
#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetEnergy(CRGB);			//��ʼ����������ǿ
	void SetDiffuse(CRGB);			//��ʼ������ķ�����
	
	CRGB Emitter;				//��������ǿ
	CRGB Diffuse;				//������������
};