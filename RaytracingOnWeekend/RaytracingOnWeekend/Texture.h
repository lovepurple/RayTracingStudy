#pragma once
/*
 *	Texture »ùÀà
 */

#include "Vec3.h"
class Texture
{
public:
	virtual vec3 sample(float u, float v, const vec3& point) const = 0;
};

