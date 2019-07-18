#pragma once
#include "WorldBase.h"
#include "PerlinNoiseTexture.h"
#include "Sphere.h"

class PerlinNoiseWorld :
	public WorldBase
{

public:
	virtual HitableList* getWorldHitable() override;


	virtual Camera getWorldCamera() override;

};
