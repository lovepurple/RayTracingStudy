#include "LambertianMaterial.h"

bool LambertianMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	//Lambertian 是向随机方向反射
	vec3 outRayRandomDir = hitInfo.HitPointNormal + unit_vector(Utility::random_direction_in_unit_sphere());
	outRay = ray(hitInfo.HitPoint, unit_vector(outRayRandomDir));
	attenuation = m_albedo;
	return true;
}
