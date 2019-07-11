#include "CubicInterpolateNoiseTexture.h"


vec3 CubicInterpolateNoiseTexture::sample(float u, float v, const vec3& point) const
{
	return  vec3::ONE * PerlinNoise::noiseInCubic(point * this->m_tiling);
}
