#include "Screen.h"

vec3 Screen::normalizedUVtoReal(const vec3& normalizedUV)
{
	return vec3(normalizedUV.x() * SCREEN_PARAM, normalizedUV.y(), normalizedUV.z());
}
