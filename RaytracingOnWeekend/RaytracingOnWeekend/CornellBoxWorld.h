#pragma once
#include "WorldBase.h"
#include "SolidColorTexture.h"
#include "DiffuseLight.h"
#include "RectCollection.h"
/*
	Cornell World
*/
class CornellBoxWorld :
	public WorldBase
{
public:
	CornellBoxWorld() {}

	virtual HitableList* getWorldHitable() override;


	virtual Camera getWorldCamera() override;

};

