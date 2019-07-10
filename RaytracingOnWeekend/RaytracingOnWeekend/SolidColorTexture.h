#pragma once
/*
 *  ´¿É«ÌùÍ¼
 */
#include "Texture.h"
class SolidColorTexture :
	public Texture
{
public:
	SolidColorTexture(vec3 solidColor);
	// Inherited via Texture
	virtual vec3 sample(float u, float v, const vec3& point) const override;

private:
	vec3 m_textureSolidColor;
};

