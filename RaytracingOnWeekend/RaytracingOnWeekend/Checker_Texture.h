#pragma once
/*
 *	ÆåÅÌ¸ñ×ÓÎÆÀíÍ¼
 */
#include "Texture.h"
#include <math.h>
class Checker_Texture :
	public Texture
{
public:
	Checker_Texture() {};
	Checker_Texture(Texture* oddTexture, Texture* evenTexture);


private:
	Texture* m_oddTexture;
	Texture* m_evenTexture;

	// Inherited via Texture
	virtual vec3 sample(float u, float v, const vec3& point) const override;
};

