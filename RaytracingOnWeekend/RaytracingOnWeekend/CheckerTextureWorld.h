#pragma once
#include "WorldBase.h"
#include "Checker_Texture.h"
#include "SolidColorTexture.h"

class CheckerTextureWorld :
	public WorldBase
{
	// Inherited via WorldBase
	virtual HitableList* getWorldHitable() override;
	virtual Camera getWorldCamera() override;
};

