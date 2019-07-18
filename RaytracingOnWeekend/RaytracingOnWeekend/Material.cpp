#include "Material.h"

vec3 Material::emitted(float u, float v, const vec3& hitPoint) const
{
	return vec3::ZERO;		//默认不发光（黑色）
}
