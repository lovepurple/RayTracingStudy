#pragma once
#include "ray.h"
#include "Hitable.h"
/**
 * 材质类，对不同的材质进行不同的着色
 */
class Material
{
public:
	/**
	 * 光线经过材质的吸收及反射
	 */
	virtual bool scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const = 0;
};

