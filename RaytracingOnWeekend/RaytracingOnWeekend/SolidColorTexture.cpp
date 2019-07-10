#include "SolidColorTexture.h"

SolidColorTexture::SolidColorTexture(vec3 solidColor)
{
	this->m_textureSolidColor = solidColor;
}

vec3 SolidColorTexture::sample(float u, float v, const vec3& point) const
{
	return  this->m_textureSolidColor;
}
