#pragma once
#include "Texture.h"
#include "Utility.h"

enum TextureWrapMode
{
	E_CLAMP,
	E_REPEAT
};

/*
	@brief:自定义贴图
*/

class ImageTexture :
	public Texture
{
public:
	ImageTexture() {}
	ImageTexture(unsigned char* imagePixels, int width, int height, TextureWrapMode wrapMode);

	//tex2D的实现
	virtual vec3 sample(float u, float v, const vec3& point) const override;

private:
	//C++ Const的另一用法，Sample 是Const的 因此要用的类里的其实函数也得是const
	float getClampUV(float val) const;
	float getRepeatUV(float val) const;

	unsigned char* m_imagePixels;
	int m_imageWidth;
	int m_imageHeight;
	TextureWrapMode m_wrapMode;

};

