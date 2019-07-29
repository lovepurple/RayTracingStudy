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

	//´¿°×Í¼Æ¬
	static SolidColorTexture WHITE_TEXTURE;

	//´¿ºÚÍ¼Æ¬
	static SolidColorTexture BLACK_TEXTURE;

private:
	vec3 m_textureSolidColor;
};


