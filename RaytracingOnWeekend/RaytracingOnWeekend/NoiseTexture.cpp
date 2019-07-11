#include "NoiseTexture.h"

vec3 NoiseTexture::sample(float u, float v, const vec3& point) const
{
	return vec3::ONE * PerlinNoise::getRandomNoise(point);
}
