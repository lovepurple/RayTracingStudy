#pragma once
#include "WorldBase.h"
#include "ImageTexture.h"

/*
	球面坐标及UV映射的测试场景
*/

class TextureMappingWorld :
	public WorldBase
{
	// Inherited via WorldBase
	virtual HitableList* getWorldHitable() override;
	virtual Camera getWorldCamera() override;
};

