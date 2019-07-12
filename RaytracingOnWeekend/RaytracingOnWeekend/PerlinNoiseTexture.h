#pragma once
/**
 * ÕæÊµµÄPerlin NoiseÌùÍ¼
 */
#include "Texture.h"
#include "PerlinNoise.h"
class PerlinNoiseTexture :
	public Texture
{
public:
	PerlinNoiseTexture() {}
	PerlinNoiseTexture(float tiling) :Texture::Texture(tiling) {}

	// Inherited via Texture
	virtual vec3 sample(float u, float v, const vec3& point) const override;

};

