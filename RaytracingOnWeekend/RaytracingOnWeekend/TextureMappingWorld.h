#pragma once
#include "WorldBase.h"
#include "ImageTexture.h"

/*
	�������꼰UVӳ��Ĳ��Գ���
*/

class TextureMappingWorld :
	public WorldBase
{
	// Inherited via WorldBase
	virtual HitableList* getWorldHitable() override;
	virtual Camera getWorldCamera() override;
};

