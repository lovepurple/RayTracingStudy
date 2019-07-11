#pragma once
#include "Texture.h"
#include "PerlinNoise.h"
/*
	基于三次线性插值的噪声图
*/
class CubicInterpolateNoiseTexture :
	public Texture
{
public:
	CubicInterpolateNoiseTexture() {}
	CubicInterpolateNoiseTexture(float tiling) :Texture::Texture(tiling) {}


	// Inherited via Texture
	virtual vec3 sample(float u, float v, const vec3& point) const override;

};

