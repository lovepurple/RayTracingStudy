#pragma once
/*
 *	Texture »ùÀà
 */

#include "Vec3.h"
class Texture
{
public:
	Texture() {}
	Texture(float tiling);
	virtual vec3 sample(float u, float v, const vec3& point) const = 0;

protected:
	float m_tiling = 1.0;
};

