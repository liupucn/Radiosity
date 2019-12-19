#pragma once

#include "RGB.h"

class CP2  
{
public:
	CP2(void);
	virtual ~CP2(void);
	CP2(double x, double y);
	CP2(double x, double y, CRGB c);
public:
	double x;
	double y;
	CRGB   c;
	double w;
};
