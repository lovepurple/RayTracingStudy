#include "CornellBoxWorld.h"

HitableList* CornellBoxWorld::getWorldHitable()
{
	if (this->m_worldObjectList == nullptr)
	{
		Material* redMat = new LambertianWithTextureMaterial(new SolidColorTexture(vec3(0.65, 0.05, 0.05)));
		Material* whiteMat = new LambertianWithTextureMaterial(new SolidColorTexture(vec3(0.73, 0.73, 0.73)));
		Material* greenMat = new LambertianWithTextureMaterial(new SolidColorTexture(vec3(0.12, 0.45, 0.15)));

		Material* light = new DiffuseLight(new SolidColorTexture(vec3(18, 18, 18)));			//因为需要多次追踪，逐次递减，所以取数值大一些使结果更亮。

		Hitable** hitableObjectList = new Hitable * [100];

		hitableObjectList[this->m_worldObjectCount++] = new YZ_Rect(0, 555, 0, 555, 555, greenMat, vec3::LEFT);
		hitableObjectList[this->m_worldObjectCount++] = new YZ_Rect(0, 555, 0, 555, 0, redMat, vec3::RIGHT);
		hitableObjectList[this->m_worldObjectCount++] = new XZ_Rect(213, 343, 227, 332, 554, light, vec3::UP);
		hitableObjectList[this->m_worldObjectCount++] = new XZ_Rect(0, 555, 0, 555, 555, whiteMat, vec3::DOWN);
		hitableObjectList[this->m_worldObjectCount++] = new XZ_Rect(0, 555, 0, 555, 0, whiteMat, vec3::UP);
		hitableObjectList[this->m_worldObjectCount++] = new XY_Rect(0, 555, 0, 555, 555, whiteMat, vec3::BACK);


		this->m_worldObjectList = new HitableList(hitableObjectList, this->m_worldObjectCount);
	}

	return this->m_worldObjectList;
}

Camera CornellBoxWorld::getWorldCamera()
{
	if (this->m_worldCamera == nullptr)
		this->m_worldCamera = new Camera(vec3(278, 278, -800), vec3(278, 278, 0), vec3::UP, 40, SCREEN_PARAM, 0, 0, 0);

	return *(this->m_worldCamera);
}
