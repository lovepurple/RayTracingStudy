#pragma once
/*
 *	������ͼ
 */
#include "Texture.h"
#include "PerlinNoise.h"

class NoiseTexture :
	public Texture
{
public:
	NoiseTexture(){}


	// Inherited via Texture
	virtual vec3 sample(float u, float v, const vec3& point) const override;

};
