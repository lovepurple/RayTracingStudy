#include "CheckerTextureWorld.h"

HitableList* CheckerTextureWorld::getWorldHitable()
{
	if (this->m_worldObjectList == nullptr)
	{
		Texture* checkerTexture = new Checker_Texture(new SolidColorTexture(vec3(0.2, 0.3, 0.1)), new SolidColorTexture(vec3(0.9, 0.9, 0.9)));

		Hitable** hitableList = new Hitable * [2];
		hitableList[this->m_worldObjectCount++] = new Sphere(vec3(0, -10, 0), 10, new LambertianWithTextureMaterial(checkerTexture));
		hitableList[this->m_worldObjectCount++] = new Sphere(vec3(0, 10, 0), 10, new LambertianWithTextureMaterial(checkerTexture));

		this->m_worldObjectList = new HitableList(hitableList, this->m_worldObjectCount);
	}

	return this->m_worldObjectList;
}

Camera CheckerTextureWorld::getWorldCamera()
{
	if (this->m_worldCamera == nullptr)
		this->m_worldCamera = new Camera(vec3(13, 2, 3), vec3::ZERO, vec3::UP, 20.0, SCREEN_PARAM, 2, 0, 0);

	return *(this->m_worldCamera);
}
