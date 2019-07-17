#include "ImageTexture.h"

ImageTexture::ImageTexture(unsigned char* imagePixels, int width, int height, TextureWrapMode wrapMode)
{
	this->m_imagePixels = imagePixels;
	this->m_imageWidth = width;
	this->m_imageHeight = height;
	this->m_wrapMode = wrapMode;
}

vec3 ImageTexture::sample(float u, float v, const vec3& point) const
{
	vec3 uv = Utility::get_uv_by_sphere_point(point);
	switch (this->m_wrapMode)
	{
	case  E_CLAMP:
		u = getClampUV(uv.u());
		v = getClampUV(uv.v());
		break;;
	case  E_REPEAT:
		u = getRepeatUV(uv.v());
		v = getRepeatUV(uv.v());
	default:
		break;
	}

	int pixelIndexU = u * (this->m_imageWidth - 1);
	int pixelIndexV = (1 - v) * (this->m_imageHeight - 1);

	/*
		stb_image ÏñËØµÄË³Ðò
		[r03,g00,b00] [r13,g13,b13] [r23,g23,b23] [r33,g33,b33] [r43,g43,b43]
		[r02,g02,b02] [r12,g12,b12] [r22,g22,b22] [r32,g32,b32] [r42,g42,b42]
		[r01,g01,b01] [r11,g11,b11] [r21,g21,b21] [r31,g31,b31] [r41,g41,b41]
		[r00,g00,b00] [r10,g10,b10] [r20,g20,b20] [r30,g30,b30] [r40,g40,b40]

	*/

	float rChannel = int(this->m_imagePixels[3 * pixelIndexV * m_imageWidth + 3 * pixelIndexU]) / 255.0f;
	float gChannel = int(this->m_imagePixels[3 * pixelIndexV * m_imageWidth + 3 * pixelIndexU + 1]) / 255.0f;
	float bChannel = int(this->m_imagePixels[3 * pixelIndexV * m_imageWidth + 3 * pixelIndexU + 2]) / 255.0f;

	return vec3(rChannel, gChannel, bChannel);
}

float ImageTexture::getClampUV(float val) const
{
	float uv = val;
	if (uv < 0)
		uv = 0.0001f;
	else if (uv > 1.0)
		uv = 0.9999f;

	return uv;
}


float ImageTexture::getRepeatUV(float val) const
{
	float uv = val;
	if (uv < 0)
		uv = 1.0 - Utility::frac(val);
	else if (uv > 1.0)
		uv = Utility::frac(val);

	return val;
}
