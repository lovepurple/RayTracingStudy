#include "Checker_Texture.h"

Checker_Texture::Checker_Texture(Texture* oddTexture, Texture* evenTexture)
{
	this->m_oddTexture = oddTexture;
	this->m_evenTexture = evenTexture;
}

vec3 Checker_Texture::sample(float u, float v, const vec3& point) const
{
	//���̸��������㷨 sin�Ľ�����  point.y() * factor �������ڡ� 
	float sines = sin(point.x() * 10) * sin(point.y() * 10) * sin(point.z() * 10);

	if (sines < 0)
		return this->m_oddTexture->sample(u, v, point);
	else
		return this->m_evenTexture->sample(u, v, point);
}
