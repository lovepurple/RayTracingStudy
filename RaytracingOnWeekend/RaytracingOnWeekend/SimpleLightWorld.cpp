#include "SimpleLightWorld.h"


HitableList* SimpleLightWorld::getWorldHitable()
{
	if (this->m_worldObjectList == nullptr)
	{
		Hitable** worldHitableList = new Hitable * [100];

		this->m_worldObjectCount = 0;

		Texture* perlinTexture = new PerlinNoiseTexture(4.0f);
		Texture* lightColorTexture = new SolidColorTexture(vec3(4, 4, 4));

		LambertianWithTextureMaterial* perlinMat = new LambertianWithTextureMaterial(perlinTexture);
		DiffuseLight* lightMat = new DiffuseLight(lightColorTexture);

		worldHitableList[m_worldObjectCount++] = new Sphere(vec3(0, -100, 0), 1000, perlinMat);
		worldHitableList[m_worldObjectCount++] = new Sphere(vec3::ZERO, 2, perlinMat);
		worldHitableList[m_worldObjectCount++] = new Sphere(vec3(0, 5, 0), 2, lightMat);
		worldHitableList[m_worldObjectCount++] = new XY_Rect(2, 5, -2, 2, -2, lightMat);

		this->m_worldObjectList = new HitableList(worldHitableList, this->m_worldObjectCount);
	}

	return this->m_worldObjectList;
}

Camera SimpleLightWorld::getWorldCamera()
{
	if (this->m_worldCamera == nullptr)
		this->m_worldCamera = new Camera(vec3(13, 0, 15), vec3::ZERO, vec3::UP, 30, SCREEN_PARAM, 0, 0, 0);

	return *(this->m_worldCamera);
}
