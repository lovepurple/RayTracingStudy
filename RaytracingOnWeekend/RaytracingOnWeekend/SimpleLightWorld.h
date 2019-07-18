#pragma once
#include "WorldBase.h"
#include "PerlinNoiseTexture.h"
#include "LambertianWithTextureMaterial.h"
#include "Sphere.h"
#include "DiffuseLight.h"
#include "SolidColorTexture.h"
#include "XY_Rect.h"
/*
	ºÚµ•æÿ–Œπ‚’’
*/
class SimpleLightWorld :
	public WorldBase
{
public:
	// Inherited via WorldBase
	virtual HitableList* getWorldHitable() override;
	virtual Camera getWorldCamera() override;
};

