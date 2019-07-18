#include "TextureMappingWorld.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"		//使用第三方图像处理库
#endif

HitableList* TextureMappingWorld::getWorldHitable()
{
	if (this->m_worldObjectList == nullptr)
	{
		int width;
		int height;
		int channels;
		unsigned char* pixels = stbi_load("./Textures/earth.png", &width, &height, &channels, 0);

		Texture* customTexturePtr = new ImageTexture(pixels, width, height, E_CLAMP);
		Hitable** hitableList = new Hitable * [2];
		hitableList[this->m_worldObjectCount++] = new Sphere(vec3(0, 0, 0), 1.0f, new LambertianWithTextureMaterial(customTexturePtr));

		this->m_worldObjectList = new HitableList(hitableList, this->m_worldObjectCount);
	}

	return this->m_worldObjectList;
}

Camera TextureMappingWorld::getWorldCamera()
{
	if (this->m_worldCamera == nullptr)
		this->m_worldCamera = new  Camera(vec3(13, 3, 3), vec3::ZERO, vec3::UP, 20, SCREEN_PARAM, 0, 0, 0);

	return *(this->m_worldCamera);
}
