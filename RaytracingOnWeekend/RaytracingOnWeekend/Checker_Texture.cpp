#include "Checker_Texture.h"

Checker_Texture::Checker_Texture(Texture* oddTexture, Texture* evenTexture)
{
	this->m_oddTexture = oddTexture;
	this->m_evenTexture = evenTexture;
}

vec3 Checker_Texture::sample(float u, float v, const vec3& point) const
{
	//棋盘格交替生成算法 sin的交替性。
	float sines = sin(point.x()) * sin(point.y()) * sin(point.z());

	if (sines < 0)
		return this->m_oddTexture->sample(u, v, point);
	else
		return this->m_evenTexture->sample(u, v, point);
}
