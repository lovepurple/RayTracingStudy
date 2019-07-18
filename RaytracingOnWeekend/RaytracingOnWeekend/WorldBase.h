#pragma once
/*
	³éÏóworldBase
*/
#include "HitableList.h"
#include "Camera.h"
#include "LambertianWithTextureMaterial.h"

class WorldBase
{
public:
	virtual HitableList* getWorldHitable() = 0;
	virtual Camera getWorldCamera() = 0;

protected:
	HitableList* m_worldObjectList;
	int m_worldObjectCount;
	Camera* m_worldCamera;
};

