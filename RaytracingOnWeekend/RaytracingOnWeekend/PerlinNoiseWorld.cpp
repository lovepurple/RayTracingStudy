#include "PerlinNoiseWorld.h"

HitableList* PerlinNoiseWorld::getWorldHitable()
{
	if (this->m_worldObjectList == nullptr)
	{
		Texture* noiseTexturePtr = new PerlinNoiseTexture(5.0);
		Hitable** hitableList = new Hitable * [2];
		hitableList[this->m_worldObjectCount++] = new Sphere(vec3(0, -1000, 0), 1000, new LambertianWithTextureMaterial(noiseTexturePtr));
		hitableList[this->m_worldObjectCount++] = new Sphere(vec3(0, 2, 0), 2, new LambertianWithTextureMaterial(noiseTexturePtr));

		return this->m_worldObjectList = new HitableList(hitableList, this->m_worldObjectCount);
	}

	return this->m_worldObjectList;
}

Camera PerlinNoiseWorld::getWorldCamera()
{
	if (this->m_worldCamera == NULL)
		this->m_worldCamera = new Camera(vec3(13, 2, 3), vec3::ZERO, vec3::UP, 20, SCREEN_PARAM, 0, 0, 0);

	return *(this->m_worldCamera);
}
