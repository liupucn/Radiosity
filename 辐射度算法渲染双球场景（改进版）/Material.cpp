#include "StdAfx.h"
#include "Material.h"

CMaterial::CMaterial(void)
{
}

CMaterial::~CMaterial(void)
{

}

void CMaterial::SetEnergy(CRGB Emitter)
{
	this->Emitter = Emitter;
}

void CMaterial::SetDiffuse(CRGB Diffuse)
{
	this->Diffuse = Diffuse;
}
