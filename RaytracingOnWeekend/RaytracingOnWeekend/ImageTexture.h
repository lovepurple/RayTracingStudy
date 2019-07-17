#pragma once
#include "Texture.h"
#include "Utility.h"

enum TextureWrapMode
{
	E_CLAMP,
	E_REPEAT
};

/*
	@brief:�Զ�����ͼ
*/

class ImageTexture :
	public Texture
{
public:
	ImageTexture() {}
	ImageTexture(unsigned char* imagePixels, int width, int height, TextureWrapMode wrapMode);

	//tex2D��ʵ��
	virtual vec3 sample(float u, float v, const vec3& point) const override;

private:
	//C++ Const����һ�÷���Sample ��Const�� ���Ҫ�õ��������ʵ����Ҳ����const
	float getClampUV(float val) const;
	float getRepeatUV(float val) const;

	unsigned char* m_imagePixels;
	int m_imageWidth;
	int m_imageHeight;
	TextureWrapMode m_wrapMode;

};

