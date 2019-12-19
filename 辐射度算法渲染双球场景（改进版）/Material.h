#pragma once
#include "RGB.h"

class CMaterial
{
public:
	CMaterial(void);
	virtual~CMaterial(void);
	void SetEnergy(CRGB);			//初始化自身辐射光强
	void SetDiffuse(CRGB);			//初始化自身的反射率
	
	CRGB Emitter;				//自身辐射光强
	CRGB Diffuse;				//物体漫反射率
};