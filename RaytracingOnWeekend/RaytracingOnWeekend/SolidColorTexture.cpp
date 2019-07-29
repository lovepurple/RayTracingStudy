#include "SolidColorTexture.h"

SolidColorTexture::SolidColorTexture(vec3 solidColor)
{
	this->m_textureSolidColor = solidColor;
}

vec3 SolidColorTexture::sample(float u, float v, const vec3& point) const
{
	return  this->m_textureSolidColor;
}

SolidColorTexture SolidColorTexture::WHITE_TEXTURE = SolidColorTexture(vec3(255));

SolidColorTexture SolidColorTexture::BLACK_TEXTURE = SolidColorTexture(vec3::ZERO);