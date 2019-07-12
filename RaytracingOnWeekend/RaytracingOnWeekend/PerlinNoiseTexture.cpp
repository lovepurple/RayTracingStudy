#include "PerlinNoiseTexture.h"

vec3 PerlinNoiseTexture::sample(float u, float v, const vec3& point) const
{
	//float perlinNoiseValue = PerlinNoise::perlinNoise(m_tiling * point);

	//noise(p) + 0.5 * noise(2p) + 0.25 * noise(4p) + 0.125 * noise(8p)
	//float perlinNoiseValue = PerlinNoise::perlinNoise(m_tiling * point) + 0.5 * PerlinNoise::perlinNoise(m_tiling * 2 * point) + 0.25 * PerlinNoise::perlinNoise(m_tiling * point * 4) +
	//	0.125 * PerlinNoise::perlinNoise(m_tiling * point * 8);

	//return vec3::ONE * PerlinNoise::Fbm(point * m_tiling, 8);
	return vec3::ONE * 0.5 * (1 + sin(m_tiling * point.z() + 20 * PerlinNoise::Fbm(point, 8)));
}
