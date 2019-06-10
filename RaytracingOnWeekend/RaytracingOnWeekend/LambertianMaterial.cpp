#include "LambertianMaterial.h"

bool LambertianMaterial::scatter(const ray& incidentRay, const HitInfo& hitInfo, vec3& attenuation, ray& outRay) const
{
	//todo:一直使用随机方向 不知道书中是否有其它用意
	vec3 outRayRandomDir = hitInfo.HitPointNormal + unit_vector(Utility::random_direction_in_unit_sphere());
	outRay = ray(hitInfo.HitPoint, unit_vector(outRayRandomDir));
	attenuation = albedoColor;
	return true;
}
